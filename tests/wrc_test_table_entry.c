/*
 * Library table_entry type test program
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

#include "../libwrc/libwrc_table_entry.h"

#if defined( __GNUC__ ) && !defined( LIBWRC_DLL_IMPORT )

/* Tests the libwrc_table_entry_initialize function
 * Returns 1 if successful or 0 if not
 */
int wrc_test_table_entry_initialize(
     void )
{
	libcerror_error_t *error          = NULL;
	libwrc_table_entry_t *table_entry = NULL;
	int result                        = 0;

#if defined( HAVE_WRC_TEST_MEMORY )
	int number_of_malloc_fail_tests   = 1;
	int number_of_memset_fail_tests   = 1;
	int test_number                   = 0;
#endif

	/* Test regular cases
	 */
	result = libwrc_table_entry_initialize(
	          &table_entry,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_IS_NOT_NULL(
	 "table_entry",
	 table_entry );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libwrc_table_entry_free(
	          &table_entry,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_IS_NULL(
	 "table_entry",
	 table_entry );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libwrc_table_entry_initialize(
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

	table_entry = (libwrc_table_entry_t *) 0x12345678UL;

	result = libwrc_table_entry_initialize(
	          &table_entry,
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

	table_entry = NULL;

#if defined( HAVE_WRC_TEST_MEMORY )

	for( test_number = 0;
	     test_number < number_of_malloc_fail_tests;
	     test_number++ )
	{
		/* Test libwrc_table_entry_initialize with malloc failing
		 */
		wrc_test_malloc_attempts_before_fail = test_number;

		result = libwrc_table_entry_initialize(
		          &table_entry,
		          &error );

		if( wrc_test_malloc_attempts_before_fail != -1 )
		{
			wrc_test_malloc_attempts_before_fail = -1;

			if( table_entry != NULL )
			{
				libwrc_table_entry_free(
				 &table_entry,
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
			 "table_entry",
			 table_entry );

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
		/* Test libwrc_table_entry_initialize with memset failing
		 */
		wrc_test_memset_attempts_before_fail = test_number;

		result = libwrc_table_entry_initialize(
		          &table_entry,
		          &error );

		if( wrc_test_memset_attempts_before_fail != -1 )
		{
			wrc_test_memset_attempts_before_fail = -1;

			if( table_entry != NULL )
			{
				libwrc_table_entry_free(
				 &table_entry,
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
			 "table_entry",
			 table_entry );

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
	if( table_entry != NULL )
	{
		libwrc_table_entry_free(
		 &table_entry,
		 NULL );
	}
	return( 0 );
}

/* Tests the libwrc_table_entry_free function
 * Returns 1 if successful or 0 if not
 */
int wrc_test_table_entry_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libwrc_table_entry_free(
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

/* Tests the libwrc_table_entry_set_string function
 * Returns 1 if successful or 0 if not
 */
int wrc_test_table_entry_set_string(
     void )
{
	libcerror_error_t *error          = NULL;
	libwrc_table_entry_t *table_entry = NULL;
	int result                        = 0;

	/* Initialize test
	 */
	result = libwrc_table_entry_initialize(
	          &table_entry,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_IS_NOT_NULL(
	 "table_entry",
	 table_entry );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libwrc_table_entry_set_string(
	          table_entry,
	          (uint8_t *) "test",
	          5,
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
	result = libwrc_table_entry_set_string(
	          NULL,
	          (uint8_t *) "test",
	          5,
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

	result = libwrc_table_entry_set_string(
	          table_entry,
	          NULL,
	          5,
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

	result = libwrc_table_entry_set_string(
	          table_entry,
	          (uint8_t *) "test",
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

	result = libwrc_table_entry_set_string(
	          table_entry,
	          (uint8_t *) "test",
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
	result = libwrc_table_entry_free(
	          &table_entry,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_IS_NULL(
	 "table_entry",
	 table_entry );

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
	if( table_entry != NULL )
	{
		libwrc_table_entry_free(
		 &table_entry,
		 NULL );
	}
	return( 0 );
}

/* Tests the libwrc_table_entry_get_utf8_string_size function
 * Returns 1 if successful or 0 if not
 */
int wrc_test_table_entry_get_utf8_string_size(
     libwrc_table_entry_t *table_entry )
{
	libcerror_error_t *error = NULL;
	size_t utf8_string_size  = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libwrc_table_entry_get_utf8_string_size(
	          table_entry,
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
	result = libwrc_table_entry_get_utf8_string_size(
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

	result = libwrc_table_entry_get_utf8_string_size(
	          table_entry,
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

/* Tests the libwrc_table_entry_get_utf8_string function
 * Returns 1 if successful or 0 if not
 */
int wrc_test_table_entry_get_utf8_string(
     libwrc_table_entry_t *table_entry )
{
	uint8_t utf8_string[ 384 ];

	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test regular cases
	 */
	result = libwrc_table_entry_get_utf8_string(
	          table_entry,
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
	result = libwrc_table_entry_get_utf8_string(
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

	result = libwrc_table_entry_get_utf8_string(
	          table_entry,
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

	result = libwrc_table_entry_get_utf8_string(
	          table_entry,
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

	result = libwrc_table_entry_get_utf8_string(
	          table_entry,
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

/* Tests the libwrc_table_entry_get_utf16_string_size function
 * Returns 1 if successful or 0 if not
 */
int wrc_test_table_entry_get_utf16_string_size(
     libwrc_table_entry_t *table_entry )
{
	libcerror_error_t *error = NULL;
	size_t utf16_string_size = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libwrc_table_entry_get_utf16_string_size(
	          table_entry,
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
	result = libwrc_table_entry_get_utf16_string_size(
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

	result = libwrc_table_entry_get_utf16_string_size(
	          table_entry,
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

/* Tests the libwrc_table_entry_get_utf16_string function
 * Returns 1 if successful or 0 if not
 */
int wrc_test_table_entry_get_utf16_string(
     libwrc_table_entry_t *table_entry )
{
	uint16_t utf16_string[ 384 ];

	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test regular cases
	 */
	result = libwrc_table_entry_get_utf16_string(
	          table_entry,
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
	result = libwrc_table_entry_get_utf16_string(
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

	result = libwrc_table_entry_get_utf16_string(
	          table_entry,
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

	result = libwrc_table_entry_get_utf16_string(
	          table_entry,
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

	result = libwrc_table_entry_get_utf16_string(
	          table_entry,
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

	libcerror_error_t *error          = NULL;
	libwrc_table_entry_t *table_entry = NULL;
	int result                        = 0;

#endif /* defined( __GNUC__ ) && !defined( LIBWRC_DLL_IMPORT ) */

	WRC_TEST_UNREFERENCED_PARAMETER( argc )
	WRC_TEST_UNREFERENCED_PARAMETER( argv )

#if defined( __GNUC__ ) && !defined( LIBWRC_DLL_IMPORT )

	WRC_TEST_RUN(
	 "libwrc_table_entry_initialize",
	 wrc_test_table_entry_initialize );

	WRC_TEST_RUN(
	 "libwrc_table_entry_free",
	 wrc_test_table_entry_free );

	WRC_TEST_RUN(
	 "libwrc_table_entry_set_string",
	 wrc_test_table_entry_set_string );

#if !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 )

	/* Initialize table_entry for tests
	 */
	result = libwrc_table_entry_initialize(
	          &table_entry,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_IS_NOT_NULL(
	 "table_entry",
	 table_entry );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libwrc_table_entry_set_string(
	          table_entry,
	          (uint8_t *) "test",
	          5,
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
	 "libwrc_table_entry_get_utf8_string_size",
	 wrc_test_table_entry_get_utf8_string_size,
	 table_entry );

	WRC_TEST_RUN_WITH_ARGS(
	 "libwrc_table_entry_get_utf8_string",
	 wrc_test_table_entry_get_utf8_string,
	 table_entry );

	WRC_TEST_RUN_WITH_ARGS(
	 "libwrc_table_entry_get_utf16_string_size",
	 wrc_test_table_entry_get_utf16_string_size,
	 table_entry );

	WRC_TEST_RUN_WITH_ARGS(
	 "libwrc_table_entry_get_utf16_string",
	 wrc_test_table_entry_get_utf16_string,
	 table_entry );

	/* Clean up
	 */
	result = libwrc_table_entry_free(
	          &table_entry,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_IS_NULL(
	 "table_entry",
	 table_entry );

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
	if( table_entry != NULL )
	{
		libwrc_table_entry_free(
		 &table_entry,
		 NULL );
	}
	return( EXIT_FAILURE );

#endif /* defined( __GNUC__ ) && !defined( LIBWRC_DLL_IMPORT ) */
}

