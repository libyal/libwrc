/*
 * Library resource_node_entry type test program
 *
 * Copyright (C) 2009-2021, Joachim Metz <joachim.metz@gmail.com>
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

#include "wrc_test_functions.h"
#include "wrc_test_libbfio.h"
#include "wrc_test_libcerror.h"
#include "wrc_test_libwrc.h"
#include "wrc_test_macros.h"
#include "wrc_test_memory.h"
#include "wrc_test_unused.h"

#include "../libwrc/libwrc_resource_node_entry.h"

uint8_t wrc_test_resource_node_entry_data1[ 8 ] = {
	0x06, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x80 };

#if defined( __GNUC__ ) && !defined( LIBWRC_DLL_IMPORT )

/* Tests the libwrc_resource_node_entry_initialize function
 * Returns 1 if successful or 0 if not
 */
int wrc_test_resource_node_entry_initialize(
     void )
{
	libcerror_error_t *error                          = NULL;
	libwrc_resource_node_entry_t *resource_node_entry = NULL;
	int result                                        = 0;

#if defined( HAVE_WRC_TEST_MEMORY )
	int number_of_malloc_fail_tests                   = 1;
	int number_of_memset_fail_tests                   = 1;
	int test_number                                   = 0;
#endif

	/* Test regular cases
	 */
	result = libwrc_resource_node_entry_initialize(
	          &resource_node_entry,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_IS_NOT_NULL(
	 "resource_node_entry",
	 resource_node_entry );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libwrc_resource_node_entry_free(
	          &resource_node_entry,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_IS_NULL(
	 "resource_node_entry",
	 resource_node_entry );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libwrc_resource_node_entry_initialize(
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

	resource_node_entry = (libwrc_resource_node_entry_t *) 0x12345678UL;

	result = libwrc_resource_node_entry_initialize(
	          &resource_node_entry,
	          &error );

	resource_node_entry = NULL;

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	WRC_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

#if defined( HAVE_WRC_TEST_MEMORY )

	for( test_number = 0;
	     test_number < number_of_malloc_fail_tests;
	     test_number++ )
	{
		/* Test libwrc_resource_node_entry_initialize with malloc failing
		 */
		wrc_test_malloc_attempts_before_fail = test_number;

		result = libwrc_resource_node_entry_initialize(
		          &resource_node_entry,
		          &error );

		if( wrc_test_malloc_attempts_before_fail != -1 )
		{
			wrc_test_malloc_attempts_before_fail = -1;

			if( resource_node_entry != NULL )
			{
				libwrc_resource_node_entry_free(
				 &resource_node_entry,
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
			 "resource_node_entry",
			 resource_node_entry );

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
		/* Test libwrc_resource_node_entry_initialize with memset failing
		 */
		wrc_test_memset_attempts_before_fail = test_number;

		result = libwrc_resource_node_entry_initialize(
		          &resource_node_entry,
		          &error );

		if( wrc_test_memset_attempts_before_fail != -1 )
		{
			wrc_test_memset_attempts_before_fail = -1;

			if( resource_node_entry != NULL )
			{
				libwrc_resource_node_entry_free(
				 &resource_node_entry,
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
			 "resource_node_entry",
			 resource_node_entry );

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
	if( resource_node_entry != NULL )
	{
		libwrc_resource_node_entry_free(
		 &resource_node_entry,
		 NULL );
	}
	return( 0 );
}

/* Tests the libwrc_resource_node_entry_free function
 * Returns 1 if successful or 0 if not
 */
int wrc_test_resource_node_entry_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libwrc_resource_node_entry_free(
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

/* Tests the libwrc_resource_node_entry_read_data function
 * Returns 1 if successful or 0 if not
 */
int wrc_test_resource_node_entry_read_data(
     void )
{
	libcerror_error_t *error                          = NULL;
	libwrc_resource_node_entry_t *resource_node_entry = NULL;
	int result                                        = 0;

	/* Initialize test
	 */
	result = libwrc_resource_node_entry_initialize(
	          &resource_node_entry,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_IS_NOT_NULL(
	 "resource_node_entry",
	 resource_node_entry );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libwrc_resource_node_entry_read_data(
	          resource_node_entry,
	          wrc_test_resource_node_entry_data1,
	          8,
	          1,
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
	result = libwrc_resource_node_entry_read_data(
	          NULL,
	          wrc_test_resource_node_entry_data1,
	          8,
	          1,
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

	result = libwrc_resource_node_entry_read_data(
	          resource_node_entry,
	          NULL,
	          8,
	          1,
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

	result = libwrc_resource_node_entry_read_data(
	          resource_node_entry,
	          wrc_test_resource_node_entry_data1,
	          0,
	          1,
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

	result = libwrc_resource_node_entry_read_data(
	          resource_node_entry,
	          wrc_test_resource_node_entry_data1,
	          (size_t) SSIZE_MAX + 1,
	          1,
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

#if defined( HAVE_WRC_TEST_MEMORY )

	/* Test wrc_test_resource_node_entry_read_data with memcpy failing
	 */
	wrc_test_memcpy_attempts_before_fail = 0;

	result = libwrc_resource_node_entry_read_data(
	          resource_node_entry,
	          wrc_test_resource_node_entry_data1,
	          8,
	          1,
	          &error );

	if( wrc_test_memcpy_attempts_before_fail != -1 )
	{
		wrc_test_memcpy_attempts_before_fail = -1;
	}
	else
	{
		WRC_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		WRC_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#endif /* defined( HAVE_WRC_TEST_MEMORY ) */

	/* Clean up
	 */
	result = libwrc_resource_node_entry_free(
	          &resource_node_entry,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_IS_NULL(
	 "resource_node_entry",
	 resource_node_entry );

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
	if( resource_node_entry != NULL )
	{
		libwrc_resource_node_entry_free(
		 &resource_node_entry,
		 NULL );
	}
	return( 0 );
}

/* Tests the libwrc_resource_node_entry_read_file_io_handle function
 * Returns 1 if successful or 0 if not
 */
int wrc_test_resource_node_entry_read_file_io_handle(
     void )
{
	libbfio_handle_t *file_io_handle                  = NULL;
	libcerror_error_t *error                          = NULL;
	libwrc_resource_node_entry_t *resource_node_entry = NULL;
	int result                                        = 0;

	/* Initialize test
	 */
	result = libwrc_resource_node_entry_initialize(
	          &resource_node_entry,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_IS_NOT_NULL(
	 "resource_node_entry",
	 resource_node_entry );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Initialize file IO handle
	 */
	result = wrc_test_open_file_io_handle(
	          &file_io_handle,
	          wrc_test_resource_node_entry_data1,
	          16,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_IS_NOT_NULL(
	 "file_io_handle",
	 file_io_handle );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libwrc_resource_node_entry_read_file_io_handle(
	          resource_node_entry,
	          file_io_handle,
	          0,
	          1,
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
	result = libwrc_resource_node_entry_read_file_io_handle(
	          NULL,
	          file_io_handle,
	          0,
	          1,
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

	result = libwrc_resource_node_entry_read_file_io_handle(
	          resource_node_entry,
	          NULL,
	          0,
	          1,
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

	/* Clean up file IO handle
	 */
	result = wrc_test_close_file_io_handle(
	          &file_io_handle,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test data too small
	 */
	result = wrc_test_open_file_io_handle(
	          &file_io_handle,
	          wrc_test_resource_node_entry_data1,
	          4,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_IS_NOT_NULL(
	 "file_io_handle",
	 file_io_handle );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libwrc_resource_node_entry_read_file_io_handle(
	          resource_node_entry,
	          file_io_handle,
	          0,
	          1,
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

	result = wrc_test_close_file_io_handle(
	          &file_io_handle,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Clean up
	 */
	result = libwrc_resource_node_entry_free(
	          &resource_node_entry,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_IS_NULL(
	 "resource_node_entry",
	 resource_node_entry );

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
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
		 NULL );
	}
	if( resource_node_entry != NULL )
	{
		libwrc_resource_node_entry_free(
		 &resource_node_entry,
		 NULL );
	}
	return( 0 );
}

/* Tests the libwrc_resource_node_entry_set_name_string function
 * Returns 1 if successful or 0 if not
 */
int wrc_test_resource_node_entry_set_name_string(
     void )
{
	uint8_t name_string[ 10 ]                         = { 't', 0, 'e', 0, 's', 0, 't', 0, 0 };
	libcerror_error_t *error                          = NULL;
	libwrc_resource_node_entry_t *resource_node_entry = NULL;
	int result                                        = 0;

	/* Initialize test
	 */
	result = libwrc_resource_node_entry_initialize(
	          &resource_node_entry,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_IS_NOT_NULL(
	 "resource_node_entry",
	 resource_node_entry );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libwrc_resource_node_entry_set_name_string(
	          resource_node_entry,
	          name_string,
	          10,
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
	result = libwrc_resource_node_entry_set_name_string(
	          NULL,
	          name_string,
	          10,
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

	result = libwrc_resource_node_entry_set_name_string(
	          resource_node_entry,
	          NULL,
	          10,
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

	result = libwrc_resource_node_entry_set_name_string(
	          resource_node_entry,
	          name_string,
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

	result = libwrc_resource_node_entry_set_name_string(
	          resource_node_entry,
	          name_string,
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
	result = libwrc_resource_node_entry_free(
	          &resource_node_entry,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_IS_NULL(
	 "resource_node_entry",
	 resource_node_entry );

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
	if( resource_node_entry != NULL )
	{
		libwrc_resource_node_entry_free(
		 &resource_node_entry,
		 NULL );
	}
	return( 0 );
}

/* Tests the libwrc_resource_node_entry_get_identifier function
 * Returns 1 if successful or 0 if not
 */
int wrc_test_resource_node_entry_get_identifier(
     libwrc_resource_node_entry_t *resource_node_entry )
{
	libcerror_error_t *error = NULL;
	uint32_t identifier      = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libwrc_resource_node_entry_get_identifier(
	          resource_node_entry,
	          &identifier,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_EQUAL_UINT32(
	 "identifier",
	 identifier,
	 (uint32_t) 6 );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libwrc_resource_node_entry_get_identifier(
	          NULL,
	          &identifier,
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

	result = libwrc_resource_node_entry_get_identifier(
	          resource_node_entry,
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

/* Tests the libwrc_resource_node_entry_get_utf8_name_size function
 * Returns 1 if successful or 0 if not
 */
int wrc_test_resource_node_entry_get_utf8_name_size(
     libwrc_resource_node_entry_t *resource_node_entry )
{
	libcerror_error_t *error = NULL;
	size_t utf8_string_size  = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libwrc_resource_node_entry_get_utf8_name_size(
	          resource_node_entry,
	          &utf8_string_size,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_EQUAL_SIZE(
	 "utf8_string_size",
	 utf8_string_size,
	 (size_t) 5 );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libwrc_resource_node_entry_get_utf8_name_size(
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

	result = libwrc_resource_node_entry_get_utf8_name_size(
	          resource_node_entry,
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

/* Tests the libwrc_resource_node_entry_get_utf8_name function
 * Returns 1 if successful or 0 if not
 */
int wrc_test_resource_node_entry_get_utf8_name(
     libwrc_resource_node_entry_t *resource_node_entry )
{
	uint8_t utf8_string[ 384 ];

	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test regular cases
	 */
	result = libwrc_resource_node_entry_get_utf8_name(
	          resource_node_entry,
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
	result = libwrc_resource_node_entry_get_utf8_name(
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

	result = libwrc_resource_node_entry_get_utf8_name(
	          resource_node_entry,
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

	result = libwrc_resource_node_entry_get_utf8_name(
	          resource_node_entry,
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

	result = libwrc_resource_node_entry_get_utf8_name(
	          resource_node_entry,
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

/* Tests the libwrc_resource_node_entry_get_utf16_name_size function
 * Returns 1 if successful or 0 if not
 */
int wrc_test_resource_node_entry_get_utf16_name_size(
     libwrc_resource_node_entry_t *resource_node_entry )
{
	libcerror_error_t *error = NULL;
	size_t utf16_string_size = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libwrc_resource_node_entry_get_utf16_name_size(
	          resource_node_entry,
	          &utf16_string_size,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_EQUAL_SIZE(
	 "utf16_string_size",
	 utf16_string_size,
	 (size_t) 5 );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libwrc_resource_node_entry_get_utf16_name_size(
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

	result = libwrc_resource_node_entry_get_utf16_name_size(
	          resource_node_entry,
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

/* Tests the libwrc_resource_node_entry_get_utf16_name function
 * Returns 1 if successful or 0 if not
 */
int wrc_test_resource_node_entry_get_utf16_name(
     libwrc_resource_node_entry_t *resource_node_entry )
{
	uint16_t utf16_string[ 384 ];

	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test regular cases
	 */
	result = libwrc_resource_node_entry_get_utf16_name(
	          resource_node_entry,
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
	result = libwrc_resource_node_entry_get_utf16_name(
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

	result = libwrc_resource_node_entry_get_utf16_name(
	          resource_node_entry,
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

	result = libwrc_resource_node_entry_get_utf16_name(
	          resource_node_entry,
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

	result = libwrc_resource_node_entry_get_utf16_name(
	          resource_node_entry,
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

#endif /* defined( __GNUC__ ) && !defined( LIBWRC_DLL_IMPORT ) */

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
#if defined( __GNUC__ ) && !defined( LIBWRC_DLL_IMPORT )

	uint8_t name_string[ 10 ]                         = { 't', 0, 'e', 0, 's', 0, 't', 0, 0 };
	libcerror_error_t *error                          = NULL;
	libwrc_resource_node_entry_t *resource_node_entry = NULL;
	int result                                        = 0;

#endif /* defined( __GNUC__ ) && !defined( LIBWRC_DLL_IMPORT ) */

	WRC_TEST_UNREFERENCED_PARAMETER( argc )
	WRC_TEST_UNREFERENCED_PARAMETER( argv )

#if defined( __GNUC__ ) && !defined( LIBWRC_DLL_IMPORT )

	WRC_TEST_RUN(
	 "libwrc_resource_node_entry_initialize",
	 wrc_test_resource_node_entry_initialize );

	WRC_TEST_RUN(
	 "libwrc_resource_node_entry_free",
	 wrc_test_resource_node_entry_free );

	WRC_TEST_RUN(
	 "libwrc_resource_node_entry_read_data",
	 wrc_test_resource_node_entry_read_data );

	WRC_TEST_RUN(
	 "libwrc_resource_node_entry_read_file_io_handle",
	 wrc_test_resource_node_entry_read_file_io_handle );

	/* TODO: add tests for libwrc_resource_node_entry_read_name_file_io_handle */

	WRC_TEST_RUN(
	 "libwrc_resource_node_entry_set_name_string",
	 wrc_test_resource_node_entry_set_name_string );

#if !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 )

	/* Initialize resource_node_entry for tests
	 */
	result = libwrc_resource_node_entry_initialize(
	          &resource_node_entry,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_IS_NOT_NULL(
	 "resource_node_entry",
	 resource_node_entry );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libwrc_resource_node_entry_read_data(
	          resource_node_entry,
	          wrc_test_resource_node_entry_data1,
	          8,
	          1,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libwrc_resource_node_entry_set_name_string(
	          resource_node_entry,
	          name_string,
	          10,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	WRC_TEST_RUN_WITH_ARGS(
	 "libwrc_resource_node_entry_get_identifier",
	 wrc_test_resource_node_entry_get_identifier,
	 resource_node_entry );

	WRC_TEST_RUN_WITH_ARGS(
	 "libwrc_resource_node_entry_get_utf8_name_size",
	 wrc_test_resource_node_entry_get_utf8_name_size,
	 resource_node_entry );

	WRC_TEST_RUN_WITH_ARGS(
	 "libwrc_resource_node_entry_get_utf8_name",
	 wrc_test_resource_node_entry_get_utf8_name,
	 resource_node_entry );

	WRC_TEST_RUN_WITH_ARGS(
	 "libwrc_resource_node_entry_get_utf16_name_size",
	 wrc_test_resource_node_entry_get_utf16_name_size,
	 resource_node_entry );

	WRC_TEST_RUN_WITH_ARGS(
	 "libwrc_resource_node_entry_get_utf16_name",
	 wrc_test_resource_node_entry_get_utf16_name,
	 resource_node_entry );

	/* Clean up
	 */
	result = libwrc_resource_node_entry_free(
	          &resource_node_entry,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_IS_NULL(
	 "resource_node_entry",
	 resource_node_entry );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

#endif /* !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 ) */
#endif /* defined( __GNUC__ ) && !defined( LIBWRC_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

#if defined( __GNUC__ ) && !defined( LIBWRC_DLL_IMPORT )
on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( resource_node_entry != NULL )
	{
		libwrc_resource_node_entry_free(
		 &resource_node_entry,
		 NULL );
	}
	return( EXIT_FAILURE );

#endif /* defined( __GNUC__ ) && !defined( LIBWRC_DLL_IMPORT ) */
}

