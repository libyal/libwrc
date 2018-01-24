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

#if !defined( _LIBWRC_INTERNAL_WEVT_EVENT_H )
#define _LIBWRC_INTERNAL_WEVT_EVENT_H

#include <common.h>
#include <types.h>

#include "libwrc_extern.h"
#include "libwrc_libcerror.h"
#include "libwrc_libfwevt.h"
#include "libwrc_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libwrc_internal_wevt_event libwrc_internal_wevt_event_t;

struct libwrc_internal_wevt_event
{
	/* The provider descriptor
	 */
	libfwevt_provider_t *provider_descriptor;

	/* The event descriptor
	 */
	libfwevt_event_t *event_descriptor;
};

int libwrc_wevt_event_initialize(
     libwrc_wevt_event_t **event,
     libfwevt_provider_t *provider_descriptor,
     libfwevt_event_t *event_descriptor,
     libcerror_error_t **error );

LIBWRC_EXTERN \
int libwrc_wevt_event_free(
     libwrc_wevt_event_t **event,
     libcerror_error_t **error );

LIBWRC_EXTERN \
int libwrc_wevt_event_get_identifier(
     libwrc_wevt_event_t *event,
     uint32_t *identifier,
     libcerror_error_t **error );

LIBWRC_EXTERN \
int libwrc_wevt_event_get_message_identifier(
     libwrc_wevt_event_t *event,
     uint32_t *message_identifier,
     libcerror_error_t **error );

LIBWRC_EXTERN \
int libwrc_wevt_event_get_template_definition(
     libwrc_wevt_event_t *event,
     libwrc_wevt_template_definition_t **template_definition,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBWRC_INTERNAL_WEVT_EVENT_H ) */

