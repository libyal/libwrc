/*
 * Library resource_item type test program
 *
 * Copyright (C) 2011-2021, Joachim Metz <joachim.metz@gmail.com>
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

#include "wrc_test_libcdata.h"
#include "wrc_test_libcerror.h"
#include "wrc_test_libwrc.h"
#include "wrc_test_macros.h"
#include "wrc_test_memory.h"
#include "wrc_test_unused.h"

#include "../libwrc/libwrc_libcdata.h"
#include "../libwrc/libwrc_resource_item.h"
#include "../libwrc/libwrc_resource_values.h"

#if defined( __GNUC__ ) && !defined( LIBWRC_DLL_IMPORT )

/* Tests the libwrc_resource_item_initialize function
 * Returns 1 if successful or 0 if not
 */
int wrc_test_resource_item_initialize(
     void )
{
	libcdata_tree_node_t *resource_node       = NULL;
	libcerror_error_t *error                  = NULL;
	libwrc_resource_item_t *resource_item     = NULL;
	libwrc_resource_values_t *resource_values = NULL;
	int result                                = 0;

#if defined( HAVE_WRC_TEST_MEMORY )
	int number_of_malloc_fail_tests           = 1;
	int number_of_memset_fail_tests           = 1;
	int test_number                           = 0;
#endif

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

	result = libcdata_tree_node_initialize(
	          &resource_node,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_IS_NOT_NULL(
	 "resource_node",
	 resource_node );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libcdata_tree_node_set_value(
	          resource_node,
	          (intptr_t *) resource_values,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	resource_values = NULL;

	/* Test regular cases
	 */
	result = libwrc_resource_item_initialize(
	          &resource_item,
	          resource_node,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_IS_NOT_NULL(
	 "resource_item",
	 resource_item );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libwrc_resource_item_free(
	          &resource_item,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_IS_NULL(
	 "resource_item",
	 resource_item );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libwrc_resource_item_initialize(
	          NULL,
	          resource_node,
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

	resource_item = (libwrc_resource_item_t *) 0x12345678UL;

	result = libwrc_resource_item_initialize(
	          &resource_item,
	          resource_node,
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

	resource_item = NULL;

	result = libwrc_resource_item_initialize(
	          &resource_item,
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

#if defined( HAVE_WRC_TEST_MEMORY )

	for( test_number = 0;
	     test_number < number_of_malloc_fail_tests;
	     test_number++ )
	{
		/* Test libwrc_resource_item_initialize with malloc failing
		 */
		wrc_test_malloc_attempts_before_fail = test_number;

		result = libwrc_resource_item_initialize(
		          &resource_item,
		          resource_node,
		          &error );

		if( wrc_test_malloc_attempts_before_fail != -1 )
		{
			wrc_test_malloc_attempts_before_fail = -1;

			if( resource_item != NULL )
			{
				libwrc_resource_item_free(
				 &resource_item,
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
			 "resource_item",
			 resource_item );

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
		/* Test libwrc_resource_item_initialize with memset failing
		 */
		wrc_test_memset_attempts_before_fail = test_number;

		result = libwrc_resource_item_initialize(
		          &resource_item,
		          resource_node,
		          &error );

		if( wrc_test_memset_attempts_before_fail != -1 )
		{
			wrc_test_memset_attempts_before_fail = -1;

			if( resource_item != NULL )
			{
				libwrc_resource_item_free(
				 &resource_item,
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
			 "resource_item",
			 resource_item );

			WRC_TEST_ASSERT_IS_NOT_NULL(
			 "error",
			 error );

			libcerror_error_free(
			 &error );
		}
	}
#endif /* defined( HAVE_WRC_TEST_MEMORY ) */

	/* Clean up
	 */
	result = libcdata_tree_node_free(
	          &resource_node,
	          (int (*)(intptr_t **, libcerror_error_t **)) &libwrc_resource_values_free,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_IS_NULL(
	 "resource_node",
	 resource_node );

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
	if( resource_item != NULL )
	{
		libwrc_resource_item_free(
		 &resource_item,
		 NULL );
	}
	if( resource_node != NULL )
	{
		libcdata_tree_node_free(
		 &resource_node,
		 (int (*)(intptr_t **, libcerror_error_t **)) &libwrc_resource_values_free,
		 NULL );
	}
	if( resource_values != NULL )
	{
		libwrc_resource_values_free(
		 &resource_values,
		 NULL );
	}
	return( 0 );
}

#endif /* defined( __GNUC__ ) && !defined( LIBWRC_DLL_IMPORT ) */

/* Tests the libwrc_resource_item_free function
 * Returns 1 if successful or 0 if not
 */
int wrc_test_resource_item_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libwrc_resource_item_free(
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

/* Tests the libwrc_resource_item_get_identifier function
 * Returns 1 if successful or 0 if not
 */
int wrc_test_resource_item_get_identifier(
     libwrc_resource_item_t *resource_item )
{
	libcerror_error_t *error = NULL;
	uint32_t identifier      = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libwrc_resource_item_get_identifier(
	          resource_item,
	          &identifier,
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
	result = libwrc_resource_item_get_identifier(
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

	result = libwrc_resource_item_get_identifier(
	          resource_item,
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

/* Tests the libwrc_resource_item_get_utf8_name_size function
 * Returns 1 if successful or 0 if not
 */
int wrc_test_resource_item_get_utf8_name_size(
     libwrc_resource_item_t *resource_item )
{
	libcerror_error_t *error = NULL;
	int result               = 0;
	size_t utf8_name_size    = 0;

	/* Test regular cases
	 */
	result = libwrc_resource_item_get_utf8_name_size(
	          resource_item,
	          &utf8_name_size,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_EQUAL_SIZE(
	 "utf8_name_size",
	 utf8_name_size,
	 (size_t) 5 );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libwrc_resource_item_get_utf8_name_size(
	          NULL,
	          &utf8_name_size,
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

	result = libwrc_resource_item_get_utf8_name_size(
	          resource_item,
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

/* Tests the libwrc_resource_item_get_utf16_name_size function
 * Returns 1 if successful or 0 if not
 */
int wrc_test_resource_item_get_utf16_name_size(
     libwrc_resource_item_t *resource_item )
{
	libcerror_error_t *error = NULL;
	int result               = 0;
	size_t utf16_name_size   = 0;

	/* Test regular cases
	 */
	result = libwrc_resource_item_get_utf16_name_size(
	          resource_item,
	          &utf16_name_size,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_EQUAL_SIZE(
	 "utf16_name_size",
	 utf16_name_size,
	 (size_t) 5 );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libwrc_resource_item_get_utf16_name_size(
	          NULL,
	          &utf16_name_size,
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

	result = libwrc_resource_item_get_utf16_name_size(
	          resource_item,
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

/* Tests the libwrc_resource_item_get_number_of_sub_items function
 * Returns 1 if successful or 0 if not
 */
int wrc_test_resource_item_get_number_of_sub_items(
     libwrc_resource_item_t *resource_item )
{
	libcerror_error_t *error = NULL;
	int number_of_sub_items  = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libwrc_resource_item_get_number_of_sub_items(
	          resource_item,
	          &number_of_sub_items,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "number_of_sub_items",
	 number_of_sub_items,
	 1 );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libwrc_resource_item_get_number_of_sub_items(
	          NULL,
	          &number_of_sub_items,
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

	result = libwrc_resource_item_get_number_of_sub_items(
	          resource_item,
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

/* Tests the libwrc_resource_item_get_sub_item_by_index function
 * Returns 1 if successful or 0 if not
 */
int wrc_test_resource_item_get_sub_item_by_index(
     libwrc_resource_item_t *resource_item )
{
	libcerror_error_t *error                  = NULL;
	libwrc_resource_item_t *resource_sub_item = NULL;
	int result                                = 0;

	/* Test regular cases
	 */
	result = libwrc_resource_item_get_sub_item_by_index(
	          resource_item,
	          0,
	          &resource_sub_item,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_IS_NOT_NULL(
	 "resource_sub_item",
	 resource_sub_item );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libwrc_resource_item_free(
	          &resource_sub_item,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_IS_NULL(
	 "resource_sub_item",
	 resource_sub_item );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libwrc_resource_item_get_sub_item_by_index(
	          NULL,
	          0,
	          &resource_sub_item,
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

	result = libwrc_resource_item_get_sub_item_by_index(
	          resource_item,
	          -1,
	          &resource_sub_item,
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

	result = libwrc_resource_item_get_sub_item_by_index(
	          resource_item,
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

	libcdata_tree_node_t *resource_node       = NULL;
	libcerror_error_t *error                  = NULL;
	libwrc_resource_item_t *resource_item     = NULL;
	libwrc_resource_values_t *resource_values = NULL;
	int result                                = 0;

#endif /* defined( __GNUC__ ) && !defined( LIBWRC_DLL_IMPORT ) */

	WRC_TEST_UNREFERENCED_PARAMETER( argc )
	WRC_TEST_UNREFERENCED_PARAMETER( argv )

#if defined( __GNUC__ ) && !defined( LIBWRC_DLL_IMPORT )

	WRC_TEST_RUN(
	 "libwrc_resource_item_initialize",
	 wrc_test_resource_item_initialize );

#endif /* defined( __GNUC__ ) && !defined( LIBWRC_DLL_IMPORT ) */

	WRC_TEST_RUN(
	 "libwrc_resource_item_free",
	 wrc_test_resource_item_free );

#if defined( __GNUC__ ) && !defined( LIBWRC_DLL_IMPORT )
#if !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 )

	/* Initialize resource_item for tests
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

	result = libwrc_resource_values_set_name_string(
	          resource_values,
	          (uint8_t *) "t\0e\0s\0t\0\0\0",
	          10,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libcdata_tree_node_initialize(
	          &resource_node,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_IS_NOT_NULL(
	 "resource_node",
	 resource_node );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libcdata_tree_node_set_value(
	          resource_node,
	          (intptr_t *) resource_values,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	resource_values = NULL;

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

	result = libcdata_tree_node_append_value(
	          resource_node,
	          (intptr_t *) resource_values,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	resource_values = NULL;

	result = libwrc_resource_item_initialize(
	          &resource_item,
	          resource_node,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_IS_NOT_NULL(
	 "resource_item",
	 resource_item );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	WRC_TEST_RUN_WITH_ARGS(
	 "libwrc_resource_item_get_identifier",
	 wrc_test_resource_item_get_identifier,
	 resource_item );

	WRC_TEST_RUN_WITH_ARGS(
	 "libwrc_resource_item_get_utf8_name_size",
	 wrc_test_resource_item_get_utf8_name_size,
	 resource_item );

	/* TODO: add tests for libwrc_resource_item_get_utf8_name */

	WRC_TEST_RUN_WITH_ARGS(
	 "libwrc_resource_item_get_utf16_name_size",
	 wrc_test_resource_item_get_utf16_name_size,
	 resource_item );

	/* TODO: add tests for libwrc_resource_item_get_utf16_name */

	WRC_TEST_RUN_WITH_ARGS(
	 "libwrc_resource_item_get_number_of_sub_items",
	 wrc_test_resource_item_get_number_of_sub_items,
	 resource_item );

	WRC_TEST_RUN_WITH_ARGS(
	 "libwrc_resource_item_get_sub_item_by_index",
	 wrc_test_resource_item_get_sub_item_by_index,
	 resource_item );

	/* Clean up
	 */
	result = libwrc_resource_item_free(
	          &resource_item,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_IS_NULL(
	 "resource_item",
	 resource_item );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libcdata_tree_node_free(
	          &resource_node,
	          (int (*)(intptr_t **, libcerror_error_t **)) &libwrc_resource_values_free,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_IS_NULL(
	 "resource_node",
	 resource_node );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

#endif /* !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 ) */
#endif /* defined( __GNUC__ ) && !defined( LIBWRC_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

on_error:
#if defined( __GNUC__ ) && !defined( LIBWRC_DLL_IMPORT )
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( resource_item != NULL )
	{
		libwrc_resource_item_free(
		 &resource_item,
		 NULL );
	}
	if( resource_node != NULL )
	{
		libcdata_tree_node_free(
		 &resource_node,
		 (int (*)(intptr_t **, libcerror_error_t **)) &libwrc_resource_values_free,
		 NULL );
	}
	if( resource_values != NULL )
	{
		libwrc_resource_values_free(
		 &resource_values,
		 NULL );
	}
#endif /* defined( __GNUC__ ) && !defined( LIBWRC_DLL_IMPORT ) */

	return( EXIT_FAILURE );
}

