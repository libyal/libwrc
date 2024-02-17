/*
 * Library stream type test program
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
#include <narrow_string.h>
#include <system_string.h>
#include <types.h>
#include <wide_string.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "wrc_test_functions.h"
#include "wrc_test_getopt.h"
#include "wrc_test_libbfio.h"
#include "wrc_test_libcerror.h"
#include "wrc_test_libwrc.h"
#include "wrc_test_macros.h"
#include "wrc_test_memory.h"
#include "wrc_test_unused.h"

#include "../libwrc/libwrc_stream.h"

#if !defined( LIBWRC_HAVE_BFIO )

extern \
int libwrc_stream_open_file_io_handle(
     libwrc_stream_t *stream,
     libbfio_handle_t *file_io_handle,
     int access_flags,
     libwrc_error_t **error );

#endif /* !defined( LIBWRC_HAVE_BFIO ) */

#if defined( HAVE_WIDE_SYSTEM_CHARACTER ) && SIZEOF_WCHAR_T != 2 && SIZEOF_WCHAR_T != 4
#error Unsupported size of wchar_t
#endif

/* Define to make wrc_test_stream generate verbose output
#define WRC_TEST_STREAM_VERBOSE
 */

/* Creates and opens a source stream
 * Returns 1 if successful or -1 on error
 */
int wrc_test_stream_open_source(
     libwrc_stream_t **stream,
     libbfio_handle_t *file_io_handle,
     uint32_t virtual_address,
     libcerror_error_t **error )
{
	static char *function = "wrc_test_stream_open_source";
	int result            = 0;

	if( stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid stream.",
		 function );

		return( -1 );
	}
	if( file_io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file IO handle.",
		 function );

		return( -1 );
	}
	if( libwrc_stream_initialize(
	     stream,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to initialize stream.",
		 function );

		goto on_error;
	}
	if( libwrc_stream_set_virtual_address(
	     *stream,
	     virtual_address,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set virtual address.",
		 function );

		goto on_error;
	}
	result = libwrc_stream_open_file_io_handle(
	          *stream,
	          file_io_handle,
	          LIBWRC_OPEN_READ,
	          error );

	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open stream.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *stream != NULL )
	{
		libwrc_stream_free(
		 stream,
		 NULL );
	}
	return( -1 );
}

/* Closes and frees a source stream
 * Returns 1 if successful or -1 on error
 */
int wrc_test_stream_close_source(
     libwrc_stream_t **stream,
     libcerror_error_t **error )
{
	static char *function = "wrc_test_stream_close_source";
	int result            = 0;

	if( stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid stream.",
		 function );

		return( -1 );
	}
	if( libwrc_stream_close(
	     *stream,
	     error ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_CLOSE_FAILED,
		 "%s: unable to close stream.",
		 function );

		result = -1;
	}
	if( libwrc_stream_free(
	     stream,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free stream.",
		 function );

		result = -1;
	}
	return( result );
}

/* Tests the libwrc_stream_initialize function
 * Returns 1 if successful or 0 if not
 */
