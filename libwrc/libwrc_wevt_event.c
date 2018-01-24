/*
 * WEVT event functions
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
#include "libwrc_wevt_event.h"
#include "libwrc_wevt_template_definition.h"

/* Creates an event
 * Make sure the value event is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libwrc_wevt_event_initialize(
     libwrc_wevt_event_t **event,
     libfwevt_provider_t *provider_descriptor,
     libfwevt_event_t *event_descriptor,
     libcerror_error_t **error )
{
	libwrc_internal_wevt_event_t *internal_event = NULL;
	static char *function                        = "libwrc_wevt_event_initialize";

	if( event == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid event.",
		 function );

		return( -1 );
	}
	if( *event != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid event value already set.",
		 function );

		return( -1 );
	}
	if( event_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid event descriptor.",
		 function );

		return( -1 );
	}
	internal_event = memory_allocate_structure(
	                  libwrc_internal_wevt_event_t );

	if( internal_event == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create event.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     internal_event,
	     0,
	     sizeof( libwrc_internal_wevt_event_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear event.",
		 function );

		goto on_error;
	}
	internal_event->provider_descriptor = provider_descriptor;
	internal_event->event_descriptor    = event_descriptor;

	*event = (libwrc_wevt_event_t *) internal_event;

	return( 1 );

on_error:
	if( internal_event != NULL )
	{
		memory_free(
		 internal_event );
	}
	return( -1 );
}

/* Frees an event
 * Returns 1 if successful or -1 on error
 */
int libwrc_wevt_event_free(
     libwrc_wevt_event_t **event,
     libcerror_error_t **error )
{
	libwrc_internal_wevt_event_t *internal_event = NULL;
	static char *function                        = "libwrc_wevt_event_free";

	if( event == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid event.",
		 function );

		return( -1 );
	}
	if( *event != NULL )
	{
		internal_event = (libwrc_internal_wevt_event_t *) *event;
		*event         = NULL;

		memory_free(
		 internal_event );
	}
	return( 1 );
}

/* Retrieves the identifier
 * Returns 1 if successful or -1 on error
 */
int libwrc_wevt_event_get_identifier(
     libwrc_wevt_event_t *event,
     uint32_t *identifier,
     libcerror_error_t **error )
{
	libwrc_internal_wevt_event_t *internal_event = NULL;
	static char *function                        = "libwrc_wevt_event_get_identifier";

	if( event == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid event.",
		 function );

		return( -1 );
	}
	internal_event = (libwrc_internal_wevt_event_t *) event;

	if( libfwevt_event_get_identifier(
	     internal_event->event_descriptor,
	     identifier,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve identifier.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the message identifier
 * Returns 1 if successful or -1 on error
 */
int libwrc_wevt_event_get_message_identifier(
     libwrc_wevt_event_t *event,
     uint32_t *message_identifier,
     libcerror_error_t **error )
{
	libwrc_internal_wevt_event_t *internal_event = NULL;
	static char *function                        = "libwrc_wevt_event_get_message_identifier";

	if( event == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid event.",
		 function );

		return( -1 );
	}
	internal_event = (libwrc_internal_wevt_event_t *) event;

	if( libfwevt_event_get_message_identifier(
	     internal_event->event_descriptor,
	     message_identifier,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve message identifier.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the template definition
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libwrc_wevt_event_get_template_definition(
     libwrc_wevt_event_t *event,
     libwrc_wevt_template_definition_t **template_definition,
     libcerror_error_t **error )
{
	libwrc_internal_wevt_event_t *internal_event = NULL;
	libfwevt_template_t *template_descriptor     = NULL;
	static char *function                        = "libwrc_wevt_event_get_template_definition";
	uint32_t template_offset                     = 0;
	int result                                   = 0;

	if( event == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid event.",
		 function );

		return( -1 );
	}
	internal_event = (libwrc_internal_wevt_event_t *) event;

	if( libfwevt_event_get_template_offset(
	     internal_event->event_descriptor,
	     &template_offset,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve template offset.",
		 function );

		return( -1 );
	}
	if( template_offset != 0 )
	{
		result = libfwevt_provider_get_template_by_offset(
			  internal_event->provider_descriptor,
			  template_offset,
			  &template_descriptor,
			  error );

		if( result == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve template by offset.",
			 function );

			return( -1 );
		}
		else if( result != 0 )
		{
			if( libwrc_wevt_template_definition_initialize(
			     template_definition,
			     template_descriptor,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
				 "%s: unable to create template definition.",
				 function );

				return( -1 );
			}
		}
	}
	return( result );
}

