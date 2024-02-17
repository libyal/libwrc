/*
 * String values functions
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
#include "libwrc_language_entry.h"
#include "libwrc_libbfio.h"
#include "libwrc_libcerror.h"
#include "libwrc_libcnotify.h"
#include "libwrc_libfvalue.h"
#include "libwrc_string_values.h"

/* Reads string values
 * Returns 1 if successful or -1 on error
 */
int libwrc_string_values_read(
     libwrc_language_entry_t *language_entry,
     libwrc_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     uint32_t identifier,
     libwrc_data_descriptor_t *data_descriptor,
     libcerror_error_t **error )
{
	libfvalue_value_t *string_value = NULL;
	uint8_t *resource_data          = NULL;
	uint8_t *string_resource_data   = NULL;
	static char *function           = "libwrc_string_values_read";
	off64_t file_offset             = 0;
	size_t resource_data_size       = 0;
	ssize_t read_count              = 0;
	uint32_t string_identifier      = 0;
	uint32_t string_index           = 0;
	uint32_t string_size            = 0;
	int value_index                 = 0;

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
	string_resource_data = resource_data;

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: resource data:\n",
		 function );
		libcnotify_print_data(
		 string_resource_data,
		 resource_data_size,
		 0 );
	}
#endif
	while( resource_data_size > 0 )
	{
		byte_stream_copy_to_uint16_little_endian(
		 string_resource_data,
		 string_size );

		string_resource_data += sizeof( uint16_t );
		resource_data_size   -= sizeof( uint16_t );

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: string: %02" PRIu32 " length\t\t\t\t: %" PRIu32 "\n",
			 function,
			 string_index,
			 string_size );
		}
#endif
		if( string_size > 0 )
		{
			string_identifier = ( identifier << 4 ) | string_index;

			string_size *= 2;

			if( string_size > resource_data_size )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
				 "%s: string size value out of bound.",
				 function );

				goto on_error;
			}
			if( libfvalue_value_type_initialize(
			     &string_value,
			     LIBFVALUE_VALUE_TYPE_STRING_UTF16,
			     error ) != 1 )
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
			     string_value,
			     (uint8_t *) &string_identifier,
			     4,
			     LIBFVALUE_VALUE_IDENTIFIER_FLAG_MANAGED,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
				 "%s: unable to set identifier of string value.",
				 function );

				goto on_error;
			}
#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "%s: string: %02" PRIu32 " data:\n",
				 function,
				 string_index );
				libcnotify_print_data(
				 string_resource_data,
				 (size_t) string_size,
				 0 );
			}
#endif
			if( libfvalue_value_set_data(
			     string_value,
			     string_resource_data,
			     (size_t) string_size,
			     LIBFVALUE_CODEPAGE_UTF16_LITTLE_ENDIAN,
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
				 "%s: string: %02" PRIu32 " value\t\t\t\t: ",
				 function,
				 string_index );

				if( libfvalue_value_print(
				     string_value,
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
			string_resource_data += (size_t) string_size;
			resource_data_size   -= (size_t) string_size;

			if( libwrc_language_entry_append_value(
			     language_entry,
			     &value_index,
			     (intptr_t *) string_value,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
				 "%s: unable to append string value.",
				 function );

				goto on_error;
			}
			string_value = NULL;
		}
#if defined( HAVE_DEBUG_OUTPUT )
		else if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "\n" );
		}
#endif
		string_index++;
	}
	memory_free(
	 resource_data );

/* TODO validate if number of strings is 16 ? */

	return( 1 );

on_error:
	if( string_value != NULL )
	{
		libfvalue_value_free(
		 &string_value,
		 NULL );
	}
	if( resource_data != NULL )
	{
		memory_free(
		 resource_data );
	}
	return( -1 );
}

