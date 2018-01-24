/*
 * Data descriptor functions
 *
 * Copyright (C) 2011-2018, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this software.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <common.h>
#include <memory.h>
#include <types.h>

#include "libwrc_data_descriptor.h"
#include "libwrc_libcerror.h"

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

