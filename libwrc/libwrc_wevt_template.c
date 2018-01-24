/*
 * WEVT_TEMPLATE (resource) functions
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
#include "libwrc_libcerror.h"
#include "libwrc_libfwevt.h"
#include "libwrc_resource.h"
#include "libwrc_types.h"
#include "libwrc_wevt_provider.h"
#include "libwrc_wevt_template.h"
#include "libwrc_wevt_template_values.h"

/* Retrieves the number of providers
 * Returns 1 if successful or -1 on error
 */
int libwrc_wevt_template_get_number_of_providers(
     libwrc_resource_t *resource,
     uint32_t language_identifier,
     int *number_of_providers,
     libcerror_error_t **error )
{
	libfwevt_manifest_t *manifest = NULL;
	static char *function         = "libwrc_wevt_template_get_number_of_providers";

	if( libwrc_resource_get_value_by_language_identifier(
	     resource,
	     LIBWRC_RESOURCE_TYPE_WEVT_TEMPLATE,
	     language_identifier,
	     0,
	     (intptr_t **) &manifest,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve WEVT_TEMPLATE manifest.",
		 function );

		return( -1 );
	}
	if( libfwevt_manifest_get_number_of_providers(
	     manifest,
	     number_of_providers,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of providers.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves a specific provider
 * Returns 1 if successful or -1 on error
 */
int libwrc_wevt_template_get_provider(
     libwrc_resource_t *resource,
     uint32_t language_identifier,
     int provider_index,
     libwrc_wevt_provider_t **provider,
     libcerror_error_t **error )
{
	libfwevt_manifest_t *manifest            = NULL;
	libfwevt_provider_t *provider_descriptor = NULL;
	static char *function                    = "libwrc_wevt_template_get_provider";

	if( libwrc_resource_get_value_by_language_identifier(
	     resource,
	     LIBWRC_RESOURCE_TYPE_WEVT_TEMPLATE,
	     language_identifier,
	     0,
	     (intptr_t **) &manifest,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve WEVT_TEMPLATE manifest.",
		 function );

		return( -1 );
	}
	if( libfwevt_manifest_get_provider(
	     manifest,
	     provider_index,
	     &provider_descriptor,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve provider: %d.",
		 function,
		 provider_index );

		return( -1 );
	}
	if( libwrc_wevt_provider_initialize(
	     provider,
	     provider_descriptor,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create provider.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves a specific provider by identifier (GUID)
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libwrc_wevt_template_get_provider_by_identifier(
     libwrc_resource_t *resource,
     uint32_t language_identifier,
     const uint8_t *provider_identifier,
     size_t provider_identifier_size,
     libwrc_wevt_provider_t **provider,
     libcerror_error_t **error )
{
	libfwevt_manifest_t *manifest            = NULL;
	libfwevt_provider_t *provider_descriptor = NULL;
	static char *function                    = "libwrc_wevt_template_get_provider_by_identifier";
	int result                               = 0;

	if( libwrc_resource_get_value_by_language_identifier(
	     resource,
	     LIBWRC_RESOURCE_TYPE_WEVT_TEMPLATE,
	     language_identifier,
	     0,
	     (intptr_t **) &manifest,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve WEVT_TEMPLATE manifest.",
		 function );

		return( -1 );
	}
	result = libfwevt_manifest_get_provider_by_identifier(
	          manifest,
	          provider_identifier,
	          provider_identifier_size,
	          &provider_descriptor,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve provider.",
		 function );

		return( -1 );
	}
	else if( result != 0 )
	{
		if( libwrc_wevt_provider_initialize(
		     provider,
		     provider_descriptor,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create provider.",
			 function );

			return( -1 );
		}
	}
	return( result );
}

