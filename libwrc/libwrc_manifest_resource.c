/*
 * Manifest resource functions
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
#include "libwrc_libcerror.h"
#include "libwrc_libcnotify.h"
#include "libwrc_libuna.h"
#include "libwrc_manifest_resource.h"

/* Creates a manifest resource
 * Make sure the value manifest_resource is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libwrc_manifest_resource_initialize(
     libwrc_manifest_resource_t **manifest_resource,
     libcerror_error_t **error )
{
	libwrc_internal_manifest_resource_t *internal_manifest_resource = NULL;
	static char *function                                           = "libwrc_manifest_resource_initialize";

	if( manifest_resource == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid manifest resource.",
		 function );

		return( -1 );
	}
	if( *manifest_resource != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid manifest resource value already set.",
		 function );

		return( -1 );
	}
	internal_manifest_resource = memory_allocate_structure(
	                              libwrc_internal_manifest_resource_t );

	if( internal_manifest_resource == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create manifest resource.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     internal_manifest_resource,
	     0,
	     sizeof( libwrc_internal_manifest_resource_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear manifest resource.",
		 function );

		goto on_error;
	}
	*manifest_resource = (libwrc_manifest_resource_t *) internal_manifest_resource;

	return( 1 );

on_error:
	if( internal_manifest_resource != NULL )
	{
		memory_free(
		 internal_manifest_resource );
	}
	return( -1 );
}

/* Frees a manifest resource
 * Returns 1 if successful or -1 on error
 */
int libwrc_manifest_resource_free(
     libwrc_manifest_resource_t **manifest_resource,
     libcerror_error_t **error )
{
	libwrc_internal_manifest_resource_t *internal_manifest_resource = NULL;
	static char *function                                           = "libwrc_manifest_resource_free";

	if( manifest_resource == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid manifest resource.",
		 function );

		return( -1 );
	}
	if( *manifest_resource != NULL )
	{
		internal_manifest_resource = (libwrc_internal_manifest_resource_t *) *manifest_resource;
		*manifest_resource         = NULL;

		if( internal_manifest_resource->string != NULL )
		{
			memory_free(
			 internal_manifest_resource->string );
		}
		memory_free(
		 internal_manifest_resource );
	}
	return( 1 );
}

/* Reads the manifest resource
 * Returns 1 if successful or -1 on error
 */
int libwrc_manifest_resource_read(
     libwrc_manifest_resource_t *manifest_resource,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error )
{
	libwrc_internal_manifest_resource_t *internal_manifest_resource = NULL;
	static char *function                                           = "libwrc_manifest_resource_read";

	if( manifest_resource == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid manifest resource.",
		 function );

		return( -1 );
	}
	internal_manifest_resource = (libwrc_internal_manifest_resource_t *) manifest_resource;

	if( internal_manifest_resource->string != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid manifest resource - string value already set.",
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
	if( ( data_size == 0 )
	 || ( data_size > (size_t) MEMORY_MAXIMUM_ALLOCATION_SIZE ) )
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
	internal_manifest_resource->string = (uint8_t *) memory_allocate(
	                                                  sizeof( uint8_t ) * data_size );

	if( internal_manifest_resource->string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create string.",
		 function );

		goto on_error;
	}
	internal_manifest_resource->string_size = data_size;

	if( memory_copy(
	     internal_manifest_resource->string,
	     data,
	     data_size ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy data to string.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( internal_manifest_resource->string != NULL )
	{
		memory_free(
		 internal_manifest_resource->string );

		internal_manifest_resource->string = NULL;
	}
	internal_manifest_resource->string_size = 0;

	return( -1 );
}

/* Retrieves the size of a specific UTF-8 formatted string
 * Returns 1 if successful or -1 on error
 */
int libwrc_manifest_resource_get_utf8_string_size(
     libwrc_manifest_resource_t *manifest_resource,
     size_t *utf8_string_size,
     libcerror_error_t **error )
{
	libwrc_internal_manifest_resource_t *internal_manifest_resource = NULL;
	static char *function                                           = "libwrc_manifest_resource_get_utf8_string_size";

	if( manifest_resource == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid manifest resource.",
		 function );

		return( -1 );
	}
	internal_manifest_resource = (libwrc_internal_manifest_resource_t *) manifest_resource;

	if( libuna_utf8_string_size_from_utf8_stream(
	     internal_manifest_resource->string,
	     internal_manifest_resource->string_size,
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

/* Retrieves a specific UTF-8 formatted string
 * Returns 1 if successful or -1 on error
 */
int libwrc_manifest_resource_get_utf8_string(
     libwrc_manifest_resource_t *manifest_resource,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error )
{
	libwrc_internal_manifest_resource_t *internal_manifest_resource = NULL;
	static char *function                                           = "libwrc_manifest_resource_get_utf8_string";

	if( manifest_resource == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid manifest resource.",
		 function );

		return( -1 );
	}
	internal_manifest_resource = (libwrc_internal_manifest_resource_t *) manifest_resource;

	if( libuna_utf8_string_copy_from_utf8_stream(
	     utf8_string,
	     utf8_string_size,
	     internal_manifest_resource->string,
	     internal_manifest_resource->string_size,
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

/* Retrieves the size of a specific UTF-16 formatted string
 * Returns 1 if successful or -1 on error
 */
int libwrc_manifest_resource_get_utf16_string_size(
     libwrc_manifest_resource_t *manifest_resource,
     size_t *utf16_string_size,
     libcerror_error_t **error )
{
	libwrc_internal_manifest_resource_t *internal_manifest_resource = NULL;
	static char *function                                           = "libwrc_manifest_resource_get_utf16_string_size";

	if( manifest_resource == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid manifest resource.",
		 function );

		return( -1 );
	}
	internal_manifest_resource = (libwrc_internal_manifest_resource_t *) manifest_resource;

	if( libuna_utf16_string_size_from_utf8_stream(
	     internal_manifest_resource->string,
	     internal_manifest_resource->string_size,
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

/* Retrieves a specific UTF-16 formatted string
 * Returns 1 if successful or -1 on error
 */
int libwrc_manifest_resource_get_utf16_string(
     libwrc_manifest_resource_t *manifest_resource,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error )
{
	libwrc_internal_manifest_resource_t *internal_manifest_resource = NULL;
	static char *function                                           = "libwrc_manifest_resource_get_utf16_string";

	if( manifest_resource == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid manifest resource.",
		 function );

		return( -1 );
	}
	internal_manifest_resource = (libwrc_internal_manifest_resource_t *) manifest_resource;

	if( libuna_utf16_string_copy_from_utf8_stream(
	     utf16_string,
	     utf16_string_size,
	     internal_manifest_resource->string,
	     internal_manifest_resource->string_size,
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

