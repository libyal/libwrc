/*
 * Resource values functions
 *
 * Copyright (C) 2011-2018, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _LIBWRC_RESOURCE_VALUES_H )
#define _LIBWRC_RESOURCE_VALUES_H

#include <common.h>
#include <types.h>

#include "libwrc_data_descriptor.h"
#include "libwrc_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libwrc_resource_values libwrc_resource_values_t;

struct libwrc_resource_values
{
	/* The identifier
	 */
	uint32_t identifier;

	/* The offset
	 */
	uint32_t offset;

	/* The name string
	 */
	uint8_t *name_string;

	/* The name string size
	 */
	size_t name_string_size;

	/* The type
	 */
	int type;

	/* The data descriptor
	 */
	libwrc_data_descriptor_t *data_descriptor;
};

int libwrc_resource_values_initialize(
     libwrc_resource_values_t **resource_values,
     libcerror_error_t **error );

int libwrc_resource_values_free(
     libwrc_resource_values_t **resource_values,
     libcerror_error_t **error );

int libwrc_resource_values_compare(
     libwrc_resource_values_t *first_resource_values,
     libwrc_resource_values_t *second_resource_values,
     libcerror_error_t **error );

int libwrc_resource_values_get_identifier(
     libwrc_resource_values_t *resource_values,
     uint32_t *identifier,
     libcerror_error_t **error );

int libwrc_resource_values_get_type(
     libwrc_resource_values_t *resource_values,
     int *type,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBWRC_RESOURCE_VALUES_H ) */

