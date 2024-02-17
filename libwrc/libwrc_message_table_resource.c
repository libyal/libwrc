/*
 * Message table (MESSAGETABLE) resource functions
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
#include <byte_stream.h>
#include <memory.h>
#include <types.h>

#include "libwrc_definitions.h"
#include "libwrc_libcdata.h"
#include "libwrc_libcerror.h"
#include "libwrc_libcnotify.h"
#include "libwrc_libuna.h"
#include "libwrc_message_table_resource.h"
#include "libwrc_table_entry.h"

#include "wrc_message_table_resource.h"

/* Creates a message table resource
 * Make sure the value message_table_resource is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libwrc_message_table_resource_initialize(
     libwrc_message_table_resource_t **message_table_resource,
     libcerror_error_t **error )
{
	libwrc_internal_message_table_resource_t *internal_message_table_resource = NULL;
	static char *function                                                     = "libwrc_message_table_resource_initialize";

	if( message_table_resource == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid message table resource.",
		 function );

		return( -1 );
	}
	if( *message_table_resource != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid message table resource value already set.",
		 function );

		return( -1 );
	}
	internal_message_table_resource = memory_allocate_structure(
	                                   libwrc_internal_message_table_resource_t );

	if( internal_message_table_resource == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create message table resource.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     internal_message_table_resource,
	     0,
	     sizeof( libwrc_internal_message_table_resource_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear message table resource.",
		 function );

		memory_free(
		 internal_message_table_resource );

		return( -1 );
	}
	if( libcdata_array_initialize(
	     &( internal_message_table_resource->entries_array ),
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create entries array.",
		 function );

		goto on_error;
	}
	*message_table_resource = (libwrc_message_table_resource_t *) internal_message_table_resource;

	return( 1 );

on_error:
	if( internal_message_table_resource != NULL )
	{
		memory_free(
		 internal_message_table_resource );
	}
	return( -1 );
}

/* Frees a message table resource
 * Returns 1 if successful or -1 on error
 */
int libwrc_message_table_resource_free(
     libwrc_message_table_resource_t **message_table_resource,
     libcerror_error_t **error )
{
	libwrc_internal_message_table_resource_t *internal_message_table_resource = NULL;
	static char *function                                                     = "libwrc_message_table_resource_free";
	int result                                                                = 1;

	if( message_table_resource == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid message table resource.",
		 function );

		return( -1 );
	}
	if( *message_table_resource != NULL )
	{
		internal_message_table_resource = (libwrc_internal_message_table_resource_t *) *message_table_resource;
		*message_table_resource         = NULL;

		if( libcdata_array_free(
		     &( internal_message_table_resource->entries_array ),
		     (int (*)(intptr_t **, libcerror_error_t **)) &libwrc_table_entry_free,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free entries array.",
			 function );

			result = -1;
		}
		memory_free(
		 internal_message_table_resource );
	}
	return( result );
}

/* Reads the message table resource
 * Returns 1 if successful or -1 on error
 */
int libwrc_message_table_resource_read(
     libwrc_message_table_resource_t *message_table_resource,
     const uint8_t *data,
     size_t data_size,
     int ascii_codepage,
     libcerror_error_t **error )
{
	libwrc_internal_message_table_resource_t *internal_message_table_resource = NULL;
	libwrc_table_entry_t *table_entry                                         = NULL;
	static char *function                                                     = "libwrc_message_table_resource_read";
	size_t data_offset                                                        = 0;
	uint32_t first_message_identifier                                         = 0;
	uint32_t last_message_identifier                                          = 0;
	uint32_t message_string_offset                                            = 0;
	uint16_t message_entry_descriptor_index                                   = 0;
	uint16_t message_string_flags                                             = 0;
	uint16_t message_string_size                                              = 0;
	uint16_t number_of_message_entry_descriptors                              = 0;
	uint16_t string_size                                                      = 0;
	int entry_index                                                           = 0;
	int value_encoding                                                        = 0;

	if( message_table_resource == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid message table resource.",
		 function );

		return( -1 );
	}
	internal_message_table_resource = (libwrc_internal_message_table_resource_t *) message_table_resource;

	if( data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data.",
		 function );

		return( -1 );
	}
	if( ( data_size < 4 )
	 || ( data_size > (size_t) SSIZE_MAX ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid data size value out of bounds.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: data:\n",
		 function );
		libcnotify_print_data(
		 data,
		 data_size,
		 0 );
	}
