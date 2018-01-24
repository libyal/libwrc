/*
 * WEVT map functions
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
#include "libwrc_wevt_map.h"

/* Creates a map
 * Make sure the value map is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libwrc_wevt_map_initialize(
     libwrc_wevt_map_t **map,
     libfwevt_map_t *map_descriptor,
     libcerror_error_t **error )
{
	libwrc_internal_wevt_map_t *internal_map = NULL;
	static char *function                    = "libwrc_wevt_map_initialize";

	if( map == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid map.",
		 function );

		return( -1 );
	}
	if( *map != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid map value already set.",
		 function );

		return( -1 );
	}
	if( map_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid map descriptor.",
		 function );

		return( -1 );
	}
	internal_map = memory_allocate_structure(
	                    libwrc_internal_wevt_map_t );

	if( internal_map == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create map.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     internal_map,
	     0,
	     sizeof( libwrc_internal_wevt_map_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear map.",
		 function );

		goto on_error;
	}
	internal_map->map_descriptor = map_descriptor;

	*map = (libwrc_wevt_map_t *) internal_map;

	return( 1 );

on_error:
	if( internal_map != NULL )
	{
		memory_free(
		 internal_map );
	}
	return( -1 );
}

/* Frees a map
 * Returns 1 if successful or -1 on error
 */
int libwrc_wevt_map_free(
     libwrc_wevt_map_t **map,
     libcerror_error_t **error )
{
	libwrc_internal_wevt_map_t *internal_map = NULL;
	static char *function                    = "libwrc_wevt_map_free";

	if( map == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid map.",
		 function );

		return( -1 );
	}
	if( *map != NULL )
	{
		internal_map = (libwrc_internal_wevt_map_t *) *map;
		*map         = NULL;

		memory_free(
		 internal_map );
	}
	return( 1 );
}

