/*
 * Info handle
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

#if !defined( _INFO_HANDLE_H )
#define _INFO_HANDLE_H

#include <common.h>
#include <file_stream.h>
#include <types.h>

#include "wrctools_libbfio.h"
#include "wrctools_libcerror.h"
#include "wrctools_libexe.h"
#include "wrctools_libwrc.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct info_handle info_handle_t;

struct info_handle
{
	/* The libexe input file
	 */
	libexe_file_t *input_exe_file;

	/* The libexe resource (.rsrc) section
	 */
	libexe_section_t *resource_section;

	/* The resource (.rsrc) section file IO handle
	 */
	libbfio_handle_t *resource_section_file_io_handle;

	/* The libwrc input resource stream
	 */
	libwrc_stream_t *input_resource_stream;

	/* The ascii codepage
	 */
	int ascii_codepage;

	/* The notification output stream
	 */
	FILE *notify_stream;

	/* Value to indicate if abort was signalled
	 */
	int abort;
};

int info_handle_initialize(
     info_handle_t **info_handle,
     libcerror_error_t **error );

int info_handle_free(
     info_handle_t **info_handle,
     libcerror_error_t **error );

int info_handle_signal_abort(
     info_handle_t *info_handle,
     libcerror_error_t **error );

int info_handle_set_ascii_codepage(
     info_handle_t *info_handle,
     const system_character_t *string,
     libcerror_error_t **error );

int info_handle_open_input(
     info_handle_t *info_handle,
     const system_character_t *filename,
     libcerror_error_t **error );

int info_handle_close_input(
     info_handle_t *info_handle,
     libcerror_error_t **error );

int info_handle_manifest_resource_item_fprint(
     info_handle_t *info_handle,
     uint32_t identifier,
     libwrc_resource_item_t *resource_item,
     libcerror_error_t **error );

int info_handle_manifest_resource_fprint(
     info_handle_t *info_handle,
     libcerror_error_t **error );

int info_handle_message_string_fprint(
     info_handle_t *info_handle,
     libwrc_resource_t *message_table_resource,
     uint32_t language_identifier,
     int message_index,
     libcerror_error_t **error );

int info_handle_message_table_resource_item_fprint(
     info_handle_t *info_handle,
     uint32_t identifier,
     libwrc_resource_item_t *resource_item,
     libcerror_error_t **error );

int info_handle_message_table_resource_fprint(
     info_handle_t *info_handle,
     libcerror_error_t **error );

int info_handle_mui_resource_item_fprint(
     info_handle_t *info_handle,
     uint32_t identifier,
     libwrc_resource_item_t *resource_item,
     libcerror_error_t **error );

int info_handle_mui_resource_fprint(
     info_handle_t *info_handle,
     libcerror_error_t **error );

int info_handle_string_table_resource_item_fprint(
     info_handle_t *info_handle,
     uint32_t identifier,
     libwrc_resource_item_t *resource_item,
     libcerror_error_t **error );

int info_handle_string_table_resource_fprint(
     info_handle_t *info_handle,
     libcerror_error_t **error );

int info_handle_version_information_resource_item_fprint(
     info_handle_t *info_handle,
     uint32_t identifier,
     libwrc_resource_item_t *resource_item,
     libcerror_error_t **error );

int info_handle_version_information_resource_fprint(
     info_handle_t *info_handle,
     libcerror_error_t **error );

int info_handle_resource_hierarchy_fprint_resource_item(
     info_handle_t *info_handle,
     libwrc_resource_item_t *resource_item,
     int indentation_level,
     libcerror_error_t **error );

int info_handle_resource_hierarchy_fprint(
     info_handle_t *info_handle,
     libcerror_error_t **error );

int info_handle_stream_fprint(
     info_handle_t *info_handle,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _INFO_HANDLE_H ) */

