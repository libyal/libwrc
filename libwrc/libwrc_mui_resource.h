/*
 * MUI resource functions
 *
 * Copyright (C) 2011-2024, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _LIBWRC_MUI_RESOURCE_H )
#define _LIBWRC_MUI_RESOURCE_H

#include <common.h>
#include <types.h>

#include "libwrc_extern.h"
#include "libwrc_libcerror.h"
#include "libwrc_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libwrc_internal_mui_resource libwrc_internal_mui_resource_t;

struct libwrc_internal_mui_resource
{
	/* The file type
	 */
	uint32_t file_type;

	/* The main name
	 */
	uint8_t *main_name;

	/* The main name size
	 */
	size_t main_name_size;

	/* The MUI name
	 */
	uint8_t *mui_name;

	/* The MUI name size
	 */
	size_t mui_name_size;

	/* The language
	 */
	uint8_t *language;

	/* The language size
	 */
	size_t language_size;

	/* The fallback language
	 */
	uint8_t *fallback_language;

	/* The fallback language size
	 */
	size_t fallback_language_size;
};

LIBWRC_EXTERN \
int libwrc_mui_resource_initialize(
     libwrc_mui_resource_t **mui_resource,
     libcerror_error_t **error );

LIBWRC_EXTERN \
int libwrc_mui_resource_free(
     libwrc_mui_resource_t **mui_resource,
     libcerror_error_t **error );

LIBWRC_EXTERN \
int libwrc_mui_resource_read(
     libwrc_mui_resource_t *mui_resource,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error );

LIBWRC_EXTERN \
int libwrc_mui_resource_get_file_type(
     libwrc_mui_resource_t *mui_resource,
     uint32_t *file_type,
     libcerror_error_t **error );

LIBWRC_EXTERN \
int libwrc_mui_resource_get_utf8_main_name_size(
     libwrc_mui_resource_t *mui_resource,
     size_t *utf8_string_size,
     libcerror_error_t **error );

LIBWRC_EXTERN \
int libwrc_mui_resource_get_utf8_main_name(
     libwrc_mui_resource_t *mui_resource,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error );

LIBWRC_EXTERN \
int libwrc_mui_resource_get_utf16_main_name_size(
     libwrc_mui_resource_t *mui_resource,
     size_t *utf16_string_size,
     libcerror_error_t **error );

LIBWRC_EXTERN \
int libwrc_mui_resource_get_utf16_main_name(
     libwrc_mui_resource_t *mui_resource,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error );

LIBWRC_EXTERN \
int libwrc_mui_resource_get_utf8_mui_name_size(
     libwrc_mui_resource_t *mui_resource,
     size_t *utf8_string_size,
     libcerror_error_t **error );

LIBWRC_EXTERN \
int libwrc_mui_resource_get_utf8_mui_name(
     libwrc_mui_resource_t *mui_resource,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error );

LIBWRC_EXTERN \
int libwrc_mui_resource_get_utf16_mui_name_size(
     libwrc_mui_resource_t *mui_resource,
     size_t *utf16_string_size,
     libcerror_error_t **error );

LIBWRC_EXTERN \
int libwrc_mui_resource_get_utf16_mui_name(
     libwrc_mui_resource_t *mui_resource,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error );

LIBWRC_EXTERN \
int libwrc_mui_resource_get_utf8_language_size(
     libwrc_mui_resource_t *mui_resource,
     size_t *utf8_string_size,
     libcerror_error_t **error );

LIBWRC_EXTERN \
int libwrc_mui_resource_get_utf8_language(
     libwrc_mui_resource_t *mui_resource,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error );

LIBWRC_EXTERN \
int libwrc_mui_resource_get_utf16_language_size(
     libwrc_mui_resource_t *mui_resource,
     size_t *utf16_string_size,
     libcerror_error_t **error );

LIBWRC_EXTERN \
int libwrc_mui_resource_get_utf16_language(
     libwrc_mui_resource_t *mui_resource,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error );

LIBWRC_EXTERN \
int libwrc_mui_resource_get_utf8_fallback_language_size(
     libwrc_mui_resource_t *mui_resource,
     size_t *utf8_string_size,
     libcerror_error_t **error );

LIBWRC_EXTERN \
int libwrc_mui_resource_get_utf8_fallback_language(
     libwrc_mui_resource_t *mui_resource,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error );

LIBWRC_EXTERN \
int libwrc_mui_resource_get_utf16_fallback_language_size(
     libwrc_mui_resource_t *mui_resource,
     size_t *utf16_string_size,
     libcerror_error_t **error );

LIBWRC_EXTERN \
int libwrc_mui_resource_get_utf16_fallback_language(
     libwrc_mui_resource_t *mui_resource,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBWRC_MUI_RESOURCE_H ) */

