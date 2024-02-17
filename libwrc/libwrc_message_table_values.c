/*
 * Message table values functions
 *
 * Copyright (C) 2011-2024, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <common.h>
#include <memory.h>
#include <types.h>

#include "libwrc_data_descriptor.h"
#include "libwrc_definitions.h"
#include "libwrc_io_handle.h"
#include "libwrc_libbfio.h"
#include "libwrc_libcerror.h"
#include "libwrc_libcnotify.h"
#include "libwrc_libfvalue.h"
#include "libwrc_language_entry.h"
#include "libwrc_message_table_values.h"

#include "wrc_message_table_resource.h"

/* Reads message table values
 * Returns 1 if successful or -1 on error
 */
int libwrc_message_table_values_read(
     libwrc_language_entry_t *language_entry,
     libwrc_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     libwrc_data_descriptor_t *data_descriptor,
     libcerror_error_t **error )
{
	libfvalue_value_t *message_table_value       = NULL;
	uint8_t *resource_data                       = NULL;
	uint8_t *message_table_resource_data         = NULL;
	uint8_t *message_table_string_resource_data  = NULL;
	static char *function                        = "libwrc_message_table_values_read";
	off64_t file_offset                          = 0;
	size_t message_entry_descriptors_size        = 0;
	size_t resource_data_size                    = 0;
	ssize_t read_count                           = 0;
	uint32_t first_message_identifier            = 0;
	uint32_t last_message_identifier             = 0;
	uint16_t message_entry_descriptor_index      = 0;
	uint16_t message_table_string_flags          = 0;
	uint32_t message_table_string_offset         = 0;
	uint16_t message_table_string_size           = 0;
	uint16_t number_of_message_entry_descriptors = 0;
	uint16_t string_size                         = 0;
	int result                                   = 0;
	int value_encoding                           = 0;
	int value_index                              = 0;

	if( language_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid language entry.",
		 function );

		return( -1 );
	}
	if( io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid IO handle.",
		 function );

		return( -1 );
	}
	if( data_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data descriptor.",
		 function );

		return( -1 );
	}
	resource_data_size = (size_t) data_descriptor->size;

	if( ( resource_data_size == 0 )
	 || ( resource_data_size > (size_t) MEMORY_MAXIMUM_ALLOCATION_SIZE ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid resource data size value out of bounds.",
		 function );

		goto on_error;
	}
	resource_data = (uint8_t *) memory_allocate(
	                             sizeof( uint8_t ) * resource_data_size );

	if( resource_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create resource data.",
		 function );

		goto on_error;
	}
	file_offset = data_descriptor->virtual_address - io_handle->virtual_address;

	read_count = libbfio_handle_read_buffer_at_offset(
	              file_io_handle,
	              resource_data,
	              resource_data_size,
	              file_offset,
	              error );

	if( read_count != (ssize_t) resource_data_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read resource data at offset: %" PRIi64 " (0x%08" PRIx64 ").",
		 function,
		 file_offset,
		 file_offset );

		goto on_error;
	}
	message_table_resource_data = resource_data;

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: resource data:\n",
		 function );
		libcnotify_print_data(
		 message_table_resource_data,
		 resource_data_size,
		 0 );
	}
#endif
	byte_stream_copy_to_uint32_little_endian(
	 message_table_resource_data,
	 number_of_message_entry_descriptors );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: number of message entry descriptors\t: %" PRIu32 "\n",
		 function,
		 number_of_message_entry_descriptors );

		libcnotify_printf(
		 "\n" );
	}
#endif
	message_table_resource_data += sizeof( uint32_t );
	resource_data_size          -= sizeof( uint32_t );

	message_entry_descriptors_size = number_of_message_entry_descriptors
	                               * sizeof( wrc_message_table_entry_descriptor_t );

	if( message_entry_descriptors_size > resource_data_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: number of message entry descriptors value out of bound.",
		 function );

		goto on_error;
	}
	for( message_entry_descriptor_index = 0;
	     message_entry_descriptor_index < number_of_message_entry_descriptors;
	     message_entry_descriptor_index++ )
	{
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: message entry descriptor: %03d\n",
			 function,
			 message_entry_descriptor_index );
			libcnotify_print_data(
			 message_table_resource_data,
			 sizeof( wrc_message_table_entry_descriptor_t ),
			 0 );
		}
#endif
		byte_stream_copy_to_uint32_little_endian(
		 ( (wrc_message_table_entry_descriptor_t *) message_table_resource_data )->first_identifier,
		 first_message_identifier );

		byte_stream_copy_to_uint32_little_endian(
		 ( (wrc_message_table_entry_descriptor_t *) message_table_resource_data )->last_identifier,
		 last_message_identifier );

		byte_stream_copy_to_uint32_little_endian(
		 ( (wrc_message_table_entry_descriptor_t *) message_table_resource_data )->offset,
		 message_table_string_offset );

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: first message identifier\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 first_message_identifier );

			libcnotify_printf(
			 "%s: last message identifier\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 last_message_identifier );

			libcnotify_printf(
			 "%s: first message string offset\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 message_table_string_offset );

			libcnotify_printf(
			 "\n" );
		}
#endif
		message_table_resource_data += sizeof( wrc_message_table_entry_descriptor_t );
		resource_data_size          -= sizeof( wrc_message_table_entry_descriptor_t );

		if( first_message_identifier > last_message_identifier )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: first message identifier exceeds last.",
			 function );

			goto on_error;
		}
		while( first_message_identifier <= last_message_identifier )
		{
			if( message_table_string_offset >= (size_t) data_descriptor->size )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
				 "%s: number of message string offset value out of bound.",
				 function );

				goto on_error;
			}
			message_table_string_resource_data = &( resource_data[ message_table_string_offset ] );

