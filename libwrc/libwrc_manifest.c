/*
 * Manifest (resource) functions
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
#include <byte_stream.h>
#include <memory.h>
#include <types.h>

#include "libwrc_definitions.h"
#include "libwrc_language_entry.h"
#include "libwrc_language_table.h"
#include "libwrc_libcerror.h"
#include "libwrc_libfvalue.h"
#include "libwrc_manifest.h"
#include "libwrc_resource.h"
#include "libwrc_resource_values.h"

/* Retrieves the size of a specific UTF-8 formatted string
 * Returns 1 if successful or -1 on error
 */
int libwrc_manifest_get_utf8_string_size(
     libwrc_resource_t *resource,
     uint32_t language_identifier,
     size_t *utf8_string_size,
     libcerror_error_t **error )
{
	libfvalue_value_t *manifest_values = NULL;
	static char *function              = "libwrc_manifest_get_utf8_string_size";

	if( libwrc_resource_get_value_by_language_identifier(
	     resource,
	     LIBWRC_RESOURCE_TYPE_MANIFEST,
	     language_identifier,
	     0,
	     (intptr_t **) &manifest_values,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve manifest values.",
		 function );

		return( -1 );
	}
	if( libfvalue_value_get_utf8_string_size(
	     manifest_values,
	     0,
	     utf8_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve UTF-8 string size of manifest value.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves a specific UTF-8 formatted string
 * Returns 1 if successful or -1 on error
 */
int libwrc_manifest_get_utf8_string(
     libwrc_resource_t *resource,
     uint32_t language_identifier,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error )
{
	libfvalue_value_t *manifest_values = NULL;
	static char *function              = "libwrc_manifest_get_utf8_string";

	if( libwrc_resource_get_value_by_language_identifier(
	     resource,
	     LIBWRC_RESOURCE_TYPE_MANIFEST,
	     language_identifier,
	     0,
	     (intptr_t **) &manifest_values,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve manifest values.",
		 function );

		return( -1 );
	}
	if( libfvalue_value_copy_to_utf8_string(
	     manifest_values,
	     0,
	     utf8_string,
	     utf8_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy manifest value to UTF-8 string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the size of a specific UTF-16 formatted string
 * Returns 1 if successful or -1 on error
 */
int libwrc_manifest_get_utf16_string_size(
     libwrc_resource_t *resource,
     uint32_t language_identifier,
     size_t *utf16_string_size,
     libcerror_error_t **error )
{
	libfvalue_value_t *manifest_values = NULL;
	static char *function              = "libwrc_manifest_get_utf16_string_size";

	if( libwrc_resource_get_value_by_language_identifier(
	     resource,
	     LIBWRC_RESOURCE_TYPE_MANIFEST,
	     language_identifier,
	     0,
	     (intptr_t **) &manifest_values,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve manifest values.",
		 function );

		return( -1 );
	}
	if( libfvalue_value_get_utf16_string_size(
	     manifest_values,
	     0,
	     utf16_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve UTF-16 string size of manifest value.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves a specific UTF-16 formatted string
 * Returns 1 if successful or -1 on error
 */
int libwrc_manifest_get_utf16_string(
     libwrc_resource_t *resource,
     uint32_t language_identifier,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error )
{
	libfvalue_value_t *manifest_values = NULL;
	static char *function              = "libwrc_manifest_get_utf16_string";

	if( libwrc_resource_get_value_by_language_identifier(
	     resource,
	     LIBWRC_RESOURCE_TYPE_MANIFEST,
	     language_identifier,
	     0,
	     (intptr_t **) &manifest_values,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve manifest values.",
		 function );

		return( -1 );
	}
	if( libfvalue_value_copy_to_utf16_string(
	     manifest_values,
	     0,
	     utf16_string,
	     utf16_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy manifest value to UTF-16 string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

