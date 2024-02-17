/*
 * The Windows RC resource node
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

#if !defined( _WRC_RESOURCE_NODE_H )
#define _WRC_RESOURCE_NODE_H

#include <common.h>
#include <types.h>

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct wrc_resource_node_header wrc_resource_node_header_t;

struct wrc_resource_node_header
{
	/* The flags
	 * Consists of 4 bytes
	 */
	uint8_t flags[ 4 ];

	/* The creation date and tims
	 * Consists of 4 bytes
	 * Contains a POSIX timestamp
	 */
	uint8_t creation_time[ 4 ];

	/* The major version
	 * Consists of 2 bytes
	 */
	uint8_t major_version[ 2 ];

	/* The minor version
	 * Consists of 2 bytes
	 */
	uint8_t minor_version[ 2 ];

	/* The number of named entries
	 * Consists of 2 bytes
	 */
	uint8_t number_of_named_entries[ 2 ];

	/* The number of unnamed entries
	 * Consists of 2 bytes
	 */
	uint8_t number_of_unnamed_entries[ 2 ];
};

typedef struct wrc_resource_node_entry wrc_resource_node_entry_t;

struct wrc_resource_node_entry
{
	/* The identifier
	 * Consists of 4 bytes
	 */
	uint8_t identifier[ 4 ];

	/* The offset
	 * Consists of 4 bytes
	 */
	uint8_t offset[ 4 ];
};

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _WRC_RESOURCE_NODE_H ) */

