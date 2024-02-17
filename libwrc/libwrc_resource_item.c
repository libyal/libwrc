/*
 * Resource item functions
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

#include "libwrc_io_handle.h"
#include "libwrc_libbfio.h"
#include "libwrc_libcdata.h"
#include "libwrc_libcerror.h"
#include "libwrc_resource_item.h"
#include "libwrc_resource_node_entry.h"

/* Creates a resource item
 * Make sure the value resource_item is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libwrc_resource_item_initialize(
     libwrc_resource_item_t **resource_item,
     libwrc_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     libcdata_tree_node_t *resource_node,
     libcerror_error_t **error )
{
	libwrc_internal_resource_item_t *internal_resource_item = NULL;
	libwrc_resource_node_entry_t *resource_node_entry       = NULL;
	static char *function                                   = "libwrc_resource_item_initialize";

	if( resource_item == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid resource item.",
		 function );

		return( -1 );
	}
	if( *resource_item != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid resource item value already set.",
		 function );

		return( -1 );
	}
	if( libcdata_tree_node_get_value(
	     resource_node,
	     (intptr_t **) &resource_node_entry,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve resource node entry.",
		 function );

		goto on_error;
	}
	if( resource_node_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid resource node entry.",
		 function );

		goto on_error;
	}
	internal_resource_item = memory_allocate_structure(
	                          libwrc_internal_resource_item_t );

	if( internal_resource_item == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create resource item.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     internal_resource_item,
	     0,
	     sizeof( libwrc_internal_resource_item_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear resource item.",
		 function );

		memory_free(
		 internal_resource_item );

		return( -1 );
	}
	internal_resource_item->io_handle           = io_handle;
	internal_resource_item->file_io_handle      = file_io_handle;
	internal_resource_item->resource_node       = resource_node;
	internal_resource_item->resource_node_entry = resource_node_entry;

	*resource_item = (libwrc_resource_item_t *) internal_resource_item;

	return( 1 );

on_error:
	if( internal_resource_item != NULL )
	{
		memory_free(
		 internal_resource_item );
	}
	return( -1 );
}

/* Frees a resource item
 * Returns 1 if successful or -1 on error
 */
int libwrc_resource_item_free(
     libwrc_resource_item_t **resource_item,
     libcerror_error_t **error )
{
	libwrc_internal_resource_item_t *internal_resource_item = NULL;
	static char *function                                   = "libwrc_resource_item_free";

	if( resource_item == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid resource item.",
		 function );

		return( -1 );
	}
	if( *resource_item != NULL )
	{
		internal_resource_item = (libwrc_internal_resource_item_t *) *resource_item;
		*resource_item         = NULL;

		memory_free(
		 internal_resource_item );
	}
	return( 1 );
}

/* Retrieves the resource item identifier
 * Returns 1 if successful or -1 on error
 */
int libwrc_resource_item_get_identifier(
     libwrc_resource_item_t *resource_item,
     uint32_t *identifier,
     libcerror_error_t **error )
{
	libwrc_internal_resource_item_t *internal_resource_item = NULL;
	static char *function                                   = "libwrc_resource_item_get_identifier";

	if( resource_item == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid resource item.",
		 function );

		return( -1 );
	}
	internal_resource_item = (libwrc_internal_resource_item_t *) resource_item;

	if( libwrc_resource_node_entry_get_identifier(
	     internal_resource_item->resource_node_entry,
	     identifier,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve identifier.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the size of the UTF-8 encoded name
 * The returned size includes the end of string character
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libwrc_resource_item_get_utf8_name_size(
     libwrc_resource_item_t *resource_item,
     size_t *utf8_string_size,
     libcerror_error_t **error )
{
	libwrc_internal_resource_item_t *internal_resource_item = NULL;
	static char *function                                   = "libwrc_resource_item_get_utf8_name_size";
	int result                                              = 0;

	if( resource_item == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid resource item.",
		 function );

		return( -1 );
	}
	internal_resource_item = (libwrc_internal_resource_item_t *) resource_item;

	result = libwrc_resource_node_entry_get_utf8_name_size(
	          internal_resource_item->resource_node_entry,
	          utf8_string_size,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve size of UTF-8 name.",
		 function );

		return( -1 );
	}
	return( result );
}

