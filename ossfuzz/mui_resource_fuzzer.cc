/*
 * OSS-Fuzz target for libwrc mui_resource type
 *
 * Copyright (C) 2011-2026, Joachim Metz <joachim.metz@gmail.com>
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

#include <stddef.h>
#include <stdint.h>

/* Note that some of the OSS-Fuzz engines use C++
 */
extern "C" {

#include "ossfuzz_libwrc.h"

int LLVMFuzzerTestOneInput(
     const uint8_t *data,
     size_t size )
{
	uint8_t utf8_string[ 384 ];
	uint16_t utf16_string[ 192 ];

	libwrc_mui_resource_t *mui_resource = NULL;
	size_t utf8_string_size             = 0;
	size_t utf16_string_size            = 0;
	uint32_t file_type                  = 0;
	int result                          = 0;

	if( libwrc_mui_resource_initialize(
	     &mui_resource,
	     NULL ) != 1 )
	{
		return( 0 );
	}
	if( libwrc_mui_resource_read(
	     mui_resource,
	     data,
	     size,
	     NULL ) == 1 )
	{
		libwrc_mui_resource_get_file_type(
		 mui_resource,
		 &file_type,
		 NULL );
		if( libwrc_mui_resource_get_utf8_main_name_size(
	            mui_resource,
	            &utf8_string_size,
	            NULL ) == 1 )
		{
			if( utf8_string_size > 0 )
			{
				libwrc_mui_resource_get_utf8_main_name(
				 mui_resource,
				 utf8_string,
				 384,
				 NULL );
			}
		}
		if( libwrc_mui_resource_get_utf8_mui_name_size(
	            mui_resource,
	            &utf8_string_size,
	            NULL ) == 1 )
		{
			if( utf8_string_size > 0 )
			{
				libwrc_mui_resource_get_utf8_mui_name(
				 mui_resource,
				 utf8_string,
				 384,
				 NULL );
			}
		}
		if( libwrc_mui_resource_get_utf8_language_size(
	            mui_resource,
	            &utf8_string_size,
	            NULL ) == 1 )
		{
			if( utf8_string_size > 0 )
			{
				libwrc_mui_resource_get_utf8_language(
				 mui_resource,
				 utf8_string,
				 384,
				 NULL );
			}
		}
		if( libwrc_mui_resource_get_utf8_fallback_language_size(
	            mui_resource,
	            &utf8_string_size,
	            NULL ) == 1 )
		{
			if( utf8_string_size > 0 )
			{
				libwrc_mui_resource_get_utf8_fallback_language(
				 mui_resource,
				 utf8_string,
				 384,
				 NULL );
			}
		}
		result = libwrc_mui_resource_get_utf16_main_name_size(
		         mui_resource,
		         &utf16_string_size,
		         NULL );

		if( result == 1 )
		{
			if( utf16_string_size > 0 )
			{
				libwrc_mui_resource_get_utf16_main_name(
				 mui_resource,
				 utf16_string,
				 384,
				 NULL );
			}
		}
	}
	libwrc_mui_resource_free(
	 &mui_resource,
	 NULL );

	return( 0 );
}

} /* extern "C" */
