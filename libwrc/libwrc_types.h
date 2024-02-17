/*
 * The internal type definitions
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

#if !defined( _LIBWRC_INTERNAL_TYPES_H )
#define _LIBWRC_INTERNAL_TYPES_H

#include <common.h>
#include <types.h>

/* Define HAVE_LOCAL_LIBWRC for local use of libwrc
 * The definitions in <libwrc/types.h> are copied here
 * for local use of libwrc
 */
#if defined( HAVE_LOCAL_LIBWRC )

/* The following type definitions hide internal data structures
 */
#if defined( HAVE_DEBUG_OUTPUT ) && !defined( WINAPI )
typedef struct libwrc_manifest_resource {}		libwrc_manifest_resource_t;
typedef struct libwrc_message_table_resource {}		libwrc_message_table_resource_t;
typedef struct libwrc_mui_resource {}			libwrc_mui_resource_t;
typedef struct libwrc_resource {}			libwrc_resource_t;
typedef struct libwrc_resource_item {}			libwrc_resource_item_t;
typedef struct libwrc_stream {}				libwrc_stream_t;
typedef struct libwrc_string_table_resource {}		libwrc_string_table_resource_t;
typedef struct libwrc_version_information_resource {}	libwrc_version_information_resource_t;

#else
typedef intptr_t libwrc_manifest_resource_t;
typedef intptr_t libwrc_message_table_resource_t;
typedef intptr_t libwrc_mui_resource_t;
typedef intptr_t libwrc_resource_t;
typedef intptr_t libwrc_resource_item_t;
typedef intptr_t libwrc_stream_t;
typedef intptr_t libwrc_string_table_resource_t;
typedef intptr_t libwrc_version_information_resource_t;

#endif /* defined( HAVE_DEBUG_OUTPUT ) && !defined( WINAPI ) */

#endif /* defined( HAVE_LOCAL_LIBWRC ) */

#endif /* !defined( _LIBWRC_INTERNAL_TYPES_H ) */

