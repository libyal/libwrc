/*
 * Library message_table_resource type test program
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

#include "../libwrc/libwrc_message_table_resource.h"

uint8_t wrc_test_message_table_resource_data1[ 120 ] = {
	0x02, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00,
	0xe8, 0x03, 0x00, 0x00, 0xe8, 0x03, 0x00, 0x00, 0x54, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00,
	0x43, 0x61, 0x74, 0x65, 0x67, 0x6f, 0x72, 0x79, 0x0d, 0x0a, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00,
	0x4d, 0x79, 0x20, 0x6d, 0x65, 0x73, 0x73, 0x61, 0x67, 0x65, 0x20, 0x77, 0x69, 0x74, 0x68, 0x20,
	0x70, 0x61, 0x72, 0x61, 0x6d, 0x65, 0x74, 0x65, 0x72, 0x73, 0x20, 0x25, 0x31, 0x20, 0x25, 0x32,
	0x2e, 0x0d, 0x0a, 0x00, 0x24, 0x00, 0x00, 0x00, 0x4d, 0x79, 0x20, 0x6d, 0x65, 0x73, 0x73, 0x61,
	0x67, 0x65, 0x20, 0x77, 0x69, 0x74, 0x68, 0x6f, 0x75, 0x74, 0x20, 0x70, 0x61, 0x72, 0x61, 0x6d,
	0x65, 0x74, 0x65, 0x72, 0x73, 0x0d, 0x0a, 0x00 };

/* Tests the libwrc_message_table_resource_initialize function
 * Returns 1 if successful or 0 if not
 */
