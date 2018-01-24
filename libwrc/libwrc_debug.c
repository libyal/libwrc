/*
 * Debug functions
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

#include <common.h>
#include <types.h>

#include "libwrc_debug.h"
#include "libwrc_definitions.h"
#include "libwrc_libbfio.h"
#include "libwrc_libcerror.h"
#include "libwrc_libcnotify.h"

#if defined( HAVE_DEBUG_OUTPUT )

/* Returns a string with the resource identifier description
 */
const char *libwrc_debug_get_resource_identifier(
             uint32_t resource_identifier )
{
	switch( resource_identifier )
	{
		case LIBWRC_RESOURCE_IDENTIFIER_CURSOR:
			return( "Cursor" );

		case LIBWRC_RESOURCE_IDENTIFIER_BITMAP:
			return( "Bitmap" );

		case LIBWRC_RESOURCE_IDENTIFIER_ICON:
			return( "Icon" );

		case LIBWRC_RESOURCE_IDENTIFIER_MENU:
			return( "Menu" );

		case LIBWRC_RESOURCE_IDENTIFIER_DIALOG:
			return( "Dialog" );

		case LIBWRC_RESOURCE_IDENTIFIER_STRING:
			return( "String" );

		case LIBWRC_RESOURCE_IDENTIFIER_FONT_DIRECTORY:
			return( "Font Directory" );

		case LIBWRC_RESOURCE_IDENTIFIER_FONT:
			return( "Font" );

		case LIBWRC_RESOURCE_IDENTIFIER_ACCELERATOR:
			return( "Accelerator" );

		case LIBWRC_RESOURCE_IDENTIFIER_RAW_DATA:
			return( "Raw data" );

		case LIBWRC_RESOURCE_IDENTIFIER_MESSAGE_TABLE:
			return( "Message Table" );

		case LIBWRC_RESOURCE_IDENTIFIER_GROUP_CURSOR:
			return( "Group Cursor" );

		case LIBWRC_RESOURCE_IDENTIFIER_GROUP_ICON:
			return( "Group Icon" );

		case LIBWRC_RESOURCE_IDENTIFIER_VERSION:
			return( "Version" );

		case LIBWRC_RESOURCE_IDENTIFIER_DIALOG_INCLUDE:
			return( "Dialog Include" );

		case LIBWRC_RESOURCE_IDENTIFIER_PLUG_AND_PLAY:
			return( "Plug and Play" );

		case LIBWRC_RESOURCE_IDENTIFIER_VXD:
			return( "VXD" );

		case LIBWRC_RESOURCE_IDENTIFIER_ANIMATED_CURSOR:
			return( "Animated Cursor" );

		case LIBWRC_RESOURCE_IDENTIFIER_ANIMATED_ICON:
			return( "Animated Icon" );

		case LIBWRC_RESOURCE_IDENTIFIER_HTML:
			return( "HTML" );

		case LIBWRC_RESOURCE_IDENTIFIER_MANIFEST:
			return( "Manifest" );

		default:
			break;
	}
	return( "UNKNOWN" );
}

/* Prints the read offsets
 * Returns 1 if successful or -1 on error
 */
int libwrc_debug_print_read_offsets(
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error )
{
	static char *function = "libwrc_debug_print_read_offsets";
	off64_t offset        = 0;
	size64_t size         = 0;
	int number_of_offsets = 0;
	int offset_iterator   = 0;

	if( file_io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file io handle.",
		 function );

		return( -1 );
	}
	if( libbfio_handle_get_number_of_offsets_read(
	     file_io_handle,
	     &number_of_offsets,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of offsets read.",
		 function );

		return( -1 );
	}
	libcnotify_printf(
	 "Offsets read:\n" );

	for( offset_iterator = 0;
	     offset_iterator < number_of_offsets;
	     offset_iterator++ )
	{
		if( libbfio_handle_get_offset_read(
		     file_io_handle,
		     offset_iterator,
		     &offset,
		     &size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve offset: %d.",
			 function,
			 ( offset_iterator + 1 ) );

			return( -1 );
		}
		libcnotify_printf(
		 "%08" PRIi64 " ( 0x%08" PRIx64 " ) - %08" PRIi64 " ( 0x%08" PRIx64 " ) size: %" PRIu64 "\n",
		 offset,
		 offset,
		 offset + size,
		 offset + size,
		 size );
	}
	libcnotify_printf(
	 "\n" );

	return( 1 );
}

#endif

