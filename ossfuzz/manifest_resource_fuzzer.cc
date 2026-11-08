/*
 * OSS-Fuzz target for libwrc manifest_resource type
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

	libwrc_manifest_resource_t *manifest_resource = NULL;
	size_t utf8_string_size                       = 0;
	size_t utf16_string_size                      = 0;

	if( libwrc_manifest_resource_initialize(
	     &manifest_resource,
	     NULL ) != 1 )
	{
		return( 0 );
	}
	if( libwrc_manifest_resource_read(
	     manifest_resource,
	     data,
	     size,
	     NULL ) == 1 )
	{
		if( libwrc_manifest_resource_get_utf8_string_size(
	            manifest_resource,
	            &utf8_string_size,
	            NULL ) == 1 )
		{
			if( utf8_string_size > 0 )
			{
				libwrc_manifest_resource_get_utf8_string(
					 manifest_resource,
					 utf8_string,
					 384,
					 NULL );
			}
		}
		if( libwrc_manifest_resource_get_utf16_string_size(
	            manifest_resource,
	            &utf16_string_size,
	            NULL ) == 1 )
		{
			if( utf16_string_size > 0 )
			{
				libwrc_manifest_resource_get_utf16_string(
					 manifest_resource,
					 utf16_string,
					 384,
					 NULL );
			}
		}
	}
	libwrc_manifest_resource_free(
	 &manifest_resource,
	 NULL );

	return( 0 );
}

} /* extern "C" */
