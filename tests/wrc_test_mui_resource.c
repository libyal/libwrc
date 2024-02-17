/*
 * Library mui_resource type test program
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

#include <common.h>
#include <file_stream.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "wrc_test_libcerror.h"
#include "wrc_test_libwrc.h"
#include "wrc_test_macros.h"
#include "wrc_test_memory.h"
#include "wrc_test_unused.h"

#include "../libwrc/libwrc_mui_resource.h"

uint8_t wrc_test_mui_resource_data1[ 232 ] = {
	0xcd, 0xfe, 0xcd, 0xfe, 0xe8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x11, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x9d, 0x73, 0x62, 0x3d,
	0x3f, 0x20, 0x93, 0x35, 0x58, 0xe7, 0x05, 0x7b, 0xb7, 0xf4, 0xd0, 0x03, 0xfb, 0xf0, 0xa9, 0x8b,
	0xbe, 0xdb, 0xf7, 0xb9, 0xb0, 0x39, 0x07, 0xe0, 0x06, 0xc4, 0x0e, 0xff, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x88, 0x00, 0x00, 0x00, 0x2a, 0x00, 0x00, 0x00, 0xb8, 0x00, 0x00, 0x00,
	0x08, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x00, 0xd0, 0x00, 0x00, 0x00,
	0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xd8, 0x00, 0x00, 0x00,
	0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x57, 0x00, 0x45, 0x00, 0x56, 0x00, 0x54, 0x00,
	0x5f, 0x00, 0x54, 0x00, 0x45, 0x00, 0x4d, 0x00, 0x50, 0x00, 0x4c, 0x00, 0x41, 0x00, 0x54, 0x00,
	0x45, 0x00, 0x00, 0x00, 0x4d, 0x00, 0x55, 0x00, 0x49, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0b, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00,
	0x4d, 0x00, 0x55, 0x00, 0x49, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x0b, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x65, 0x00, 0x6e, 0x00, 0x2d, 0x00, 0x55, 0x00,
	0x53, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

/* Tests the libwrc_mui_resource_initialize function
 * Returns 1 if successful or 0 if not
 */
