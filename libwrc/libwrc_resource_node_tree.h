/*
 * Resource node tree functions
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

#if !defined( _LIBWRC_RESOURCE_NODE_TREE_H )
#define _LIBWRC_RESOURCE_NODE_TREE_H

#include <common.h>
#include <types.h>

#include "libwrc_io_handle.h"
#include "libwrc_libbfio.h"
#include "libwrc_libcdata.h"
#include "libwrc_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

int libwrc_resource_node_tree_read_node(
     libcdata_tree_node_t *node,
     libwrc_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     off64_t file_offset,
     int node_level,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBWRC_RESOURCE_NODE_TREE_H ) */

