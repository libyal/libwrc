/*
 * WEVT keyword functions
 *
 * Copyright (C) 2011-2019, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _LIBWRC_INTERNAL_WEVT_KEYWORD_H )
#define _LIBWRC_INTERNAL_WEVT_KEYWORD_H

#include <common.h>
#include <types.h>

#include "libwrc_extern.h"
#include "libwrc_libcerror.h"
#include "libwrc_libfwevt.h"
#include "libwrc_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libwrc_internal_wevt_keyword libwrc_internal_wevt_keyword_t;

struct libwrc_internal_wevt_keyword
{
	/* The keyword descriptor
	 */
	libfwevt_keyword_t *keyword_descriptor;
};

int libwrc_wevt_keyword_initialize(
     libwrc_wevt_keyword_t **keyword,
     libfwevt_keyword_t *keyword_descriptor,
     libcerror_error_t **error );

LIBWRC_EXTERN \
int libwrc_wevt_keyword_free(
     libwrc_wevt_keyword_t **keyword,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBWRC_INTERNAL_WEVT_KEYWORD_H ) */

