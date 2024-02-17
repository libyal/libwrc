/*
 * Language table functions
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

#if !defined( _LIBWRC_LANGUAGE_TABLE_H )
#define _LIBWRC_LANGUAGE_TABLE_H

#include <common.h>
#include <types.h>

#include "libwrc_language_entry.h"
#include "libwrc_libcdata.h"
#include "libwrc_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libwrc_language_table libwrc_language_table_t;

struct libwrc_language_table
{
	/* The language entries array
	 */
	libcdata_array_t *entries_array;
};

int libwrc_language_table_initialize(
     libwrc_language_table_t **language_table,
     libcerror_error_t **error );

int libwrc_language_table_free(
     libwrc_language_table_t **language_table,
     libcerror_error_t **error );

int libwrc_language_table_get_number_of_entries(
     libwrc_language_table_t *language_table,
     int *number_of_entries,
     libcerror_error_t **error );

int libwrc_language_table_get_identifier(
     libwrc_language_table_t *language_table,
     int entry_index,
     uint32_t *language_identifier,
     libcerror_error_t **error );

int libwrc_language_table_get_entry_by_identifier(
     libwrc_language_table_t *language_table,
     uint32_t language_identifier,
     libwrc_language_entry_t **language_entry,
     libcerror_error_t **error );

int libwrc_language_table_append_entry(
     libwrc_language_table_t *language_table,
     int *entry_index,
     libwrc_language_entry_t *language_entry,
     libcerror_error_t **error );

int libwrc_language_table_get_number_of_values(
     libwrc_language_table_t *language_table,
     uint32_t language_identifier,
     int *number_of_values,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBWRC_LANGUAGE_TABLE_H ) */

