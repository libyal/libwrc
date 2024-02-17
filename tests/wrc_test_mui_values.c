/*
 * Library mui_values type test program
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

#include "../libwrc/libwrc_mui_values.h"

#if defined( __GNUC__ ) && !defined( LIBWRC_DLL_IMPORT )

/* Tests the libwrc_mui_values_initialize function
 * Returns 1 if successful or 0 if not
 */
int wrc_test_mui_values_initialize(
     void )
{
	libcerror_error_t *error        = NULL;
	libwrc_mui_values_t *mui_values = NULL;
	int result                      = 0;

#if defined( HAVE_WRC_TEST_MEMORY )
	int number_of_malloc_fail_tests = 1;
	int number_of_memset_fail_tests = 1;
	int test_number                 = 0;
#endif

	/* Test regular cases
	 */
	result = libwrc_mui_values_initialize(
	          &mui_values,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_IS_NOT_NULL(
	 "mui_values",
	 mui_values );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libwrc_mui_values_free(
	          &mui_values,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_IS_NULL(
	 "mui_values",
	 mui_values );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libwrc_mui_values_initialize(
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

	mui_values = (libwrc_mui_values_t *) 0x12345678UL;

	result = libwrc_mui_values_initialize(
	          &mui_values,
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

	mui_values = NULL;

#if defined( HAVE_WRC_TEST_MEMORY )

	for( test_number = 0;
	     test_number < number_of_malloc_fail_tests;
	     test_number++ )
	{
		/* Test libwrc_mui_values_initialize with malloc failing
		 */
		wrc_test_malloc_attempts_before_fail = test_number;

		result = libwrc_mui_values_initialize(
		          &mui_values,
		          &error );

		if( wrc_test_malloc_attempts_before_fail != -1 )
		{
			wrc_test_malloc_attempts_before_fail = -1;

			if( mui_values != NULL )
			{
				libwrc_mui_values_free(
				 &mui_values,
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
			 "mui_values",
			 mui_values );

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
		/* Test libwrc_mui_values_initialize with memset failing
		 */
		wrc_test_memset_attempts_before_fail = test_number;

		result = libwrc_mui_values_initialize(
		          &mui_values,
		          &error );

		if( wrc_test_memset_attempts_before_fail != -1 )
		{
			wrc_test_memset_attempts_before_fail = -1;

			if( mui_values != NULL )
			{
				libwrc_mui_values_free(
				 &mui_values,
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
			 "mui_values",
			 mui_values );

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
	if( mui_values != NULL )
	{
		libwrc_mui_values_free(
		 &mui_values,
		 NULL );
	}
	return( 0 );
}

/* Tests the libwrc_mui_values_free function
 * Returns 1 if successful or 0 if not
 */
int wrc_test_mui_values_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libwrc_mui_values_free(
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

/* Tests the libwrc_mui_values_get_file_type function
 * Returns 1 if successful or 0 if not
 */
int wrc_test_mui_values_get_file_type(
     void )
{
	libcerror_error_t *error        = NULL;
	libwrc_mui_values_t *mui_values = NULL;
	uint32_t file_type              = 0;
	int file_type_is_set            = 0;
	int result                      = 0;

	/* Initialize test
	 */
	result = libwrc_mui_values_initialize(
	          &mui_values,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_IS_NOT_NULL(
	 "mui_values",
	 mui_values );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libwrc_mui_values_get_file_type(
	          mui_values,
	          &file_type,
	          &error );

	WRC_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	file_type_is_set = result;

	/* Test error cases
	 */
	result = libwrc_mui_values_get_file_type(
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

	if( file_type_is_set != 0 )
	{
		result = libwrc_mui_values_get_file_type(
		          mui_values,
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
	}
	/* Clean up
	 */
	result = libwrc_mui_values_free(
	          &mui_values,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_IS_NULL(
	 "mui_values",
	 mui_values );

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
	if( mui_values != NULL )
	{
		libwrc_mui_values_free(
		 &mui_values,
		 NULL );
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
	WRC_TEST_UNREFERENCED_PARAMETER( argc )
	WRC_TEST_UNREFERENCED_PARAMETER( argv )

#if defined( __GNUC__ ) && !defined( LIBWRC_DLL_IMPORT )

	WRC_TEST_RUN(
	 "libwrc_mui_values_initialize",
	 wrc_test_mui_values_initialize );

	WRC_TEST_RUN(
	 "libwrc_mui_values_free",
	 wrc_test_mui_values_free );

	/* TODO: add tests for libwrc_mui_values_read */

	WRC_TEST_RUN(
	 "libwrc_mui_values_get_file_type",
	 wrc_test_mui_values_get_file_type );

#endif /* defined( __GNUC__ ) && !defined( LIBWRC_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