/* Retrieves the UTF-8 encoded name
 * The size should include the end of string character
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libwrc_resource_item_get_utf8_name(
     libwrc_resource_item_t *resource_item,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error )
{
	libwrc_internal_resource_item_t *internal_resource_item = NULL;
	static char *function                                   = "libwrc_resource_item_get_utf8_name";
	int result                                              = 0;

	if( resource_item == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid resource item.",
		 function );

		return( -1 );
	}
	internal_resource_item = (libwrc_internal_resource_item_t *) resource_item;

	result = libwrc_resource_node_entry_get_utf8_name(
	          internal_resource_item->resource_node_entry,
	          utf8_string,
	          utf8_string_size,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve size of UTF-8 name.",
		 function );

		return( -1 );
	}
	return( result );
}

/* Retrieves the size of the UTF-16 encoded name
 * The returned size includes the end of string character
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libwrc_resource_item_get_utf16_name_size(
     libwrc_resource_item_t *resource_item,
     size_t *utf16_string_size,
     libcerror_error_t **error )
{
	libwrc_internal_resource_item_t *internal_resource_item = NULL;
	static char *function                                   = "libwrc_resource_item_get_utf16_name_size";
	int result                                              = 0;

	if( resource_item == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid resource item.",
		 function );

		return( -1 );
	}
	internal_resource_item = (libwrc_internal_resource_item_t *) resource_item;

	result = libwrc_resource_node_entry_get_utf16_name_size(
	          internal_resource_item->resource_node_entry,
	          utf16_string_size,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve size of UTF-16 name.",
		 function );

		return( -1 );
	}
	return( result );
}

/* Retrieves the UTF-16 encoded name
 * The size should include the end of string character
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libwrc_resource_item_get_utf16_name(
     libwrc_resource_item_t *resource_item,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error )
{
	libwrc_internal_resource_item_t *internal_resource_item = NULL;
	static char *function                                   = "libwrc_resource_item_get_utf16_name";
	int result                                              = 0;

	if( resource_item == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid resource item.",
		 function );

		return( -1 );
	}
	internal_resource_item = (libwrc_internal_resource_item_t *) resource_item;

	result = libwrc_resource_node_entry_get_utf16_name(
	          internal_resource_item->resource_node_entry,
	          utf16_string,
	          utf16_string_size,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve size of UTF-16 name.",
		 function );

		return( -1 );
	}
	return( result );
}

/* Reads resource item data from the current offset into a buffer
 * Returns the number of bytes read or -1 on error
 */
