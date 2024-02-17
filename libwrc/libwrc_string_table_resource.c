/*
 * String table (STRINGTABLE) resource functions
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

#include "libwrc_definitions.h"
#include "libwrc_libcdata.h"
#include "libwrc_libcerror.h"
#include "libwrc_libcnotify.h"
#include "libwrc_libuna.h"
#include "libwrc_string_table_resource.h"
#include "libwrc_table_entry.h"

/* Creates a string table resource
 * Make sure the value string_table_resource is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libwrc_string_table_resource_initialize(
     libwrc_string_table_resource_t **string_table_resource,
     libcerror_error_t **error )
{
	libwrc_internal_string_table_resource_t *internal_string_table_resource = NULL;
	static char *function                                                   = "libwrc_string_table_resource_initialize";

	if( string_table_resource == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid string table resource.",
		 function );

		return( -1 );
	}
	if( *string_table_resource != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid string table resource value already set.",
		 function );

		return( -1 );
	}
	internal_string_table_resource = memory_allocate_structure(
	                                  libwrc_internal_string_table_resource_t );

	if( internal_string_table_resource == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create string table resource.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     internal_string_table_resource,
	     0,
	     sizeof( libwrc_internal_string_table_resource_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear string table resource.",
		 function );

		memory_free(
		 internal_string_table_resource );

		return( -1 );
	}
	if( libcdata_array_initialize(
	     &( internal_string_table_resource->entries_array ),
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
	*string_table_resource = (libwrc_string_table_resource_t *) internal_string_table_resource;

	return( 1 );

on_error:
	if( internal_string_table_resource != NULL )
	{
		memory_free(
		 internal_string_table_resource );
	}
	return( -1 );
}

/* Frees a string table resource
 * Returns 1 if successful or -1 on error
 */
int libwrc_string_table_resource_free(
     libwrc_string_table_resource_t **string_table_resource,
     libcerror_error_t **error )
{
	libwrc_internal_string_table_resource_t *internal_string_table_resource = NULL;
	static char *function                                                   = "libwrc_string_table_resource_free";
	int result                                                              = 1;

	if( string_table_resource == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid string table resource.",
		 function );

		return( -1 );
	}
	if( *string_table_resource != NULL )
	{
		internal_string_table_resource = (libwrc_internal_string_table_resource_t *) *string_table_resource;
		*string_table_resource         = NULL;

		if( libcdata_array_free(
		     &( internal_string_table_resource->entries_array ),
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
		 internal_string_table_resource );
	}
	return( result );
}

/* Reads the string table resource
 * Returns 1 if successful or -1 on error
 */
int libwrc_string_table_resource_read(
     libwrc_string_table_resource_t *string_table_resource,
     const uint8_t *data,
     size_t data_size,
     uint32_t base_identifier,
     libcerror_error_t **error )
{
	libwrc_internal_string_table_resource_t *internal_string_table_resource = NULL;
	libwrc_table_entry_t *table_entry                                       = NULL;
	static char *function                                                   = "libwrc_string_table_resource_read";
	size_t data_offset                                                      = 0;
	uint32_t string_size                                                    = 0;
	int entry_index                                                         = 0;
	int string_index                                                        = 0;

	if( string_table_resource == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid string table resource.",
		 function );

		return( -1 );
	}
	internal_string_table_resource = (libwrc_internal_string_table_resource_t *) string_table_resource;

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
	if( ( data_size < 2 )
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
	while( data_offset < ( data_size - 2 ) )
	{
		byte_stream_copy_to_uint16_little_endian(
		 &( data[ data_offset ] ),
		 string_size );

		data_offset += 2;

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: string: %02d length\t\t\t: %" PRIu32 "\n",
			 function,
			 string_index,
			 string_size );
		}
#endif
		if( string_size > 0 )
		{
			if( string_size > ( ( data_size - data_offset ) / 2 ) )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
				 "%s: invalid string size value out of bound.",
				 function );

				goto on_error;
			}
			string_size *= 2;

#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "%s: string: %02 data:\n",
				 function,
				 string_index );
				libcnotify_print_data(
				 &( data[ data_offset ] ),
				 (size_t) string_size,
				 0 );
			}
