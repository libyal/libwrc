/*
 * Resource functions
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

#if !defined( _LIBWRC_RESOURCE_H )
#define _LIBWRC_RESOURCE_H

#include <common.h>
#include <types.h>

#include "libwrc_extern.h"
#include "libwrc_io_handle.h"
#include "libwrc_libbfio.h"
#include "libwrc_libcdata.h"
#include "libwrc_libcerror.h"
#include "libwrc_resource_node_entry.h"
#include "libwrc_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libwrc_internal_resource libwrc_internal_resource_t;

struct libwrc_internal_resource
{
	/* The IO handle
	 */
	libwrc_io_handle_t *io_handle;

	/* The file IO handle
	 */
	libbfio_handle_t *file_io_handle;

	/* The resource node
	 */
	libcdata_tree_node_t *resource_node;

	/* The resource node entry
	 */
	libwrc_resource_node_entry_t *resource_node_entry;

	/* The resource value
	 */
        intptr_t *value;

	/* The resource free value function
	 */
	int (*free_value)(
	       intptr_t **value,
	       libcerror_error_t **error );
};

int libwrc_resource_initialize(
     libwrc_resource_t **resource,
     libwrc_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     libcdata_tree_node_t *resource_node,
     libcerror_error_t **error );

LIBWRC_EXTERN \
int libwrc_resource_free(
     libwrc_resource_t **resource,
     libcerror_error_t **error );

int libwrc_resource_read_value(
     libwrc_internal_resource_t *internal_resource,
     libcerror_error_t **error );

int libwrc_resource_read_data_descriptor(
     libwrc_internal_resource_t *internal_resource,
     libwrc_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     libwrc_data_descriptor_t *data_descriptor,
     libcerror_error_t **error );

LIBWRC_EXTERN \
int libwrc_resource_get_identifier(
     libwrc_resource_t *resource,
     uint32_t *identifier,
     libcerror_error_t **error );

LIBWRC_EXTERN \
int libwrc_resource_get_utf8_name_size(
     libwrc_resource_t *resource,
     size_t *utf8_string_size,
     libcerror_error_t **error );

LIBWRC_EXTERN \
int libwrc_resource_get_utf8_name(
     libwrc_resource_t *resource,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error );

LIBWRC_EXTERN \
int libwrc_resource_get_utf16_name_size(
     libwrc_resource_t *resource,
     size_t *utf16_string_size,
     libcerror_error_t **error );

LIBWRC_EXTERN \
int libwrc_resource_get_utf16_name(
     libwrc_resource_t *resource,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error );

LIBWRC_EXTERN \
int libwrc_resource_get_type(
     libwrc_resource_t *resource,
     int *type,
     libcerror_error_t **error );

int libwrc_resource_get_value_by_language_identifier(
     libwrc_resource_t *resource,
     int resource_type,
     uint32_t language_identifier,
     int value_index,
     intptr_t **value,
     libcerror_error_t **error );

LIBWRC_EXTERN \
int libwrc_resource_get_number_of_items(
     libwrc_resource_t *resource,
     int *number_of_items,
     libcerror_error_t **error );

LIBWRC_EXTERN \
int libwrc_resource_get_item_by_index(
     libwrc_resource_t *resource,
     int item_index,
     libwrc_resource_item_t **resource_item,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBWRC_RESOURCE_H ) */

