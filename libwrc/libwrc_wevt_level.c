/*
 * WEVT level functions
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
#include "libwrc_wevt_level.h"

/* Creates a level
 * Make sure the value level is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libwrc_wevt_level_initialize(
     libwrc_wevt_level_t **level,
     libfwevt_level_t *level_descriptor,
     libcerror_error_t **error )
{
	libwrc_internal_wevt_level_t *internal_level = NULL;
	static char *function                        = "libwrc_wevt_level_initialize";

	if( level == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid level.",
		 function );

		return( -1 );
	}
	if( *level != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid level value already set.",
		 function );

		return( -1 );
	}
	if( level_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid level descriptor.",
		 function );

		return( -1 );
	}
	internal_level = memory_allocate_structure(
	                  libwrc_internal_wevt_level_t );

	if( internal_level == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create level.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     internal_level,
	     0,
	     sizeof( libwrc_internal_wevt_level_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear level.",
		 function );

		goto on_error;
	}
	internal_level->level_descriptor = level_descriptor;

	*level = (libwrc_wevt_level_t *) internal_level;

	return( 1 );

on_error:
	if( internal_level != NULL )
	{
		memory_free(
		 internal_level );
	}
	return( -1 );
}

/* Frees a level
 * Returns 1 if successful or -1 on error
 */
int libwrc_wevt_level_free(
     libwrc_wevt_level_t **level,
     libcerror_error_t **error )
{
	libwrc_internal_wevt_level_t *internal_level = NULL;
	static char *function                        = "libwrc_wevt_level_free";

	if( level == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid level.",
		 function );

		return( -1 );
	}
	if( *level != NULL )
	{
		internal_level = (libwrc_internal_wevt_level_t *) *level;
		*level         = NULL;

		memory_free(
		 internal_level );
	}
	return( 1 );
}

