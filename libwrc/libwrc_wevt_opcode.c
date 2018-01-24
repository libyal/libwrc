/*
 * WEVT opcode functions
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
#include "libwrc_wevt_opcode.h"

/* Creates an opcode
 * Make sure the value opcode is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libwrc_wevt_opcode_initialize(
     libwrc_wevt_opcode_t **opcode,
     libfwevt_opcode_t *opcode_descriptor,
     libcerror_error_t **error )
{
	libwrc_internal_wevt_opcode_t *internal_opcode = NULL;
	static char *function                          = "libwrc_wevt_opcode_initialize";

	if( opcode == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid opcode.",
		 function );

		return( -1 );
	}
	if( *opcode != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid opcode value already set.",
		 function );

		return( -1 );
	}
	if( opcode_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid opcode descriptor.",
		 function );

		return( -1 );
	}
	internal_opcode = memory_allocate_structure(
	                   libwrc_internal_wevt_opcode_t );

	if( internal_opcode == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create opcode.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     internal_opcode,
	     0,
	     sizeof( libwrc_internal_wevt_opcode_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear opcode.",
		 function );

		goto on_error;
	}
	internal_opcode->opcode_descriptor = opcode_descriptor;

	*opcode = (libwrc_wevt_opcode_t *) internal_opcode;

	return( 1 );

on_error:
	if( internal_opcode != NULL )
	{
		memory_free(
		 internal_opcode );
	}
	return( -1 );
}

/* Frees an opcode
 * Returns 1 if successful or -1 on error
 */
int libwrc_wevt_opcode_free(
     libwrc_wevt_opcode_t **opcode,
     libcerror_error_t **error )
{
	libwrc_internal_wevt_opcode_t *internal_opcode = NULL;
	static char *function                          = "libwrc_wevt_opcode_free";

	if( opcode == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid opcode.",
		 function );

		return( -1 );
	}
	if( *opcode != NULL )
	{
		internal_opcode = (libwrc_internal_wevt_opcode_t *) *opcode;
		*opcode         = NULL;

		memory_free(
		 internal_opcode );
	}
	return( 1 );
}

