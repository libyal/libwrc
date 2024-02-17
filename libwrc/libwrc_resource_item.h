/*
 * Resource item functions
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

#if !defined( _LIBWRC_RESOURCE_ITEM_H )
#define _LIBWRC_RESOURCE_ITEM_H

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

typedef struct libwrc_internal_resource_item libwrc_internal_resource_item_t;

struct libwrc_internal_resource_item
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

	/* The current data offset
	 */
	off64_t current_offset;
};

int libwrc_resource_item_initialize(
     libwrc_resource_item_t **resource_item,
     libwrc_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     libcdata_tree_node_t *resource_node,
     libcerror_error_t **error );

LIBWRC_EXTERN \
int libwrc_resource_item_free(
     libwrc_resource_item_t **resource_item,
     libcerror_error_t **error );

LIBWRC_EXTERN \
int libwrc_resource_item_get_identifier(
     libwrc_resource_item_t *resource_item,
     uint32_t *identifier,
     libcerror_error_t **error );

LIBWRC_EXTERN \
int libwrc_resource_item_get_utf8_name_size(
     libwrc_resource_item_t *resource_item,
     size_t *utf8_string_size,
     libcerror_error_t **error );

LIBWRC_EXTERN \
int libwrc_resource_item_get_utf8_name(
     libwrc_resource_item_t *resource_item,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error );

LIBWRC_EXTERN \
int libwrc_resource_item_get_utf16_name_size(
     libwrc_resource_item_t *resource_item,
     size_t *utf16_string_size,
     libcerror_error_t **error );

LIBWRC_EXTERN \
int libwrc_resource_item_get_utf16_name(
     libwrc_resource_item_t *resource_item,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error );

LIBWRC_EXTERN \
ssize_t libwrc_resource_item_read_buffer(
         libwrc_resource_item_t *resource_item,
         uint8_t *buffer,
         size_t size,
         libcerror_error_t **error );

LIBWRC_EXTERN \
ssize_t libwrc_resource_item_read_buffer_at_offset(
         libwrc_resource_item_t *resource_item,
         uint8_t *buffer,
         size_t size,
         off64_t offset,
         libcerror_error_t **error );

LIBWRC_EXTERN \
off64_t libwrc_resource_item_seek_offset(
         libwrc_resource_item_t *resource_item,
         off64_t offset,
         int whence,
         libcerror_error_t **error );

LIBWRC_EXTERN \
int libwrc_resource_item_get_offset(
     libwrc_resource_item_t *resource_item,
     off64_t *offset,
     libcerror_error_t **error );

LIBWRC_EXTERN \
int libwrc_resource_item_get_size(
     libwrc_resource_item_t *resource_item,
     uint32_t *size,
     libcerror_error_t **error );

LIBWRC_EXTERN \
int libwrc_resource_item_get_number_of_sub_items(
     libwrc_resource_item_t *resource_item,
     int *number_of_sub_items,
     libcerror_error_t **error );

LIBWRC_EXTERN \
int libwrc_resource_item_get_sub_item_by_index(
     libwrc_resource_item_t *resource_item,
     int item_index,
     libwrc_resource_item_t **resource_sub_item,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBWRC_RESOURCE_ITEM_H ) */

