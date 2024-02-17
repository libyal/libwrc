/*
 * Resource node header functions
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

#include "libwrc_libbfio.h"
#include "libwrc_libcerror.h"
#include "libwrc_libcnotify.h"
#include "libwrc_resource_node_header.h"

#include "wrc_resource_node.h"

/* Creates a table entry
 * Make sure the value resource_node_header is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libwrc_resource_node_header_initialize(
     libwrc_resource_node_header_t **resource_node_header,
     libcerror_error_t **error )
{
	static char *function = "libwrc_resource_node_header_initialize";

	if( resource_node_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid table entry.",
		 function );

		return( -1 );
	}
	if( *resource_node_header != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid table entry value already set.",
		 function );

		return( -1 );
	}
	*resource_node_header = memory_allocate_structure(
	                         libwrc_resource_node_header_t );

	if( *resource_node_header == NULL )
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
	     *resource_node_header,
	     0,
	     sizeof( libwrc_resource_node_header_t ) ) == NULL )
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
	if( *resource_node_header != NULL )
	{
		memory_free(
		 *resource_node_header );

		*resource_node_header = NULL;
	}
	return( -1 );
}

/* Frees a table entry
 * Returns 1 if successful or -1 on error
 */
int libwrc_resource_node_header_free(
     libwrc_resource_node_header_t **resource_node_header,
     libcerror_error_t **error )
{
	static char *function = "libwrc_resource_node_header_free";

	if( resource_node_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid table entry.",
		 function );

		return( -1 );
	}
	if( *resource_node_header != NULL )
	{
		memory_free(
		 *resource_node_header );

		*resource_node_header = NULL;
	}
	return( 1 );
}

/* Reads the resource node header data
 * Returns 1 if successful or -1 on error
 */
int libwrc_resource_node_header_read_data(
     libwrc_resource_node_header_t *resource_node_header,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error )
{
	static char *function = "libwrc_resource_node_header_read_data";

#if defined( HAVE_DEBUG_OUTPUT )
	uint32_t value_32bit  = 0;
	uint16_t value_16bit  = 0;
#endif

	if( resource_node_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid resource node header.",
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
	if( ( data_size < sizeof( wrc_resource_node_header_t ) )
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
		 "%s: resource node header data:\n",
		 function );
		libcnotify_print_data(
		 data,
		 sizeof( wrc_resource_node_header_t ),
		 0 );
	}
#endif
	byte_stream_copy_to_uint32_little_endian(
	 ( (wrc_resource_node_header_t *) data )->flags,
	 resource_node_header->flags );

	byte_stream_copy_to_uint16_little_endian(
	 ( (wrc_resource_node_header_t *) data )->number_of_named_entries,
	 resource_node_header->number_of_named_entries );

	byte_stream_copy_to_uint16_little_endian(
	 ( (wrc_resource_node_header_t *) data )->number_of_unnamed_entries,
	 resource_node_header->number_of_unnamed_entries );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: flags\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 resource_node_header->flags );

/* TODO print meaning of flags */

		byte_stream_copy_to_uint32_little_endian(
		 ( (wrc_resource_node_header_t *) data )->flags,
		 value_32bit );
		libcnotify_printf(
		 "%s: creation time\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint16_little_endian(
		 ( (wrc_resource_node_header_t *) data )->major_version,
		 value_16bit );
		libcnotify_printf(
		 "%s: major version\t\t\t: %" PRIu16 "\n",
		 function,
		 value_16bit );

		byte_stream_copy_to_uint16_little_endian(
		 ( (wrc_resource_node_header_t *) data )->minor_version,
		 value_16bit );
		libcnotify_printf(
		 "%s: minor version\t\t\t: %" PRIu16 "\n",
		 function,
		 value_16bit );

		libcnotify_printf(
		 "%s: number of named entries\t\t: %" PRIu16 "\n",
		 function,
		 resource_node_header->number_of_named_entries );

		libcnotify_printf(
		 "%s: number of unnamed entries\t: %" PRIu16 "\n",
		 function,
		 resource_node_header->number_of_unnamed_entries );

		libcnotify_printf(
		 "\n" );
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	if( resource_node_header->flags != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported flags: 0x%08" PRIx32 ".",
		 function,
		 resource_node_header->flags );

		return( -1 );
	}
	return( 1 );
}

/* Reads the resource node header
 * Returns 1 if successful or -1 on error
 */
int libwrc_resource_node_header_read_file_io_handle(
     libwrc_resource_node_header_t *resource_node_header,
     libbfio_handle_t *file_io_handle,
     off64_t file_offset,
     libcerror_error_t **error )
{
	uint8_t resource_node_header_data[ sizeof( wrc_resource_node_header_t ) ];

	static char *function = "libwrc_resource_node_header_read_file_io_handle";
	ssize_t read_count    = 0;

	if( resource_node_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid resource node header.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading resource node header at offset: %" PRIi64 " (0x%08" PRIx64 ")\n",
		 function,
		 file_offset,
		 file_offset );
	}
#endif
	read_count = libbfio_handle_read_buffer_at_offset(
	              file_io_handle,
	              resource_node_header_data,
	              sizeof( wrc_resource_node_header_t ),
	              file_offset,
	              error );

	if( read_count != (ssize_t) sizeof( wrc_resource_node_header_t ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read resource node header data at offset: %" PRIi64 " (0x%08" PRIx64 ").",
		 function,
		 file_offset,
		 file_offset );

		return( -1 );
	}
	if( libwrc_resource_node_header_read_data(
	     resource_node_header,
	     resource_node_header_data,
	     sizeof( wrc_resource_node_header_t ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read resource node header.",
		 function );

		return( -1 );
	}
	return( 1 );
}

