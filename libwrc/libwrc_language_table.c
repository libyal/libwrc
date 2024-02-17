/*
 * Language table functions
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

#include "libwrc_language_entry.h"
#include "libwrc_language_table.h"
#include "libwrc_libcdata.h"
#include "libwrc_libcerror.h"

/* Creates a language table
 * Make sure the value language_table is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libwrc_language_table_initialize(
     libwrc_language_table_t **language_table,
     libcerror_error_t **error )
{
	static char *function = "libwrc_language_table_initialize";

	if( language_table == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid language table.",
		 function );

		return( -1 );
	}
	if( *language_table != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid language table value already set.",
		 function );

		return( -1 );
	}
	*language_table = memory_allocate_structure(
	                   libwrc_language_table_t );

	if( *language_table == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create language table.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *language_table,
	     0,
	     sizeof( libwrc_language_table_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear language table.",
		 function );

		memory_free(
		 *language_table );

		*language_table = NULL;

		return( -1 );
	}
	if( libcdata_array_initialize(
	     &( ( *language_table )->entries_array ),
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create entries array.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *language_table != NULL )
	{
		memory_free(
		 *language_table );

		*language_table = NULL;
	}
	return( -1 );
}

/* Frees a language table
 * Returns 1 if successful or -1 on error
 */
int libwrc_language_table_free(
     libwrc_language_table_t **language_table,
     libcerror_error_t **error )
{
	static char *function = "libwrc_language_table_free";
	int result            = 1;

	if( language_table == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid language table.",
		 function );

		return( -1 );
	}
	if( *language_table != NULL )
	{
		if( libcdata_array_free(
		     &( ( *language_table )->entries_array ),
		     (int (*)(intptr_t **, libcerror_error_t **)) &libwrc_language_entry_free,
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
		 *language_table );

		*language_table = NULL;
	}
	return( result );
}

/* Retrieves the number of entries
 * Returns 1 if successful or -1 on error
 */
int libwrc_language_table_get_number_of_entries(
     libwrc_language_table_t *language_table,
     int *number_of_entries,
     libcerror_error_t **error )
{
	static char *function = "libwrc_language_table_get_number_of_entries";

	if( language_table == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid language table.",
		 function );

		return( -1 );
	}
	if( libcdata_array_get_number_of_entries(
	     language_table->entries_array,
	     number_of_entries,
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

/* Retrieves a specific language identifier
 * Returns 1 if successful or -1 on error
 */
int libwrc_language_table_get_identifier(
     libwrc_language_table_t *language_table,
     int entry_index,
     uint32_t *language_identifier,
     libcerror_error_t **error )
{
	libwrc_language_entry_t *language_entry = NULL;
	static char *function                   = "libwrc_language_table_get_identifier";

	if( language_table == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid language table.",
		 function );

		return( -1 );
	}
	if( language_identifier == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid language identifier.",
		 function );

		return( -1 );
	}
	if( libcdata_array_get_entry_by_index(
	     language_table->entries_array,
	     entry_index,
	     (intptr_t **) &language_entry,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve language entry: %d.",
		 function,
		 entry_index );

		return( -1 );
	}
	if( language_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: missing language entry: %d.",
		 function,
		 entry_index );

		return( -1 );
	}
	*language_identifier = language_entry->language_identifier;

	return( 1 );
}

/* Retrieves the entry for a specific language identifier
 * Returns 1 if successful, 0 if no such language or -1 on error
 */
int libwrc_language_table_get_entry_by_identifier(
     libwrc_language_table_t *language_table,
     uint32_t language_identifier,
     libwrc_language_entry_t **language_entry,
     libcerror_error_t **error )
{
	static char *function = "libwrc_language_table_get_entry_by_identifier";
	int entry_index       = 0;
	int number_of_entries = 0;

	if( language_table == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid language table.",
		 function );

		return( -1 );
	}
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
	     language_table->entries_array,
	     &number_of_entries,
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
	for( entry_index = 0;
	     entry_index < number_of_entries;
	     entry_index++ )
	{
		if( libcdata_array_get_entry_by_index(
		     language_table->entries_array,
		     entry_index,
		     (intptr_t **) language_entry,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve language entry: %d.",
			 function,
			 entry_index );

			return( -1 );
		}
		if( *language_entry == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: missing language entry: %d.",
			 function,
			 entry_index );

			return( -1 );
		}
		if( ( *language_entry )->language_identifier == language_identifier )
		{
			return( 1 );
		}
	}
	*language_entry = NULL;

	return( 0 );
}

/* Appends a language entry
 * Returns 1 if successful or -1 on error
 */
int libwrc_language_table_append_entry(
     libwrc_language_table_t *language_table,
     int *entry_index,
     libwrc_language_entry_t *language_entry,
     libcerror_error_t **error )
{
	static char *function = "libwrc_language_table_append_entry";

	if( language_table == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid language table.",
		 function );

		return( -1 );
	}
	if( libcdata_array_append_entry(
	     language_table->entries_array,
	     entry_index,
	     (intptr_t *) language_entry,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
		 "%s: unable to append entry.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the number of values for a specific language identifier
 * Returns 1 if successful or -1 on error
 */
int libwrc_language_table_get_number_of_values(
     libwrc_language_table_t *language_table,
     uint32_t language_identifier,
     int *number_of_values,
     libcerror_error_t **error )
{
	libwrc_language_entry_t *language_entry = NULL;
	static char *function                   = "libwrc_language_table_get_number_of_values";

	if( language_table == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid language table.",
		 function );

		return( -1 );
	}
	if( libwrc_language_table_get_entry_by_identifier(
	     language_table,
	     language_identifier,
	     &language_entry,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve language entry for identifier: 0x%08" PRIx32 ".",
		 function,
		 language_identifier );

		return( -1 );
	}
	if( libwrc_language_entry_get_number_of_values(
	     language_entry,
	     number_of_values,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of values.",
		 function );

		return( -1 );
	}
	return( 1 );
}

