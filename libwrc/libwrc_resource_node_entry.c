/*
 * Resource node entry functions
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

#include "libwrc_data_descriptor.h"
#include "libwrc_debug.h"
#include "libwrc_definitions.h"
#include "libwrc_libbfio.h"
#include "libwrc_libcdata.h"
#include "libwrc_libcerror.h"
#include "libwrc_libcnotify.h"
#include "libwrc_libuna.h"
#include "libwrc_resource_node_entry.h"

#include "wrc_resource_node.h"

/* Creates a table entry
 * Make sure the value resource_node_entry is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libwrc_resource_node_entry_initialize(
     libwrc_resource_node_entry_t **resource_node_entry,
     libcerror_error_t **error )
{
	static char *function = "libwrc_resource_node_entry_initialize";

	if( resource_node_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid table entry.",
		 function );

		return( -1 );
	}
	if( *resource_node_entry != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid table entry value already set.",
		 function );

		return( -1 );
	}
	*resource_node_entry = memory_allocate_structure(
	                        libwrc_resource_node_entry_t );

	if( *resource_node_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create table entry.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *resource_node_entry,
	     0,
	     sizeof( libwrc_resource_node_entry_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear table entry.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *resource_node_entry != NULL )
	{
		memory_free(
		 *resource_node_entry );

		*resource_node_entry = NULL;
	}
	return( -1 );
}

/* Frees a table entry
 * Returns 1 if successful or -1 on error
 */
int libwrc_resource_node_entry_free(
     libwrc_resource_node_entry_t **resource_node_entry,
     libcerror_error_t **error )
{
	static char *function = "libwrc_resource_node_entry_free";
	int result            = 1;

	if( resource_node_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid table entry.",
		 function );

		return( -1 );
	}
	if( *resource_node_entry != NULL )
	{
		if( libwrc_data_descriptor_free(
		     &( ( *resource_node_entry )->data_descriptor ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free data descriptor.",
			 function );

			result = -1;
		}
		if( ( *resource_node_entry )->name_string != NULL )
		{
			memory_free(
			 ( *resource_node_entry )->name_string );
		}
		memory_free(
		 *resource_node_entry );

		*resource_node_entry = NULL;
	}
	return( result );
}

/* Reads the resource node entry data
 * Returns 1 if successful or -1 on error
 */
int libwrc_resource_node_entry_read_data(
     libwrc_resource_node_entry_t *resource_node_entry,
     const uint8_t *data,
     size_t data_size,
     int node_level,
     libcerror_error_t **error )
{
	static char *function = "libwrc_resource_node_entry_read_data";

	if( resource_node_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid resource node entry.",
		 function );

		return( -1 );
	}
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
	if( ( data_size < sizeof( wrc_resource_node_entry_t ) )
	 || ( data_size > (size_t) SSIZE_MAX ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid data size value out of bounds.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: resource node entry data:\n",
		 function );
		libcnotify_print_data(
		 data,
		 sizeof( wrc_resource_node_entry_t ),
		 0 );
	}
#endif
	byte_stream_copy_to_uint32_little_endian(
	 ( (wrc_resource_node_entry_t *) data )->identifier,
	 resource_node_entry->identifier );

	byte_stream_copy_to_uint32_little_endian(
	 ( (wrc_resource_node_entry_t *) data )->offset,
	 resource_node_entry->offset );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: identifier\t\t\t: 0x%08" PRIx32 "",
		 function,
		 resource_node_entry->identifier );

		if( ( node_level == 1 )
		 && ( ( resource_node_entry->identifier & LIBWRC_RESOURCE_IDENTIFIER_FLAG_HAS_NAME ) == 0 ) )
		{
			libcnotify_printf(
			 " (%s)",
			 libwrc_debug_get_resource_identifier(
			  resource_node_entry->identifier ) );
		}
		libcnotify_printf(
		 "\n" );

		libcnotify_printf(
		 "%s: offset\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 resource_node_entry->offset );
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	return( 1 );
}

