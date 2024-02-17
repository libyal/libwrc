/*
 * Message or string table entry functions
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

#if !defined( _LIBWRC_TABLE_ENTRY_H )
#define _LIBWRC_TABLE_ENTRY_H

#include <common.h>
#include <types.h>

#include "libwrc_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libwrc_table_entry libwrc_table_entry_t;

struct libwrc_table_entry
{
	/* The identifier
	 */
	uint32_t identifier;

	/* The string
	 */
	uint8_t *string;

	/* The string size
	 */
	size_t string_size;

	/* The codepage
	 */
	int codepage;
};

int libwrc_table_entry_initialize(
     libwrc_table_entry_t **table_entry,
     libcerror_error_t **error );

int libwrc_table_entry_free(
     libwrc_table_entry_t **table_entry,
     libcerror_error_t **error );

int libwrc_table_entry_set_string(
     libwrc_table_entry_t *table_entry,
     const uint8_t *string,
     size_t string_size,
     int codepage,
     libcerror_error_t **error );

int libwrc_table_entry_get_utf8_string_size(
     libwrc_table_entry_t *table_entry,
     size_t *utf8_string_size,
     libcerror_error_t **error );

int libwrc_table_entry_get_utf8_string(
     libwrc_table_entry_t *table_entry,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error );

int libwrc_table_entry_get_utf16_string_size(
     libwrc_table_entry_t *table_entry,
     size_t *utf16_string_size,
     libcerror_error_t **error );

int libwrc_table_entry_get_utf16_string(
     libwrc_table_entry_t *table_entry,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBWRC_TABLE_ENTRY_H ) */

