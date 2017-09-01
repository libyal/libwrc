/*
 * Library stream type test program
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
#include <narrow_string.h>
#include <system_string.h>
#include <types.h>
#include <wide_string.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "wrc_test_getopt.h"
#include "wrc_test_libcerror.h"
#include "wrc_test_libclocale.h"
#include "wrc_test_libuna.h"
#include "wrc_test_libwrc.h"
#include "wrc_test_macros.h"
#include "wrc_test_memory.h"

#if defined( HAVE_WIDE_SYSTEM_CHARACTER ) && SIZEOF_WCHAR_T != 2 && SIZEOF_WCHAR_T != 4
#error Unsupported size of wchar_t
#endif

/* Define to make wrc_test_stream generate verbose output
#define WRC_TEST_STREAM_VERBOSE
 */

/* Retrieves source as a narrow string
 * Returns 1 if successful or -1 on error
 */
int wrc_test_stream_get_narrow_source(
     const system_character_t *source,
     char *narrow_string,
     size_t narrow_string_size,
     libcerror_error_t **error )
{
	static char *function     = "wrc_test_stream_get_narrow_source";
	size_t narrow_source_size = 0;
	size_t source_length      = 0;

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	int result                = 0;
#endif

	if( source == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid source.",
		 function );

		return( -1 );
	}
	if( narrow_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid narrow string.",
		 function );

		return( -1 );
	}
	if( narrow_string_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid narrow string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	source_length = system_string_length(
	                 source );

	if( source_length > (size_t) ( SSIZE_MAX - 1 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid source length value out of bounds.",
		 function );

		return( -1 );
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	if( libclocale_codepage == 0 )
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf8_string_size_from_utf32(
		          (libuna_utf32_character_t *) source,
		          source_length + 1,
		          &narrow_source_size,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf8_string_size_from_utf16(
		          (libuna_utf16_character_t *) source,
		          source_length + 1,
		          &narrow_source_size,
		          error );
#endif
	}
	else
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_byte_stream_size_from_utf32(
		          (libuna_utf32_character_t *) source,
		          source_length + 1,
		          libclocale_codepage,
		          &narrow_source_size,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_byte_stream_size_from_utf16(
		          (libuna_utf16_character_t *) source,
		          source_length + 1,
		          libclocale_codepage,
		          &narrow_source_size,
		          error );
#endif
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to determine narrow string size.",
		 function );

		return( -1 );
	}
#else
	narrow_source_size = source_length + 1;

#endif /* defined( HAVE_WIDE_SYSTEM_CHARACTER ) */

	if( narrow_string_size < narrow_source_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: narrow string too small.",
		 function );

		return( -1 );
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	if( libclocale_codepage == 0 )
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf8_string_copy_from_utf32(
		          (libuna_utf8_character_t *) narrow_string,
		          narrow_string_size,
		          (libuna_utf32_character_t *) source,
		          source_length + 1,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf8_string_copy_from_utf16(
		          (libuna_utf8_character_t *) narrow_string,
		          narrow_string_size,
		          (libuna_utf16_character_t *) source,
		          source_length + 1,
		          error );
#endif
	}
	else
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_byte_stream_copy_from_utf32(
		          (uint8_t *) narrow_string,
		          narrow_string_size,
		          libclocale_codepage,
		          (libuna_utf32_character_t *) source,
		          source_length + 1,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_byte_stream_copy_from_utf16(
		          (uint8_t *) narrow_string,
		          narrow_string_size,
		          libclocale_codepage,
		          (libuna_utf16_character_t *) source,
		          source_length + 1,
		          error );
#endif
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to set narrow string.",
		 function );

		return( -1 );
	}
#else
	if( system_string_copy(
	     narrow_string,
	     source,
	     source_length ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to set narrow string.",
		 function );

		return( -1 );
	}
	narrow_string[ source_length ] = 0;

#endif /* defined( HAVE_WIDE_SYSTEM_CHARACTER ) */

	return( 1 );
}

#if defined( HAVE_WIDE_CHARACTER_TYPE )

/* Retrieves source as a wide string
 * Returns 1 if successful or -1 on error
 */
