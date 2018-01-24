/*
 * Version (resource) functions
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

#include "libwrc_definitions.h"
#include "libwrc_language_entry.h"
#include "libwrc_language_table.h"
#include "libwrc_libcerror.h"
#include "libwrc_libfvalue.h"
#include "libwrc_libuna.h"
#include "libwrc_resource.h"
#include "libwrc_resource_values.h"
#include "libwrc_version.h"
#include "libwrc_version_values.h"

/* Retrieves the file version
 * Returns 1 if successful or -1 on error
 */
int libwrc_version_get_file_version(
     libwrc_resource_t *resource,
     uint32_t language_identifier,
     uint64_t *version,
     libcerror_error_t **error )
{
	libwrc_version_values_t *version_values = NULL;
	static char *function                   = "libwrc_version_get_file_version";

	if( libwrc_resource_get_value_by_language_identifier(
	     resource,
	     LIBWRC_RESOURCE_TYPE_VERSION,
	     language_identifier,
	     0,
	     (intptr_t **) &version_values,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve version values.",
		 function );

		return( -1 );
	}
	if( libwrc_version_values_get_file_version(
	     version_values,
	     version,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve file version.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the product version
 * Returns 1 if successful or -1 on error
 */
int libwrc_version_get_product_version(
     libwrc_resource_t *resource,
     uint32_t language_identifier,
     uint64_t *version,
     libcerror_error_t **error )
{
	libwrc_version_values_t *version_values = NULL;
	static char *function                   = "libwrc_version_get_product_version";

	if( libwrc_resource_get_value_by_language_identifier(
	     resource,
	     LIBWRC_RESOURCE_TYPE_VERSION,
	     language_identifier,
	     0,
	     (intptr_t **) &version_values,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve version values.",
		 function );

		return( -1 );
	}
	if( libwrc_version_values_get_product_version(
	     version_values,
	     version,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve product version.",
		 function );

		return( -1 );
	}
	return( 1 );
}