ssize_t libwrc_resource_item_read_buffer(
         libwrc_resource_item_t *resource_item,
         uint8_t *buffer,
         size_t size,
         libcerror_error_t **error )
{
	libwrc_internal_resource_item_t *internal_resource_item = NULL;
	static char *function                                   = "libwrc_resource_item_read_buffer";
	ssize_t read_count                                      = 0;
	off64_t data_offset                                     = 0;

	if( resource_item == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid resource item.",
		 function );

		return( -1 );
	}
	internal_resource_item = (libwrc_internal_resource_item_t *) resource_item;

	if( internal_resource_item->io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid resource item - missing IO handle.",
		 function );

		return( -1 );
	}
	if( internal_resource_item->resource_node_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid resource item - missing resource node entry.",
		 function );

		return( -1 );
	}
	if( internal_resource_item->resource_node_entry->data_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid resource item - invalid resource node entry - missing data descriptor.",
		 function );

		return( -1 );
	}
	if( internal_resource_item->current_offset < 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid resource item - current offset value out of bounds.",
		 function );

		return( -1 );
	}
	if( buffer == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid buffer.",
		 function );

		return( -1 );
	}
	if( size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( internal_resource_item->current_offset >= (off64_t) internal_resource_item->resource_node_entry->data_descriptor->size )
	{
		return( 0 );
	}
	if( ( size > (size64_t) internal_resource_item->resource_node_entry->data_descriptor->size )
	 || ( (size64_t) internal_resource_item->current_offset > ( (size64_t) internal_resource_item->resource_node_entry->data_descriptor->size - size ) ) )
	{
		size = (size_t)( (off64_t) internal_resource_item->resource_node_entry->data_descriptor->size - internal_resource_item->current_offset );
	}
	data_offset  = internal_resource_item->resource_node_entry->data_descriptor->virtual_address;
	data_offset -= internal_resource_item->io_handle->virtual_address;
	data_offset += internal_resource_item->current_offset;

	read_count = libbfio_handle_read_buffer_at_offset(
	              internal_resource_item->file_io_handle,
	              buffer,
	              size,
	              data_offset,
	              error );

	if( read_count != (ssize_t) size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read resource data at offset: %" PRIi64 " (0x%08" PRIx64 ").",
		 function,
		 data_offset,
		 data_offset );

		return( -1 );
	}
	return( read_count );
}

/* Reads resource item data a specific offset into a buffer
 * Returns the number of bytes read or -1 on error
 */
ssize_t libwrc_resource_item_read_buffer_at_offset(
         libwrc_resource_item_t *resource_item,
         uint8_t *buffer,
         size_t buffer_size,
         off64_t offset,
         libcerror_error_t **error )
{
	static char *function = "libwrc_resource_item_read_buffer_at_offset";
	ssize_t read_count    = 0;

	if( libwrc_resource_item_seek_offset(
	     resource_item,
	     offset,
	     SEEK_SET,
	     error ) == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to seek offset.",
		 function );

		return( -1 );
	}
	read_count = libwrc_resource_item_read_buffer(
	              resource_item,
	              buffer,
	              buffer_size,
	              error );

	if( read_count < 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read buffer.",
		 function );

		return( -1 );
	}
	return( read_count );
}

/* Seeks a certain offset of the resource item data
 * Returns the offset if seek is successful or -1 on error
 */
off64_t libwrc_resource_item_seek_offset(
         libwrc_resource_item_t *resource_item,
         off64_t offset,
         int whence,
         libcerror_error_t **error )
{
	libwrc_internal_resource_item_t *internal_resource_item = NULL;
	static char *function                                   = "libwrc_resource_item_seek_offset";

	if( resource_item == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid resource item.",
		 function );

		return( -1 );
	}
	internal_resource_item = (libwrc_internal_resource_item_t *) resource_item;

	if( internal_resource_item->resource_node_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid resource item - missing resource node entry.",
		 function );

		return( -1 );
	}
	if( internal_resource_item->resource_node_entry->data_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid resource item - invalid resource node entry - missing data descriptor.",
		 function );

		return( -1 );
	}
	if( internal_resource_item->current_offset < 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid resource item - current offset value out of bounds.",
		 function );

		return( -1 );
	}
	if( ( whence != SEEK_CUR )
	 && ( whence != SEEK_END )
	 && ( whence != SEEK_SET ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported whence.",
		 function );

		return( -1 );
	}
	if( whence == SEEK_CUR )
	{
		offset += internal_resource_item->current_offset;
	}
	else if( whence == SEEK_END )
	{
		offset += internal_resource_item->resource_node_entry->data_descriptor->size;
	}
	if( offset < 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to seek offset.",
		 function );

		return( -1 );
	}
	internal_resource_item->current_offset = offset;

	return( offset );
}

/* Retireves the current offset in the resource item data
 * Returns 1 if successful or -1 on error
 */
