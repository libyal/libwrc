/*
 * Library manifest_resource type test program
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

#include "../libwrc/libwrc_manifest_resource.h"

uint8_t wrc_test_manifest_resource_data1[ 381 ] = {
	0x3c, 0x3f, 0x78, 0x6d, 0x6c, 0x20, 0x76, 0x65, 0x72, 0x73, 0x69, 0x6f, 0x6e, 0x3d, 0x27, 0x31,
	0x2e, 0x30, 0x27, 0x20, 0x65, 0x6e, 0x63, 0x6f, 0x64, 0x69, 0x6e, 0x67, 0x3d, 0x27, 0x55, 0x54,
	0x46, 0x2d, 0x38, 0x27, 0x20, 0x73, 0x74, 0x61, 0x6e, 0x64, 0x61, 0x6c, 0x6f, 0x6e, 0x65, 0x3d,
	0x27, 0x79, 0x65, 0x73, 0x27, 0x3f, 0x3e, 0x0d, 0x0a, 0x3c, 0x61, 0x73, 0x73, 0x65, 0x6d, 0x62,
	0x6c, 0x79, 0x20, 0x78, 0x6d, 0x6c, 0x6e, 0x73, 0x3d, 0x27, 0x75, 0x72, 0x6e, 0x3a, 0x73, 0x63,
	0x68, 0x65, 0x6d, 0x61, 0x73, 0x2d, 0x6d, 0x69, 0x63, 0x72, 0x6f, 0x73, 0x6f, 0x66, 0x74, 0x2d,
	0x63, 0x6f, 0x6d, 0x3a, 0x61, 0x73, 0x6d, 0x2e, 0x76, 0x31, 0x27, 0x20, 0x6d, 0x61, 0x6e, 0x69,
	0x66, 0x65, 0x73, 0x74, 0x56, 0x65, 0x72, 0x73, 0x69, 0x6f, 0x6e, 0x3d, 0x27, 0x31, 0x2e, 0x30,
	0x27, 0x3e, 0x0d, 0x0a, 0x20, 0x20, 0x3c, 0x74, 0x72, 0x75, 0x73, 0x74, 0x49, 0x6e, 0x66, 0x6f,
	0x20, 0x78, 0x6d, 0x6c, 0x6e, 0x73, 0x3d, 0x22, 0x75, 0x72, 0x6e, 0x3a, 0x73, 0x63, 0x68, 0x65,
	0x6d, 0x61, 0x73, 0x2d, 0x6d, 0x69, 0x63, 0x72, 0x6f, 0x73, 0x6f, 0x66, 0x74, 0x2d, 0x63, 0x6f,
	0x6d, 0x3a, 0x61, 0x73, 0x6d, 0x2e, 0x76, 0x33, 0x22, 0x3e, 0x0d, 0x0a, 0x20, 0x20, 0x20, 0x20,
	0x3c, 0x73, 0x65, 0x63, 0x75, 0x72, 0x69, 0x74, 0x79, 0x3e, 0x0d, 0x0a, 0x20, 0x20, 0x20, 0x20,
	0x20, 0x20, 0x3c, 0x72, 0x65, 0x71, 0x75, 0x65, 0x73, 0x74, 0x65, 0x64, 0x50, 0x72, 0x69, 0x76,
	0x69, 0x6c, 0x65, 0x67, 0x65, 0x73, 0x3e, 0x0d, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
	0x20, 0x3c, 0x72, 0x65, 0x71, 0x75, 0x65, 0x73, 0x74, 0x65, 0x64, 0x45, 0x78, 0x65, 0x63, 0x75,
	0x74, 0x69, 0x6f, 0x6e, 0x4c, 0x65, 0x76, 0x65, 0x6c, 0x20, 0x6c, 0x65, 0x76, 0x65, 0x6c, 0x3d,
	0x27, 0x61, 0x73, 0x49, 0x6e, 0x76, 0x6f, 0x6b, 0x65, 0x72, 0x27, 0x20, 0x75, 0x69, 0x41, 0x63,
	0x63, 0x65, 0x73, 0x73, 0x3d, 0x27, 0x66, 0x61, 0x6c, 0x73, 0x65, 0x27, 0x20, 0x2f, 0x3e, 0x0d,
	0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x2f, 0x72, 0x65, 0x71, 0x75, 0x65, 0x73, 0x74,
	0x65, 0x64, 0x50, 0x72, 0x69, 0x76, 0x69, 0x6c, 0x65, 0x67, 0x65, 0x73, 0x3e, 0x0d, 0x0a, 0x20,
	0x20, 0x20, 0x20, 0x3c, 0x2f, 0x73, 0x65, 0x63, 0x75, 0x72, 0x69, 0x74, 0x79, 0x3e, 0x0d, 0x0a,
	0x20, 0x20, 0x3c, 0x2f, 0x74, 0x72, 0x75, 0x73, 0x74, 0x49, 0x6e, 0x66, 0x6f, 0x3e, 0x0d, 0x0a,
	0x3c, 0x2f, 0x61, 0x73, 0x73, 0x65, 0x6d, 0x62, 0x6c, 0x79, 0x3e, 0x0d, 0x0a };

/* Tests the libwrc_manifest_resource_initialize function
 * Returns 1 if successful or 0 if not
 */
