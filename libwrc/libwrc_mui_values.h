/*
 * Multilingual User Interface (MUI) (resource) values functions
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

#if !defined( _LIBWRC_MUI_VALUES_H )
#define _LIBWRC_MUI_VALUES_H

#include <common.h>
#include <types.h>

#include "libwrc_data_descriptor.h"
#include "libwrc_io_handle.h"
#include "libwrc_language_entry.h"
#include "libwrc_libbfio.h"
#include "libwrc_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

extern uint8_t libwrc_mui_signature[ 4 ];

typedef struct libwrc_mui_values libwrc_mui_values_t;

struct libwrc_mui_values
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

int libwrc_mui_values_initialize(
     libwrc_mui_values_t **mui_values,
     libcerror_error_t **error );

int libwrc_mui_values_free(
     libwrc_mui_values_t **mui_values,
     libcerror_error_t **error );

int libwrc_mui_values_read(
     libwrc_language_entry_t *language_entry,
     libwrc_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     libwrc_data_descriptor_t *data_descriptor,
     libcerror_error_t **error );

int libwrc_mui_values_get_file_type(
     libwrc_mui_values_t *mui_values,
     uint32_t *file_type,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBWRC_MUI_VALUES_H ) */

