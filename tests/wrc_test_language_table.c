/*
 * Library language_table type test program
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

#include "../libwrc/libwrc_language_table.h"

#if defined( __GNUC__ ) && !defined( LIBWRC_DLL_IMPORT )

/* Tests the libwrc_language_table_initialize function
 * Returns 1 if successful or 0 if not
 */
int wrc_test_language_table_initialize(
     void )
{
	libcerror_error_t *error                = NULL;
	libwrc_language_table_t *language_table = NULL;
	int result                              = 0;

#if defined( HAVE_WRC_TEST_MEMORY )
	int number_of_malloc_fail_tests         = 1;
	int number_of_memset_fail_tests         = 1;
	int test_number                         = 0;
#endif

	/* Test regular cases
	 */
	result = libwrc_language_table_initialize(
	          &language_table,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_IS_NOT_NULL(
	 "language_table",
	 language_table );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libwrc_language_table_free(
	          &language_table,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_IS_NULL(
	 "language_table",
	 language_table );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libwrc_language_table_initialize(
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

	language_table = (libwrc_language_table_t *) 0x12345678UL;

	result = libwrc_language_table_initialize(
	          &language_table,
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

	language_table = NULL;

#if defined( HAVE_WRC_TEST_MEMORY )

	for( test_number = 0;
	     test_number < number_of_malloc_fail_tests;
	     test_number++ )
	{
		/* Test libwrc_language_table_initialize with malloc failing
		 */
		wrc_test_malloc_attempts_before_fail = test_number;

		result = libwrc_language_table_initialize(
		          &language_table,
		          &error );

		if( wrc_test_malloc_attempts_before_fail != -1 )
		{
			wrc_test_malloc_attempts_before_fail = -1;

			if( language_table != NULL )
			{
				libwrc_language_table_free(
				 &language_table,
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
			 "language_table",
			 language_table );

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
		/* Test libwrc_language_table_initialize with memset failing
		 */
		wrc_test_memset_attempts_before_fail = test_number;

		result = libwrc_language_table_initialize(
		          &language_table,
		          &error );

		if( wrc_test_memset_attempts_before_fail != -1 )
		{
			wrc_test_memset_attempts_before_fail = -1;

			if( language_table != NULL )
			{
				libwrc_language_table_free(
				 &language_table,
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
			 "language_table",
			 language_table );

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
	if( language_table != NULL )
	{
		libwrc_language_table_free(
		 &language_table,
		 NULL );
	}
	return( 0 );
}

/* Tests the libwrc_language_table_free function
 * Returns 1 if successful or 0 if not
 */
int wrc_test_language_table_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libwrc_language_table_free(
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

/* Tests the libwrc_language_table_get_number_of_entries function
 * Returns 1 if successful or 0 if not
 */
int wrc_test_language_table_get_number_of_entries(
     void )
{
	libcerror_error_t *error                = NULL;
	libwrc_language_table_t *language_table = NULL;
	int number_of_entries                   = 0;
	int number_of_entries_is_set            = 0;
	int result                              = 0;

	/* Initialize test
	 */
	result = libwrc_language_table_initialize(
	          &language_table,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_IS_NOT_NULL(
	 "language_table",
	 language_table );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libwrc_language_table_get_number_of_entries(
	          language_table,
	          &number_of_entries,
	          &error );

	WRC_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	number_of_entries_is_set = result;

	/* Test error cases
	 */
	result = libwrc_language_table_get_number_of_entries(
	          NULL,
	          &number_of_entries,
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

	if( number_of_entries_is_set != 0 )
	{
		result = libwrc_language_table_get_number_of_entries(
		          language_table,
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
	result = libwrc_language_table_free(
	          &language_table,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_IS_NULL(
	 "language_table",
	 language_table );

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
	if( language_table != NULL )
	{
		libwrc_language_table_free(
		 &language_table,
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
	 "libwrc_language_table_initialize",
	 wrc_test_language_table_initialize );

	WRC_TEST_RUN(
	 "libwrc_language_table_free",
	 wrc_test_language_table_free );

	WRC_TEST_RUN(
	 "libwrc_language_table_get_number_of_entries",
	 wrc_test_language_table_get_number_of_entries );

	/* TODO: add tests for libwrc_language_table_get_identifier */

	/* TODO: add tests for libwrc_language_table_get_entry_by_identifier */

	/* TODO: add tests for libwrc_language_table_append_entry */

	/* TODO: add tests for libwrc_language_table_get_number_of_values */

#endif /* defined( __GNUC__ ) && !defined( LIBWRC_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

