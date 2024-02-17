/*
 * Library version_information_resource type test program
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

#include "../libwrc/libwrc_version_information_resource.h"

uint8_t wrc_test_version_information_resource_data1[ 764 ] = {
	0xfc, 0x02, 0x34, 0x00, 0x00, 0x00, 0x56, 0x00, 0x53, 0x00, 0x5f, 0x00, 0x56, 0x00, 0x45, 0x00,
	0x52, 0x00, 0x53, 0x00, 0x49, 0x00, 0x4f, 0x00, 0x4e, 0x00, 0x5f, 0x00, 0x49, 0x00, 0x4e, 0x00,
	0x46, 0x00, 0x4f, 0x00, 0x00, 0x00, 0x00, 0x00, 0xbd, 0x04, 0xef, 0xfe, 0x00, 0x00, 0x01, 0x00,
	0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x5c, 0x02, 0x00, 0x00,
	0x01, 0x00, 0x53, 0x00, 0x74, 0x00, 0x72, 0x00, 0x69, 0x00, 0x6e, 0x00, 0x67, 0x00, 0x46, 0x00,
	0x69, 0x00, 0x6c, 0x00, 0x65, 0x00, 0x49, 0x00, 0x6e, 0x00, 0x66, 0x00, 0x6f, 0x00, 0x00, 0x00,
	0x38, 0x02, 0x00, 0x00, 0x01, 0x00, 0x30, 0x00, 0x34, 0x00, 0x30, 0x00, 0x39, 0x00, 0x30, 0x00,
	0x34, 0x00, 0x65, 0x00, 0x34, 0x00, 0x00, 0x00, 0x2a, 0x00, 0x09, 0x00, 0x01, 0x00, 0x43, 0x00,
	0x6f, 0x00, 0x6d, 0x00, 0x6d, 0x00, 0x65, 0x00, 0x6e, 0x00, 0x74, 0x00, 0x73, 0x00, 0x00, 0x00,
	0x43, 0x00, 0x6f, 0x00, 0x6d, 0x00, 0x6d, 0x00, 0x65, 0x00, 0x6e, 0x00, 0x74, 0x00, 0x73, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x5e, 0x00, 0x1b, 0x00, 0x01, 0x00, 0x46, 0x00, 0x69, 0x00, 0x6c, 0x00,
	0x65, 0x00, 0x44, 0x00, 0x65, 0x00, 0x73, 0x00, 0x63, 0x00, 0x72, 0x00, 0x69, 0x00, 0x70, 0x00,
	0x74, 0x00, 0x69, 0x00, 0x6f, 0x00, 0x6e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x57, 0x00, 0x69, 0x00,
	0x6e, 0x00, 0x64, 0x00, 0x6f, 0x00, 0x77, 0x00, 0x73, 0x00, 0x20, 0x00, 0x52, 0x00, 0x65, 0x00,
	0x73, 0x00, 0x6f, 0x00, 0x75, 0x00, 0x72, 0x00, 0x63, 0x00, 0x65, 0x00, 0x20, 0x00, 0x74, 0x00,
	0x65, 0x00, 0x73, 0x00, 0x74, 0x00, 0x20, 0x00, 0x66, 0x00, 0x69, 0x00, 0x6c, 0x00, 0x65, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x2c, 0x00, 0x06, 0x00, 0x01, 0x00, 0x46, 0x00, 0x69, 0x00, 0x6c, 0x00,
	0x65, 0x00, 0x56, 0x00, 0x65, 0x00, 0x72, 0x00, 0x73, 0x00, 0x69, 0x00, 0x6f, 0x00, 0x6e, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x31, 0x00, 0x2e, 0x00, 0x30, 0x00, 0x2e, 0x00, 0x30, 0x00, 0x00, 0x00,
	0x3a, 0x00, 0x0d, 0x00, 0x01, 0x00, 0x49, 0x00, 0x6e, 0x00, 0x74, 0x00, 0x65, 0x00, 0x72, 0x00,
	0x6e, 0x00, 0x61, 0x00, 0x6c, 0x00, 0x4e, 0x00, 0x61, 0x00, 0x6d, 0x00, 0x65, 0x00, 0x00, 0x00,
	0x77, 0x00, 0x72, 0x00, 0x63, 0x00, 0x5f, 0x00, 0x74, 0x00, 0x65, 0x00, 0x73, 0x00, 0x74, 0x00,
	0x2e, 0x00, 0x64, 0x00, 0x6c, 0x00, 0x6c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x84, 0x00, 0x30, 0x00,
	0x01, 0x00, 0x4c, 0x00, 0x65, 0x00, 0x67, 0x00, 0x61, 0x00, 0x6c, 0x00, 0x43, 0x00, 0x6f, 0x00,
	0x70, 0x00, 0x79, 0x00, 0x72, 0x00, 0x69, 0x00, 0x67, 0x00, 0x68, 0x00, 0x74, 0x00, 0x00, 0x00,
	0x28, 0x00, 0x43, 0x00, 0x29, 0x00, 0x20, 0x00, 0x32, 0x00, 0x30, 0x00, 0x31, 0x00, 0x37, 0x00,
	0x2c, 0x00, 0x20, 0x00, 0x4a, 0x00, 0x6f, 0x00, 0x61, 0x00, 0x63, 0x00, 0x68, 0x00, 0x69, 0x00,
	0x6d, 0x00, 0x20, 0x00, 0x4d, 0x00, 0x65, 0x00, 0x74, 0x00, 0x7a, 0x00, 0x20, 0x00, 0x3c, 0x00,
	0x6a, 0x00, 0x6f, 0x00, 0x61, 0x00, 0x63, 0x00, 0x68, 0x00, 0x69, 0x00, 0x6d, 0x00, 0x2e, 0x00,
	0x6d, 0x00, 0x65, 0x00, 0x74, 0x00, 0x7a, 0x00, 0x40, 0x00, 0x67, 0x00, 0x6d, 0x00, 0x61, 0x00,
	0x69, 0x00, 0x6c, 0x00, 0x2e, 0x00, 0x63, 0x00, 0x6f, 0x00, 0x6d, 0x00, 0x3e, 0x00, 0x00, 0x00,
	0x42, 0x00, 0x0d, 0x00, 0x01, 0x00, 0x4f, 0x00, 0x72, 0x00, 0x69, 0x00, 0x67, 0x00, 0x69, 0x00,
	0x6e, 0x00, 0x61, 0x00, 0x6c, 0x00, 0x46, 0x00, 0x69, 0x00, 0x6c, 0x00, 0x65, 0x00, 0x6e, 0x00,
	0x61, 0x00, 0x6d, 0x00, 0x65, 0x00, 0x00, 0x00, 0x77, 0x00, 0x72, 0x00, 0x63, 0x00, 0x5f, 0x00,
	0x74, 0x00, 0x65, 0x00, 0x73, 0x00, 0x74, 0x00, 0x2e, 0x00, 0x64, 0x00, 0x6c, 0x00, 0x6c, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x32, 0x00, 0x09, 0x00, 0x01, 0x00, 0x50, 0x00, 0x72, 0x00, 0x6f, 0x00,
	0x64, 0x00, 0x75, 0x00, 0x63, 0x00, 0x74, 0x00, 0x4e, 0x00, 0x61, 0x00, 0x6d, 0x00, 0x65, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x77, 0x00, 0x72, 0x00, 0x63, 0x00, 0x5f, 0x00, 0x74, 0x00, 0x65, 0x00,
	0x73, 0x00, 0x74, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x06, 0x00, 0x01, 0x00, 0x50, 0x00,
	0x72, 0x00, 0x6f, 0x00, 0x64, 0x00, 0x75, 0x00, 0x63, 0x00, 0x74, 0x00, 0x56, 0x00, 0x65, 0x00,
	0x72, 0x00, 0x73, 0x00, 0x69, 0x00, 0x6f, 0x00, 0x6e, 0x00, 0x00, 0x00, 0x31, 0x00, 0x2e, 0x00,
	0x30, 0x00, 0x2e, 0x00, 0x30, 0x00, 0x00, 0x00, 0x44, 0x00, 0x00, 0x00, 0x01, 0x00, 0x56, 0x00,
	0x61, 0x00, 0x72, 0x00, 0x46, 0x00, 0x69, 0x00, 0x6c, 0x00, 0x65, 0x00, 0x49, 0x00, 0x6e, 0x00,
	0x66, 0x00, 0x6f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x24, 0x00, 0x04, 0x00, 0x00, 0x00, 0x54, 0x00,
	0x72, 0x00, 0x61, 0x00, 0x6e, 0x00, 0x73, 0x00, 0x6c, 0x00, 0x61, 0x00, 0x74, 0x00, 0x69, 0x00,
	0x6f, 0x00, 0x6e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x04, 0xe4, 0x04 };

/* Tests the libwrc_version_information_resource_initialize function
 * Returns 1 if successful or 0 if not
 */
