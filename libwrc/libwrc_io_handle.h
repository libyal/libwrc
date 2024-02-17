/*
 * Input/Output (IO) handle functions
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

#if !defined( _LIBWRC_IO_HANDLE_H )
#define _LIBWRC_IO_HANDLE_H

#include <common.h>
#include <types.h>

#include "libwrc_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

extern const char *wrc_mz_signature;

typedef struct libwrc_io_handle libwrc_io_handle_t;

struct libwrc_io_handle
{
	/* The virtual address
	 */
	uint32_t virtual_address;

	/* The stream size
	 */
	size64_t stream_size;

	/* The codepage of the extended ASCII strings
	 */
	int ascii_codepage;

	/* Value to indicate if abort was signalled
	 */
	int abort;
};

int libwrc_io_handle_initialize(
     libwrc_io_handle_t **io_handle,
     libcerror_error_t **error );

int libwrc_io_handle_free(
     libwrc_io_handle_t **io_handle,
     libcerror_error_t **error );

int libwrc_io_handle_clear(
     libwrc_io_handle_t *io_handle,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBWRC_IO_HANDLE_H ) */