int wrc_test_stream_get_wide_source(
     const system_character_t *source,
     wchar_t *wide_string,
     size_t wide_string_size,
     libcerror_error_t **error )
{
	static char *function   = "wrc_test_stream_get_wide_source";
	size_t source_length    = 0;
	size_t wide_source_size = 0;

#if !defined( HAVE_WIDE_SYSTEM_CHARACTER )
	int result              = 0;
#endif

	if( source == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid source.",
		 function );

		return( -1 );
	}
	if( wide_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid wide string.",
		 function );

		return( -1 );
	}
	if( wide_string_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid wide string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	source_length = system_string_length(
	                 source );

	if( source_length > (size_t) ( SSIZE_MAX - 1 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid source length value out of bounds.",
		 function );

		return( -1 );
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	wide_source_size = source_length + 1;
#else
	if( libclocale_codepage == 0 )
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf32_string_size_from_utf8(
		          (libuna_utf8_character_t *) source,
		          source_length + 1,
		          &wide_source_size,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf16_string_size_from_utf8(
		          (libuna_utf8_character_t *) source,
		          source_length + 1,
		          &wide_source_size,
		          error );
#endif
	}
	else
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf32_string_size_from_byte_stream(
		          (uint8_t *) source,
		          source_length + 1,
		          libclocale_codepage,
		          &wide_source_size,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf16_string_size_from_byte_stream(
		          (uint8_t *) source,
		          source_length + 1,
		          libclocale_codepage,
		          &wide_source_size,
		          error );
#endif
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to determine wide string size.",
		 function );

		return( -1 );
	}

#endif /* defined( HAVE_WIDE_SYSTEM_CHARACTER ) */

	if( wide_string_size < wide_source_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: wide string too small.",
		 function );

		return( -1 );
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	if( system_string_copy(
	     wide_string,
	     source,
	     source_length ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to set wide string.",
		 function );

		return( -1 );
	}
	wide_string[ source_length ] = 0;
#else
	if( libclocale_codepage == 0 )
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf32_string_copy_from_utf8(
		          (libuna_utf32_character_t *) wide_string,
		          wide_string_size,
		          (libuna_utf8_character_t *) source,
		          source_length + 1,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf16_string_copy_from_utf8(
		          (libuna_utf16_character_t *) wide_string,
		          wide_string_size,
		          (libuna_utf8_character_t *) source,
		          source_length + 1,
		          error );
#endif
	}
	else
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf32_string_copy_from_byte_stream(
		          (libuna_utf32_character_t *) wide_string,
		          wide_string_size,
		          (uint8_t *) source,
		          source_length + 1,
		          libclocale_codepage,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf16_string_copy_from_byte_stream(
		          (libuna_utf16_character_t *) wide_string,
		          wide_string_size,
		          (uint8_t *) source,
		          source_length + 1,
		          libclocale_codepage,
		          error );
#endif
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to set wide string.",
		 function );

		return( -1 );
	}

#endif /* defined( HAVE_WIDE_SYSTEM_CHARACTER ) */

	return( 1 );
}

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

/* Creates and opens a source stream
 * Returns 1 if successful or -1 on error
 */
int wrc_test_stream_open_source(
     libwrc_stream_t **stream,
     const system_character_t *source,
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
	if( source == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid source.",
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
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libwrc_stream_open_wide(
	          *stream,
	          source,
	          LIBWRC_OPEN_READ,
	          error );
#else
	result = libwrc_stream_open(
	          *stream,
	          source,
	          LIBWRC_OPEN_READ,
	          error );
#endif
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
     const system_character_t *source )
{
	char narrow_source[ 256 ];

	libcerror_error_t *error = NULL;
	libwrc_stream_t *stream  = NULL;
	int result               = 0;

	/* Initialize test
	 */
	result = wrc_test_stream_get_narrow_source(
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
     const system_character_t *source )
{
	wchar_t wide_source[ 256 ];

	libcerror_error_t *error = NULL;
	libwrc_stream_t *stream  = NULL;
	int result               = 0;

	/* Initialize test
	 */
	result = wrc_test_stream_get_wide_source(
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
     const system_character_t *source )
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
	libcerror_error_t *error  = NULL;
	int ascii_codepage        = 0;
	int ascii_codepage_is_set = 0;
	int result                = 0;

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

	ascii_codepage_is_set = result;

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

	if( ascii_codepage_is_set != 0 )
	{
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
	}
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
	libcerror_error_t *error   = NULL;
	uint32_t virtual_address   = 0;
	int result                 = 0;
	int virtual_address_is_set = 0;

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

	virtual_address_is_set = result;

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

	if( virtual_address_is_set != 0 )
	{
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
	}
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
	libcerror_error_t *error       = NULL;
	int number_of_resources        = 0;
	int number_of_resources_is_set = 0;
	int result                     = 0;

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

	number_of_resources_is_set = result;

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

	if( number_of_resources_is_set != 0 )
	{
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
	}
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
	libcerror_error_t *error   = NULL;
	libwrc_stream_t *stream    = NULL;
	system_character_t *source = NULL;
	system_integer_t option    = 0;
	int result                 = 0;

	while( ( option = wrc_test_getopt(
	                   argc,
	                   argv,
	                   _SYSTEM_STRING( "" ) ) ) != (system_integer_t) -1 )
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
		}
	}
	if( optind < argc )
	{
		source = argv[ optind ];
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
		 source );

#if defined( HAVE_WIDE_CHARACTER_TYPE )

		WRC_TEST_RUN_WITH_ARGS(
		 "libwrc_stream_open_wide",
		 wrc_test_stream_open_wide,
		 source );

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

#if defined( LIBWRC_HAVE_BFIO )

		/* TODO add test for libwrc_stream_open_file_io_handle */

#endif /* defined( LIBWRC_HAVE_BFIO ) */

		WRC_TEST_RUN(
		 "libwrc_stream_close",
		 wrc_test_stream_close );

		WRC_TEST_RUN_WITH_ARGS(
		 "libwrc_stream_open_close",
		 wrc_test_stream_open_close,
		 source );

		/* Initialize test
		 */
		result = wrc_test_stream_open_source(
		          &stream,
		          source,
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

		/* TODO: add tests for libwrc_stream_get_resource */

		/* TODO: add tests for libwrc_stream_get_resource_by_identifier */

		/* TODO: add tests for libwrc_stream_get_resource_by_type */

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
		wrc_test_stream_close_source(
		 &stream,
		 NULL );
	}
	return( EXIT_FAILURE );
}

