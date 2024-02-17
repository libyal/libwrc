/*
 * Manifest values functions
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
#include "libwrc_manifest_values.h"

/* Reads manifest values
 * Returns 1 if successful or -1 on error
 */
int libwrc_manifest_values_read(
     libwrc_language_entry_t *language_entry,
     libwrc_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     libwrc_data_descriptor_t *data_descriptor,
     libcerror_error_t **error )
{
	libfvalue_value_t *manifest_value = NULL;
	uint8_t *resource_data            = NULL;
	static char *function             = "libwrc_manifest_values_read";
	off64_t file_offset               = 0;
	size_t resource_data_size         = 0;
	ssize_t read_count                = 0;
	int value_index                   = 0;

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
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: resource data:\n",
		 function );
		libcnotify_print_data(
		 resource_data,
		 resource_data_size,
		 0 );
	}
#endif
	if( libfvalue_value_type_initialize(
	     &manifest_value,
	     LIBFVALUE_VALUE_TYPE_STRING_UTF8,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create manifest value.",
		 function );

		goto on_error;
	}
	if( libfvalue_value_set_data(
	     manifest_value,
	     resource_data,
	     resource_data_size,
	     LIBFVALUE_CODEPAGE_UTF8,
	     LIBFVALUE_VALUE_DATA_FLAG_MANAGED,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set data of manifest value.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: manifest string:\n",
		 function );

		if( libfvalue_value_print(
		     manifest_value,
		     0,
		     0,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
			 "%s: unable to print manifest value.",
			 function );

			goto on_error;
		}
		libcnotify_printf(
		 "\n\n" );
	}
#endif
	if( libwrc_language_entry_append_value(
	     language_entry,
	     &value_index,
	     (intptr_t *) manifest_value,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
		 "%s: unable to append manifest value.",
		 function );

		goto on_error;
	}
	manifest_value = NULL;

	memory_free(
	 resource_data );

	return( 1 );

on_error:
	if( manifest_value != NULL )
	{
		libfvalue_value_free(
		 &manifest_value,
		 NULL );
	}
	if( resource_data != NULL )
	{
		memory_free(
		 resource_data );
	}
	return( -1 );
}

