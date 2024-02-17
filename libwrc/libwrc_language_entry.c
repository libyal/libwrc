/*
 * Language (table) entry functions
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

#include "libwrc_definitions.h"
#include "libwrc_language_entry.h"
#include "libwrc_libcdata.h"
#include "libwrc_libcerror.h"
#include "libwrc_libcnotify.h"

/* Creates a language entry
 * Make sure the value language_entry is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libwrc_language_entry_initialize(
     libwrc_language_entry_t **language_entry,
     uint32_t language_identifier,
     int (*value_free_function)(
            intptr_t **value,
            libcerror_error_t **error ),
     libcerror_error_t **error )
{
	static char *function = "libwrc_language_entry_initialize";

	if( language_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid language entry.",
		 function );

		return( -1 );
	}
	if( *language_entry != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid language entry value already set.",
		 function );

		return( -1 );
	}
	if( value_free_function == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid value free function.",
		 function );

		return( -1 );
	}
	*language_entry = memory_allocate_structure(
	                   libwrc_language_entry_t );

	if( *language_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create language entry.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *language_entry,
	     0,
	     sizeof( libwrc_language_entry_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear language entry.",
		 function );

		memory_free(
		 *language_entry );

		*language_entry = NULL;

		return( -1 );
	}
	if( libcdata_array_initialize(
	     &( ( *language_entry )->values_array ),
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create values array.",
		 function );

		goto on_error;
	}
	( *language_entry )->language_identifier = language_identifier;
	( *language_entry )->value_free_function = value_free_function;


	return( 1 );

on_error:
	if( *language_entry != NULL )
	{
		memory_free(
		 *language_entry );

		*language_entry = NULL;
	}
	return( -1 );
}

/* Frees a language entry
 * Returns 1 if successful or -1 on error
 */
int libwrc_language_entry_free(
     libwrc_language_entry_t **language_entry,
     libcerror_error_t **error )
{
	static char *function = "libwrc_language_entry_free";
	int result            = 1;

	if( language_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid language entry.",
		 function );

		return( -1 );
	}
	if( *language_entry != NULL )
	{
		if( libcdata_array_free(
		     &( ( *language_entry )->values_array ),
		     ( *language_entry )->value_free_function,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free values array.",
			 function );

			result = -1;
		}
		memory_free(
		 *language_entry );

		*language_entry = NULL;
	}
	return( result );
}

/* Retrieves the number of values
 * Returns 1 if successful or -1 on error
 */
int libwrc_language_entry_get_number_of_values(
     libwrc_language_entry_t *language_entry,
     int *number_of_values,
     libcerror_error_t **error )
{
	static char *function = "libwrc_language_entry_get_number_of_values";

	if( language_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid language entry.",
		 function );

		return( -1 );
	}
	if( libcdata_array_get_number_of_entries(
	     language_entry->values_array,
	     number_of_values,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of entries.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves a specific value
 * Returns 1 if successful or -1 on error
 */
int libwrc_language_entry_get_value_by_index(
     libwrc_language_entry_t *language_entry,
     int value_index,
     intptr_t **value,
     libcerror_error_t **error )
{
	static char *function = "libwrc_language_entry_get_value_by_index";

	if( language_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid language entry.",
		 function );

		return( -1 );
	}
	if( libcdata_array_get_entry_by_index(
	     language_entry->values_array,
	     value_index,
	     value,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve entry: %d.",
		 function,
		 value_index );

		return( -1 );
	}
	return( 1 );
}

/* Appends a value
 * Returns 1 if successful or -1 on error
 */
int libwrc_language_entry_append_value(
     libwrc_language_entry_t *language_entry,
     int *value_index,
     intptr_t *value,
     libcerror_error_t **error )
{
	static char *function = "libwrc_language_entry_append_value";

	if( language_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid language entry.",
		 function );

		return( -1 );
	}
	if( libcdata_array_append_entry(
	     language_entry->values_array,
	     value_index,
	     value,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
		 "%s: unable to append entry.",
		 function,
		 value_index );

		return( -1 );
	}
	return( 1 );
}