int wrc_test_manifest_resource_initialize(
     void )
{
	libcerror_error_t *error                      = NULL;
	libwrc_manifest_resource_t *manifest_resource = NULL;
	int result                                    = 0;

#if defined( HAVE_WRC_TEST_MEMORY )
	int number_of_malloc_fail_tests               = 1;
	int number_of_memset_fail_tests               = 1;
	int test_number                               = 0;
#endif

	/* Test regular cases
	 */
	result = libwrc_manifest_resource_initialize(
	          &manifest_resource,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_IS_NOT_NULL(
	 "manifest_resource",
	 manifest_resource );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libwrc_manifest_resource_free(
	          &manifest_resource,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_IS_NULL(
	 "manifest_resource",
	 manifest_resource );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libwrc_manifest_resource_initialize(
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

	manifest_resource = (libwrc_manifest_resource_t *) 0x12345678UL;

	result = libwrc_manifest_resource_initialize(
	          &manifest_resource,
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

	manifest_resource = NULL;

#if defined( HAVE_WRC_TEST_MEMORY )

	for( test_number = 0;
	     test_number < number_of_malloc_fail_tests;
	     test_number++ )
	{
		/* Test libwrc_manifest_resource_initialize with malloc failing
		 */
		wrc_test_malloc_attempts_before_fail = test_number;

		result = libwrc_manifest_resource_initialize(
		          &manifest_resource,
		          &error );

		if( wrc_test_malloc_attempts_before_fail != -1 )
		{
			wrc_test_malloc_attempts_before_fail = -1;

			if( manifest_resource != NULL )
			{
				libwrc_manifest_resource_free(
				 &manifest_resource,
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
			 "manifest_resource",
			 manifest_resource );

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
		/* Test libwrc_manifest_resource_initialize with memset failing
		 */
		wrc_test_memset_attempts_before_fail = test_number;

		result = libwrc_manifest_resource_initialize(
		          &manifest_resource,
		          &error );

		if( wrc_test_memset_attempts_before_fail != -1 )
		{
			wrc_test_memset_attempts_before_fail = -1;

			if( manifest_resource != NULL )
			{
				libwrc_manifest_resource_free(
				 &manifest_resource,
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
			 "manifest_resource",
			 manifest_resource );

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
	if( manifest_resource != NULL )
	{
		libwrc_manifest_resource_free(
		 &manifest_resource,
		 NULL );
	}
	return( 0 );
}

/* Tests the libwrc_manifest_resource_free function
 * Returns 1 if successful or 0 if not
 */
int wrc_test_manifest_resource_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libwrc_manifest_resource_free(
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

/* Tests the libwrc_manifest_resource_read function
 * Returns 1 if successful or 0 if not
 */
int wrc_test_manifest_resource_read(
     void )
{
	libcerror_error_t *error                      = NULL;
	libwrc_manifest_resource_t *manifest_resource = NULL;
	int result                                    = 0;

	/* Initialize test
	 */
	result = libwrc_manifest_resource_initialize(
	          &manifest_resource,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_IS_NOT_NULL(
	 "manifest_resource",
	 manifest_resource );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libwrc_manifest_resource_read(
	          manifest_resource,
	          wrc_test_manifest_resource_data1,
	          381,
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
	result = libwrc_manifest_resource_read(
	          NULL,
	          wrc_test_manifest_resource_data1,
	          381,
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

	result = libwrc_manifest_resource_read(
	          manifest_resource,
	          NULL,
	          381,
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

	result = libwrc_manifest_resource_read(
	          manifest_resource,
	          wrc_test_manifest_resource_data1,
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

	result = libwrc_manifest_resource_read(
	          manifest_resource,
	          wrc_test_manifest_resource_data1,
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
	result = libwrc_manifest_resource_free(
	          &manifest_resource,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_IS_NULL(
	 "manifest_resource",
	 manifest_resource );

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
	if( manifest_resource != NULL )
	{
		libwrc_manifest_resource_free(
		 &manifest_resource,
		 NULL );
	}
	return( 0 );
}

/* Tests the libwrc_manifest_resource_get_utf8_string_size function
 * Returns 1 if successful or 0 if not
 */
int wrc_test_manifest_resource_get_utf8_string_size(
     libwrc_manifest_resource_t *manifest_resource )
{
	libcerror_error_t *error = NULL;
	size_t utf8_string_size  = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libwrc_manifest_resource_get_utf8_string_size(
	          manifest_resource,
	          &utf8_string_size,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_EQUAL_SIZE(
	 "utf8_string_size",
	 utf8_string_size,
	 (size_t) 382 );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libwrc_manifest_resource_get_utf8_string_size(
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

	result = libwrc_manifest_resource_get_utf8_string_size(
	          manifest_resource,
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

/* Tests the libwrc_manifest_resource_get_utf8_string function
 * Returns 1 if successful or 0 if not
 */
int wrc_test_manifest_resource_get_utf8_string(
     libwrc_message_table_resource_t *message_table_resource )
{
	uint8_t utf8_string[ 384 ];

	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test regular cases
	 */
	result = libwrc_manifest_resource_get_utf8_string(
	          message_table_resource,
	          utf8_string,
	          384,
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
	result = libwrc_manifest_resource_get_utf8_string(
	          NULL,
	          utf8_string,
	          384,
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

	result = libwrc_manifest_resource_get_utf8_string(
	          message_table_resource,
	          NULL,
	          384,
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

	result = libwrc_manifest_resource_get_utf8_string(
	          message_table_resource,
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

	result = libwrc_manifest_resource_get_utf8_string(
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

/* Tests the libwrc_manifest_resource_get_utf16_string_size function
 * Returns 1 if successful or 0 if not
 */
int wrc_test_manifest_resource_get_utf16_string_size(
     libwrc_manifest_resource_t *manifest_resource )
{
	libcerror_error_t *error = NULL;
	size_t utf16_string_size = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libwrc_manifest_resource_get_utf16_string_size(
	          manifest_resource,
	          &utf16_string_size,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_EQUAL_SIZE(
	 "utf16_string_size",
	 utf16_string_size,
	 (size_t) 382 );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libwrc_manifest_resource_get_utf16_string_size(
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

	result = libwrc_manifest_resource_get_utf16_string_size(
	          manifest_resource,
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

/* Tests the libwrc_manifest_resource_get_utf16_string function
 * Returns 1 if successful or 0 if not
 */
int wrc_test_manifest_resource_get_utf16_string(
     libwrc_message_table_resource_t *message_table_resource )
{
	uint16_t utf16_string[ 384 ];

	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test regular cases
	 */
	result = libwrc_manifest_resource_get_utf16_string(
	          message_table_resource,
	          utf16_string,
	          384,
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
	result = libwrc_manifest_resource_get_utf16_string(
	          NULL,
	          utf16_string,
	          384,
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

	result = libwrc_manifest_resource_get_utf16_string(
	          message_table_resource,
	          NULL,
	          384,
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

	result = libwrc_manifest_resource_get_utf16_string(
	          message_table_resource,
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

	result = libwrc_manifest_resource_get_utf16_string(
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
	libwrc_manifest_resource_t *manifest_resource = NULL;
	int result                                    = 0;

	WRC_TEST_UNREFERENCED_PARAMETER( argc )
	WRC_TEST_UNREFERENCED_PARAMETER( argv )

	WRC_TEST_RUN(
	 "libwrc_manifest_resource_initialize",
	 wrc_test_manifest_resource_initialize );

	WRC_TEST_RUN(
	 "libwrc_manifest_resource_free",
	 wrc_test_manifest_resource_free );

	WRC_TEST_RUN(
	 "libwrc_manifest_resource_read",
	 wrc_test_manifest_resource_read );

#if !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 )

	/* Initialize manifest_resource for tests
	 */
	result = libwrc_manifest_resource_initialize(
	          &manifest_resource,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_IS_NOT_NULL(
	 "manifest_resource",
	 manifest_resource );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libwrc_manifest_resource_read(
	          manifest_resource,
	          wrc_test_manifest_resource_data1,
	          381,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	WRC_TEST_RUN_WITH_ARGS(
	 "libwrc_manifest_resource_get_utf8_string_size",
	 wrc_test_manifest_resource_get_utf8_string_size,
	 manifest_resource );

	WRC_TEST_RUN_WITH_ARGS(
	 "libwrc_manifest_resource_get_utf8_string",
	 wrc_test_manifest_resource_get_utf8_string,
	 manifest_resource );

	WRC_TEST_RUN_WITH_ARGS(
	 "libwrc_manifest_resource_get_utf16_string_size",
	 wrc_test_manifest_resource_get_utf16_string_size,
	 manifest_resource );

	WRC_TEST_RUN_WITH_ARGS(
	 "libwrc_manifest_resource_get_utf16_string",
	 wrc_test_manifest_resource_get_utf16_string,
	 manifest_resource );

	/* Clean up
	 */
	result = libwrc_manifest_resource_free(
	          &manifest_resource,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_IS_NULL(
	 "manifest_resource",
	 manifest_resource );

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
	if( manifest_resource != NULL )
	{
		libwrc_manifest_resource_free(
		 &manifest_resource,
		 NULL );
	}
	return( EXIT_FAILURE );
}

