/*
 * Resource values functions
 *
 * Copyright (C) 2011-2018, Joachim Metz <joachim.metz@gmail.com>
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
#include <memory.h>
#include <types.h>

#include "libwrc_data_descriptor.h"
#include "libwrc_libcdata.h"
#include "libwrc_libcerror.h"
#include "libwrc_resource_values.h"

/* Creates resource values
 * Make sure the value resource_values is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libwrc_resource_values_initialize(
     libwrc_resource_values_t **resource_values,
     libcerror_error_t **error )
{
	static char *function = "libwrc_resource_values_initialize";

	if( resource_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid resource values.",
		 function );

		return( -1 );
	}
	if( *resource_values != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid resource values value already set.",
		 function );

		return( -1 );
	}
	*resource_values = memory_allocate_structure(
	                    libwrc_resource_values_t );

	if( *resource_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create resource values.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *resource_values,
	     0,
	     sizeof( libwrc_resource_values_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear resource values.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *resource_values != NULL )
	{
		memory_free(
		 *resource_values );

		*resource_values = NULL;
	}
	return( -1 );
}

/* Frees resource values
 * Returns 1 if successful or -1 on error
 */
int libwrc_resource_values_free(
     libwrc_resource_values_t **resource_values,
     libcerror_error_t **error )
{
	static char *function = "libwrc_resource_values_free";
	int result            = 1;

	if( resource_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid resource values.",
		 function );

		return( -1 );
	}
	if( *resource_values != NULL )
	{
		if( libwrc_data_descriptor_free(
		     &( ( *resource_values )->data_descriptor ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free data descriptor.",
			 function );

			result = -1;
		}
		if( ( *resource_values )->name_string != NULL )
		{
			memory_free(
			 ( *resource_values )->name_string );
		}
		memory_free(
		 *resource_values );

		*resource_values = NULL;
	}
	return( result );
}

/* Compares two resource values
 * Returns LIBCDATA_COMPARE_LESS, LIBCDATA_COMPARE_EQUAL, LIBCDATA_COMPARE_GREATER if successful or -1 on error
 */
int libwrc_resource_values_compare(
     libwrc_resource_values_t *first_resource_values,
     libwrc_resource_values_t *second_resource_values,
     libcerror_error_t **error )
{
	static char *function = "libwrc_resource_values_compare";

	if( first_resource_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid first resource values.",
		 function );

		return( -1 );
	}
	if( second_resource_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid second resource values.",
		 function );

		return( -1 );
	}
	if( first_resource_values->identifier < second_resource_values->identifier )
	{
		return( LIBCDATA_COMPARE_LESS );
	}
	else if( first_resource_values->identifier > second_resource_values->identifier )
	{
		return( LIBCDATA_COMPARE_GREATER );
	}
	return( LIBCDATA_COMPARE_EQUAL );
}

/* Retrieves the identifier
 * Returns 1 if successful or -1 on error
 */
int libwrc_resource_values_get_identifier(
     libwrc_resource_values_t *resource_values,
     uint32_t *identifier,
     libcerror_error_t **error )
{
	static char *function = "libwrc_resource_values_get_identifier";

	if( resource_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid resource values.",
		 function );

		return( -1 );
	}
	if( identifier == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid identifier.",
		 function );

		return( -1 );
	}
	*identifier = resource_values->identifier;

	return( 1 );
}

/* Retrieves the type
 * Returns 1 if successful or -1 on error
 */
int libwrc_resource_values_get_type(
     libwrc_resource_values_t *resource_values,
     int *type,
     libcerror_error_t **error )
{
	static char *function = "libwrc_resource_values_get_type";

	if( resource_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid resource values.",
		 function );

		return( -1 );
	}
	if( type == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid type.",
		 function );

		return( -1 );
	}
	*type = resource_values->type;

	return( 1 );
}