/* Reads the resource node entry
 * Returns 1 if successful or -1 on error
 */
int libwrc_resource_node_entry_read_file_io_handle(
     libwrc_resource_node_entry_t *resource_node_entry,
     libbfio_handle_t *file_io_handle,
     off64_t file_offset,
     int node_level,
     libcerror_error_t **error )
{
	uint8_t resource_node_entry_data[ sizeof( wrc_resource_node_entry_t ) ];

	static char *function = "libwrc_resource_node_entry_read_file_io_handle";
	ssize_t read_count    = 0;

	if( resource_node_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid resource node entry.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading resource node entry at offset: %" PRIi64 " (0x%08" PRIx64 ")\n",
		 function,
		 file_offset,
		 file_offset );
	}
#endif
	read_count = libbfio_handle_read_buffer_at_offset(
	              file_io_handle,
	              resource_node_entry_data,
	              sizeof( wrc_resource_node_entry_t ),
	              file_offset,
	              error );

	if( read_count != (ssize_t) sizeof( wrc_resource_node_entry_t ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read resource node entry data at offset: %" PRIi64 " (0x%08" PRIx64 ").",
		 function,
		 file_offset,
		 file_offset );

		return( -1 );
	}
	if( libwrc_resource_node_entry_read_data(
	     resource_node_entry,
	     resource_node_entry_data,
	     sizeof( wrc_resource_node_entry_t ),
	     node_level,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read resource node entry.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Reads the resource node entry name
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libwrc_resource_node_entry_read_name_file_io_handle(
     libwrc_resource_node_entry_t *resource_node_entry,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error )
{
	uint8_t name_size_data[ 2 ];

	static char *function   = "libwrc_resource_node_entry_read_name_file_io_handle";
	size_t name_string_size = 0;
	ssize_t read_count      = 0;
	off64_t file_offset     = 0;

	if( resource_node_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid resource node entry.",
		 function );

		return( -1 );
	}
	if( ( resource_node_entry->identifier & LIBWRC_RESOURCE_IDENTIFIER_FLAG_HAS_NAME ) == 0 )
	{
		return( 0 );
	}
	file_offset = (off64_t) ( resource_node_entry->identifier & 0x7fffffffUL );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading name at offset: %" PRIi64 " (0x%08" PRIx64 ")\n",
		 function,
		 file_offset,
		 file_offset );
	}
#endif
	read_count = libbfio_handle_read_buffer_at_offset(
		      file_io_handle,
		      name_size_data,
		      2,
		      file_offset,
		      error );

	if( read_count != (ssize_t) 2 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read resource node entry name string size at offset: %" PRIi64 " (0x%08" PRIx64 ").",
		 function,
		 file_offset,
		 file_offset );

		goto on_error;
	}
	byte_stream_copy_to_uint16_little_endian(
	 name_size_data,
	 name_string_size );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: name string size\t: %" PRIzd "\n",
		 function,
		 name_string_size );
	}
#endif
	name_string_size *= 2;

	if( ( name_string_size == 0 )
	 || ( name_string_size > (size_t) MEMORY_MAXIMUM_ALLOCATION_SIZE ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid name string size value out of bounds.",
		 function );

		goto on_error;
	}
	resource_node_entry->name_string = (uint8_t *) memory_allocate(
	                                                sizeof( uint8_t ) * name_string_size );

	if( resource_node_entry->name_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create name string.",
		 function );

		goto on_error;
	}
	resource_node_entry->name_string_size = name_string_size;

	read_count = libbfio_handle_read_buffer(
		      file_io_handle,
		      resource_node_entry->name_string,
		      name_string_size,
		      error );

	if( read_count != (ssize_t) name_string_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read name string.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		if( libwrc_debug_print_utf16_string_value(
		     function,
		     "name string\t",
		     resource_node_entry->name_string,
		     resource_node_entry->name_string_size,
		     LIBUNA_ENDIAN_LITTLE,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
			 "%s: unable to print UTF-16 string value.",
			 function );

			return( -1 );
		}
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	return( 1 );

on_error:
	if( resource_node_entry->name_string != NULL )
	{
		memory_free(
		 resource_node_entry->name_string );

		resource_node_entry->name_string = NULL;
	}
	resource_node_entry->name_string_size = 0;

	return( -1 );
}

