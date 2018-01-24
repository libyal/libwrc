/*
 * Data descriptor functions
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

#if !defined( _LIBWRC_DATA_DESCRIPTOR_H )
#define _LIBWRC_DATA_DESCRIPTOR_H

#include <common.h>
#include <types.h>

#include "libwrc_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libwrc_data_descriptor libwrc_data_descriptor_t;

struct libwrc_data_descriptor
{
	/* The virtual address
	 */
	uint32_t virtual_address;

	/* The size
	 */
	uint32_t size;
};

int libwrc_data_descriptor_initialize(
     libwrc_data_descriptor_t **data_descriptor,
     libcerror_error_t **error );

int libwrc_data_descriptor_free(
     libwrc_data_descriptor_t **data_descriptor,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBWRC_DATA_DESCRIPTOR_H ) */

