/*
 * OSS-Fuzz target for libwrc string_table_resource type
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

	libwrc_string_table_resource_t *string_table_resource = NULL;
	size_t utf8_string_size                               = 0;
	size_t utf16_string_size                              = 0;
	uint32_t string_identifier                            = 0;
	int string_index                                      = 0;
	int number_of_strings                                 = 0;

	if( libwrc_string_table_resource_initialize(
	     &string_table_resource,
	     NULL ) != 1 )
	{
		return( 0 );
	}
	if( libwrc_string_table_resource_read(
	     string_table_resource,
	     data,
	     size,
	     1,
	     NULL ) == 1 )
	{
		if( libwrc_string_table_resource_get_number_of_strings(
	            string_table_resource,
	            &number_of_strings,
	            NULL ) == 1 )
		{
			if( number_of_strings > 0 )
			{
				if( libwrc_string_table_resource_get_identifier(
	                    string_table_resource,
	                    0,
	                    &string_identifier,
	                    NULL ) == 1 )
				{
					libwrc_string_table_resource_get_index_by_identifier(
					 string_table_resource,
					 string_identifier,
					 &string_index,
					 NULL );
				}
				if( libwrc_string_table_resource_get_utf8_string_size(
	                    string_table_resource,
	                    0,
	                    &utf8_string_size,
	                    NULL ) == 1 )
				{
					if( utf8_string_size > 0 )
					{
						libwrc_string_table_resource_get_utf8_string(
						 string_table_resource,
						 0,
						 utf8_string,
						 384,
						 NULL );
					}
				}
				if( libwrc_string_table_resource_get_utf16_string_size(
	                    string_table_resource,
	                    0,
	                    &utf16_string_size,
	                    NULL ) == 1 )
				{
					if( utf16_string_size > 0 )
					{
						libwrc_string_table_resource_get_utf16_string(
						 string_table_resource,
						 0,
						 utf16_string,
						 384,
						 NULL );
					}
				}
			}
		}
	}
	libwrc_string_table_resource_free(
	 &string_table_resource,
	 NULL );

	return( 0 );
}

} /* extern "C" */
