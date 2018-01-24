/*
 * WEVT channel functions
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
#include "libwrc_wevt_channel.h"

/* Creates a channel
 * Make sure the value channel is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libwrc_wevt_channel_initialize(
     libwrc_wevt_channel_t **channel,
     libfwevt_channel_t *channel_descriptor,
     libcerror_error_t **error )
{
	libwrc_internal_wevt_channel_t *internal_channel = NULL;
	static char *function                            = "libwrc_wevt_channel_initialize";

	if( channel == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid channel.",
		 function );

		return( -1 );
	}
	if( *channel != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid channel value already set.",
		 function );

		return( -1 );
	}
	if( channel_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid channel descriptor.",
		 function );

		return( -1 );
	}
	internal_channel = memory_allocate_structure(
	                    libwrc_internal_wevt_channel_t );

	if( internal_channel == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create channel.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     internal_channel,
	     0,
	     sizeof( libwrc_internal_wevt_channel_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear channel.",
		 function );

		goto on_error;
	}
	internal_channel->channel_descriptor = channel_descriptor;

	*channel = (libwrc_wevt_channel_t *) internal_channel;

	return( 1 );

on_error:
	if( internal_channel != NULL )
	{
		memory_free(
		 internal_channel );
	}
	return( -1 );
}

/* Frees a channel
 * Returns 1 if successful or -1 on error
 */
int libwrc_wevt_channel_free(
     libwrc_wevt_channel_t **channel,
     libcerror_error_t **error )
{
	libwrc_internal_wevt_channel_t *internal_channel = NULL;
	static char *function                            = "libwrc_wevt_channel_free";

	if( channel == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid channel.",
		 function );

		return( -1 );
	}
	if( *channel != NULL )
	{
		internal_channel = (libwrc_internal_wevt_channel_t *) *channel;
		*channel         = NULL;

		memory_free(
		 internal_channel );
	}
	return( 1 );
}