int wrc_test_message_table_resource_initialize(
     void )
{
	libcerror_error_t *error                                = NULL;
	libwrc_message_table_resource_t *message_table_resource = NULL;
	int result                                              = 0;

#if defined( HAVE_WRC_TEST_MEMORY )
	int number_of_malloc_fail_tests                         = 2;
	int number_of_memset_fail_tests                         = 1;
	int test_number                                         = 0;
#endif

	/* Test regular cases
	 */
	result = libwrc_message_table_resource_initialize(
	          &message_table_resource,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_IS_NOT_NULL(
	 "message_table_resource",
	 message_table_resource );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libwrc_message_table_resource_free(
	          &message_table_resource,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_IS_NULL(
	 "message_table_resource",
	 message_table_resource );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libwrc_message_table_resource_initialize(
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

	message_table_resource = (libwrc_message_table_resource_t *) 0x12345678UL;

	result = libwrc_message_table_resource_initialize(
	          &message_table_resource,
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

	message_table_resource = NULL;

#if defined( HAVE_WRC_TEST_MEMORY )

	for( test_number = 0;
	     test_number < number_of_malloc_fail_tests;
	     test_number++ )
	{
		/* Test libwrc_message_table_resource_initialize with malloc failing
		 */
		wrc_test_malloc_attempts_before_fail = test_number;

		result = libwrc_message_table_resource_initialize(
		          &message_table_resource,
		          &error );

		if( wrc_test_malloc_attempts_before_fail != -1 )
		{
			wrc_test_malloc_attempts_before_fail = -1;

			if( message_table_resource != NULL )
			{
				libwrc_message_table_resource_free(
				 &message_table_resource,
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
			 "message_table_resource",
			 message_table_resource );

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
		/* Test libwrc_message_table_resource_initialize with memset failing
		 */
		wrc_test_memset_attempts_before_fail = test_number;

		result = libwrc_message_table_resource_initialize(
		          &message_table_resource,
		          &error );

		if( wrc_test_memset_attempts_before_fail != -1 )
		{
			wrc_test_memset_attempts_before_fail = -1;

			if( message_table_resource != NULL )
			{
				libwrc_message_table_resource_free(
				 &message_table_resource,
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
			 "message_table_resource",
			 message_table_resource );

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
	if( message_table_resource != NULL )
	{
		libwrc_message_table_resource_free(
		 &message_table_resource,
		 NULL );
	}
	return( 0 );
}

/* Tests the libwrc_message_table_resource_free function
 * Returns 1 if successful or 0 if not
 */
int wrc_test_message_table_resource_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libwrc_message_table_resource_free(
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

/* Tests the libwrc_message_table_resource_read function
 * Returns 1 if successful or 0 if not
 */
int wrc_test_message_table_resource_read(
     void )
{
	libcerror_error_t *error                                = NULL;
	libwrc_message_table_resource_t *message_table_resource = NULL;
	int result                                              = 0;

	/* Initialize test
	 */
	result = libwrc_message_table_resource_initialize(
	          &message_table_resource,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_IS_NOT_NULL(
	 "message_table_resource",
	 message_table_resource );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libwrc_message_table_resource_read(
	          message_table_resource,
	          wrc_test_message_table_resource_data1,
	          120,
	          LIBWRC_CODEPAGE_WINDOWS_1252,
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
	result = libwrc_message_table_resource_read(
	          NULL,
	          wrc_test_message_table_resource_data1,
	          120,
	          LIBWRC_CODEPAGE_WINDOWS_1252,
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

	result = libwrc_message_table_resource_read(
	          message_table_resource,
	          NULL,
	          120,
	          LIBWRC_CODEPAGE_WINDOWS_1252,
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

	result = libwrc_message_table_resource_read(
	          message_table_resource,
	          wrc_test_message_table_resource_data1,
	          0,
	          LIBWRC_CODEPAGE_WINDOWS_1252,
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

	result = libwrc_message_table_resource_read(
	          message_table_resource,
	          wrc_test_message_table_resource_data1,
	          (size_t) SSIZE_MAX + 1,
	          LIBWRC_CODEPAGE_WINDOWS_1252,
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
	result = libwrc_message_table_resource_free(
	          &message_table_resource,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_IS_NULL(
	 "message_table_resource",
	 message_table_resource );

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
	if( message_table_resource != NULL )
	{
		libwrc_message_table_resource_free(
		 &message_table_resource,
		 NULL );
	}
	return( 0 );
}

/* Tests the libwrc_message_table_resource_get_number_of_messages function
 * Returns 1 if successful or 0 if not
 */
int wrc_test_message_table_resource_get_number_of_messages(
     libwrc_message_table_resource_t *message_table_resource )
{
	libcerror_error_t *error = NULL;
	int number_of_messages   = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libwrc_message_table_resource_get_number_of_messages(
	          message_table_resource,
	          &number_of_messages,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "number_of_messages",
	 number_of_messages,
	 3 );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libwrc_message_table_resource_get_number_of_messages(
	          NULL,
	          &number_of_messages,
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

	result = libwrc_message_table_resource_get_number_of_messages(
	          message_table_resource,
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

/* Tests the libwrc_message_table_resource_get_identifier function
 * Returns 1 if successful or 0 if not
 */
int wrc_test_message_table_resource_get_identifier(
     libwrc_message_table_resource_t *message_table_resource )
{
	libcerror_error_t *error     = NULL;
	uint32_t messages_identifier = 0;
	int result                   = 0;

	/* Test regular cases
	 */
	result = libwrc_message_table_resource_get_identifier(
	          message_table_resource,
	          2,
	          &messages_identifier,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_EQUAL_UINT32(
	 "messages_identifier",
	 messages_identifier,
	 (uint32_t) 0x000003e8UL );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libwrc_message_table_resource_get_identifier(
	          NULL,
	          2,
	          &messages_identifier,
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

	result = libwrc_message_table_resource_get_identifier(
	          message_table_resource,
	          -1,
	          &messages_identifier,
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

	result = libwrc_message_table_resource_get_identifier(
	          message_table_resource,
	          2,
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

/* Tests the libwrc_message_table_resource_get_index_by_identifier function
 * Returns 1 if successful or 0 if not
 */
int wrc_test_message_table_resource_get_index_by_identifier(
     libwrc_message_table_resource_t *message_table_resource )
{
	libcerror_error_t *error = NULL;
	int messages_index       = 0;
	int result               = 0;

	/* Test regular cases
	 */
	messages_index = -1;

	result = libwrc_message_table_resource_get_index_by_identifier(
	          message_table_resource,
	          (uint32_t) 0x000003e8UL,
	          &messages_index,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "messages_index",
	 messages_index,
	 2 );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	messages_index = -1;

	result = libwrc_message_table_resource_get_index_by_identifier(
	          message_table_resource,
	          (uint32_t) 0x00001234UL,
	          &messages_index,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "messages_index",
	 messages_index,
	 -1 );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	messages_index = -1;

	result = libwrc_message_table_resource_get_index_by_identifier(
	          NULL,
	          (uint32_t) 0x000003e8UL,
	          &messages_index,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "messages_index",
	 messages_index,
	 -1 );

	WRC_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libwrc_message_table_resource_get_index_by_identifier(
	          message_table_resource,
	          (uint32_t) 0x000003e8UL,
	          NULL,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "messages_index",
	 messages_index,
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

/* Tests the libwrc_message_table_resource_get_utf8_string_size function
 * Returns 1 if successful or 0 if not
 */
int wrc_test_message_table_resource_get_utf8_string_size(
     libwrc_message_table_resource_t *message_table_resource )
{
	libcerror_error_t *error = NULL;
	size_t utf8_string_size  = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libwrc_message_table_resource_get_utf8_string_size(
	          message_table_resource,
	          0,
	          &utf8_string_size,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_EQUAL_SIZE(
	 "utf8_string_size",
	 utf8_string_size,
	 (size_t) 11 );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libwrc_message_table_resource_get_utf8_string_size(
	          NULL,
	          0,
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

	result = libwrc_message_table_resource_get_utf8_string_size(
	          message_table_resource,
	          -1,
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

	result = libwrc_message_table_resource_get_utf8_string_size(
	          message_table_resource,
	          0,
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

/* Tests the libwrc_message_table_resource_get_utf8_string function
 * Returns 1 if successful or 0 if not
 */
int wrc_test_message_table_resource_get_utf8_string(
     libwrc_message_table_resource_t *message_table_resource )
{
	uint8_t utf8_string[ 32 ];

	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test regular cases
	 */
	result = libwrc_message_table_resource_get_utf8_string(
	          message_table_resource,
	          0,
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
	result = libwrc_message_table_resource_get_utf8_string(
	          NULL,
	          0,
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

	result = libwrc_message_table_resource_get_utf8_string(
	          message_table_resource,
	          -1,
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

	result = libwrc_message_table_resource_get_utf8_string(
	          message_table_resource,
	          0,
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

	result = libwrc_message_table_resource_get_utf8_string(
	          message_table_resource,
	          0,
	          utf8_string,
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

	result = libwrc_message_table_resource_get_utf8_string(
	          message_table_resource,
	          0,
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

/* Tests the libwrc_message_table_resource_get_utf16_string_size function
 * Returns 1 if successful or 0 if not
 */
int wrc_test_message_table_resource_get_utf16_string_size(
     libwrc_message_table_resource_t *message_table_resource )
{
	libcerror_error_t *error = NULL;
	size_t utf16_string_size = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libwrc_message_table_resource_get_utf16_string_size(
	          message_table_resource,
	          0,
	          &utf16_string_size,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_EQUAL_SIZE(
	 "utf16_string_size",
	 utf16_string_size,
	 (size_t) 11 );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libwrc_message_table_resource_get_utf16_string_size(
	          NULL,
	          0,
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

	result = libwrc_message_table_resource_get_utf16_string_size(
	          message_table_resource,
	          -1,
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

	result = libwrc_message_table_resource_get_utf16_string_size(
	          message_table_resource,
	          0,
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

/* Tests the libwrc_message_table_resource_get_utf16_string function
 * Returns 1 if successful or 0 if not
 */
int wrc_test_message_table_resource_get_utf16_string(
     libwrc_message_table_resource_t *message_table_resource )
{
	uint16_t utf16_string[ 32 ];

	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test regular cases
	 */
	result = libwrc_message_table_resource_get_utf16_string(
	          message_table_resource,
	          0,
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
	result = libwrc_message_table_resource_get_utf16_string(
	          NULL,
	          0,
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

	result = libwrc_message_table_resource_get_utf16_string(
	          message_table_resource,
	          -1,
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

	result = libwrc_message_table_resource_get_utf16_string(
	          message_table_resource,
	          0,
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

	result = libwrc_message_table_resource_get_utf16_string(
	          message_table_resource,
	          0,
	          utf16_string,
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

	result = libwrc_message_table_resource_get_utf16_string(
	          message_table_resource,
	          0,
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
	libcerror_error_t *error                                = NULL;
	libwrc_message_table_resource_t *message_table_resource = NULL;
	int result                                              = 0;

	WRC_TEST_UNREFERENCED_PARAMETER( argc )
	WRC_TEST_UNREFERENCED_PARAMETER( argv )

	WRC_TEST_RUN(
	 "libwrc_message_table_resource_initialize",
	 wrc_test_message_table_resource_initialize );

	WRC_TEST_RUN(
	 "libwrc_message_table_resource_free",
	 wrc_test_message_table_resource_free );

	WRC_TEST_RUN(
	 "libwrc_message_table_resource_read",
	 wrc_test_message_table_resource_read );

#if !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 )

	/* Initialize message_table_resource for tests
	 */
	result = libwrc_message_table_resource_initialize(
	          &message_table_resource,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_IS_NOT_NULL(
	 "message_table_resource",
	 message_table_resource );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libwrc_message_table_resource_read(
	          message_table_resource,
	          wrc_test_message_table_resource_data1,
	          120,
	          LIBWRC_CODEPAGE_WINDOWS_1252,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	WRC_TEST_RUN_WITH_ARGS(
	 "libwrc_message_table_resource_get_number_of_messages",
	 wrc_test_message_table_resource_get_number_of_messages,
	 message_table_resource );

	WRC_TEST_RUN_WITH_ARGS(
	 "libwrc_message_table_resource_get_identifier",
	 wrc_test_message_table_resource_get_identifier,
	 message_table_resource );

	WRC_TEST_RUN_WITH_ARGS(
	 "libwrc_message_table_resource_get_index_by_identifier",
	 wrc_test_message_table_resource_get_index_by_identifier,
	 message_table_resource );

	WRC_TEST_RUN_WITH_ARGS(
	 "libwrc_message_table_resource_get_utf8_string_size",
	 wrc_test_message_table_resource_get_utf8_string_size,
	 message_table_resource );

	WRC_TEST_RUN_WITH_ARGS(
	 "libwrc_message_table_resource_get_utf8_string",
	 wrc_test_message_table_resource_get_utf8_string,
	 message_table_resource );

	WRC_TEST_RUN_WITH_ARGS(
	 "libwrc_message_table_resource_get_utf16_string_size",
	 wrc_test_message_table_resource_get_utf16_string_size,
	 message_table_resource );

	WRC_TEST_RUN_WITH_ARGS(
	 "libwrc_message_table_resource_get_utf16_string",
	 wrc_test_message_table_resource_get_utf16_string,
	 message_table_resource );

	/* Clean up
	 */
	result = libwrc_message_table_resource_free(
	          &message_table_resource,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_IS_NULL(
	 "message_table_resource",
	 message_table_resource );

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
	if( message_table_resource != NULL )
	{
		libwrc_message_table_resource_free(
		 &message_table_resource,
		 NULL );
	}
	return( EXIT_FAILURE );
}