int wrc_test_stream_initialize(
     void )
{
	libcerror_error_t *error        = NULL;
	libwrc_stream_t *stream         = NULL;
	int result                      = 0;

#if defined( HAVE_WRC_TEST_MEMORY )
	int number_of_malloc_fail_tests = 1;
	int number_of_memset_fail_tests = 1;
	int test_number                 = 0;
#endif

	/* Test regular cases
	 */
	result = libwrc_stream_initialize(
	          &stream,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_IS_NOT_NULL(
	 "stream",
	 stream );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libwrc_stream_free(
	          &stream,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_IS_NULL(
	 "stream",
	 stream );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libwrc_stream_initialize(
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

	stream = (libwrc_stream_t *) 0x12345678UL;

	result = libwrc_stream_initialize(
	          &stream,
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

	stream = NULL;

#if defined( HAVE_WRC_TEST_MEMORY )

	for( test_number = 0;
	     test_number < number_of_malloc_fail_tests;
	     test_number++ )
	{
		/* Test libwrc_stream_initialize with malloc failing
		 */
		wrc_test_malloc_attempts_before_fail = test_number;

		result = libwrc_stream_initialize(
		          &stream,
		          &error );

		if( wrc_test_malloc_attempts_before_fail != -1 )
		{
			wrc_test_malloc_attempts_before_fail = -1;

			if( stream != NULL )
			{
				libwrc_stream_free(
				 &stream,
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
			 "stream",
			 stream );

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
		/* Test libwrc_stream_initialize with memset failing
		 */
		wrc_test_memset_attempts_before_fail = test_number;

		result = libwrc_stream_initialize(
		          &stream,
		          &error );

		if( wrc_test_memset_attempts_before_fail != -1 )
		{
			wrc_test_memset_attempts_before_fail = -1;

			if( stream != NULL )
			{
				libwrc_stream_free(
				 &stream,
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
			 "stream",
			 stream );

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
	if( stream != NULL )
	{
		libwrc_stream_free(
		 &stream,
		 NULL );
	}
	return( 0 );
}

/* Tests the libwrc_stream_free function
 * Returns 1 if successful or 0 if not
 */
int wrc_test_stream_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libwrc_stream_free(
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

/* Tests the libwrc_stream_open function
 * Returns 1 if successful or 0 if not
 */
int wrc_test_stream_open(
     const system_character_t *source,
     uint32_t virtual_address )
{
	char narrow_source[ 256 ];

	libcerror_error_t *error = NULL;
	libwrc_stream_t *stream  = NULL;
	int result               = 0;

	/* Initialize test
	 */
	result = wrc_test_get_narrow_source(
	          source,
	          narrow_source,
	          256,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libwrc_stream_initialize(
	          &stream,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_IS_NOT_NULL(
	 "stream",
	 stream );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libwrc_stream_set_virtual_address(
	          stream,
	          virtual_address,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test open
	 */
	result = libwrc_stream_open(
	          stream,
	          narrow_source,
	          LIBWRC_OPEN_READ,
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
	result = libwrc_stream_open(
	          NULL,
	          narrow_source,
	          LIBWRC_OPEN_READ,
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

	result = libwrc_stream_open(
	          stream,
	          NULL,
	          LIBWRC_OPEN_READ,
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

	result = libwrc_stream_open(
	          stream,
	          narrow_source,
	          -1,
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

	/* Test open when already opened
	 */
	result = libwrc_stream_open(
	          stream,
	          narrow_source,
	          LIBWRC_OPEN_READ,
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
	result = libwrc_stream_free(
	          &stream,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_IS_NULL(
	 "stream",
	 stream );

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
	if( stream != NULL )
	{
		libwrc_stream_free(
		 &stream,
		 NULL );
	}
	return( 0 );
}

#if defined( HAVE_WIDE_CHARACTER_TYPE )

/* Tests the libwrc_stream_open_wide function
 * Returns 1 if successful or 0 if not
 */
int wrc_test_stream_open_wide(
     const system_character_t *source,
     uint32_t virtual_address )
{
	wchar_t wide_source[ 256 ];

	libcerror_error_t *error = NULL;
	libwrc_stream_t *stream  = NULL;
	int result               = 0;

	/* Initialize test
	 */
	result = wrc_test_get_wide_source(
	          source,
	          wide_source,
	          256,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libwrc_stream_initialize(
	          &stream,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_IS_NOT_NULL(
	 "stream",
	 stream );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libwrc_stream_set_virtual_address(
	          stream,
	          virtual_address,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test open
	 */
	result = libwrc_stream_open_wide(
	          stream,
	          wide_source,
	          LIBWRC_OPEN_READ,
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
	result = libwrc_stream_open_wide(
	          NULL,
	          wide_source,
	          LIBWRC_OPEN_READ,
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

	result = libwrc_stream_open_wide(
	          stream,
	          NULL,
	          LIBWRC_OPEN_READ,
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

	result = libwrc_stream_open_wide(
	          stream,
	          wide_source,
	          -1,
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

	/* Test open when already opened
	 */
	result = libwrc_stream_open_wide(
	          stream,
	          wide_source,
	          LIBWRC_OPEN_READ,
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
	result = libwrc_stream_free(
	          &stream,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_IS_NULL(
	 "stream",
	 stream );

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
	if( stream != NULL )
	{
		libwrc_stream_free(
		 &stream,
		 NULL );
	}
	return( 0 );
}

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

/* Tests the libwrc_stream_open_file_io_handle function
 * Returns 1 if successful or 0 if not
 */
int wrc_test_stream_open_file_io_handle(
     const system_character_t *source,
     uint32_t virtual_address )
{
	libbfio_handle_t *file_io_handle = NULL;
	libcerror_error_t *error         = NULL;
	libwrc_stream_t *stream          = NULL;
	size_t source_length             = 0;
	int result                       = 0;

	/* Initialize test
	 */
	result = libbfio_file_initialize(
	          &file_io_handle,
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

	source_length = system_string_length(
	                 source );

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libbfio_file_set_name_wide(
	          file_io_handle,
	          source,
	          source_length,
	          &error );
#else
	result = libbfio_file_set_name(
	          file_io_handle,
	          source,
	          source_length,
	          &error );
#endif
	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        WRC_TEST_ASSERT_IS_NULL(
         "error",
         error );

	result = libwrc_stream_initialize(
	          &stream,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_IS_NOT_NULL(
	 "stream",
	 stream );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libwrc_stream_set_virtual_address(
	          stream,
	          virtual_address,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test open
	 */
	result = libwrc_stream_open_file_io_handle(
	          stream,
	          file_io_handle,
	          LIBWRC_OPEN_READ,
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
	result = libwrc_stream_open_file_io_handle(
	          NULL,
	          file_io_handle,
	          LIBWRC_OPEN_READ,
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

	result = libwrc_stream_open_file_io_handle(
	          stream,
	          NULL,
	          LIBWRC_OPEN_READ,
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

	result = libwrc_stream_open_file_io_handle(
	          stream,
	          file_io_handle,
	          -1,
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

	/* Test open when already opened
	 */
	result = libwrc_stream_open_file_io_handle(
	          stream,
	          file_io_handle,
	          LIBWRC_OPEN_READ,
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
	result = libwrc_stream_free(
	          &stream,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_IS_NULL(
	 "stream",
	 stream );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libbfio_handle_free(
	          &file_io_handle,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_IS_NULL(
         "file_io_handle",
         file_io_handle );

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
	if( stream != NULL )
	{
		libwrc_stream_free(
		 &stream,
		 NULL );
	}
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
		 NULL );
	}
	return( 0 );
}

/* Tests the libwrc_stream_close function
 * Returns 1 if successful or 0 if not
 */
int wrc_test_stream_close(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libwrc_stream_close(
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

/* Tests the libwrc_stream_open and libwrc_stream_close functions
 * Returns 1 if successful or 0 if not
 */
int wrc_test_stream_open_close(
     const system_character_t *source,
     uint32_t virtual_address )
{
	libcerror_error_t *error = NULL;
	libwrc_stream_t *stream  = NULL;
	int result               = 0;

	/* Initialize test
	 */
	result = libwrc_stream_initialize(
	          &stream,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_IS_NOT_NULL(
	 "stream",
	 stream );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libwrc_stream_set_virtual_address(
	          stream,
	          virtual_address,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test open and close
	 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libwrc_stream_open_wide(
	          stream,
	          source,
	          LIBWRC_OPEN_READ,
	          &error );
#else
	result = libwrc_stream_open(
	          stream,
	          source,
	          LIBWRC_OPEN_READ,
	          &error );
#endif

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libwrc_stream_close(
	          stream,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test open and close a second time to validate clean up on close
	 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libwrc_stream_open_wide(
	          stream,
	          source,
	          LIBWRC_OPEN_READ,
	          &error );
#else
	result = libwrc_stream_open(
	          stream,
	          source,
	          LIBWRC_OPEN_READ,
	          &error );
#endif

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libwrc_stream_close(
	          stream,
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
	result = libwrc_stream_free(
	          &stream,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_IS_NULL(
	 "stream",
	 stream );

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
	if( stream != NULL )
	{
		libwrc_stream_free(
		 &stream,
		 NULL );
	}
	return( 0 );
}

/* Tests the libwrc_stream_signal_abort function
 * Returns 1 if successful or 0 if not
 */
int wrc_test_stream_signal_abort(
     libwrc_stream_t *stream )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test regular cases
	 */
	result = libwrc_stream_signal_abort(
	          stream,
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
	result = libwrc_stream_signal_abort(
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

/* Tests the libwrc_stream_get_ascii_codepage function
 * Returns 1 if successful or 0 if not
 */
int wrc_test_stream_get_ascii_codepage(
     libwrc_stream_t *stream )
{
	libcerror_error_t *error = NULL;
	int ascii_codepage       = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libwrc_stream_get_ascii_codepage(
	          stream,
	          &ascii_codepage,
	          &error );

	WRC_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libwrc_stream_get_ascii_codepage(
	          NULL,
	          &ascii_codepage,
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

	result = libwrc_stream_get_ascii_codepage(
	          stream,
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

/* Tests the libwrc_stream_set_ascii_codepage function
 * Returns 1 if successful or 0 if not
 */
int wrc_test_stream_set_ascii_codepage(
     libwrc_stream_t *stream )
{
	int supported_codepages[ 15 ] = {
		LIBWRC_CODEPAGE_ASCII,
		LIBWRC_CODEPAGE_WINDOWS_874,
		LIBWRC_CODEPAGE_WINDOWS_932,
		LIBWRC_CODEPAGE_WINDOWS_936,
		LIBWRC_CODEPAGE_WINDOWS_949,
		LIBWRC_CODEPAGE_WINDOWS_950,
		LIBWRC_CODEPAGE_WINDOWS_1250,
		LIBWRC_CODEPAGE_WINDOWS_1251,
		LIBWRC_CODEPAGE_WINDOWS_1252,
		LIBWRC_CODEPAGE_WINDOWS_1253,
		LIBWRC_CODEPAGE_WINDOWS_1254,
		LIBWRC_CODEPAGE_WINDOWS_1255,
		LIBWRC_CODEPAGE_WINDOWS_1256,
		LIBWRC_CODEPAGE_WINDOWS_1257,
		LIBWRC_CODEPAGE_WINDOWS_1258 };

	int unsupported_codepages[ 17 ] = {
		LIBWRC_CODEPAGE_ISO_8859_1,
		LIBWRC_CODEPAGE_ISO_8859_2,
		LIBWRC_CODEPAGE_ISO_8859_3,
		LIBWRC_CODEPAGE_ISO_8859_4,
		LIBWRC_CODEPAGE_ISO_8859_5,
		LIBWRC_CODEPAGE_ISO_8859_6,
		LIBWRC_CODEPAGE_ISO_8859_7,
		LIBWRC_CODEPAGE_ISO_8859_8,
		LIBWRC_CODEPAGE_ISO_8859_9,
		LIBWRC_CODEPAGE_ISO_8859_10,
		LIBWRC_CODEPAGE_ISO_8859_11,
		LIBWRC_CODEPAGE_ISO_8859_13,
		LIBWRC_CODEPAGE_ISO_8859_14,
		LIBWRC_CODEPAGE_ISO_8859_15,
		LIBWRC_CODEPAGE_ISO_8859_16,
		LIBWRC_CODEPAGE_KOI8_R,
		LIBWRC_CODEPAGE_KOI8_U };

	libcerror_error_t *error = NULL;
	int codepage             = 0;
	int index                = 0;
	int result               = 0;

	/* Test set ASCII codepage
	 */
	for( index = 0;
	     index < 15;
	     index++ )
	{
		codepage = supported_codepages[ index ];

		result = libwrc_stream_set_ascii_codepage(
		          stream,
		          codepage,
		          &error );

		WRC_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		WRC_TEST_ASSERT_IS_NULL(
		 "error",
		 error );
	}
	/* Test error cases
	 */
	result = libwrc_stream_set_ascii_codepage(
	          NULL,
	          LIBWRC_CODEPAGE_ASCII,
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

	for( index = 0;
	     index < 17;
	     index++ )
	{
		codepage = unsupported_codepages[ index ];

		result = libwrc_stream_set_ascii_codepage(
		          stream,
		          codepage,
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
	result = libwrc_stream_set_ascii_codepage(
	          stream,
	          LIBWRC_CODEPAGE_WINDOWS_1252,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

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
	return( 0 );
}

/* Tests the libwrc_stream_get_virtual_address function
 * Returns 1 if successful or 0 if not
 */
int wrc_test_stream_get_virtual_address(
     libwrc_stream_t *stream )
{
	libcerror_error_t *error = NULL;
	uint32_t virtual_address = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libwrc_stream_get_virtual_address(
	          stream,
	          &virtual_address,
	          &error );

	WRC_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libwrc_stream_get_virtual_address(
	          NULL,
	          &virtual_address,
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

	result = libwrc_stream_get_virtual_address(
	          stream,
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

/* Tests the libwrc_stream_get_number_of_resources function
 * Returns 1 if successful or 0 if not
 */
int wrc_test_stream_get_number_of_resources(
     libwrc_stream_t *stream )
{
	libcerror_error_t *error = NULL;
	int number_of_resources  = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libwrc_stream_get_number_of_resources(
	          stream,
	          &number_of_resources,
	          &error );

	WRC_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libwrc_stream_get_number_of_resources(
	          NULL,
	          &number_of_resources,
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

	result = libwrc_stream_get_number_of_resources(
	          stream,
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

/* Tests the libwrc_stream_get_resource_by_index function
 * Returns 1 if successful or 0 if not
 */
int wrc_test_stream_get_resource_by_index(
     libwrc_stream_t *stream )
{
	libcerror_error_t *error    = NULL;
	libwrc_resource_t *resource = NULL;
	int result                  = 0;

	/* Test regular cases
	 */
	result = libwrc_stream_get_resource_by_index(
	          stream,
	          0,
	          &resource,
	          &error );

	WRC_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	WRC_TEST_ASSERT_IS_NOT_NULL(
	 "resource",
	 resource );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libwrc_resource_free(
	          &resource,
	          &error );

	WRC_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	WRC_TEST_ASSERT_IS_NULL(
	 "resource",
	 resource );

	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libwrc_stream_get_resource_by_index(
	          NULL,
	          0,
	          &resource,
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

	result = libwrc_stream_get_resource_by_index(
	          stream,
	          -1,
	          &resource,
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

	result = libwrc_stream_get_resource_by_index(
	          stream,
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

/* Tests the libwrc_stream_get_resource_by_identifier function
 * Returns 1 if successful or 0 if not
 */
int wrc_test_stream_get_resource_by_identifier(
     libwrc_stream_t *stream )
{
	libcerror_error_t *error    = NULL;
	libwrc_resource_t *resource = NULL;
	int result                  = 0;

	/* Test regular cases
	 */
	result = libwrc_stream_get_resource_by_identifier(
	          stream,
	          0x0000038eUL,
	          &resource,
	          &error );

	WRC_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	if( result == 0 )
	{
		WRC_TEST_ASSERT_IS_NULL(
		 "resource",
		 resource );
	}
	else
	{
		WRC_TEST_ASSERT_IS_NOT_NULL(
		 "resource",
		 resource );
	}
	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	if( resource != NULL )
	{
		result = libwrc_resource_free(
		          &resource,
		          &error );

		WRC_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		WRC_TEST_ASSERT_IS_NULL(
		 "resource",
		 resource );

		WRC_TEST_ASSERT_IS_NULL(
		 "error",
		 error );
	}
	/* Test error cases
	 */
	result = libwrc_stream_get_resource_by_identifier(
	          NULL,
	          0x0000038eUL,
	          &resource,
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

	result = libwrc_stream_get_resource_by_identifier(
	          stream,
	          0x0000038eUL,
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

/* Tests the libwrc_stream_get_resource_by_type function
 * Returns 1 if successful or 0 if not
 */
int wrc_test_stream_get_resource_by_type(
     libwrc_stream_t *stream )
{
	libcerror_error_t *error    = NULL;
	libwrc_resource_t *resource = NULL;
	int result                  = 0;

	/* Test regular cases
	 */
	result = libwrc_stream_get_resource_by_type(
	          stream,
	          0x0000038eUL,
	          &resource,
	          &error );

	WRC_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	if( result == 0 )
	{
		WRC_TEST_ASSERT_IS_NULL(
		 "resource",
		 resource );
	}
	else
	{
		WRC_TEST_ASSERT_IS_NOT_NULL(
		 "resource",
		 resource );
	}
	WRC_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	if( resource != NULL )
	{
		result = libwrc_resource_free(
		          &resource,
		          &error );

		WRC_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		WRC_TEST_ASSERT_IS_NULL(
		 "resource",
		 resource );

		WRC_TEST_ASSERT_IS_NULL(
		 "error",
		 error );
	}
	/* Test error cases
	 */
	result = libwrc_stream_get_resource_by_type(
	          NULL,
	          0x0000038eUL,
	          &resource,
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

	result = libwrc_stream_get_resource_by_type(
	          stream,
	          0x0000038eUL,
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
     int argc,
     wchar_t * const argv[] )
#else
int main(
     int argc,
     char * const argv[] )
#endif
{
	libbfio_handle_t *file_io_handle           = NULL;
	libcerror_error_t *error                   = NULL;
	libwrc_stream_t *stream                    = NULL;
	system_character_t *option_virtual_address = NULL;
	system_character_t *source                 = NULL;
	system_integer_t option                    = 0;
	size_t string_length                       = 0;
	uint64_t virtual_address                   = 0;
	int result                                 = 0;

	while( ( option = wrc_test_getopt(
	                   argc,
	                   argv,
	                   _SYSTEM_STRING( "v:" ) ) ) != (system_integer_t) -1 )
	{
		switch( option )
		{
			case (system_integer_t) '?':
			default:
				fprintf(
				 stderr,
				 "Invalid argument: %" PRIs_SYSTEM ".\n",
				 argv[ optind - 1 ] );

				return( EXIT_FAILURE );

			case (system_integer_t) 'v':
				option_virtual_address = optarg;

				break;
		}
	}
	if( optind < argc )
	{
		source = argv[ optind ];
	}
	if( option_virtual_address != NULL )
	{
		string_length = system_string_length(
		                 option_virtual_address );

		result = wrc_test_system_string_copy_from_64_bit_in_decimal(
		          option_virtual_address,
		          string_length + 1,
		          (uint64_t *) &virtual_address,
		          &error );

		WRC_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

	        WRC_TEST_ASSERT_IS_NULL(
	         "error",
	         error );
	}
#if defined( HAVE_DEBUG_OUTPUT ) && defined( WRC_TEST_STREAM_VERBOSE )
	libwrc_notify_set_verbose(
	 1 );
	libwrc_notify_set_stream(
	 stderr,
	 NULL );
#endif

	WRC_TEST_RUN(
	 "libwrc_stream_initialize",
	 wrc_test_stream_initialize );

	WRC_TEST_RUN(
	 "libwrc_stream_free",
	 wrc_test_stream_free );

#if !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 )
	if( source != NULL )
	{
		WRC_TEST_RUN_WITH_ARGS(
		 "libwrc_stream_open",
		 wrc_test_stream_open,
		 source,
		 (uint32_t) virtual_address );

#if defined( HAVE_WIDE_CHARACTER_TYPE )

		WRC_TEST_RUN_WITH_ARGS(
		 "libwrc_stream_open_wide",
		 wrc_test_stream_open_wide,
		 source,
		 (uint32_t) virtual_address );

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

		WRC_TEST_RUN_WITH_ARGS(
		 "libwrc_stream_open_file_io_handle",
		 wrc_test_stream_open_file_io_handle,
		 source,
		 (uint32_t) virtual_address );

		WRC_TEST_RUN(
		 "libwrc_stream_close",
		 wrc_test_stream_close );

		WRC_TEST_RUN_WITH_ARGS(
		 "libwrc_stream_open_close",
		 wrc_test_stream_open_close,
		 source,
		 (uint32_t) virtual_address );

		/* Initialize test
		 */
		result = libbfio_file_initialize(
		          &file_io_handle,
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

		string_length = system_string_length(
		                 source );

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
		result = libbfio_file_set_name_wide(
		          file_io_handle,
		          source,
		          string_length,
		          &error );
#else
		result = libbfio_file_set_name(
		          file_io_handle,
		          source,
		          string_length,
		          &error );
#endif
		WRC_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

	        WRC_TEST_ASSERT_IS_NULL(
	         "error",
	         error );

		result = wrc_test_stream_open_source(
		          &stream,
		          file_io_handle,
		          (uint32_t) virtual_address,
		          &error );

		WRC_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		WRC_TEST_ASSERT_IS_NOT_NULL(
		 "stream",
		 stream );

		WRC_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		WRC_TEST_RUN_WITH_ARGS(
		 "libwrc_stream_signal_abort",
		 wrc_test_stream_signal_abort,
		 stream );

#if defined( __GNUC__ ) && !defined( LIBWRC_DLL_IMPORT )

		/* TODO: add tests for libwrc_stream_open_read */

#endif /* defined( __GNUC__ ) && !defined( LIBWRC_DLL_IMPORT ) */

		WRC_TEST_RUN_WITH_ARGS(
		 "libwrc_stream_get_ascii_codepage",
		 wrc_test_stream_get_ascii_codepage,
		 stream );

		WRC_TEST_RUN_WITH_ARGS(
		 "libwrc_stream_set_ascii_codepage",
		 wrc_test_stream_set_ascii_codepage,
		 stream );

		WRC_TEST_RUN_WITH_ARGS(
		 "libwrc_stream_get_virtual_address",
		 wrc_test_stream_get_virtual_address,
		 stream );

		/* TODO: add tests for libwrc_stream_set_virtual_address */

		WRC_TEST_RUN_WITH_ARGS(
		 "libwrc_stream_get_number_of_resources",
		 wrc_test_stream_get_number_of_resources,
		 stream );

		WRC_TEST_RUN_WITH_ARGS(
		 "libwrc_stream_get_resource_by_index",
		 wrc_test_stream_get_resource_by_index,
		 stream );

		WRC_TEST_RUN_WITH_ARGS(
		 "libwrc_stream_get_resource_by_identifier",
		 wrc_test_stream_get_resource_by_identifier,
		 stream );

		WRC_TEST_RUN_WITH_ARGS(
		 "libwrc_stream_get_resource_by_type",
		 wrc_test_stream_get_resource_by_type,
		 stream );

		/* TODO: add tests for libwrc_stream_get_resource_by_utf8_name */

		/* TODO: add tests for libwrc_stream_get_resource_by_utf16_name */

		/* Clean up
		 */
		result = wrc_test_stream_close_source(
		          &stream,
		          &error );

		WRC_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 0 );

		WRC_TEST_ASSERT_IS_NULL(
		 "stream",
		 stream );

		WRC_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		result = libbfio_handle_free(
		          &file_io_handle,
		          &error );

		WRC_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		WRC_TEST_ASSERT_IS_NULL(
	         "file_io_handle",
	         file_io_handle );

	        WRC_TEST_ASSERT_IS_NULL(
	         "error",
	         error );
	}
#endif /* !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 ) */

	return( EXIT_SUCCESS );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( stream != NULL )
	{
		libwrc_stream_free(
		 &stream,
		 NULL );
	}
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
		 NULL );
	}
	return( EXIT_FAILURE );
}

