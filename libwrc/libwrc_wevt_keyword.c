/*
 * WEVT keyword functions
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
#include "libwrc_wevt_keyword.h"

/* Creates a keyword
 * Make sure the value keyword is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libwrc_wevt_keyword_initialize(
     libwrc_wevt_keyword_t **keyword,
     libfwevt_keyword_t *keyword_descriptor,
     libcerror_error_t **error )
{
	libwrc_internal_wevt_keyword_t *internal_keyword = NULL;
	static char *function                            = "libwrc_wevt_keyword_initialize";

	if( keyword == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid keyword.",
		 function );

		return( -1 );
	}
	if( *keyword != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid keyword value already set.",
		 function );

		return( -1 );
	}
	if( keyword_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid keyword descriptor.",
		 function );

		return( -1 );
	}
	internal_keyword = memory_allocate_structure(
	                    libwrc_internal_wevt_keyword_t );

	if( internal_keyword == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create keyword.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     internal_keyword,
	     0,
	     sizeof( libwrc_internal_wevt_keyword_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear keyword.",
		 function );

		goto on_error;
	}
	internal_keyword->keyword_descriptor = keyword_descriptor;

	*keyword = (libwrc_wevt_keyword_t *) internal_keyword;

	return( 1 );

on_error:
	if( internal_keyword != NULL )
	{
		memory_free(
		 internal_keyword );
	}
	return( -1 );
}

/* Frees a keyword
 * Returns 1 if successful or -1 on error
 */
int libwrc_wevt_keyword_free(
     libwrc_wevt_keyword_t **keyword,
     libcerror_error_t **error )
{
	libwrc_internal_wevt_keyword_t *internal_keyword = NULL;
	static char *function                            = "libwrc_wevt_keyword_free";

	if( keyword == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid keyword.",
		 function );

		return( -1 );
	}
	if( *keyword != NULL )
	{
		internal_keyword = (libwrc_internal_wevt_keyword_t *) *keyword;
		*keyword         = NULL;

		memory_free(
		 internal_keyword );
	}
	return( 1 );
}

