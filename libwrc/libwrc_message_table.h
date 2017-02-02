/*
 * Message table (resource) functions
 *
 * Copyright (C) 2011-2017, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _LIBWRC_MESSAGE_TABLE_H )
#define _LIBWRC_MESSAGE_TABLE_H

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
int libwrc_message_table_get_number_of_messages(
     libwrc_resource_t *resource,
     uint32_t language_identifier,
     int *number_of_messages,
     libcerror_error_t **error );

LIBWRC_EXTERN \
int libwrc_message_table_get_identifier(
     libwrc_resource_t *resource,
     uint32_t language_identifier,
     int message_index,
     uint32_t *message_identifier,
     libcerror_error_t **error );

LIBWRC_EXTERN \
int libwrc_message_table_get_index_by_identifier(
     libwrc_resource_t *resource,
     uint32_t language_identifier,
     uint32_t message_identifier,
     int *message_index,
     libcerror_error_t **error );

LIBWRC_EXTERN \
int libwrc_message_table_get_utf8_string_size(
     libwrc_resource_t *resource,
     uint32_t language_identifier,
     int message_index,
     size_t *utf8_string_size,
     libcerror_error_t **error );

LIBWRC_EXTERN \
int libwrc_message_table_get_utf8_string(
     libwrc_resource_t *resource,
     uint32_t language_identifier,
     int message_index,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error );

LIBWRC_EXTERN \
int libwrc_message_table_get_utf16_string_size(
     libwrc_resource_t *resource,
     uint32_t language_identifier,
     int message_index,
     size_t *utf16_string_size,
     libcerror_error_t **error );

LIBWRC_EXTERN \
int libwrc_message_table_get_utf16_string(
     libwrc_resource_t *resource,
     uint32_t language_identifier,
     int message_index,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBWRC_MESSAGE_TABLE_H ) */

