/*
 * WEVT template definition functions
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

#include "libwrc_definitions.h"
#include "libwrc_libcerror.h"
#include "libwrc_libfwevt.h"
#include "libwrc_types.h"
#include "libwrc_wevt_template_definition.h"

/* Creates a template definition
 * Make sure the value template_definition is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libwrc_wevt_template_definition_initialize(
     libwrc_wevt_template_definition_t **template_definition,
     libfwevt_template_t *template_descriptor,
     libcerror_error_t **error )
{
	libwrc_internal_wevt_template_definition_t *internal_template_definition = NULL;
	static char *function                                                    = "libwrc_wevt_template_definition_initialize";

	if( template_definition == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid template definition.",
		 function );

		return( -1 );
	}
	if( *template_definition != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid template definition value already set.",
		 function );

		return( -1 );
	}
	if( template_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid template descriptor.",
		 function );

		return( -1 );
	}
	internal_template_definition = memory_allocate_structure(
	                                libwrc_internal_wevt_template_definition_t );

	if( internal_template_definition == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create template definition.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     internal_template_definition,
	     0,
	     sizeof( libwrc_internal_wevt_template_definition_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear template definition.",
		 function );

		goto on_error;
	}
	internal_template_definition->template_descriptor = template_descriptor;

	*template_definition = (libwrc_wevt_template_definition_t *) internal_template_definition;

	return( 1 );

on_error:
	if( internal_template_definition != NULL )
	{
		memory_free(
		 internal_template_definition );
	}
	return( -1 );
}

/* Frees a template definition
 * Returns 1 if successful or -1 on error
 */
int libwrc_wevt_template_definition_free(
     libwrc_wevt_template_definition_t **template_definition,
     libcerror_error_t **error )
{
	libwrc_internal_wevt_template_definition_t *internal_template_definition = NULL;
	static char *function                                                    = "libwrc_wevt_template_definition_free";

	if( template_definition == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid template definition.",
		 function );

		return( -1 );
	}
	if( *template_definition != NULL )
	{
		internal_template_definition = (libwrc_internal_wevt_template_definition_t *) *template_definition;
		*template_definition         = NULL;

		memory_free(
		 internal_template_definition );
	}
	return( 1 );
}

/* Retrieves the data
 * Returns 1 if successful or -1 on error
 */
int libwrc_wevt_template_definition_get_data(
     libwrc_wevt_template_definition_t *template_definition,
     uint8_t *data,
     size_t data_size,
     libcerror_error_t **error )
{
	libwrc_internal_wevt_template_definition_t *internal_template_definition = NULL;
	const uint8_t *template_data                                             = NULL;
	static char *function                                                    = "libwrc_wevt_template_definition_get_data";
	size_t template_data_size                                                = 0;

	if( template_definition == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid template definition.",
		 function );

		return( -1 );
	}
	internal_template_definition = (libwrc_internal_wevt_template_definition_t *) template_definition;

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
	if( data_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid data size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( libfwevt_template_get_data(
	     internal_template_definition->template_descriptor,
	     &template_data,
	     &template_data_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve data.",
		 function );

		return( -1 );
	}
	if( data_size < template_data_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: invalid data value too small.",
		 function );

		return( -1 );
	}
	if( memory_copy(
	     data,
	     template_data,
	     template_data_size ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy data.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the offset
 * Returns 1 if successful or -1 on error
 */
int libwrc_wevt_template_definition_get_offset(
     libwrc_wevt_template_definition_t *template_definition,
     uint32_t *offset,
     libcerror_error_t **error )
{
	libwrc_internal_wevt_template_definition_t *internal_template_definition = NULL;
	static char *function                                                    = "libwrc_wevt_template_definition_get_offset";

	if( template_definition == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid template definition.",
		 function );

		return( -1 );
	}
	internal_template_definition = (libwrc_internal_wevt_template_definition_t *) template_definition;

	if( libfwevt_template_get_offset(
	     internal_template_definition->template_descriptor,
	     offset,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve offest.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the size
 * Returns 1 if successful or -1 on error
 */
int libwrc_wevt_template_definition_get_size(
     libwrc_wevt_template_definition_t *template_definition,
     size_t *size,
     libcerror_error_t **error )
{
	libwrc_internal_wevt_template_definition_t *internal_template_definition = NULL;
	static char *function                                                    = "libwrc_wevt_template_definition_get_size";

	if( template_definition == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid template definition.",
		 function );

		return( -1 );
	}
	internal_template_definition = (libwrc_internal_wevt_template_definition_t *) template_definition;

	if( libfwevt_template_get_size(
	     internal_template_definition->template_descriptor,
	     (uint32_t *) size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve size.",
		 function );

		return( -1 );
	}
	return( 1 );
}