#endif
	byte_stream_copy_to_uint32_little_endian(
	 data,
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
	data_offset += 4;

	if( number_of_message_entry_descriptors > ( ( data_size - data_offset ) / sizeof( wrc_message_table_entry_descriptor_t ) ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid number of message entry descriptors value out of bounds.",
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
			 &( data[ data_offset ] ),
			 sizeof( wrc_message_table_entry_descriptor_t ),
			 0 );
		}
#endif
		byte_stream_copy_to_uint32_little_endian(
		 ( (wrc_message_table_entry_descriptor_t *) &( data[ data_offset ] ) )->first_identifier,
		 first_message_identifier );

		byte_stream_copy_to_uint32_little_endian(
		 ( (wrc_message_table_entry_descriptor_t *) &( data[ data_offset ] ) )->last_identifier,
		 last_message_identifier );

		byte_stream_copy_to_uint32_little_endian(
		 ( (wrc_message_table_entry_descriptor_t *) &( data[ data_offset ] ) )->offset,
		 message_string_offset );

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: first message identifier\t\t: 0x%08" PRIx32 "\n",
			 function,
			 first_message_identifier );

			libcnotify_printf(
			 "%s: last message identifier\t\t: 0x%08" PRIx32 "\n",
			 function,
			 last_message_identifier );

			libcnotify_printf(
			 "%s: first message string offset\t\t: 0x%08" PRIx32 "\n",
			 function,
			 message_string_offset );

			libcnotify_printf(
			 "\n" );
		}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

		data_offset += sizeof( wrc_message_table_entry_descriptor_t );

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
			if( ( message_string_offset < data_offset )
			 || ( message_string_offset >= ( data_size - sizeof( wrc_message_table_string_t ) ) ) )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
				 "%s: invalid message table string offset value out of bounds.",
				 function );

				goto on_error;
			}
#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "%s: message string: 0x%08" PRIx32 "\n",
				 function,
				 first_message_identifier );
				libcnotify_print_data(
				 &( data[ message_string_offset ] ),
				 sizeof( wrc_message_table_string_t ),
				 0 );
			}
#endif
			byte_stream_copy_to_uint16_little_endian(
			 ( (wrc_message_table_string_t *) &( data[ message_string_offset ] ) )->size,
			 message_string_size );

			byte_stream_copy_to_uint16_little_endian(
			 ( (wrc_message_table_string_t *) &( data[ message_string_offset ] ) )->flags,
			 message_string_flags );

#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "%s: message string: 0x%08" PRIx32 " size\t: %" PRIu16 "\n",
				 function,
				 first_message_identifier,
				 message_string_size );

				libcnotify_printf(
				 "%s: message string: 0x%08" PRIx32 " flags\t: 0x%04" PRIx16 "\n",
				 function,
				 first_message_identifier,
				 message_string_flags );
			}
#endif
			if( ( message_string_size < sizeof( wrc_message_table_string_t ) )
			 || ( message_string_size > ( data_size - message_string_offset ) ) )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
				 "%s: invalid message string size value out of bounds.",
				 function );

				goto on_error;
			}
			message_string_offset += sizeof( wrc_message_table_string_t );
			message_string_size   -= sizeof( wrc_message_table_string_t );

			if( message_string_size > 0 )
			{
#if defined( HAVE_DEBUG_OUTPUT )
				if( libcnotify_verbose != 0 )
				{
					libcnotify_printf(
					 "%s: message string: 0x%08" PRIx32 " data:\n",
					 function,
					 first_message_identifier );
					libcnotify_print_data(
					 &( data[ message_string_offset ] ),
					 (size_t) message_string_size,
					 0 );
				}
#endif
				/* Strip off trailing 0-byte values
				 */
				string_size = message_string_size;

				if( ( message_string_flags & 0x0001 ) == 0 )
				{
					while( string_size > 0 )
					{
						string_size -= 1;

						if( data[ message_string_offset + string_size ] != 0 )
						{
							break;
						}
					}
					string_size += 1;
				}
				else
				{
					if( ( message_string_size % 2 ) != 0 )
					{
						libcerror_error_set(
						 error,
						 LIBCERROR_ERROR_DOMAIN_RUNTIME,
						 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
						 "%s: invalid message string: 0x%08" PRIx32 " size value not a multitude of 2.",
						 function,
						 first_message_identifier );

						goto on_error;
					}
					while( string_size > 1 )
					{
						string_size -= 2;

						if( ( data[ message_string_offset + string_size ] != 0 )
						 || ( data[ message_string_offset + string_size + 1 ] != 0 ) )
						{
							break;
						}
					}
					string_size += 2;
				}
				if( libwrc_table_entry_initialize(
				     &table_entry,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
					 "%s: unable to create table entry.",
					 function );

					goto on_error;
				}
				if( ( message_string_flags & 0x0001 ) == 0 )
				{
					value_encoding = ascii_codepage;
				}
				else
				{
					value_encoding = LIBUNA_CODEPAGE_UTF16_LITTLE_ENDIAN;
				}
				if( libwrc_table_entry_set_string(
				     table_entry,
				     &( data[ message_string_offset ] ),
				     (size_t) string_size,
				     value_encoding,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
					 "%s: unable to set data of table entry.",
					 function );

					goto on_error;
				}
				table_entry->identifier = first_message_identifier;

				if( libcdata_array_append_entry(
				     internal_message_table_resource->entries_array,
				     &entry_index,
				     (intptr_t *) table_entry,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
					 "%s: unable to append table entry to array.",
					 function );

					goto on_error;
				}
				table_entry = NULL;

				message_string_offset += message_string_size;
			}
