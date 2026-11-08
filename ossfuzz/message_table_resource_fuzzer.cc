/*
 * OSS-Fuzz target for libwrc message_table_resource type
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

	libwrc_message_table_resource_t *message_table_resource = NULL;
	size_t utf8_string_size                                 = 0;
	size_t utf16_string_size                                = 0;
	uint32_t message_identifier                             = 0;
	int message_index                                       = 0;
	int number_of_messages                                  = 0;

	if( libwrc_message_table_resource_initialize(
	     &message_table_resource,
	     NULL ) != 1 )
	{
		return( 0 );
	}
	if( libwrc_message_table_resource_read(
	     message_table_resource,
	     data,
	     size,
	     LIBWRC_CODEPAGE_WINDOWS_1252,
	     NULL ) == 1 )
	{
		if( libwrc_message_table_resource_get_number_of_messages(
	            message_table_resource,
	            &number_of_messages,
	            NULL ) == 1 )
		{
			if( number_of_messages > 0 )
			{
				if( libwrc_message_table_resource_get_identifier(
	                    message_table_resource,
	                    0,
	                    &message_identifier,
	                    NULL ) == 1 )
				{
					libwrc_message_table_resource_get_index_by_identifier(
					 message_table_resource,
					 message_identifier,
					 &message_index,
					 NULL );
				}
				if( libwrc_message_table_resource_get_utf8_string_size(
	                    message_table_resource,
	                    0,
	                    &utf8_string_size,
	                    NULL ) == 1 )
				{
					if( utf8_string_size > 0 )
					{
						libwrc_message_table_resource_get_utf8_string(
						 message_table_resource,
						 0,
						 utf8_string,
						 384,
						 NULL );
					}
				}
				if( libwrc_message_table_resource_get_utf16_string_size(
	                    message_table_resource,
	                    0,
	                    &utf16_string_size,
	                    NULL ) == 1 )
				{
					if( utf16_string_size > 0 )
					{
						libwrc_message_table_resource_get_utf16_string(
						 message_table_resource,
						 0,
						 utf16_string,
						 384,
						 NULL );
					}
				}
			}
		}
	}
	libwrc_message_table_resource_free(
	 &message_table_resource,
	 NULL );

	return( 0 );
}

} /* extern "C" */
