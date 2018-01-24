/*
 * The internal type definitions
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
typedef struct libwrc_resource {}			libwrc_resource_t;
typedef struct libwrc_stream {}				libwrc_stream_t;
typedef struct libwrc_wevt_channel {}			libwrc_wevt_channel_t;
typedef struct libwrc_wevt_event {}			libwrc_wevt_event_t;
typedef struct libwrc_wevt_keyword {}			libwrc_wevt_keyword_t;
typedef struct libwrc_wevt_level {}			libwrc_wevt_level_t;
typedef struct libwrc_wevt_map {}			libwrc_wevt_map_t;
typedef struct libwrc_wevt_opcode {}			libwrc_wevt_opcode_t;
typedef struct libwrc_wevt_provider {}			libwrc_wevt_provider_t;
typedef struct libwrc_wevt_task {}			libwrc_wevt_task_t;
typedef struct libwrc_wevt_template_definition {}	libwrc_wevt_template_definition_t;

#else
typedef intptr_t libwrc_resource_t;
typedef intptr_t libwrc_stream_t;
typedef intptr_t libwrc_wevt_channel_t;
typedef intptr_t libwrc_wevt_event_t;
typedef intptr_t libwrc_wevt_keyword_t;
typedef intptr_t libwrc_wevt_level_t;
typedef intptr_t libwrc_wevt_map_t;
typedef intptr_t libwrc_wevt_opcode_t;
typedef intptr_t libwrc_wevt_provider_t;
typedef intptr_t libwrc_wevt_task_t;
typedef intptr_t libwrc_wevt_template_definition_t;

#endif /* defined( HAVE_DEBUG_OUTPUT ) && !defined( WINAPI ) */

#endif /* defined( HAVE_LOCAL_LIBWRC ) */

#endif /* !defined( _LIBWRC_INTERNAL_TYPES_H ) */