#if defined( HAVE_DEBUG_OUTPUT )
			else if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "\n" );
			}
#endif
			first_message_identifier++;
		}
	}
	return( 1 );

on_error:
	if( table_entry != NULL )
	{
		libwrc_table_entry_free(
		 &table_entry,
		 NULL );
	}
	return( -1 );
}

/* Retrieves the number of messages
 * Returns 1 if successful or -1 on error
 */
int libwrc_message_table_resource_get_number_of_messages(
     libwrc_message_table_resource_t *message_table_resource,
     int *number_of_messages,
     libcerror_error_t **error )
{
	libwrc_internal_message_table_resource_t *internal_message_table_resource = NULL;
	static char *function                                                     = "libwrc_message_table_resource_get_number_of_messages";

	if( message_table_resource == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid message table resource.",
		 function );

		return( -1 );
	}
	internal_message_table_resource = (libwrc_internal_message_table_resource_t *) message_table_resource;

	if( libcdata_array_get_number_of_entries(
	     internal_message_table_resource->entries_array,
	     number_of_messages,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of entries from array.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves a specific message identifier
 * Returns 1 if successful or -1 on error
 */
int libwrc_message_table_resource_get_identifier(
     libwrc_message_table_resource_t *message_table_resource,
     int message_index,
     uint32_t *message_identifier,
     libcerror_error_t **error )
{
	libwrc_internal_message_table_resource_t *internal_message_table_resource = NULL;
	libwrc_table_entry_t *table_entry                                         = NULL;
	static char *function                                                     = "libwrc_message_table_resource_get_identifier";

	if( message_table_resource == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid message table resource.",
		 function );

		return( -1 );
	}
	internal_message_table_resource = (libwrc_internal_message_table_resource_t *) message_table_resource;

	if( message_identifier == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid message identifier.",
		 function );

		return( -1 );
	}
	if( libcdata_array_get_entry_by_index(
	     internal_message_table_resource->entries_array,
	     message_index,
	     (intptr_t **) &table_entry,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve table entry: %d.",
		 function,
		 message_index );

		return( -1 );
	}
	if( table_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: missing table entry: %d.",
		 function,
		 message_index );

		return( -1 );
	}
	*message_identifier = table_entry->identifier;

	return( 1 );
}

/* Retrieves the message index for a specific identifier
 * Returns 1 if successful, 0 if no such message identifier or -1 on error
 */
int libwrc_message_table_resource_get_index_by_identifier(
     libwrc_message_table_resource_t *message_table_resource,
     uint32_t message_identifier,
     int *message_index,
     libcerror_error_t **error )
{
	libwrc_internal_message_table_resource_t *internal_message_table_resource = NULL;
	libwrc_table_entry_t *table_entry                                         = NULL;
	static char *function                                                     = "libwrc_message_table_resource_get_index_by_identifier";
	int number_of_messages                                                    = 0;
	int safe_message_index                                                    = 0;

	if( message_table_resource == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid message table resource.",
		 function );

		return( -1 );
	}
	internal_message_table_resource = (libwrc_internal_message_table_resource_t *) message_table_resource;

	if( message_index == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid message index.",
		 function );

		return( -1 );
	}
	if( libcdata_array_get_number_of_entries(
	     internal_message_table_resource->entries_array,
	     &number_of_messages,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of entries from array.",
		 function );

		return( -1 );
	}
	for( safe_message_index = 0;
	     safe_message_index < number_of_messages;
	     safe_message_index++ )
	{
		if( libcdata_array_get_entry_by_index(
		     internal_message_table_resource->entries_array,
		     safe_message_index,
		     (intptr_t **) &table_entry,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve table entry: %d.",
			 function,
			 safe_message_index );

			return( -1 );
		}
		if( table_entry == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: missing table entry: %d.",
			 function,
			 safe_message_index );

			return( -1 );
		}
		if( message_identifier == table_entry->identifier )
		{
			*message_index = safe_message_index;

			return( 1 );
		}
	}
	return( 0 );
}

