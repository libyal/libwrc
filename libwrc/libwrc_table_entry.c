/*
 * Message or string table entry functions
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
#include <memory.h>
#include <types.h>

#include "libwrc_libcerror.h"
#include "libwrc_libuna.h"
#include "libwrc_table_entry.h"

/* Creates a table entry
 * Make sure the value table_entry is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libwrc_table_entry_initialize(
     libwrc_table_entry_t **table_entry,
     libcerror_error_t **error )
{
	static char *function = "libwrc_table_entry_initialize";

	if( table_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid table entry.",
		 function );

		return( -1 );
	}
	if( *table_entry != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid table entry value already set.",
		 function );

		return( -1 );
	}
	*table_entry = memory_allocate_structure(
	                libwrc_table_entry_t );

	if( *table_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create table entry.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *table_entry,
	     0,
	     sizeof( libwrc_table_entry_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear table entry.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *table_entry != NULL )
	{
		memory_free(
		 *table_entry );

		*table_entry = NULL;
	}
	return( -1 );
}

/* Frees a table entry
 * Returns 1 if successful or -1 on error
 */
int libwrc_table_entry_free(
     libwrc_table_entry_t **table_entry,
     libcerror_error_t **error )
{
	static char *function = "libwrc_table_entry_free";

	if( table_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid table entry.",
		 function );

		return( -1 );
	}
	if( *table_entry != NULL )
	{
		if( ( *table_entry )->string != NULL )
		{
			memory_free(
			 ( *table_entry )->string );
		}
		memory_free(
		 *table_entry );

		*table_entry = NULL;
	}
	return( 1 );
}

/* Sets the string
 * Returns 1 if successful or -1 on error
 */
int libwrc_table_entry_set_string(
     libwrc_table_entry_t *table_entry,
     const uint8_t *string,
     size_t string_size,
     int codepage,
     libcerror_error_t **error )
{
	static char *function = "libwrc_table_entry_set_string";

	if( table_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid table entry.",
		 function );

		return( -1 );
	}
	if( table_entry->string != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid table entry - string value already set.",
		 function );

		return( -1 );
	}
	if( string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid string.",
		 function );

		return( -1 );
	}
	if( ( string_size == 0 )
	 || ( string_size > (size_t) MEMORY_MAXIMUM_ALLOCATION_SIZE ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid string size value out of bounds.",
		 function );

		return( -1 );
	}
	table_entry->string = (uint8_t *) memory_allocate(
	                                   sizeof( uint8_t ) * string_size );

	if( table_entry->string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create string.",
		 function );

		goto on_error;
	}
	table_entry->string_size = string_size;

	if( memory_copy(
	     table_entry->string,
	     string,
	     string_size ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy data to string.",
		 function );

		goto on_error;
	}
	table_entry->codepage = codepage;

	return( 1 );

on_error:
	if( table_entry->string != NULL )
	{
		memory_free(
		 table_entry->string );

		table_entry->string = NULL;
	}
	table_entry->string_size = 0;

	return( -1 );
}

/* Retrieves the size of a specific UTF-8 formatted string
 * Returns 1 if successful or -1 on error
 */
int libwrc_table_entry_get_utf8_string_size(
     libwrc_table_entry_t *table_entry,
     size_t *utf8_string_size,
     libcerror_error_t **error )
{
	static char *function = "libwrc_table_entry_get_utf8_string_size";
	int result            = 0;

	if( table_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid manifest resource.",
		 function );

		return( -1 );
	}
	if( table_entry->codepage == LIBUNA_CODEPAGE_UTF16_LITTLE_ENDIAN )
	{
		result = libuna_utf8_string_size_from_utf16_stream(
		          table_entry->string,
		          table_entry->string_size,
		          LIBUNA_ENDIAN_LITTLE,
		          utf8_string_size,
		          error );
	}
	else
	{
		result = libuna_utf8_string_size_from_byte_stream(
		          table_entry->string,
		          table_entry->string_size,
		          table_entry->codepage,
		          utf8_string_size,
		          error );
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve UTF-8 string size.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves a specific UTF-8 formatted string
 * Returns 1 if successful or -1 on error
 */
int libwrc_table_entry_get_utf8_string(
     libwrc_table_entry_t *table_entry,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error )
{
	static char *function = "libwrc_table_entry_get_utf8_string";
	int result            = 0;

	if( table_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid manifest resource.",
		 function );

		return( -1 );
	}
	if( table_entry->codepage == LIBUNA_CODEPAGE_UTF16_LITTLE_ENDIAN )
	{
		result = libuna_utf8_string_copy_from_utf16_stream(
		          utf8_string,
		          utf8_string_size,
		          table_entry->string,
		          table_entry->string_size,
		          LIBUNA_ENDIAN_LITTLE,
		          error );
	}
	else
	{
		result = libuna_utf8_string_copy_from_byte_stream(
		          utf8_string,
		          utf8_string_size,
		          table_entry->string,
		          table_entry->string_size,
		          table_entry->codepage,
		          error );
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve UTF-8 string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the size of a specific UTF-16 formatted string
 * Returns 1 if successful or -1 on error
 */
int libwrc_table_entry_get_utf16_string_size(
     libwrc_table_entry_t *table_entry,
     size_t *utf16_string_size,
     libcerror_error_t **error )
{
	static char *function = "libwrc_table_entry_get_utf16_string_size";
	int result            = 0;

	if( table_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid manifest resource.",
		 function );

		return( -1 );
	}
	if( table_entry->codepage == LIBUNA_CODEPAGE_UTF16_LITTLE_ENDIAN )
	{
		result = libuna_utf16_string_size_from_utf16_stream(
		          table_entry->string,
		          table_entry->string_size,
		          LIBUNA_ENDIAN_LITTLE,
		          utf16_string_size,
		          error );
	}
	else
	{
		result = libuna_utf16_string_size_from_byte_stream(
		          table_entry->string,
		          table_entry->string_size,
		          table_entry->codepage,
		          utf16_string_size,
		          error );
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve UTF-16 string size.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves a specific UTF-16 formatted string
 * Returns 1 if successful or -1 on error
 */
int libwrc_table_entry_get_utf16_string(
     libwrc_table_entry_t *table_entry,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error )
{
	static char *function = "libwrc_table_entry_get_utf16_string";
	int result            = 0;

	if( table_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid manifest resource.",
		 function );

		return( -1 );
	}
	if( table_entry->codepage == LIBUNA_CODEPAGE_UTF16_LITTLE_ENDIAN )
	{
		result = libuna_utf16_string_copy_from_utf16_stream(
		          utf16_string,
		          utf16_string_size,
		          table_entry->string,
		          table_entry->string_size,
		          LIBUNA_ENDIAN_LITTLE,
		          error );
	}
	else
	{
		result = libuna_utf16_string_copy_from_byte_stream(
		          utf16_string,
		          utf16_string_size,
		          table_entry->string,
		          table_entry->string_size,
		          table_entry->codepage,
		          error );
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve UTF-16 string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

