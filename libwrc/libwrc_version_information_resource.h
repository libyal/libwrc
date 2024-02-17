/*
 * String table (VERSIONINFO) resource functions
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

#if !defined( _LIBWRC_VERSION_INFORMATION_RESOURCE_H )
#define _LIBWRC_VERSION_INFORMATION_RESOURCE_H

#include <common.h>
#include <types.h>

#include "libwrc_extern.h"
#include "libwrc_libcerror.h"
#include "libwrc_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libwrc_internal_version_information_resource libwrc_internal_version_information_resource_t;

struct libwrc_internal_version_information_resource
{
	/* The file version
	 */
	uint64_t file_version;

	/* The product version
	 */
	uint64_t product_version;
};

LIBWRC_EXTERN \
int libwrc_version_information_resource_initialize(
     libwrc_version_information_resource_t **version_information_resource,
     libcerror_error_t **error );

ssize_t libwrc_internal_version_information_resource_read_string_file_information(
         libwrc_internal_version_information_resource_t *internal_version_information_resource,
         const uint8_t *data,
         size_t data_size,
         size_t data_offset,
         libcerror_error_t **error );

ssize_t libwrc_internal_version_information_resource_read_string_table(
         libwrc_internal_version_information_resource_t *internal_version_information_resource,
         const uint8_t *data,
         size_t data_size,
         size_t data_offset,
         libcerror_error_t **error );

ssize_t libwrc_internal_version_information_resource_read_string(
         libwrc_internal_version_information_resource_t *internal_version_information_resource,
         const uint8_t *data,
         size_t data_size,
         size_t data_offset,
         libcerror_error_t **error );

ssize_t libwrc_internal_version_information_resource_read_variable_file_information(
         libwrc_internal_version_information_resource_t *internal_version_information_resource,
         const uint8_t *data,
         size_t data_size,
         size_t data_offset,
         libcerror_error_t **error );

ssize_t libwrc_internal_version_information_resource_read_variable(
         libwrc_internal_version_information_resource_t *internal_version_information_resource,
         const uint8_t *data,
         size_t data_size,
         size_t data_offset,
         libcerror_error_t **error );

LIBWRC_EXTERN \
int libwrc_version_information_resource_free(
     libwrc_version_information_resource_t **version_information_resource,
     libcerror_error_t **error );

LIBWRC_EXTERN \
int libwrc_version_information_resource_read(
     libwrc_version_information_resource_t *version_information_resource,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error );

LIBWRC_EXTERN \
int libwrc_version_information_resource_get_file_version(
     libwrc_version_information_resource_t *version_information_resource,
     uint64_t *file_version,
     libcerror_error_t **error );

LIBWRC_EXTERN \
int libwrc_version_information_resource_get_product_version(
     libwrc_version_information_resource_t *version_information_resource,
     uint64_t *product_version,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBWRC_VERSION_INFORMATION_RESOURCE_H ) */

