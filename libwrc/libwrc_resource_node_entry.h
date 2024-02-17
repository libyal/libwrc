/*
 * Resource node entry functions
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

#if !defined( _LIBWRC_RESOURCE_NODE_ENTRY_H )
#define _LIBWRC_RESOURCE_NODE_ENTRY_H

#include <common.h>
#include <types.h>

#include "libwrc_data_descriptor.h"
#include "libwrc_libbfio.h"
#include "libwrc_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libwrc_resource_node_entry libwrc_resource_node_entry_t;

struct libwrc_resource_node_entry
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

	/* The data descriptor
	 */
	libwrc_data_descriptor_t *data_descriptor;

	/* The type
	 */
	int type;
};

int libwrc_resource_node_entry_initialize(
     libwrc_resource_node_entry_t **resource_node_entry,
     libcerror_error_t **error );

int libwrc_resource_node_entry_free(
     libwrc_resource_node_entry_t **resource_node_entry,
     libcerror_error_t **error );

int libwrc_resource_node_entry_read_data(
     libwrc_resource_node_entry_t *resource_node_entry,
     const uint8_t *data,
     size_t data_size,
     int node_level,
     libcerror_error_t **error );

int libwrc_resource_node_entry_read_file_io_handle(
     libwrc_resource_node_entry_t *resource_node_entry,
     libbfio_handle_t *file_io_handle,
     off64_t file_offset,
     int node_level,
     libcerror_error_t **error );

int libwrc_resource_node_entry_read_name_file_io_handle(
     libwrc_resource_node_entry_t *resource_node_entry,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error );

int libwrc_resource_node_entry_compare(
     libwrc_resource_node_entry_t *first_resource_node_entry,
     libwrc_resource_node_entry_t *second_resource_node_entry,
     libcerror_error_t **error );

int libwrc_resource_node_entry_set_name_string(
     libwrc_resource_node_entry_t *resource_node_entry,
     const uint8_t *name_string,
     size_t name_string_size,
     libcerror_error_t **error );

int libwrc_resource_node_entry_get_identifier(
     libwrc_resource_node_entry_t *resource_node_entry,
     uint32_t *identifier,
     libcerror_error_t **error );

int libwrc_resource_node_entry_get_utf8_name_size(
     libwrc_resource_node_entry_t *resource_node_entry,
     size_t *utf8_string_size,
     libcerror_error_t **error );

int libwrc_resource_node_entry_get_utf8_name(
     libwrc_resource_node_entry_t *resource_node_entry,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error );

int libwrc_resource_node_entry_get_utf16_name_size(
     libwrc_resource_node_entry_t *resource_node_entry,
     size_t *utf16_string_size,
     libcerror_error_t **error );

int libwrc_resource_node_entry_get_utf16_name(
     libwrc_resource_node_entry_t *resource_node_entry,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error );

int libwrc_resource_node_entry_get_type(
     libwrc_resource_node_entry_t *resource_node_entry,
     int *type,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBWRC_RESOURCE_NODE_ENTRY_H ) */