int wrc_test_version_information_resource_initialize(
     void )
{
	libcerror_error_t *error                                            = NULL;
	libwrc_version_information_resource_t *version_information_resource = NULL;
	int result                                                          = 0;

#if defined( HAVE_WRC_TEST_MEMORY )
	int number_of_malloc_fail_tests                                     = 1;
	int number_of_memset_fail_tests                                     = 1;
	int test_number                                                     = 0;
#endif

	/* Test regular cases
	 */
	result = libwrc_version_information_resource_initialize(
	          &version_information_resource,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_IS_NOT_NULL(
	 "version_information_resource",
	 version_information_resource );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libwrc_version_information_resource_free(
	          &version_information_resource,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_IS_NULL(
	 "version_information_resource",
	 version_information_resource );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libwrc_version_information_resource_initialize(
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

	version_information_resource = (libwrc_version_information_resource_t *) 0x12345678UL;

	result = libwrc_version_information_resource_initialize(
	          &version_information_resource,
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

	version_information_resource = NULL;

#if defined( HAVE_WRC_TEST_MEMORY )

	for( test_number = 0;
	     test_number < number_of_malloc_fail_tests;
	     test_number++ )
	{
		/* Test libwrc_version_information_resource_initialize with malloc failing
		 */
		wrc_test_malloc_attempts_before_fail = test_number;

		result = libwrc_version_information_resource_initialize(
		          &version_information_resource,
		          &error );

		if( wrc_test_malloc_attempts_before_fail != -1 )
		{
			wrc_test_malloc_attempts_before_fail = -1;

			if( version_information_resource != NULL )
			{
				libwrc_version_information_resource_free(
				 &version_information_resource,
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
			 "version_information_resource",
			 version_information_resource );

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
		/* Test libwrc_version_information_resource_initialize with memset failing
		 */
		wrc_test_memset_attempts_before_fail = test_number;

		result = libwrc_version_information_resource_initialize(
		          &version_information_resource,
		          &error );

		if( wrc_test_memset_attempts_before_fail != -1 )
		{
			wrc_test_memset_attempts_before_fail = -1;

			if( version_information_resource != NULL )
			{
				libwrc_version_information_resource_free(
				 &version_information_resource,
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
			 "version_information_resource",
			 version_information_resource );

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
	if( version_information_resource != NULL )
	{
		libwrc_version_information_resource_free(
		 &version_information_resource,
		 NULL );
	}
	return( 0 );
}

/* Tests the libwrc_version_information_resource_free function
 * Returns 1 if successful or 0 if not
 */
int wrc_test_version_information_resource_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libwrc_version_information_resource_free(
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

/* Tests the libwrc_version_information_resource_read function
 * Returns 1 if successful or 0 if not
 */
int wrc_test_version_information_resource_read(
     void )
{
	libcerror_error_t *error                                            = NULL;
	libwrc_version_information_resource_t *version_information_resource = NULL;
	int result                                                          = 0;

	/* Initialize test
	 */
	result = libwrc_version_information_resource_initialize(
	          &version_information_resource,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_IS_NOT_NULL(
	 "version_information_resource",
	 version_information_resource );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libwrc_version_information_resource_read(
	          version_information_resource,
	          wrc_test_version_information_resource_data1,
	          764,
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
	result = libwrc_version_information_resource_read(
	          NULL,
	          wrc_test_version_information_resource_data1,
	          764,
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

	result = libwrc_version_information_resource_read(
	          version_information_resource,
	          NULL,
	          764,
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

	result = libwrc_version_information_resource_read(
	          version_information_resource,
	          wrc_test_version_information_resource_data1,
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

	result = libwrc_version_information_resource_read(
	          version_information_resource,
	          wrc_test_version_information_resource_data1,
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
	result = libwrc_version_information_resource_free(
	          &version_information_resource,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_IS_NULL(
	 "version_information_resource",
	 version_information_resource );

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
	if( version_information_resource != NULL )
	{
		libwrc_version_information_resource_free(
		 &version_information_resource,
		 NULL );
	}
	return( 0 );
}

/* Tests the libwrc_version_information_resource_get_file_version function
 * Returns 1 if successful or 0 if not
 */
int wrc_test_version_information_resource_get_file_version(
     libwrc_version_information_resource_t *version_information_resource )
{
	libcerror_error_t *error = NULL;
	uint64_t file_version    = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libwrc_version_information_resource_get_file_version(
	          version_information_resource,
	          &file_version,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_EQUAL_UINT64(
	 "file_version",
	 file_version,
	 (uint64_t) 0x1000000000000UL );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libwrc_version_information_resource_get_file_version(
	          NULL,
	          &file_version,
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

	result = libwrc_version_information_resource_get_file_version(
	          version_information_resource,
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

/* Tests the libwrc_version_information_resource_get_product_version function
 * Returns 1 if successful or 0 if not
 */
int wrc_test_version_information_resource_get_product_version(
     libwrc_version_information_resource_t *version_information_resource )
{
	libcerror_error_t *error = NULL;
	uint64_t product_version = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libwrc_version_information_resource_get_product_version(
	          version_information_resource,
	          &product_version,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_EQUAL_UINT64(
	 "product_version",
	 product_version,
	 (uint64_t) 0x1000000000000UL );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libwrc_version_information_resource_get_product_version(
	          NULL,
	          &product_version,
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

	result = libwrc_version_information_resource_get_product_version(
	          version_information_resource,
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
	libcerror_error_t *error                                            = NULL;
	libwrc_version_information_resource_t *version_information_resource = NULL;
	int result                                                          = 0;

	WRC_TEST_UNREFERENCED_PARAMETER( argc )
	WRC_TEST_UNREFERENCED_PARAMETER( argv )

	WRC_TEST_RUN(
	 "libwrc_version_information_resource_initialize",
	 wrc_test_version_information_resource_initialize );

	WRC_TEST_RUN(
	 "libwrc_version_information_resource_free",
	 wrc_test_version_information_resource_free );

	WRC_TEST_RUN(
	 "libwrc_version_information_resource_read",
	 wrc_test_version_information_resource_read );

#if !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 )

	/* Initialize version_information_resource for tests
	 */
	result = libwrc_version_information_resource_initialize(
	          &version_information_resource,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_IS_NOT_NULL(
	 "version_information_resource",
	 version_information_resource );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libwrc_version_information_resource_read(
	          version_information_resource,
	          wrc_test_version_information_resource_data1,
	          764,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	WRC_TEST_RUN_WITH_ARGS(
	 "libwrc_version_information_resource_get_file_version",
	 wrc_test_version_information_resource_get_file_version,
	 version_information_resource );

	WRC_TEST_RUN_WITH_ARGS(
	 "libwrc_version_information_resource_get_product_version",
	 wrc_test_version_information_resource_get_product_version,
	 version_information_resource );

	/* Clean up
	 */
	result = libwrc_version_information_resource_free(
	          &version_information_resource,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_IS_NULL(
	 "version_information_resource",
	 version_information_resource );

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
	if( version_information_resource != NULL )
	{
		libwrc_version_information_resource_free(
		 &version_information_resource,
		 NULL );
	}
	return( EXIT_FAILURE );
}

