/*
 * Data descriptor functions
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
#include "libwrc_libbfio.h"
#include "libwrc_libcerror.h"
#include "libwrc_libcnotify.h"

#include "wrc_data_descriptor.h"

/* Creates a data descriptor
 * Make sure the value data_descriptor is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libwrc_data_descriptor_initialize(
     libwrc_data_descriptor_t **data_descriptor,
     libcerror_error_t **error )
{
	static char *function = "libwrc_data_descriptor_initialize";

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
	if( *data_descriptor != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid data descriptor value already set.",
		 function );

		return( -1 );
	}
	*data_descriptor = memory_allocate_structure(
	                    libwrc_data_descriptor_t );

	if( *data_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create data descriptor.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *data_descriptor,
	     0,
	     sizeof( libwrc_data_descriptor_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear data descriptor.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *data_descriptor != NULL )
	{
		memory_free(
		 *data_descriptor );

		*data_descriptor = NULL;
	}
	return( -1 );
}

/* Frees a data descriptor
 * Returns 1 if successful or -1 on error
 */
int libwrc_data_descriptor_free(
     libwrc_data_descriptor_t **data_descriptor,
     libcerror_error_t **error )
{
	static char *function = "libwrc_data_descriptor_free";

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
	if( *data_descriptor != NULL )
	{
		memory_free(
		 *data_descriptor );

		*data_descriptor = NULL;
	}
	return( 1 );
}

/* Reads the data descriptor data
 * Returns 1 if successful or -1 on error
 */
int libwrc_data_descriptor_read_data(
     libwrc_data_descriptor_t *data_descriptor,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error )
{
	static char *function = "libwrc_data_descriptor_read_data";

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
	if( ( data_size < 8 )
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
		 "%s: data descriptor data:\n",
		 function );
		libcnotify_print_data(
		 data,
		 sizeof( wrc_data_descriptor_t ),
		 0 );
	}
#endif
	byte_stream_copy_to_uint32_little_endian(
	 ( (wrc_data_descriptor_t *) data )->virtual_address,
	 data_descriptor->virtual_address );

	byte_stream_copy_to_uint32_little_endian(
	 ( (wrc_data_descriptor_t *) data )->size,
	 data_descriptor->size );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: virtual address\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 data_descriptor->virtual_address );

		libcnotify_printf(
		 "%s: size\t\t\t\t\t: %" PRIu32 "\n",
		 function,
		 data_descriptor->size );

		libcnotify_printf(
		 "\n" );
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	return( 1 );
}

/* Reads the data descriptor
 * Returns 1 if successful or -1 on error
 */
int libwrc_data_descriptor_read_file_io_handle(
     libwrc_data_descriptor_t *data_descriptor,
     libbfio_handle_t *file_io_handle,
     off64_t file_offset,
     libcerror_error_t **error )
{
	uint8_t data_descriptor_data[ sizeof( wrc_data_descriptor_t ) ];

	static char *function = "libwrc_data_descriptor_read_file_io_handle";
	ssize_t read_count    = 0;

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
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading data descriptor at offset: %" PRIi64 " (0x%08" PRIx64 ")\n",
		 function,
		 file_offset,
		 file_offset );
	}
#endif
	read_count = libbfio_handle_read_buffer_at_offset(
	              file_io_handle,
	              data_descriptor_data,
	              sizeof( wrc_data_descriptor_t ),
	              file_offset,
	              error );

	if( read_count != (ssize_t) sizeof( wrc_data_descriptor_t ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read data descriptor data at offset: %" PRIi64 " (0x%08" PRIx64 ").",
		 function,
		 file_offset,
		 file_offset );

		return( -1 );
	}
	if( libwrc_data_descriptor_read_data(
	     data_descriptor,
	     data_descriptor_data,
	     sizeof( wrc_data_descriptor_t ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read data descriptor.",
		 function );

		return( -1 );
	}
	return( 1 );
}