#endif
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
			if( libwrc_table_entry_set_string(
			     table_entry,
			     &( data[ data_offset ] ),
			     (size_t) string_size,
			     LIBUNA_CODEPAGE_UTF16_LITTLE_ENDIAN,
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
			table_entry->identifier = ( ( base_identifier - 1 ) << 4 ) | (uint32_t) string_index;

			if( libcdata_array_append_entry(
			     internal_string_table_resource->entries_array,
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

			data_offset += (size_t) string_size;
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
	return( 1 );

on_error:
	if( table_entry != NULL )
	{
		libwrc_table_entry_free(
		 &table_entry,
		 NULL );
	}
	libcdata_array_empty(
	 internal_string_table_resource->entries_array,
	 (int (*)(intptr_t **, libcerror_error_t **)) &libwrc_table_entry_free,
	 error );

	return( -1 );
}

/* Retrieves the number of strings
 * Returns 1 if successful or -1 on error
 */
int libwrc_string_table_resource_get_number_of_strings(
     libwrc_string_table_resource_t *string_table_resource,
     int *number_of_strings,
     libcerror_error_t **error )
{
	libwrc_internal_string_table_resource_t *internal_string_table_resource = NULL;
	static char *function                                                   = "libwrc_string_table_resource_get_number_of_strings";

	if( string_table_resource == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid string table resource.",
		 function );

		return( -1 );
	}
	internal_string_table_resource = (libwrc_internal_string_table_resource_t *) string_table_resource;

	if( libcdata_array_get_number_of_entries(
	     internal_string_table_resource->entries_array,
	     number_of_strings,
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

/* Retrieves a specific string identifier
 * Returns 1 if successful or -1 on error
 */
int libwrc_string_table_resource_get_identifier(
     libwrc_string_table_resource_t *string_table_resource,
     int string_index,
     uint32_t *string_identifier,
     libcerror_error_t **error )
{
	libwrc_internal_string_table_resource_t *internal_string_table_resource = NULL;
	libwrc_table_entry_t *table_entry                                       = NULL;
	static char *function                                                   = "libwrc_string_table_resource_get_identifier";

	if( string_table_resource == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid string table resource.",
		 function );

		return( -1 );
	}
	internal_string_table_resource = (libwrc_internal_string_table_resource_t *) string_table_resource;

	if( string_identifier == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid string identifier.",
		 function );

		return( -1 );
	}
	if( libcdata_array_get_entry_by_index(
	     internal_string_table_resource->entries_array,
	     string_index,
	     (intptr_t **) &table_entry,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve table entry: %d.",
		 function,
		 string_index );

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
		 string_index );

		return( -1 );
	}
	*string_identifier = table_entry->identifier;

	return( 1 );
}

/* Retrieves the string index for a specific identifier
 * Returns 1 if successful, 0 if no such string identifier or -1 on error
 */
int libwrc_string_table_resource_get_index_by_identifier(
     libwrc_string_table_resource_t *string_table_resource,
     uint32_t string_identifier,
     int *string_index,
     libcerror_error_t **error )
{
	libwrc_internal_string_table_resource_t *internal_string_table_resource = NULL;
	libwrc_table_entry_t *table_entry                                       = NULL;
	static char *function                                                   = "libwrc_string_table_resource_get_index_by_identifier";
	int number_of_strings                                                   = 0;
	int safe_string_index                                                   = 0;

	if( string_table_resource == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid string table resource.",
		 function );

		return( -1 );
	}
	internal_string_table_resource = (libwrc_internal_string_table_resource_t *) string_table_resource;

	if( string_index == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid string index.",
		 function );

		return( -1 );
	}
	if( libcdata_array_get_number_of_entries(
	     internal_string_table_resource->entries_array,
	     &number_of_strings,
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
	for( safe_string_index = 0;
	     safe_string_index < number_of_strings;
	     safe_string_index++ )
	{
		if( libcdata_array_get_entry_by_index(
		     internal_string_table_resource->entries_array,
		     safe_string_index,
		     (intptr_t **) &table_entry,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve table entry: %d.",
			 function,
			 safe_string_index );

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
			 safe_string_index );

			return( -1 );
		}
		if( string_identifier == table_entry->identifier )
		{
			*string_index = safe_string_index;

			return( 1 );
		}
	}
	return( 0 );
}

/* Retrieves the size of a specific UTF-8 formatted string string
 * Returns 1 if successful or -1 on error
 */
int libwrc_string_table_resource_get_utf8_string_size(
     libwrc_string_table_resource_t *string_table_resource,
     int string_index,
     size_t *utf8_string_size,
     libcerror_error_t **error )
{
	libwrc_internal_string_table_resource_t *internal_string_table_resource = NULL;
	libwrc_table_entry_t *table_entry                                       = NULL;
	static char *function                                                   = "libwrc_string_table_resource_get_utf8_string_size";

	if( string_table_resource == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid string table resource.",
		 function );

		return( -1 );
	}
	internal_string_table_resource = (libwrc_internal_string_table_resource_t *) string_table_resource;

	if( libcdata_array_get_entry_by_index(
	     internal_string_table_resource->entries_array,
	     string_index,
	     (intptr_t **) &table_entry,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve table entry: %d.",
		 function,
		 string_index );

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
		 string_index );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves a specific UTF-8 formatted string string
 * Returns 1 if successful or -1 on error
 */
int libwrc_string_table_resource_get_utf8_string(
     libwrc_string_table_resource_t *string_table_resource,
     int string_index,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error )
{
	libwrc_internal_string_table_resource_t *internal_string_table_resource = NULL;
	libwrc_table_entry_t *table_entry                                       = NULL;
	static char *function                                                   = "libwrc_string_table_resource_get_utf8_string";

	if( string_table_resource == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid string table resource.",
		 function );

		return( -1 );
	}
	internal_string_table_resource = (libwrc_internal_string_table_resource_t *) string_table_resource;

	if( libcdata_array_get_entry_by_index(
	     internal_string_table_resource->entries_array,
	     string_index,
	     (intptr_t **) &table_entry,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve table entry: %d.",
		 function,
		 string_index );

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
		 string_index );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the size of a specific UTF-16 formatted string string
 * Returns 1 if successful or -1 on error
 */
int libwrc_string_table_resource_get_utf16_string_size(
     libwrc_string_table_resource_t *string_table_resource,
     int string_index,
     size_t *utf16_string_size,
     libcerror_error_t **error )
{
	libwrc_internal_string_table_resource_t *internal_string_table_resource = NULL;
	libwrc_table_entry_t *table_entry                                       = NULL;
	static char *function                                                   = "libwrc_string_table_resource_get_utf16_string_size";

	if( string_table_resource == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid string table resource.",
		 function );

		return( -1 );
	}
	internal_string_table_resource = (libwrc_internal_string_table_resource_t *) string_table_resource;

	if( libcdata_array_get_entry_by_index(
	     internal_string_table_resource->entries_array,
	     string_index,
	     (intptr_t **) &table_entry,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve table entry: %d.",
		 function,
		 string_index );

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
		 string_index );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves a specific UTF-16 formatted string string
 * Returns 1 if successful or -1 on error
 */
int libwrc_string_table_resource_get_utf16_string(
     libwrc_string_table_resource_t *string_table_resource,
     int string_index,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error )
{
	libwrc_internal_string_table_resource_t *internal_string_table_resource = NULL;
	libwrc_table_entry_t *table_entry                                       = NULL;
	static char *function                                                   = "libwrc_string_table_resource_get_utf16_string";

	if( string_table_resource == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid string table resource.",
		 function );

		return( -1 );
	}
	internal_string_table_resource = (libwrc_internal_string_table_resource_t *) string_table_resource;

	if( libcdata_array_get_entry_by_index(
	     internal_string_table_resource->entries_array,
	     string_index,
	     (intptr_t **) &table_entry,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve table entry: %d.",
		 function,
		 string_index );

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
		 string_index );

		return( -1 );
	}
	return( 1 );
}