/* Retrieves the size of a specific UTF-8 formatted message string
 * Returns 1 if successful or -1 on error
 */
int libwrc_message_table_resource_get_utf8_string_size(
     libwrc_message_table_resource_t *message_table_resource,
     int message_index,
     size_t *utf8_string_size,
     libcerror_error_t **error )
{
	libwrc_internal_message_table_resource_t *internal_message_table_resource = NULL;
	libwrc_table_entry_t *table_entry                                         = NULL;
	static char *function                                                     = "libwrc_message_table_resource_get_utf8_string_size";

	if( message_table_resource == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid message table resource.",
		 function );

		return( -1 );
	}
	internal_message_table_resource = (libwrc_internal_message_table_resource_t *) message_table_resource;

	if( libcdata_array_get_entry_by_index(
	     internal_message_table_resource->entries_array,
	     message_index,
	     (intptr_t **) &table_entry,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve table entry: %d.",
		 function,
		 message_index );

		return( -1 );
	}
	if( libwrc_table_entry_get_utf8_string_size(
	     table_entry,
	     utf8_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve UTF-8 string size of table entry: %d.",
		 function,
		 message_index );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves a specific UTF-8 formatted message string
 * Returns 1 if successful or -1 on error
 */
int libwrc_message_table_resource_get_utf8_string(
     libwrc_message_table_resource_t *message_table_resource,
     int message_index,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error )
{
	libwrc_internal_message_table_resource_t *internal_message_table_resource = NULL;
	libwrc_table_entry_t *table_entry                                         = NULL;
	static char *function                                                     = "libwrc_message_table_resource_get_utf8_string";

	if( message_table_resource == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid message table resource.",
		 function );

		return( -1 );
	}
	internal_message_table_resource = (libwrc_internal_message_table_resource_t *) message_table_resource;

	if( libcdata_array_get_entry_by_index(
	     internal_message_table_resource->entries_array,
	     message_index,
	     (intptr_t **) &table_entry,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve table entry: %d.",
		 function,
		 message_index );

		return( -1 );
	}
	if( libwrc_table_entry_get_utf8_string(
	     table_entry,
	     utf8_string,
	     utf8_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy table entry: %d to UTF-8 string.",
		 function,
		 message_index );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the size of a specific UTF-16 formatted message string
 * Returns 1 if successful or -1 on error
 */
int libwrc_message_table_resource_get_utf16_string_size(
     libwrc_message_table_resource_t *message_table_resource,
     int message_index,
     size_t *utf16_string_size,
     libcerror_error_t **error )
{
	libwrc_internal_message_table_resource_t *internal_message_table_resource = NULL;
	libwrc_table_entry_t *table_entry                                         = NULL;
	static char *function                                                     = "libwrc_message_table_resource_get_utf16_string_size";

	if( message_table_resource == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid message table resource.",
		 function );

		return( -1 );
	}
	internal_message_table_resource = (libwrc_internal_message_table_resource_t *) message_table_resource;

	if( libcdata_array_get_entry_by_index(
	     internal_message_table_resource->entries_array,
	     message_index,
	     (intptr_t **) &table_entry,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve table entry: %d.",
		 function,
		 message_index );

		return( -1 );
	}
	if( libwrc_table_entry_get_utf16_string_size(
	     table_entry,
	     utf16_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve UTF-16 string size of table entry: %d.",
		 function,
		 message_index );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves a specific UTF-16 formatted message string
 * Returns 1 if successful or -1 on error
 */
int libwrc_message_table_resource_get_utf16_string(
     libwrc_message_table_resource_t *message_table_resource,
     int message_index,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error )
{
	libwrc_internal_message_table_resource_t *internal_message_table_resource = NULL;
	libwrc_table_entry_t *table_entry                                         = NULL;
	static char *function                                                     = "libwrc_message_table_resource_get_utf16_string";

	if( message_table_resource == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid message table resource.",
		 function );

		return( -1 );
	}
	internal_message_table_resource = (libwrc_internal_message_table_resource_t *) message_table_resource;

	if( libcdata_array_get_entry_by_index(
	     internal_message_table_resource->entries_array,
	     message_index,
	     (intptr_t **) &table_entry,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve table entry: %d.",
		 function,
		 message_index );

		return( -1 );
	}
	if( libwrc_table_entry_get_utf16_string(
	     table_entry,
	     utf16_string,
	     utf16_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy table entry: %d to UTF-16 string.",
		 function,
		 message_index );

		return( -1 );
	}
	return( 1 );
}