/* Compares two resource node entries
 * Returns LIBCDATA_COMPARE_LESS, LIBCDATA_COMPARE_EQUAL, LIBCDATA_COMPARE_GREATER if successful or -1 on error
 */
int libwrc_resource_node_entry_compare(
     libwrc_resource_node_entry_t *first_resource_node_entry,
     libwrc_resource_node_entry_t *second_resource_node_entry,
     libcerror_error_t **error )
{
	static char *function = "libwrc_resource_node_entry_compare";

	if( first_resource_node_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid first resource node entry.",
		 function );

		return( -1 );
	}
	if( second_resource_node_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid second resource node entry.",
		 function );

		return( -1 );
	}
	if( first_resource_node_entry->identifier < second_resource_node_entry->identifier )
	{
		return( LIBCDATA_COMPARE_LESS );
	}
	else if( first_resource_node_entry->identifier > second_resource_node_entry->identifier )
	{
		return( LIBCDATA_COMPARE_GREATER );
	}
	return( LIBCDATA_COMPARE_EQUAL );
}

/* Sets the name string
 * Returns 1 if successful or -1 on error
 */
int libwrc_resource_node_entry_set_name_string(
     libwrc_resource_node_entry_t *resource_node_entry,
     const uint8_t *name_string,
     size_t name_string_size,
     libcerror_error_t **error )
{
	static char *function = "libwrc_resource_node_entry_set_name_string";

	if( resource_node_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid resource node entry.",
		 function );

		return( -1 );
	}
	if( resource_node_entry->name_string != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid resource node entry - name string value already set.",
		 function );

		return( -1 );
	}
	if( name_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid name string.",
		 function );

		return( -1 );
	}
	if( ( name_string_size == 0 )
	 || ( name_string_size > (size_t) MEMORY_MAXIMUM_ALLOCATION_SIZE ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid name string size value out of bounds.",
		 function );

		return( -1 );
	}
	resource_node_entry->name_string = (uint8_t *) memory_allocate(
	                                                sizeof( uint8_t ) * name_string_size );

	if( resource_node_entry->name_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create resource node name string.",
		 function );

		goto on_error;
	}
	resource_node_entry->name_string_size = name_string_size;

	if( memory_copy(
	     resource_node_entry->name_string,
	     name_string,
	     name_string_size ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy name string.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( resource_node_entry->name_string != NULL )
	{
		memory_free(
		 resource_node_entry->name_string );

		resource_node_entry->name_string = NULL;
	}
	resource_node_entry->name_string_size = 0;

	return( -1 );
}

/* Retrieves the identifier
 * Returns 1 if successful or -1 on error
 */
int libwrc_resource_node_entry_get_identifier(
     libwrc_resource_node_entry_t *resource_node_entry,
     uint32_t *identifier,
     libcerror_error_t **error )
{
	static char *function = "libwrc_resource_node_entry_get_identifier";

	if( resource_node_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid resource node entry.",
		 function );

		return( -1 );
	}
	if( identifier == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid identifier.",
		 function );

		return( -1 );
	}
	*identifier = resource_node_entry->identifier;

	return( 1 );
}

