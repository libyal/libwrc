/*
 * The Windows RC version information (VERSIONINFO) resource
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

#if !defined( _WRC_VERSION_INFORMATION_RESOURCE_H )
#define _WRC_VERSION_INFORMATION_RESOURCE_H

#include <common.h>
#include <types.h>

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct wrc_version_value_header wrc_version_value_header_t;

struct wrc_version_value_header
{
	/* The size
	 * Consists of 2 bytes
	 */
	uint8_t size[ 2 ];

	/* The value data size
	 * Consists of 2 bytes
	 */
	uint8_t value_data_size[ 2 ];

	/* The value data type
	 * Consists of 2 bytes
	 */
	uint8_t value_data_type[ 2 ];
};

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _WRC_VERSION_INFORMATION_RESOURCE_H ) */

