/*
 * The Windows RC Multilingual User Interface (MUI) resource
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

#if !defined( _WRC_MUI_RESOURCE_H )
#define _WRC_MUI_RESOURCE_H

#include <common.h>
#include <types.h>

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct wrc_mui_header wrc_mui_header_t;

struct wrc_mui_header
{
	/* The signature
	 * Consists of 4 bytes
	 * Contains: 0xfecdfecd
	 */
	uint8_t signature[ 4 ];

	/* The size
	 * Consists of 4 bytes
	 */
	uint8_t size[ 4 ];

	/* The version
	 * Consists of 4 bytes
	 */
	uint8_t version[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown1[ 4 ];

	/* The file type
	 * Consists of 4 bytes
	 */
	uint8_t file_type[ 4 ];

	/* The system attributes
	 * Consists of 4 bytes
	 */
	uint8_t system_attributes[ 4 ];

	/* The ultimate fallback location
	 * Consists of 4 bytes
	 */
	uint8_t ultimate_fallback_location[ 4 ];

	/* The service checksum
	 * Consists of 16 bytes
	 */
	uint8_t service_checksum[ 16 ];

	/* The checksum
	 * Consists of 16 bytes
	 */
	uint8_t checksum[ 16 ];

	/* Unknown
	 * Consists of 24 bytes
	 */
	uint8_t unknown2[ 24 ];
};

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _WRC_MUI_RESOURCE_H ) */