/* Retrieves the size of the UTF-8 encoded name
 * The returned size includes the end of string character
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libwrc_resource_node_entry_get_utf8_name_size(
     libwrc_resource_node_entry_t *resource_node_entry,
     size_t *utf8_string_size,
     libcerror_error_t **error )
{
	static char *function = "libwrc_resource_node_entry_get_utf8_name_size";

	if( resource_node_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid resource node entry.",
		 function );

		return( -1 );
	}
	if( utf8_string_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-8 string size.",
		 function );

		return( -1 );
	}
	if( ( resource_node_entry->name_string == NULL )
	 || ( resource_node_entry->name_string_size == 0 ) )
	{
		return( 0 );
	}
	if( libuna_utf8_string_size_from_utf16_stream(
	     resource_node_entry->name_string,
	     resource_node_entry->name_string_size,
	     LIBUNA_ENDIAN_LITTLE,
	     utf8_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve UTF-8 string size.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the UTF-8 encoded name
 * The size should include the end of string character
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libwrc_resource_node_entry_get_utf8_name(
     libwrc_resource_node_entry_t *resource_node_entry,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error )
{
	static char *function = "libwrc_resource_node_entry_get_utf8_name";

	if( resource_node_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid resource node entry.",
		 function );

		return( -1 );
	}
	if( utf8_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-8 string.",
		 function );

		return( -1 );
	}
	if( utf8_string_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-8 string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( ( resource_node_entry->name_string == NULL )
	 || ( resource_node_entry->name_string_size == 0 ) )
	{
		return( 0 );
	}
	if( libuna_utf8_string_copy_from_utf16_stream(
	     utf8_string,
	     utf8_string_size,
	     resource_node_entry->name_string,
	     resource_node_entry->name_string_size,
	     LIBUNA_ENDIAN_LITTLE,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve UTF-8 string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the size of the UTF-16 encoded name
 * The returned size includes the end of string character
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libwrc_resource_node_entry_get_utf16_name_size(
     libwrc_resource_node_entry_t *resource_node_entry,
     size_t *utf16_string_size,
     libcerror_error_t **error )
{
	static char *function = "libwrc_resource_node_entry_get_utf16_name_size";

	if( resource_node_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid resource node entry.",
		 function );

		return( -1 );
	}
	if( utf16_string_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 string size.",
		 function );

		return( -1 );
	}
	if( ( resource_node_entry->name_string == NULL )
	 || ( resource_node_entry->name_string_size == 0 ) )
	{
		return( 0 );
	}
	if( libuna_utf16_string_size_from_utf16_stream(
	     resource_node_entry->name_string,
	     resource_node_entry->name_string_size,
	     LIBUNA_ENDIAN_LITTLE,
	     utf16_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve UTF-16 string size.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the UTF-16 encoded name
 * The size should include the end of string character
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libwrc_resource_node_entry_get_utf16_name(
     libwrc_resource_node_entry_t *resource_node_entry,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error )
{
	static char *function = "libwrc_resource_node_entry_get_utf16_name";

	if( resource_node_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid resource node entry.",
		 function );

		return( -1 );
	}
	if( utf16_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 string.",
		 function );

		return( -1 );
	}
	if( utf16_string_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-16 string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( ( resource_node_entry->name_string == NULL )
	 || ( resource_node_entry->name_string_size == 0 ) )
	{
		return( 0 );
	}
	if( libuna_utf16_string_copy_from_utf16_stream(
	     utf16_string,
	     utf16_string_size,
	     resource_node_entry->name_string,
	     resource_node_entry->name_string_size,
	     LIBUNA_ENDIAN_LITTLE,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve UTF-16 string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the type
 * Returns 1 if successful or -1 on error
 */
int libwrc_resource_node_entry_get_type(
     libwrc_resource_node_entry_t *resource_node_entry,
     int *type,
     libcerror_error_t **error )
{
	static char *function = "libwrc_resource_node_entry_get_type";

	if( resource_node_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid resource node entry.",
		 function );

		return( -1 );
	}
	if( type == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid type.",
		 function );

		return( -1 );
	}
	*type = resource_node_entry->type;

	return( 1 );
}

