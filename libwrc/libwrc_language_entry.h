/*
 * Language (table) entry functions
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

#if !defined( _LIBWRC_LANGUAGE_ENTRY_H )
#define _LIBWRC_LANGUAGE_ENTRY_H

#include <common.h>
#include <types.h>

#include "libwrc_libcdata.h"
#include "libwrc_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libwrc_language_entry libwrc_language_entry_t;

struct libwrc_language_entry
{
	/* The language identifier
	 */
	uint32_t language_identifier;

	/* The values array
	 */
	libcdata_array_t *values_array;

	/* The language entry value free function
	 */
	int (*value_free_function)(
	       intptr_t **value,
	       libcerror_error_t **error );
};

int libwrc_language_entry_initialize(
     libwrc_language_entry_t **language_entry,
     uint32_t language_identifier,
     int (*value_free_function)(
            intptr_t **value,
            libcerror_error_t **error ),
     libcerror_error_t **error );

int libwrc_language_entry_free(
     libwrc_language_entry_t **language_entry,
     libcerror_error_t **error );

int libwrc_language_entry_get_number_of_values(
     libwrc_language_entry_t *language_entry,
     int *number_of_values,
     libcerror_error_t **error );

int libwrc_language_entry_get_value_by_index(
     libwrc_language_entry_t *language_entry,
     int value_index,
     intptr_t **value,
     libcerror_error_t **error );

int libwrc_language_entry_append_value(
     libwrc_language_entry_t *language_entry,
     int *value_index,
     intptr_t *value,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBWRC_LANGUAGE_ENTRY_H ) */

