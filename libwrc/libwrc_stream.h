/*
 * Stream functions
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

#if !defined( _LIBWRC_STREAM_H )
#define _LIBWRC_STREAM_H

#include <common.h>
#include <types.h>

#include "libwrc_extern.h"
#include "libwrc_io_handle.h"
#include "libwrc_libbfio.h"
#include "libwrc_libcdata.h"
#include "libwrc_libcerror.h"
#include "libwrc_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libwrc_internal_stream libwrc_internal_stream_t;

struct libwrc_internal_stream
{
	/* The virtual address
	 */
	uint32_t virtual_address;

	/* The resources (tree) root node
	 */
	libcdata_tree_node_t *resources_root_node;

	/* The IO handle
	 */
	libwrc_io_handle_t *io_handle;

	/* The file IO handle
	 */
	libbfio_handle_t *file_io_handle;

	/* Value to indicate if the file IO handle was created inside the library
	 */
	uint8_t file_io_handle_created_in_library;

	/* Value to indicate if the file IO handle was opened inside the library
	 */
	uint8_t file_io_handle_opened_in_library;
};

LIBWRC_EXTERN \
int libwrc_stream_initialize(
     libwrc_stream_t **stream,
     libcerror_error_t **error );

LIBWRC_EXTERN \
int libwrc_stream_free(
     libwrc_stream_t **stream,
     libcerror_error_t **error );

LIBWRC_EXTERN \
int libwrc_stream_signal_abort(
     libwrc_stream_t *stream,
     libcerror_error_t **error );

LIBWRC_EXTERN \
int libwrc_stream_open(
     libwrc_stream_t *stream,
     const char *filename,
     int access_flags,
     libcerror_error_t **error );

#if defined( HAVE_WIDE_CHARACTER_TYPE )

LIBWRC_EXTERN \
int libwrc_stream_open_wide(
     libwrc_stream_t *stream,
     const wchar_t *filename,
     int access_flags,
     libcerror_error_t **error );

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

LIBWRC_EXTERN \
int libwrc_stream_open_file_io_handle(
     libwrc_stream_t *stream,
     libbfio_handle_t *file_io_handle,
     int access_flags,
     libcerror_error_t **error );

LIBWRC_EXTERN \
int libwrc_stream_close(
     libwrc_stream_t *stream,
     libcerror_error_t **error );

int libwrc_internal_stream_open_read(
     libwrc_internal_stream_t *internal_stream,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error );

LIBWRC_EXTERN \
int libwrc_stream_get_ascii_codepage(
     libwrc_stream_t *stream,
     int *ascii_codepage,
     libcerror_error_t **error );

LIBWRC_EXTERN \
int libwrc_stream_set_ascii_codepage(
     libwrc_stream_t *stream,
     int ascii_codepage,
     libcerror_error_t **error );

LIBWRC_EXTERN \
int libwrc_stream_get_virtual_address(
     libwrc_stream_t *stream,
     uint32_t *virtual_address,
     libcerror_error_t **error );

LIBWRC_EXTERN \
int libwrc_stream_set_virtual_address(
     libwrc_stream_t *stream,
     uint32_t virtual_address,
     libcerror_error_t **error );

LIBWRC_EXTERN \
int libwrc_stream_get_number_of_resources(
     libwrc_stream_t *stream,
     int *number_of_resources,
     libcerror_error_t **error );

LIBWRC_EXTERN \
int libwrc_stream_get_resource_by_index(
     libwrc_stream_t *stream,
     int resource_index,
     libwrc_resource_t **resource,
     libcerror_error_t **error );

LIBWRC_EXTERN \
int libwrc_stream_get_resource_by_identifier(
     libwrc_stream_t *stream,
     uint32_t identifier,
     libwrc_resource_t **resource,
     libcerror_error_t **error );

LIBWRC_EXTERN \
int libwrc_stream_get_resource_by_type(
     libwrc_stream_t *stream,
     int type,
     libwrc_resource_t **resource,
     libcerror_error_t **error );

LIBWRC_EXTERN \
int libwrc_stream_get_resource_by_utf8_name(
     libwrc_stream_t *stream,
     const uint8_t *utf8_string,
     size_t utf8_string_length,
     libwrc_resource_t **resource,
     libcerror_error_t **error );

LIBWRC_EXTERN \
int libwrc_stream_get_resource_by_utf16_name(
     libwrc_stream_t *stream,
     const uint16_t *utf16_string,
     size_t utf16_string_length,
     libwrc_resource_t **resource,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBWRC_STREAM_H ) */

