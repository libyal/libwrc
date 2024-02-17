/*
 * Version (resource) values functions
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

#if !defined( _LIBWRC_VERSION_VALUES_H )
#define _LIBWRC_VERSION_VALUES_H

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

typedef struct libwrc_version_values libwrc_version_values_t;

struct libwrc_version_values
{
	/* The file version
	 */
	uint64_t file_version;

	/* The product version
	 */
	uint64_t product_version;
};

int libwrc_version_values_initialize(
     libwrc_version_values_t **version_values,
     libcerror_error_t **error );

int libwrc_version_values_free(
     libwrc_version_values_t **version_values,
     libcerror_error_t **error );

int libwrc_version_values_read(
     libwrc_language_entry_t *language_entry,
     libwrc_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     libwrc_data_descriptor_t *data_descriptor,
     libcerror_error_t **error );

ssize_t libwrc_version_values_read_string_file_information(
         libwrc_language_entry_t *language_entry,
         const uint8_t *resource_data,
         size_t resource_data_size,
         size_t resource_data_offset,
         libcerror_error_t **error );

ssize_t libwrc_version_values_read_string_table(
         libwrc_language_entry_t *language_entry,
         const uint8_t *resource_data,
         size_t resource_data_size,
         size_t resource_data_offset,
         libcerror_error_t **error );

ssize_t libwrc_version_values_read_string(
         libwrc_language_entry_t *language_entry,
         const uint8_t *resource_data,
         size_t resource_data_size,
         size_t resource_data_offset,
         libcerror_error_t **error );

ssize_t libwrc_version_values_read_variable_file_information(
         libwrc_language_entry_t *language_entry,
         const uint8_t *resource_data,
         size_t resource_data_size,
         size_t resource_data_offset,
         libcerror_error_t **error );

ssize_t libwrc_version_values_read_variable(
         libwrc_language_entry_t *language_entry,
         const uint8_t *resource_data,
         size_t resource_data_size,
         size_t resource_data_offset,
         libcerror_error_t **error );

int libwrc_version_values_get_file_version(
     libwrc_version_values_t *version_values,
     uint64_t *file_version,
     libcerror_error_t **error );

int libwrc_version_values_get_product_version(
     libwrc_version_values_t *version_values,
     uint64_t *product_version,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBWRC_VERSION_VALUES_H ) */

