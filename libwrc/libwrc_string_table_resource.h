/*
 * String table (STRINGTABLE) resource functions
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

#if !defined( _LIBWRC_STRING_TABLE_RESOURCE_H )
#define _LIBWRC_STRING_TABLE_RESOURCE_H

#include <common.h>
#include <types.h>

#include "libwrc_extern.h"
#include "libwrc_libcdata.h"
#include "libwrc_libcerror.h"
#include "libwrc_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libwrc_internal_string_table_resource libwrc_internal_string_table_resource_t;

struct libwrc_internal_string_table_resource
{
	/* The entries array
	 */
	libcdata_array_t *entries_array;
};

LIBWRC_EXTERN \
int libwrc_string_table_resource_initialize(
     libwrc_string_table_resource_t **string_table_resource,
     libcerror_error_t **error );

LIBWRC_EXTERN \
int libwrc_string_table_resource_free(
     libwrc_string_table_resource_t **string_table_resource,
     libcerror_error_t **error );

LIBWRC_EXTERN \
int libwrc_string_table_resource_read(
     libwrc_string_table_resource_t *string_table_resource,
     const uint8_t *data,
     size_t data_size,
     uint32_t base_identifier,
     libcerror_error_t **error );

LIBWRC_EXTERN \
int libwrc_string_table_resource_get_number_of_strings(
     libwrc_string_table_resource_t *string_table_resource,
     int *number_of_strings,
     libcerror_error_t **error );

LIBWRC_EXTERN \
int libwrc_string_table_resource_get_identifier(
     libwrc_string_table_resource_t *string_table_resource,
     int string_index,
     uint32_t *string_identifier,
     libcerror_error_t **error );

LIBWRC_EXTERN \
int libwrc_string_table_resource_get_index_by_identifier(
     libwrc_string_table_resource_t *string_table_resource,
     uint32_t string_identifier,
     int *string_index,
     libcerror_error_t **error );

LIBWRC_EXTERN \
int libwrc_string_table_resource_get_utf8_string_size(
     libwrc_string_table_resource_t *string_table_resource,
     int string_index,
     size_t *utf8_string_size,
     libcerror_error_t **error );

LIBWRC_EXTERN \
int libwrc_string_table_resource_get_utf8_string(
     libwrc_string_table_resource_t *string_table_resource,
     int string_index,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error );

LIBWRC_EXTERN \
int libwrc_string_table_resource_get_utf16_string_size(
     libwrc_string_table_resource_t *string_table_resource,
     int string_index,
     size_t *utf16_string_size,
     libcerror_error_t **error );

LIBWRC_EXTERN \
int libwrc_string_table_resource_get_utf16_string(
     libwrc_string_table_resource_t *string_table_resource,
     int string_index,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBWRC_STRING_TABLE_RESOURCE_H ) */

