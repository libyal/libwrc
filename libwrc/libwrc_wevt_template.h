/*
 * WEVT_TEMPLATE (resource) functions
 *
 * Copyright (C) 2011-2021, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#if !defined( _LIBWRC_WEVT_TEMPLATE_H )
#define _LIBWRC_WEVT_TEMPLATE_H

#include <common.h>
#include <types.h>

#include "libwrc_extern.h"
#include "libwrc_libcerror.h"
#include "libwrc_resource.h"
#include "libwrc_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

LIBWRC_EXTERN \
int libwrc_wevt_template_get_number_of_providers(
     libwrc_resource_t *resource,
     uint32_t language_identifier,
     int *number_of_providers,
     libcerror_error_t **error );

LIBWRC_EXTERN \
int libwrc_wevt_template_get_provider(
     libwrc_resource_t *resource,
     uint32_t language_identifier,
     int provider_index,
     libwrc_wevt_provider_t **provider,
     libcerror_error_t **error );

LIBWRC_EXTERN \
int libwrc_wevt_template_get_provider_by_identifier(
     libwrc_resource_t *resource,
     uint32_t language_identifier,
     const uint8_t *provider_identifier,
     size_t provider_identifier_size,
     libwrc_wevt_provider_t **provider,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBWRC_WEVT_TEMPLATE_H ) */

