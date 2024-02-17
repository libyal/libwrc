/*
 * String values functions
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

#if !defined( _LIBWRC_STRING_VALUES_H )
#define _LIBWRC_STRING_VALUES_H

#include <common.h>
#include <types.h>

#include "libwrc_data_descriptor.h"
#include "libwrc_io_handle.h"
#include "libwrc_language_entry.h"
#include "libwrc_libcerror.h"
#include "libwrc_libbfio.h"

#if defined( __cplusplus )
extern "C" {
#endif

int libwrc_string_values_read(
     libwrc_language_entry_t *language_entry,
     libwrc_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     uint32_t identifier,
     libwrc_data_descriptor_t *data_descriptor,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBWRC_STRING_VALUES_H ) */

