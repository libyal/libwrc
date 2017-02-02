/*
 * Library resource_values type test program
 *
 * Copyright (C) 2011-2017, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this software.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <common.h>
#include <file_stream.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "wrc_test_libcdata.h"
#include "wrc_test_libcerror.h"
#include "wrc_test_libwrc.h"
#include "wrc_test_macros.h"
#include "wrc_test_memory.h"
#include "wrc_test_unused.h"

#include "../libwrc/libwrc_resource_values.h"

#if defined( __GNUC__ )

/* Tests the libwrc_resource_values_initialize function
 * Returns 1 if successful or 0 if not
 */
int wrc_test_resource_values_initialize(
     void )
{
	libcerror_error_t *error                  = NULL;
	libwrc_resource_values_t *resource_values = NULL;
	int result                                = 0;

#if defined( HAVE_WRC_TEST_MEMORY )
	int number_of_malloc_fail_tests           = 1;
	int number_of_memset_fail_tests           = 1;
	int test_number                           = 0;
#endif

	/* Test regular cases
	 */
	result = libwrc_resource_values_initialize(
	          &resource_values,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        WRC_TEST_ASSERT_IS_NOT_NULL(
         "resource_values",
         resource_values );

        WRC_TEST_ASSERT_IS_NULL(
         "error",
         error );

	result = libwrc_resource_values_free(
	          &resource_values,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        WRC_TEST_ASSERT_IS_NULL(
         "resource_values",
         resource_values );

        WRC_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test error cases
	 */
	result = libwrc_resource_values_initialize(
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

	resource_values = (libwrc_resource_values_t *) 0x12345678UL;

	result = libwrc_resource_values_initialize(
	          &resource_values,
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

	resource_values = NULL;

#if defined( HAVE_WRC_TEST_MEMORY )

	for( test_number = 0;
	     test_number < number_of_malloc_fail_tests;
	     test_number++ )
	{
		/* Test libwrc_resource_values_initialize with malloc failing
		 */
		wrc_test_malloc_attempts_before_fail = test_number;

		result = libwrc_resource_values_initialize(
		          &resource_values,
		          &error );

		if( wrc_test_malloc_attempts_before_fail != -1 )
		{
			wrc_test_malloc_attempts_before_fail = -1;

			if( resource_values != NULL )
			{
				libwrc_resource_values_free(
				 &resource_values,
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
			 "resource_values",
			 resource_values );

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
		/* Test libwrc_resource_values_initialize with memset failing
		 */
		wrc_test_memset_attempts_before_fail = test_number;

		result = libwrc_resource_values_initialize(
		          &resource_values,
		          &error );

		if( wrc_test_memset_attempts_before_fail != -1 )
		{
			wrc_test_memset_attempts_before_fail = -1;

			if( resource_values != NULL )
			{
				libwrc_resource_values_free(
				 &resource_values,
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
			 "resource_values",
			 resource_values );

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
	if( resource_values != NULL )
	{
		libwrc_resource_values_free(
		 &resource_values,
		 NULL );
	}
	return( 0 );
}

/* Tests the libwrc_resource_values_free function
 * Returns 1 if successful or 0 if not
 */
int wrc_test_resource_values_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libwrc_resource_values_free(
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

/* Tests the libwrc_resource_values_compare function
 * Returns 1 if successful or 0 if not
 */
int wrc_test_resource_values_compare(
     void )
{
	libcerror_error_t *error                         = NULL;
	libwrc_resource_values_t *first_resource_values  = NULL;
	libwrc_resource_values_t *second_resource_values = NULL;
	int result                                       = 0;

	/* Initialize test
	 */
	result = libwrc_resource_values_initialize(
	          &first_resource_values,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        WRC_TEST_ASSERT_IS_NOT_NULL(
         "first_resource_values",
         first_resource_values );

        WRC_TEST_ASSERT_IS_NULL(
         "error",
         error );

	result = libwrc_resource_values_initialize(
	          &second_resource_values,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        WRC_TEST_ASSERT_IS_NOT_NULL(
         "second_resource_values",
         second_resource_values );

        WRC_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test regular cases
	 */
	result = libwrc_resource_values_compare(
	          first_resource_values,
	          second_resource_values,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 LIBCDATA_COMPARE_EQUAL );

        WRC_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test error cases
	 */
	result = libwrc_resource_values_compare(
	          NULL,
	          second_resource_values,
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

	result = libwrc_resource_values_compare(
	          first_resource_values,
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

	/* Clean up
	 */
	result = libwrc_resource_values_free(
	          &second_resource_values,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        WRC_TEST_ASSERT_IS_NULL(
         "second_resource_values",
         second_resource_values );

        WRC_TEST_ASSERT_IS_NULL(
         "error",
         error );

	result = libwrc_resource_values_free(
	          &first_resource_values,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        WRC_TEST_ASSERT_IS_NULL(
         "first_resource_values",
         first_resource_values );

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
	if( second_resource_values != NULL )
	{
		libwrc_resource_values_free(
		 &second_resource_values,
		 NULL );
	}
	if( first_resource_values != NULL )
	{
		libwrc_resource_values_free(
		 &first_resource_values,
		 NULL );
	}
	return( 0 );
}

/* Tests the libwrc_resource_values_get_identifier function
 * Returns 1 if successful or 0 if not
 */
int wrc_test_resource_values_get_identifier(
     void )
{
	libcerror_error_t *error                  = NULL;
	libwrc_resource_values_t *resource_values = NULL;
	uint32_t identifier                       = 0;
	int identifier_is_set                     = 0;
	int result                                = 0;

	/* Initialize test
	 */
	result = libwrc_resource_values_initialize(
	          &resource_values,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_IS_NOT_NULL(
	 "resource_values",
	 resource_values );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libwrc_resource_values_get_identifier(
	          resource_values,
	          &identifier,
	          &error );

	WRC_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	identifier_is_set = result;

	/* Test error cases
	 */
	result = libwrc_resource_values_get_identifier(
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

	if( identifier_is_set != 0 )
	{
		result = libwrc_resource_values_get_identifier(
		          resource_values,
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
	result = libwrc_resource_values_free(
	          &resource_values,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_IS_NULL(
	 "resource_values",
	 resource_values );

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
	if( resource_values != NULL )
	{
		libwrc_resource_values_free(
		 &resource_values,
		 NULL );
	}
	return( 0 );
}

/* Tests the libwrc_resource_values_get_type function
 * Returns 1 if successful or 0 if not
 */
int wrc_test_resource_values_get_type(
     void )
{
	libcerror_error_t *error                  = NULL;
	libwrc_resource_values_t *resource_values = NULL;
	int result                                = 0;
	int type                                  = 0;
	int type_is_set                           = 0;

	/* Initialize test
	 */
	result = libwrc_resource_values_initialize(
	          &resource_values,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_IS_NOT_NULL(
	 "resource_values",
	 resource_values );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libwrc_resource_values_get_type(
	          resource_values,
	          &type,
	          &error );

	WRC_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	type_is_set = result;

	/* Test error cases
	 */
	result = libwrc_resource_values_get_type(
	          NULL,
	          &type,
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

	if( type_is_set != 0 )
	{
		result = libwrc_resource_values_get_type(
		          resource_values,
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
	result = libwrc_resource_values_free(
	          &resource_values,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_IS_NULL(
	 "resource_values",
	 resource_values );

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
	if( resource_values != NULL )
	{
		libwrc_resource_values_free(
		 &resource_values,
		 NULL );
	}
	return( 0 );
}

#endif /* defined( __GNUC__ ) */

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

#if defined( __GNUC__ )

	WRC_TEST_RUN(
	 "libwrc_resource_values_initialize",
	 wrc_test_resource_values_initialize );

	WRC_TEST_RUN(
	 "libwrc_resource_values_free",
	 wrc_test_resource_values_free );

	WRC_TEST_RUN(
	 "libwrc_resource_values_compare",
	 wrc_test_resource_values_compare );

	WRC_TEST_RUN(
	 "libwrc_resource_values_get_identifier",
	 wrc_test_resource_values_get_identifier );

	WRC_TEST_RUN(
	 "libwrc_resource_values_get_type",
	 wrc_test_resource_values_get_type );

#endif /* defined( __GNUC__ ) */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