int libwrc_resource_item_get_offset(
     libwrc_resource_item_t *resource_item,
     off64_t *offset,
     libcerror_error_t **error )
{
	libwrc_internal_resource_item_t *internal_resource_item = NULL;
	static char *function                                   = "libwrc_resource_item_get_offset";

	if( resource_item == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid resource item.",
		 function );

		return( -1 );
	}
	internal_resource_item = (libwrc_internal_resource_item_t *) resource_item;

	if( internal_resource_item->resource_node_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid resource item - missing resource node entry.",
		 function );

		return( -1 );
	}
	if( internal_resource_item->resource_node_entry->data_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid resource item - invalid resource node entry - missing data descriptor.",
		 function );

		return( -1 );
	}
	if( offset == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid offset.",
		 function );

		return( -1 );
	}
	*offset = internal_resource_item->current_offset;

	return( 1 );
}

/* Retrieves the size of the resource data
 * Returns 1 if successful or -1 on error
 */
int libwrc_resource_item_get_size(
     libwrc_resource_item_t *resource_item,
     uint32_t *size,
     libcerror_error_t **error )
{
	libwrc_internal_resource_item_t *internal_resource_item = NULL;
	static char *function                                   = "libwrc_resource_item_get_size";
	uint32_t safe_size                                      = 0;

	if( resource_item == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid resource item.",
		 function );

		return( -1 );
	}
	internal_resource_item = (libwrc_internal_resource_item_t *) resource_item;

	if( internal_resource_item->resource_node_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid resource item - missing resource node entry.",
		 function );

		return( -1 );
	}
	if( size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid size.",
		 function );

		return( -1 );
	}
	if( internal_resource_item->resource_node_entry->data_descriptor != NULL )
	{
		safe_size = (uint32_t) internal_resource_item->resource_node_entry->data_descriptor->size;
	}
	*size = safe_size;

	return( 1 );
}

/* Retrieves the number of sub items
 * Returns 1 if successful or -1 on error
 */
int libwrc_resource_item_get_number_of_sub_items(
     libwrc_resource_item_t *resource_item,
     int *number_of_sub_items,
     libcerror_error_t **error )
{
	libwrc_internal_resource_item_t *internal_resource_item = NULL;
	static char *function                                   = "libwrc_resource_item_get_number_of_sub_items";

	if( resource_item == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid resource item.",
		 function );

		return( -1 );
	}
	internal_resource_item = (libwrc_internal_resource_item_t *) resource_item;

	if( libcdata_tree_node_get_number_of_sub_nodes(
	     internal_resource_item->resource_node,
	     number_of_sub_items,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of resource sub nodes.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves a specific sub item
 * Returns 1 if successful or -1 on error
 */
int libwrc_resource_item_get_sub_item_by_index(
     libwrc_resource_item_t *resource_item,
     int sub_item_index,
     libwrc_resource_item_t **resource_sub_item,
     libcerror_error_t **error )
{
	libcdata_tree_node_t *resource_sub_node                 = NULL;
	libwrc_internal_resource_item_t *internal_resource_item = NULL;
	static char *function                                   = "libwrc_resource_item_get_sub_item_by_index";

	if( resource_item == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid resource item.",
		 function );

		return( -1 );
	}
	internal_resource_item = (libwrc_internal_resource_item_t *) resource_item;

	if( libcdata_tree_node_get_sub_node_by_index(
	     internal_resource_item->resource_node,
	     sub_item_index,
	     &resource_sub_node,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve resource sub node: %d.",
		 function,
		 sub_item_index );

		return( -1 );
	}
	if( libwrc_resource_item_initialize(
	     resource_sub_item,
	     internal_resource_item->io_handle,
	     internal_resource_item->file_io_handle,
	     resource_sub_node,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create resource sub item.",
		 function );

		return( -1 );
	}
	return( 1 );
}