#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "%s: message string: 0x%08" PRIx32 "\n",
				 function,
				 first_message_identifier );
				libcnotify_print_data(
				 message_table_string_resource_data,
				 sizeof( wrc_message_table_string_t ),
				 0 );
			}
#endif
			byte_stream_copy_to_uint16_little_endian(
			 ( (wrc_message_table_string_t *) message_table_string_resource_data )->size,
			 message_table_string_size );

			byte_stream_copy_to_uint16_little_endian(
			 ( (wrc_message_table_string_t *) message_table_string_resource_data )->flags,
			 message_table_string_flags );

#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "%s: message string: 0x%08" PRIx32 " size\t\t: %" PRIu16 "\n",
				 function,
				 first_message_identifier,
				 message_table_string_size );

				libcnotify_printf(
				 "%s: message string: 0x%08" PRIx32 " flags\t\t: 0x%04" PRIx16 "\n",
				 function,
				 first_message_identifier,
				 message_table_string_flags );
			}
#endif
			if( message_table_string_size > sizeof( wrc_message_table_string_t ) )
			{
				message_table_string_resource_data += sizeof( wrc_message_table_string_t );
				message_table_string_offset        += sizeof( wrc_message_table_string_t );
				message_table_string_size          -= sizeof( wrc_message_table_string_t );

				if( ( message_table_string_flags & 0x0001 ) == 0 )
				{
					result = libfvalue_value_type_initialize(
					          &( message_table_value ),
					          LIBFVALUE_VALUE_TYPE_STRING_BYTE_STREAM,
					          error );
				}
				else
				{
					result = libfvalue_value_type_initialize(
					          &( message_table_value ),
					          LIBFVALUE_VALUE_TYPE_STRING_UTF16,
					          error );
				}
				if( result != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
					 "%s: unable to create string value.",
					 function );

					goto on_error;
				}
				if( libfvalue_value_set_identifier(
				     message_table_value,
				     (uint8_t *) &first_message_identifier,
				     4,
				     LIBFVALUE_VALUE_IDENTIFIER_FLAG_MANAGED,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
					 "%s: unable to set identifier of message table value.",
					 function );

					goto on_error;
				}
				if( ( message_table_string_flags & 0x0001 ) == 0 )
				{
					value_encoding = io_handle->ascii_codepage;
				}
				else
				{
					value_encoding = LIBFVALUE_CODEPAGE_UTF16_LITTLE_ENDIAN;
				}
/* TODO data bounds check */
#if defined( HAVE_DEBUG_OUTPUT )
				if( libcnotify_verbose != 0 )
				{
					libcnotify_printf(
					 "%s: message string: 0x%08" PRIx32 " data:\n",
					 function,
					 first_message_identifier );
					libcnotify_print_data(
					 message_table_string_resource_data,
					 (size_t) message_table_string_size,
					 0 );
				}
#endif
				/* Strip off trailing 0-byte values
				 */
				string_size = message_table_string_size;

				if( ( message_table_string_flags & 0x0001 ) == 0 )
				{
					while( string_size > 0 )
					{
						string_size -= 1;

						if( message_table_string_resource_data[ string_size ] != 0 )
						{
							break;
						}
					}
					string_size += 1;
				}
				else
				{
					while( string_size > 1 )
					{
						string_size -= 2;

						if( ( message_table_string_resource_data[ string_size ] != 0 )
						 || ( message_table_string_resource_data[ string_size + 1 ] != 0 ) )
						{
							break;
						}
					}
					string_size += 2;
				}
				if( libfvalue_value_set_data(
				     message_table_value,
				     message_table_string_resource_data,
				     (size_t) string_size,
				     value_encoding,
				     LIBFVALUE_VALUE_DATA_FLAG_MANAGED,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
					 "%s: unable to set data of string value.",
					 function );

					goto on_error;
				}
#if defined( HAVE_DEBUG_OUTPUT )
				if( libcnotify_verbose != 0 )
				{
					libcnotify_printf(
					 "%s: message string: 0x%08" PRIx32 " value\t\t: ",
					 function,
					 first_message_identifier );

					if( libfvalue_value_print(
					     message_table_value,
					     0,
					     0,
					     error ) != 1 )
					{
						libcerror_error_set(
						 error,
						 LIBCERROR_ERROR_DOMAIN_RUNTIME,
						 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
						 "%s: unable to print string value.",
						 function );

						goto on_error;
					}
					libcnotify_printf(
					 "\n" );
				}
#endif
			}
#if defined( HAVE_DEBUG_OUTPUT )
			else if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "\n" );
			}
#endif
			message_table_string_resource_data += message_table_string_size;
			message_table_string_offset        += message_table_string_size;

			if( libwrc_language_entry_append_value(
			     language_entry,
			     &value_index,
			     (intptr_t *) message_table_value,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
				 "%s: unable to append message table values.",
				 function );

				goto on_error;
			}
			message_table_value = NULL;

			first_message_identifier++;
		}
	}
	memory_free(
	 resource_data );

	return( 1 );

on_error:
	if( message_table_value != NULL )
	{
		libfvalue_value_free(
		 &message_table_value,
		 NULL );
	}
	if( resource_data != NULL )
	{
		memory_free(
		 resource_data );
	}
	return( -1 );
}

