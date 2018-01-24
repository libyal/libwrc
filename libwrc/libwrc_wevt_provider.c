/*
 * WEVT provider functions
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
#include <byte_stream.h>
#include <memory.h>
#include <types.h>

#include "libwrc_definitions.h"
#include "libwrc_libcdata.h"
#include "libwrc_libcerror.h"
#include "libwrc_libfwevt.h"
#include "libwrc_types.h"
#include "libwrc_wevt_event.h"
#include "libwrc_wevt_provider.h"

/* Creates a provider
 * Make sure the value provider is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libwrc_wevt_provider_initialize(
     libwrc_wevt_provider_t **provider,
     libfwevt_provider_t *provider_descriptor,
     libcerror_error_t **error )
{
	libwrc_internal_wevt_provider_t *internal_provider = NULL;
	static char *function                              = "libwrc_wevt_provider_initialize";

	if( provider == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid provider.",
		 function );

		return( -1 );
	}
	if( *provider != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid provider value already set.",
		 function );

		return( -1 );
	}
	if( provider_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid provider descriptor.",
		 function );

		return( -1 );
	}
	internal_provider = memory_allocate_structure(
	                     libwrc_internal_wevt_provider_t );

	if( internal_provider == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create provider.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     internal_provider,
	     0,
	     sizeof( libwrc_internal_wevt_provider_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear provider.",
		 function );

		goto on_error;
	}
	internal_provider->provider_descriptor = provider_descriptor;

	*provider = (libwrc_wevt_provider_t *) internal_provider;

	return( 1 );

on_error:
	if( internal_provider != NULL )
	{
		memory_free(
		 internal_provider );
	}
	return( -1 );
}

/* Frees a provider
 * Returns 1 if successful or -1 on error
 */
int libwrc_wevt_provider_free(
     libwrc_wevt_provider_t **provider,
     libcerror_error_t **error )
{
	libwrc_internal_wevt_provider_t *internal_provider = NULL;
	static char *function                              = "libwrc_wevt_provider_free";

	if( provider == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid provider.",
		 function );

		return( -1 );
	}
	if( *provider != NULL )
	{
		internal_provider = (libwrc_internal_wevt_provider_t *) *provider;
		*provider         = NULL;

		memory_free(
		 internal_provider );
	}
	return( 1 );
}

/* Retrieves the number of events
 * Returns 1 if successful or -1 on error
 */
int libwrc_wevt_provider_get_number_of_events(
     libwrc_wevt_provider_t *provider,
     int *number_of_events,
     libcerror_error_t **error )
{
	libwrc_internal_wevt_provider_t *internal_provider = NULL;
	static char *function                              = "libwrc_wevt_provider_get_number_of_events";

	if( provider == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid provider.",
		 function );

		return( -1 );
	}
	internal_provider = (libwrc_internal_wevt_provider_t *) provider;

	if( libfwevt_provider_get_number_of_events(
	     internal_provider->provider_descriptor,
	     number_of_events,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of events.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves a specific event
 * Returns 1 if successful or -1 on error
 */
int libwrc_wevt_provider_get_event(
     libwrc_wevt_provider_t *provider,
     int event_index,
     libwrc_wevt_event_t **event,
     libcerror_error_t **error )
{
	libwrc_internal_wevt_provider_t *internal_provider = NULL;
	libfwevt_event_t *event_descriptor                 = NULL;
	static char *function                              = "libwrc_wevt_provider_get_event";

	if( provider == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid provider.",
		 function );

		return( -1 );
	}
	internal_provider = (libwrc_internal_wevt_provider_t *) provider;

	if( libfwevt_provider_get_event(
	     internal_provider->provider_descriptor,
	     event_index,
	     &event_descriptor,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve event: %d.",
		 function,
		 event_index );

		return( -1 );
	}
	if( libwrc_wevt_event_initialize(
	     event,
	     internal_provider->provider_descriptor,
	     event_descriptor,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create event.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves a specific event by identifier
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libwrc_wevt_provider_get_event_by_identifier(
     libwrc_wevt_provider_t *provider,
     uint32_t event_identifier,
     libwrc_wevt_event_t **event,
     libcerror_error_t **error )
{
	libwrc_internal_wevt_provider_t *internal_provider = NULL;
	libfwevt_event_t *event_descriptor                 = NULL;
	static char *function                              = "libwrc_wevt_provider_get_event_by_identifier";
	int result                                         = 0;

	if( provider == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid provider.",
		 function );

		return( -1 );
	}
	internal_provider = (libwrc_internal_wevt_provider_t *) provider;

	result = libfwevt_provider_get_event_by_identifier(
	          internal_provider->provider_descriptor,
	          event_identifier,
	          &event_descriptor,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve event.",
		 function );

		return( -1 );
	}
	else if( result != 0 )
	{
		if( libwrc_wevt_event_initialize(
		     event,
		     internal_provider->provider_descriptor,
		     event_descriptor,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create event.",
			 function );

			return( -1 );
		}
	}
	return( result );
}