int wrc_test_mui_resource_initialize(
     void )
{
	libcerror_error_t *error            = NULL;
	libwrc_mui_resource_t *mui_resource = NULL;
	int result                          = 0;

#if defined( HAVE_WRC_TEST_MEMORY )
	int number_of_malloc_fail_tests     = 1;
	int number_of_memset_fail_tests     = 1;
	int test_number                     = 0;
#endif

	/* Test regular cases
	 */
	result = libwrc_mui_resource_initialize(
	          &mui_resource,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_IS_NOT_NULL(
	 "mui_resource",
	 mui_resource );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libwrc_mui_resource_free(
	          &mui_resource,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_IS_NULL(
	 "mui_resource",
	 mui_resource );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libwrc_mui_resource_initialize(
	          NULL,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	WRC_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	mui_resource = (libwrc_mui_resource_t *) 0x12345678UL;

	result = libwrc_mui_resource_initialize(
	          &mui_resource,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	WRC_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	mui_resource = NULL;

#if defined( HAVE_WRC_TEST_MEMORY )

	for( test_number = 0;
	     test_number < number_of_malloc_fail_tests;
	     test_number++ )
	{
		/* Test libwrc_mui_resource_initialize with malloc failing
		 */
		wrc_test_malloc_attempts_before_fail = test_number;

		result = libwrc_mui_resource_initialize(
		          &mui_resource,
		          &error );

		if( wrc_test_malloc_attempts_before_fail != -1 )
		{
			wrc_test_malloc_attempts_before_fail = -1;

			if( mui_resource != NULL )
			{
				libwrc_mui_resource_free(
				 &mui_resource,
				 NULL );
			}
		}
		else
		{
			WRC_TEST_ASSERT_EQUAL_INT(
			 "result",
			 result,
			 -1 );

			WRC_TEST_ASSERT_IS_NULL(
			 "mui_resource",
			 mui_resource );

			WRC_TEST_ASSERT_IS_NOT_NULL(
			 "error",
			 error );

			libcerror_error_free(
			 &error );
		}
	}
	for( test_number = 0;
	     test_number < number_of_memset_fail_tests;
	     test_number++ )
	{
		/* Test libwrc_mui_resource_initialize with memset failing
		 */
		wrc_test_memset_attempts_before_fail = test_number;

		result = libwrc_mui_resource_initialize(
		          &mui_resource,
		          &error );

		if( wrc_test_memset_attempts_before_fail != -1 )
		{
			wrc_test_memset_attempts_before_fail = -1;

			if( mui_resource != NULL )
			{
				libwrc_mui_resource_free(
				 &mui_resource,
				 NULL );
			}
		}
		else
		{
			WRC_TEST_ASSERT_EQUAL_INT(
			 "result",
			 result,
			 -1 );

			WRC_TEST_ASSERT_IS_NULL(
			 "mui_resource",
			 mui_resource );

			WRC_TEST_ASSERT_IS_NOT_NULL(
			 "error",
			 error );

			libcerror_error_free(
			 &error );
		}
	}
#endif /* defined( HAVE_WRC_TEST_MEMORY ) */

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( mui_resource != NULL )
	{
		libwrc_mui_resource_free(
		 &mui_resource,
		 NULL );
	}
	return( 0 );
}

/* Tests the libwrc_mui_resource_free function
 * Returns 1 if successful or 0 if not
 */
int wrc_test_mui_resource_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libwrc_mui_resource_free(
	          NULL,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	WRC_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libwrc_mui_resource_read function
 * Returns 1 if successful or 0 if not
 */
int wrc_test_mui_resource_read(
     void )
{
	libcerror_error_t *error            = NULL;
	libwrc_mui_resource_t *mui_resource = NULL;
	int result                          = 0;

	/* Initialize test
	 */
	result = libwrc_mui_resource_initialize(
	          &mui_resource,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_IS_NOT_NULL(
	 "mui_resource",
	 mui_resource );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libwrc_mui_resource_read(
	          mui_resource,
	          wrc_test_mui_resource_data1,
	          232,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libwrc_mui_resource_read(
	          NULL,
	          wrc_test_mui_resource_data1,
	          232,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	WRC_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libwrc_mui_resource_read(
	          mui_resource,
	          NULL,
	          232,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	WRC_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libwrc_mui_resource_read(
	          mui_resource,
	          wrc_test_mui_resource_data1,
	          0,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	WRC_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libwrc_mui_resource_read(
	          mui_resource,
	          wrc_test_mui_resource_data1,
	          (size_t) SSIZE_MAX + 1,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	WRC_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	result = libwrc_mui_resource_free(
	          &mui_resource,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_IS_NULL(
	 "mui_resource",
	 mui_resource );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( mui_resource != NULL )
	{
		libwrc_mui_resource_free(
		 &mui_resource,
		 NULL );
	}
	return( 0 );
}

/* Tests the libwrc_mui_resource_get_file_type function
 * Returns 1 if successful or 0 if not
 */
int wrc_test_mui_resource_get_file_type(
     libwrc_mui_resource_t *mui_resource )
{
	libcerror_error_t *error = NULL;
	uint32_t file_type       = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libwrc_mui_resource_get_file_type(
	          mui_resource,
	          &file_type,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_EQUAL_UINT32(
	 "file_type",
	 file_type,
	 (uint32_t) 17 );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libwrc_mui_resource_get_file_type(
	          NULL,
	          &file_type,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	WRC_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libwrc_mui_resource_get_file_type(
	          mui_resource,
	          NULL,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	WRC_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libwrc_mui_resource_get_utf8_main_name_size function
 * Returns 1 if successful or 0 if not
 */
int wrc_test_mui_resource_get_utf8_main_name_size(
     libwrc_mui_resource_t *mui_resource )
{
	libcerror_error_t *error = NULL;
	size_t utf8_string_size  = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libwrc_mui_resource_get_utf8_main_name_size(
	          mui_resource,
	          &utf8_string_size,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_EQUAL_SIZE(
	 "utf8_string_size",
	 utf8_string_size,
	 (size_t) 14 );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libwrc_mui_resource_get_utf8_main_name_size(
	          NULL,
	          &utf8_string_size,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	WRC_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libwrc_mui_resource_get_utf8_main_name_size(
	          mui_resource,
	          NULL,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	WRC_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libwrc_mui_resource_get_utf8_main_name function
 * Returns 1 if successful or 0 if not
 */
int wrc_test_mui_resource_get_utf8_main_name(
     libwrc_message_table_resource_t *message_table_resource )
{
	uint8_t utf8_string[ 32 ];

	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test regular cases
	 */
	result = libwrc_mui_resource_get_utf8_main_name(
	          message_table_resource,
	          utf8_string,
	          32,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

/* TODO compare string */

	/* Test error cases
	 */
	result = libwrc_mui_resource_get_utf8_main_name(
	          NULL,
	          utf8_string,
	          32,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	WRC_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libwrc_mui_resource_get_utf8_main_name(
	          message_table_resource,
	          NULL,
	          32,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	WRC_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libwrc_mui_resource_get_utf8_main_name(
	          message_table_resource,
	          utf8_string,
	          (size_t) SSIZE_MAX + 1,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	WRC_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libwrc_mui_resource_get_utf16_main_name_size function
 * Returns 1 if successful or 0 if not
 */
int wrc_test_mui_resource_get_utf16_main_name_size(
     libwrc_mui_resource_t *mui_resource )
{
	libcerror_error_t *error = NULL;
	size_t utf16_string_size = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libwrc_mui_resource_get_utf16_main_name_size(
	          mui_resource,
	          &utf16_string_size,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_EQUAL_SIZE(
	 "utf16_string_size",
	 utf16_string_size,
	 (size_t) 14 );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libwrc_mui_resource_get_utf16_main_name_size(
	          NULL,
	          &utf16_string_size,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	WRC_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libwrc_mui_resource_get_utf16_main_name_size(
	          mui_resource,
	          NULL,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	WRC_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libwrc_mui_resource_get_utf16_main_name function
 * Returns 1 if successful or 0 if not
 */
int wrc_test_mui_resource_get_utf16_main_name(
     libwrc_message_table_resource_t *message_table_resource )
{
	uint16_t utf16_string[ 32 ];

	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test regular cases
	 */
	result = libwrc_mui_resource_get_utf16_main_name(
	          message_table_resource,
	          utf16_string,
	          32,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

/* TODO compare string */

	/* Test error cases
	 */
	result = libwrc_mui_resource_get_utf16_main_name(
	          NULL,
	          utf16_string,
	          32,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	WRC_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libwrc_mui_resource_get_utf16_main_name(
	          message_table_resource,
	          NULL,
	          32,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	WRC_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libwrc_mui_resource_get_utf16_main_name(
	          message_table_resource,
	          utf16_string,
	          (size_t) SSIZE_MAX + 1,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	WRC_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libwrc_mui_resource_get_utf8_mui_name_size function
 * Returns 1 if successful or 0 if not
 */
int wrc_test_mui_resource_get_utf8_mui_name_size(
     libwrc_mui_resource_t *mui_resource )
{
	libcerror_error_t *error = NULL;
	size_t utf8_string_size  = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libwrc_mui_resource_get_utf8_mui_name_size(
	          mui_resource,
	          &utf8_string_size,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_EQUAL_SIZE(
	 "utf8_string_size",
	 utf8_string_size,
	 (size_t) 4 );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libwrc_mui_resource_get_utf8_mui_name_size(
	          NULL,
	          &utf8_string_size,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	WRC_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libwrc_mui_resource_get_utf8_mui_name_size(
	          mui_resource,
	          NULL,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	WRC_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libwrc_mui_resource_get_utf8_mui_name function
 * Returns 1 if successful or 0 if not
 */
int wrc_test_mui_resource_get_utf8_mui_name(
     libwrc_message_table_resource_t *message_table_resource )
{
	uint8_t utf8_string[ 32 ];

	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test regular cases
	 */
	result = libwrc_mui_resource_get_utf8_mui_name(
	          message_table_resource,
	          utf8_string,
	          32,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

/* TODO compare string */

	/* Test error cases
	 */
	result = libwrc_mui_resource_get_utf8_mui_name(
	          NULL,
	          utf8_string,
	          32,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	WRC_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libwrc_mui_resource_get_utf8_mui_name(
	          message_table_resource,
	          NULL,
	          32,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	WRC_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libwrc_mui_resource_get_utf8_mui_name(
	          message_table_resource,
	          utf8_string,
	          (size_t) SSIZE_MAX + 1,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	WRC_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libwrc_mui_resource_get_utf16_mui_name_size function
 * Returns 1 if successful or 0 if not
 */
int wrc_test_mui_resource_get_utf16_mui_name_size(
     libwrc_mui_resource_t *mui_resource )
{
	libcerror_error_t *error = NULL;
	size_t utf16_string_size = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libwrc_mui_resource_get_utf16_mui_name_size(
	          mui_resource,
	          &utf16_string_size,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_EQUAL_SIZE(
	 "utf16_string_size",
	 utf16_string_size,
	 (size_t) 4 );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libwrc_mui_resource_get_utf16_mui_name_size(
	          NULL,
	          &utf16_string_size,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	WRC_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libwrc_mui_resource_get_utf16_mui_name_size(
	          mui_resource,
	          NULL,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	WRC_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libwrc_mui_resource_get_utf16_mui_name function
 * Returns 1 if successful or 0 if not
 */
int wrc_test_mui_resource_get_utf16_mui_name(
     libwrc_message_table_resource_t *message_table_resource )
{
	uint16_t utf16_string[ 32 ];

	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test regular cases
	 */
	result = libwrc_mui_resource_get_utf16_mui_name(
	          message_table_resource,
	          utf16_string,
	          32,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

/* TODO compare string */

	/* Test error cases
	 */
	result = libwrc_mui_resource_get_utf16_mui_name(
	          NULL,
	          utf16_string,
	          32,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	WRC_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libwrc_mui_resource_get_utf16_mui_name(
	          message_table_resource,
	          NULL,
	          32,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	WRC_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libwrc_mui_resource_get_utf16_mui_name(
	          message_table_resource,
	          utf16_string,
	          (size_t) SSIZE_MAX + 1,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	WRC_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libwrc_mui_resource_get_utf8_language_size function
 * Returns 1 if successful or 0 if not
 */
int wrc_test_mui_resource_get_utf8_language_size(
     libwrc_mui_resource_t *mui_resource )
{
	libcerror_error_t *error = NULL;
	size_t utf8_string_size  = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libwrc_mui_resource_get_utf8_language_size(
	          mui_resource,
	          &utf8_string_size,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_EQUAL_SIZE(
	 "utf8_string_size",
	 utf8_string_size,
	 (size_t) 6 );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libwrc_mui_resource_get_utf8_language_size(
	          NULL,
	          &utf8_string_size,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	WRC_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libwrc_mui_resource_get_utf8_language_size(
	          mui_resource,
	          NULL,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	WRC_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libwrc_mui_resource_get_utf8_language function
 * Returns 1 if successful or 0 if not
 */
int wrc_test_mui_resource_get_utf8_language(
     libwrc_message_table_resource_t *message_table_resource )
{
	uint8_t utf8_string[ 32 ];

	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test regular cases
	 */
	result = libwrc_mui_resource_get_utf8_language(
	          message_table_resource,
	          utf8_string,
	          32,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

/* TODO compare string */

	/* Test error cases
	 */
	result = libwrc_mui_resource_get_utf8_language(
	          NULL,
	          utf8_string,
	          32,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	WRC_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libwrc_mui_resource_get_utf8_language(
	          message_table_resource,
	          NULL,
	          32,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	WRC_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libwrc_mui_resource_get_utf8_language(
	          message_table_resource,
	          utf8_string,
	          (size_t) SSIZE_MAX + 1,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	WRC_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libwrc_mui_resource_get_utf16_language_size function
 * Returns 1 if successful or 0 if not
 */
int wrc_test_mui_resource_get_utf16_language_size(
     libwrc_mui_resource_t *mui_resource )
{
	libcerror_error_t *error = NULL;
	size_t utf16_string_size = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libwrc_mui_resource_get_utf16_language_size(
	          mui_resource,
	          &utf16_string_size,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_EQUAL_SIZE(
	 "utf16_string_size",
	 utf16_string_size,
	 (size_t) 6 );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libwrc_mui_resource_get_utf16_language_size(
	          NULL,
	          &utf16_string_size,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	WRC_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libwrc_mui_resource_get_utf16_language_size(
	          mui_resource,
	          NULL,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	WRC_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libwrc_mui_resource_get_utf16_language function
 * Returns 1 if successful or 0 if not
 */
int wrc_test_mui_resource_get_utf16_language(
     libwrc_message_table_resource_t *message_table_resource )
{
	uint16_t utf16_string[ 32 ];

	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test regular cases
	 */
	result = libwrc_mui_resource_get_utf16_language(
	          message_table_resource,
	          utf16_string,
	          32,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

/* TODO compare string */

	/* Test error cases
	 */
	result = libwrc_mui_resource_get_utf16_language(
	          NULL,
	          utf16_string,
	          32,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	WRC_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libwrc_mui_resource_get_utf16_language(
	          message_table_resource,
	          NULL,
	          32,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	WRC_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libwrc_mui_resource_get_utf16_language(
	          message_table_resource,
	          utf16_string,
	          (size_t) SSIZE_MAX + 1,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	WRC_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libwrc_mui_resource_get_utf8_fallback_language_size function
 * Returns 1 if successful or 0 if not
 */
int wrc_test_mui_resource_get_utf8_fallback_language_size(
     libwrc_mui_resource_t *mui_resource )
{
	libcerror_error_t *error = NULL;
	size_t utf8_string_size  = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libwrc_mui_resource_get_utf8_fallback_language_size(
	          mui_resource,
	          &utf8_string_size,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_EQUAL_SIZE(
	 "utf8_string_size",
	 utf8_string_size,
	 (size_t) 6 );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libwrc_mui_resource_get_utf8_fallback_language_size(
	          NULL,
	          &utf8_string_size,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	WRC_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libwrc_mui_resource_get_utf8_fallback_language_size(
	          mui_resource,
	          NULL,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	WRC_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libwrc_mui_resource_get_utf8_fallback_language function
 * Returns 1 if successful or 0 if not
 */
int wrc_test_mui_resource_get_utf8_fallback_language(
     libwrc_message_table_resource_t *message_table_resource )
{
	uint8_t utf8_string[ 32 ];

	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test regular cases
	 */
	result = libwrc_mui_resource_get_utf8_fallback_language(
	          message_table_resource,
	          utf8_string,
	          32,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

/* TODO compare string */

	/* Test error cases
	 */
	result = libwrc_mui_resource_get_utf8_fallback_language(
	          NULL,
	          utf8_string,
	          32,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	WRC_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libwrc_mui_resource_get_utf8_fallback_language(
	          message_table_resource,
	          NULL,
	          32,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	WRC_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libwrc_mui_resource_get_utf8_fallback_language(
	          message_table_resource,
	          utf8_string,
	          (size_t) SSIZE_MAX + 1,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	WRC_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libwrc_mui_resource_get_utf16_fallback_language_size function
 * Returns 1 if successful or 0 if not
 */
int wrc_test_mui_resource_get_utf16_fallback_language_size(
     libwrc_mui_resource_t *mui_resource )
{
	libcerror_error_t *error = NULL;
	size_t utf16_string_size = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libwrc_mui_resource_get_utf16_fallback_language_size(
	          mui_resource,
	          &utf16_string_size,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_EQUAL_SIZE(
	 "utf16_string_size",
	 utf16_string_size,
	 (size_t) 6 );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libwrc_mui_resource_get_utf16_fallback_language_size(
	          NULL,
	          &utf16_string_size,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	WRC_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libwrc_mui_resource_get_utf16_fallback_language_size(
	          mui_resource,
	          NULL,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	WRC_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libwrc_mui_resource_get_utf16_fallback_language function
 * Returns 1 if successful or 0 if not
 */
int wrc_test_mui_resource_get_utf16_fallback_language(
     libwrc_message_table_resource_t *message_table_resource )
{
	uint16_t utf16_string[ 32 ];

	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test regular cases
	 */
	result = libwrc_mui_resource_get_utf16_fallback_language(
	          message_table_resource,
	          utf16_string,
	          32,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

/* TODO compare string */

	/* Test error cases
	 */
	result = libwrc_mui_resource_get_utf16_fallback_language(
	          NULL,
	          utf16_string,
	          32,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	WRC_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libwrc_mui_resource_get_utf16_fallback_language(
	          message_table_resource,
	          NULL,
	          32,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	WRC_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libwrc_mui_resource_get_utf16_fallback_language(
	          message_table_resource,
	          utf16_string,
	          (size_t) SSIZE_MAX + 1,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	WRC_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* The main program
 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
int wmain(
     int argc WRC_TEST_ATTRIBUTE_UNUSED,
     wchar_t * const argv[] WRC_TEST_ATTRIBUTE_UNUSED )
#else
int main(
     int argc WRC_TEST_ATTRIBUTE_UNUSED,
     char * const argv[] WRC_TEST_ATTRIBUTE_UNUSED )
#endif
{
	libcerror_error_t *error                      = NULL;
	libwrc_mui_resource_t *mui_resource = NULL;
	int result                                    = 0;

	WRC_TEST_UNREFERENCED_PARAMETER( argc )
	WRC_TEST_UNREFERENCED_PARAMETER( argv )

	WRC_TEST_RUN(
	 "libwrc_mui_resource_initialize",
	 wrc_test_mui_resource_initialize );

	WRC_TEST_RUN(
	 "libwrc_mui_resource_free",
	 wrc_test_mui_resource_free );

	WRC_TEST_RUN(
	 "libwrc_mui_resource_read",
	 wrc_test_mui_resource_read );

#if !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 )

	/* Initialize mui_resource for tests
	 */
	result = libwrc_mui_resource_initialize(
	          &mui_resource,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_IS_NOT_NULL(
	 "mui_resource",
	 mui_resource );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libwrc_mui_resource_read(
	          mui_resource,
	          wrc_test_mui_resource_data1,
	          232,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	WRC_TEST_RUN_WITH_ARGS(
	 "libwrc_mui_resource_get_file_type",
	 wrc_test_mui_resource_get_file_type,
	 mui_resource );

	WRC_TEST_RUN_WITH_ARGS(
	 "libwrc_mui_resource_get_utf8_main_name_size",
	 wrc_test_mui_resource_get_utf8_main_name_size,
	 mui_resource );

	WRC_TEST_RUN_WITH_ARGS(
	 "libwrc_mui_resource_get_utf8_main_name",
	 wrc_test_mui_resource_get_utf8_main_name,
	 mui_resource );

	WRC_TEST_RUN_WITH_ARGS(
	 "libwrc_mui_resource_get_utf16_main_name_size",
	 wrc_test_mui_resource_get_utf16_main_name_size,
	 mui_resource );

	WRC_TEST_RUN_WITH_ARGS(
	 "libwrc_mui_resource_get_utf16_main_name",
	 wrc_test_mui_resource_get_utf16_main_name,
	 mui_resource );

	WRC_TEST_RUN_WITH_ARGS(
	 "libwrc_mui_resource_get_utf8_mui_name_size",
	 wrc_test_mui_resource_get_utf8_mui_name_size,
	 mui_resource );

	WRC_TEST_RUN_WITH_ARGS(
	 "libwrc_mui_resource_get_utf8_mui_name",
	 wrc_test_mui_resource_get_utf8_mui_name,
	 mui_resource );

	WRC_TEST_RUN_WITH_ARGS(
	 "libwrc_mui_resource_get_utf16_mui_name_size",
	 wrc_test_mui_resource_get_utf16_mui_name_size,
	 mui_resource );

	WRC_TEST_RUN_WITH_ARGS(
	 "libwrc_mui_resource_get_utf16_mui_name",
	 wrc_test_mui_resource_get_utf16_mui_name,
	 mui_resource );

	WRC_TEST_RUN_WITH_ARGS(
	 "libwrc_mui_resource_get_utf8_language_size",
	 wrc_test_mui_resource_get_utf8_language_size,
	 mui_resource );

	WRC_TEST_RUN_WITH_ARGS(
	 "libwrc_mui_resource_get_utf8_language",
	 wrc_test_mui_resource_get_utf8_language,
	 mui_resource );

	WRC_TEST_RUN_WITH_ARGS(
	 "libwrc_mui_resource_get_utf16_language_size",
	 wrc_test_mui_resource_get_utf16_language_size,
	 mui_resource );

	WRC_TEST_RUN_WITH_ARGS(
	 "libwrc_mui_resource_get_utf16_language",
	 wrc_test_mui_resource_get_utf16_language,
	 mui_resource );

	WRC_TEST_RUN_WITH_ARGS(
	 "libwrc_mui_resource_get_utf8_fallback_language_size",
	 wrc_test_mui_resource_get_utf8_fallback_language_size,
	 mui_resource );

	WRC_TEST_RUN_WITH_ARGS(
	 "libwrc_mui_resource_get_utf8_fallback_language",
	 wrc_test_mui_resource_get_utf8_fallback_language,
	 mui_resource );

	WRC_TEST_RUN_WITH_ARGS(
	 "libwrc_mui_resource_get_utf16_fallback_language_size",
	 wrc_test_mui_resource_get_utf16_fallback_language_size,
	 mui_resource );

	WRC_TEST_RUN_WITH_ARGS(
	 "libwrc_mui_resource_get_utf16_fallback_language",
	 wrc_test_mui_resource_get_utf16_fallback_language,
	 mui_resource );

	/* Clean up
	 */
	result = libwrc_mui_resource_free(
	          &mui_resource,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_IS_NULL(
	 "mui_resource",
	 mui_resource );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

#endif /* !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 ) */

	return( EXIT_SUCCESS );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( mui_resource != NULL )
	{
		libwrc_mui_resource_free(
		 &mui_resource,
		 NULL );
	}
	return( EXIT_FAILURE );
}

