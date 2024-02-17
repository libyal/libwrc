/*
 * Message table (MESSAGETABLE) resource functions
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

#if !defined( _LIBWRC_MESSAGE_TABLE_RESOURCE_H )
#define _LIBWRC_MESSAGE_TABLE_RESOURCE_H

#include <common.h>
#include <types.h>

#include "libwrc_extern.h"
#include "libwrc_libcdata.h"
#include "libwrc_libcerror.h"
#include "libwrc_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libwrc_internal_message_table_resource libwrc_internal_message_table_resource_t;

struct libwrc_internal_message_table_resource
{
	/* The entries array
	 */
	libcdata_array_t *entries_array;
};

LIBWRC_EXTERN \
int libwrc_message_table_resource_initialize(
     libwrc_message_table_resource_t **message_table_resource,
     libcerror_error_t **error );

LIBWRC_EXTERN \
int libwrc_message_table_resource_free(
     libwrc_message_table_resource_t **message_table_resource,
     libcerror_error_t **error );

LIBWRC_EXTERN \
int libwrc_message_table_resource_read(
     libwrc_message_table_resource_t *message_table_resource,
     const uint8_t *data,
     size_t data_size,
     int ascii_codepage,
     libcerror_error_t **error );

LIBWRC_EXTERN \
int libwrc_message_table_resource_get_number_of_messages(
     libwrc_message_table_resource_t *message_table_resource,
     int *number_of_messages,
     libcerror_error_t **error );

LIBWRC_EXTERN \
int libwrc_message_table_resource_get_identifier(
     libwrc_message_table_resource_t *message_table_resource,
     int message_index,
     uint32_t *message_identifier,
     libcerror_error_t **error );

LIBWRC_EXTERN \
int libwrc_message_table_resource_get_index_by_identifier(
     libwrc_message_table_resource_t *message_table_resource,
     uint32_t message_identifier,
     int *message_index,
     libcerror_error_t **error );

LIBWRC_EXTERN \
int libwrc_message_table_resource_get_utf8_string_size(
     libwrc_message_table_resource_t *message_table_resource,
     int message_index,
     size_t *utf8_string_size,
     libcerror_error_t **error );

LIBWRC_EXTERN \
int libwrc_message_table_resource_get_utf8_string(
     libwrc_message_table_resource_t *message_table_resource,
     int message_index,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error );

LIBWRC_EXTERN \
int libwrc_message_table_resource_get_utf16_string_size(
     libwrc_message_table_resource_t *message_table_resource,
     int message_index,
     size_t *utf16_string_size,
     libcerror_error_t **error );

LIBWRC_EXTERN \
int libwrc_message_table_resource_get_utf16_string(
     libwrc_message_table_resource_t *message_table_resource,
     int message_index,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBWRC_MESSAGE_TABLE_RESOURCE_H ) */

