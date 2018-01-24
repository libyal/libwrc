/*
 * MUI (resource) functions
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
#include "libwrc_libuna.h"
#include "libwrc_mui.h"
#include "libwrc_mui_values.h"
#include "libwrc_resource.h"

/* Retrieves the file type
 * Returns 1 if successful or -1 on error
 */
int libwrc_mui_get_file_type(
     libwrc_resource_t *resource,
     uint32_t language_identifier,
     uint32_t *file_type,
     libcerror_error_t **error )
{
	libwrc_mui_values_t *mui_values = NULL;
	static char *function           = "libwrc_mui_get_file_type";

	if( libwrc_resource_get_value_by_language_identifier(
	     resource,
	     LIBWRC_RESOURCE_TYPE_MUI,
	     language_identifier,
	     0,
	     (intptr_t **) &mui_values,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve MUI values.",
		 function );

		return( -1 );
	}
	if( libwrc_mui_values_get_file_type(
	     mui_values,
	     file_type,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve file type.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the size of the UTF-8 formatted main name
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libwrc_mui_get_utf8_main_name_size(
     libwrc_resource_t *resource,
     uint32_t language_identifier,
     size_t *utf8_string_size,
     libcerror_error_t **error )
{
	libwrc_mui_values_t *mui_values = NULL;
	static char *function           = "libwrc_mui_get_utf8_main_name_size";

	if( libwrc_resource_get_value_by_language_identifier(
	     resource,
	     LIBWRC_RESOURCE_TYPE_MUI,
	     language_identifier,
	     0,
	     (intptr_t **) &mui_values,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve MUI values.",
		 function );

		return( -1 );
	}
/* TODO move to mui values function */
	if( mui_values->main_name_size == 0 )
	{
		return( 0 );
	}
	if( libuna_utf8_string_size_from_utf16_stream(
	     mui_values->main_name,
	     mui_values->main_name_size,
	     LIBUNA_ENDIAN_LITTLE,
	     utf8_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to determine size of main name string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the UTF-8 formatted main name
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libwrc_mui_get_utf8_main_name(
     libwrc_resource_t *resource,
     uint32_t language_identifier,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error )
{
	libwrc_mui_values_t *mui_values = NULL;
	static char *function           = "libwrc_mui_get_utf8_main_name";

	if( libwrc_resource_get_value_by_language_identifier(
	     resource,
	     LIBWRC_RESOURCE_TYPE_MUI,
	     language_identifier,
	     0,
	     (intptr_t **) &mui_values,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve MUI values.",
		 function );

		return( -1 );
	}
/* TODO move to mui values function */
	if( mui_values->main_name_size == 0 )
	{
		return( 0 );
	}
	if( libuna_utf8_string_copy_from_utf16_stream(
	     utf8_string,
	     utf8_string_size,
	     mui_values->main_name,
	     mui_values->main_name_size,
	     LIBUNA_ENDIAN_LITTLE,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set main name string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the size of the UTF-16 formatted main name
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libwrc_mui_get_utf16_main_name_size(
     libwrc_resource_t *resource,
     uint32_t language_identifier,
     size_t *utf16_string_size,
     libcerror_error_t **error )
{
	libwrc_mui_values_t *mui_values = NULL;
	static char *function           = "libwrc_mui_get_utf16_main_name_size";

	if( libwrc_resource_get_value_by_language_identifier(
	     resource,
	     LIBWRC_RESOURCE_TYPE_MUI,
	     language_identifier,
	     0,
	     (intptr_t **) &mui_values,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve MUI values.",
		 function );

		return( -1 );
	}
/* TODO move to mui values function */
	if( mui_values->main_name_size == 0 )
	{
		return( 0 );
	}
	if( libuna_utf16_string_size_from_utf16_stream(
	     mui_values->main_name,
	     mui_values->main_name_size,
	     LIBUNA_ENDIAN_LITTLE,
	     utf16_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to determine size of main name string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the UTF-16 formatted main name
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libwrc_mui_get_utf16_main_name(
     libwrc_resource_t *resource,
     uint32_t language_identifier,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error )
{
	libwrc_mui_values_t *mui_values = NULL;
	static char *function           = "libwrc_mui_get_utf16_main_name";

	if( libwrc_resource_get_value_by_language_identifier(
	     resource,
	     LIBWRC_RESOURCE_TYPE_MUI,
	     language_identifier,
	     0,
	     (intptr_t **) &mui_values,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve MUI values.",
		 function );

		return( -1 );
	}
/* TODO move to mui values function */
	if( mui_values->main_name_size == 0 )
	{
		return( 0 );
	}
	if( libuna_utf16_string_copy_from_utf16_stream(
	     utf16_string,
	     utf16_string_size,
	     mui_values->main_name,
	     mui_values->main_name_size,
	     LIBUNA_ENDIAN_LITTLE,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set main name string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the size of the UTF-8 formatted MUI name
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libwrc_mui_get_utf8_mui_name_size(
     libwrc_resource_t *resource,
     uint32_t language_identifier,
     size_t *utf8_string_size,
     libcerror_error_t **error )
{
	libwrc_mui_values_t *mui_values = NULL;
	static char *function           = "libwrc_mui_get_utf8_mui_name_size";

	if( libwrc_resource_get_value_by_language_identifier(
	     resource,
	     LIBWRC_RESOURCE_TYPE_MUI,
	     language_identifier,
	     0,
	     (intptr_t **) &mui_values,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve MUI values.",
		 function );

		return( -1 );
	}
/* TODO move to mui values function */
	if( mui_values->mui_name_size == 0 )
	{
		return( 0 );
	}
	if( libuna_utf8_string_size_from_utf16_stream(
	     mui_values->mui_name,
	     mui_values->mui_name_size,
	     LIBUNA_ENDIAN_LITTLE,
	     utf8_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to determine size of MUI name string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the UTF-8 formatted MUI name
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libwrc_mui_get_utf8_mui_name(
     libwrc_resource_t *resource,
     uint32_t language_identifier,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error )
{
	libwrc_mui_values_t *mui_values = NULL;
	static char *function           = "libwrc_mui_get_utf8_mui_name";

	if( libwrc_resource_get_value_by_language_identifier(
	     resource,
	     LIBWRC_RESOURCE_TYPE_MUI,
	     language_identifier,
	     0,
	     (intptr_t **) &mui_values,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve MUI values.",
		 function );

		return( -1 );
	}
/* TODO move to mui values function */
	if( mui_values->mui_name_size == 0 )
	{
		return( 0 );
	}
	if( libuna_utf8_string_copy_from_utf16_stream(
	     utf8_string,
	     utf8_string_size,
	     mui_values->mui_name,
	     mui_values->mui_name_size,
	     LIBUNA_ENDIAN_LITTLE,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set MUI name string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the size of the UTF-16 formatted MUI name
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libwrc_mui_get_utf16_mui_name_size(
     libwrc_resource_t *resource,
     uint32_t language_identifier,
     size_t *utf16_string_size,
     libcerror_error_t **error )
{
	libwrc_mui_values_t *mui_values = NULL;
	static char *function           = "libwrc_mui_get_utf16_mui_name_size";

	if( libwrc_resource_get_value_by_language_identifier(
	     resource,
	     LIBWRC_RESOURCE_TYPE_MUI,
	     language_identifier,
	     0,
	     (intptr_t **) &mui_values,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve MUI values.",
		 function );

		return( -1 );
	}
/* TODO move to mui values function */
	if( mui_values->mui_name_size == 0 )
	{
		return( 0 );
	}
	if( libuna_utf16_string_size_from_utf16_stream(
	     mui_values->mui_name,
	     mui_values->mui_name_size,
	     LIBUNA_ENDIAN_LITTLE,
	     utf16_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to determine size of MUI name string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the UTF-16 formatted MUI name
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libwrc_mui_get_utf16_mui_name(
     libwrc_resource_t *resource,
     uint32_t language_identifier,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error )
{
	libwrc_mui_values_t *mui_values = NULL;
	static char *function           = "libwrc_mui_get_utf16_mui_name";

	if( libwrc_resource_get_value_by_language_identifier(
	     resource,
	     LIBWRC_RESOURCE_TYPE_MUI,
	     language_identifier,
	     0,
	     (intptr_t **) &mui_values,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve MUI values.",
		 function );

		return( -1 );
	}
/* TODO move to mui values function */
	if( mui_values->mui_name_size == 0 )
	{
		return( 0 );
	}
	if( libuna_utf16_string_copy_from_utf16_stream(
	     utf16_string,
	     utf16_string_size,
	     mui_values->mui_name,
	     mui_values->mui_name_size,
	     LIBUNA_ENDIAN_LITTLE,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set MUI name string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the size of the UTF-8 formatted language
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libwrc_mui_get_utf8_language_size(
     libwrc_resource_t *resource,
     uint32_t language_identifier,
     size_t *utf8_string_size,
     libcerror_error_t **error )
{
	libwrc_mui_values_t *mui_values = NULL;
	static char *function           = "libwrc_mui_get_utf8_language_size";

	if( libwrc_resource_get_value_by_language_identifier(
	     resource,
	     LIBWRC_RESOURCE_TYPE_MUI,
	     language_identifier,
	     0,
	     (intptr_t **) &mui_values,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve MUI values.",
		 function );

		return( -1 );
	}
/* TODO move to mui values function */
	if( mui_values->language_size == 0 )
	{
		return( 0 );
	}
	if( libuna_utf8_string_size_from_utf16_stream(
	     mui_values->language,
	     mui_values->language_size,
	     LIBUNA_ENDIAN_LITTLE,
	     utf8_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to determine size of language string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the UTF-8 formatted language
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libwrc_mui_get_utf8_language(
     libwrc_resource_t *resource,
     uint32_t language_identifier,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error )
{
	libwrc_mui_values_t *mui_values = NULL;
	static char *function           = "libwrc_mui_get_utf8_language";

	if( libwrc_resource_get_value_by_language_identifier(
	     resource,
	     LIBWRC_RESOURCE_TYPE_MUI,
	     language_identifier,
	     0,
	     (intptr_t **) &mui_values,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve MUI values.",
		 function );

		return( -1 );
	}
/* TODO move to mui values function */
	if( mui_values->language_size == 0 )
	{
		return( 0 );
	}
	if( libuna_utf8_string_copy_from_utf16_stream(
	     utf8_string,
	     utf8_string_size,
	     mui_values->language,
	     mui_values->language_size,
	     LIBUNA_ENDIAN_LITTLE,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set language string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the size of the UTF-16 formatted language
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libwrc_mui_get_utf16_language_size(
     libwrc_resource_t *resource,
     uint32_t language_identifier,
     size_t *utf16_string_size,
     libcerror_error_t **error )
{
	libwrc_mui_values_t *mui_values = NULL;
	static char *function           = "libwrc_mui_get_utf16_language_size";

	if( libwrc_resource_get_value_by_language_identifier(
	     resource,
	     LIBWRC_RESOURCE_TYPE_MUI,
	     language_identifier,
	     0,
	     (intptr_t **) &mui_values,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve MUI values.",
		 function );

		return( -1 );
	}
/* TODO move to mui values function */
	if( mui_values->language_size == 0 )
	{
		return( 0 );
	}
	if( libuna_utf16_string_size_from_utf16_stream(
	     mui_values->language,
	     mui_values->language_size,
	     LIBUNA_ENDIAN_LITTLE,
	     utf16_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to determine size of language string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the UTF-16 formatted language
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libwrc_mui_get_utf16_language(
     libwrc_resource_t *resource,
     uint32_t language_identifier,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error )
{
	libwrc_mui_values_t *mui_values = NULL;
	static char *function           = "libwrc_mui_get_utf16_language";

	if( libwrc_resource_get_value_by_language_identifier(
	     resource,
	     LIBWRC_RESOURCE_TYPE_MUI,
	     language_identifier,
	     0,
	     (intptr_t **) &mui_values,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve MUI values.",
		 function );

		return( -1 );
	}
/* TODO move to mui values function */
	if( mui_values->language_size == 0 )
	{
		return( 0 );
	}
	if( libuna_utf16_string_copy_from_utf16_stream(
	     utf16_string,
	     utf16_string_size,
	     mui_values->language,
	     mui_values->language_size,
	     LIBUNA_ENDIAN_LITTLE,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set language string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the size of the UTF-8 formatted language
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libwrc_mui_get_utf8_fallback_language_size(
     libwrc_resource_t *resource,
     uint32_t language_identifier,
     size_t *utf8_string_size,
     libcerror_error_t **error )
{
	libwrc_mui_values_t *mui_values = NULL;
	static char *function           = "libwrc_mui_get_utf8_fallback_language_size";

	if( libwrc_resource_get_value_by_language_identifier(
	     resource,
	     LIBWRC_RESOURCE_TYPE_MUI,
	     language_identifier,
	     0,
	     (intptr_t **) &mui_values,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve MUI values.",
		 function );

		return( -1 );
	}
/* TODO move to mui values function */
	if( mui_values->fallback_language_size == 0 )
	{
		return( 0 );
	}
	if( libuna_utf8_string_size_from_utf16_stream(
	     mui_values->fallback_language,
	     mui_values->fallback_language_size,
	     LIBUNA_ENDIAN_LITTLE,
	     utf8_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to determine size of fallback language string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the UTF-8 formatted fallback language
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libwrc_mui_get_utf8_fallback_language(
     libwrc_resource_t *resource,
     uint32_t language_identifier,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error )
{
	libwrc_mui_values_t *mui_values = NULL;
	static char *function           = "libwrc_mui_get_utf8_fallback_language";

	if( libwrc_resource_get_value_by_language_identifier(
	     resource,
	     LIBWRC_RESOURCE_TYPE_MUI,
	     language_identifier,
	     0,
	     (intptr_t **) &mui_values,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve MUI values.",
		 function );

		return( -1 );
	}
/* TODO move to mui values function */
	if( mui_values->fallback_language_size == 0 )
	{
		return( 0 );
	}
	if( libuna_utf8_string_copy_from_utf16_stream(
	     utf8_string,
	     utf8_string_size,
	     mui_values->fallback_language,
	     mui_values->fallback_language_size,
	     LIBUNA_ENDIAN_LITTLE,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set fallback language string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the size of the UTF-16 formatted fallback language
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libwrc_mui_get_utf16_fallback_language_size(
     libwrc_resource_t *resource,
     uint32_t language_identifier,
     size_t *utf16_string_size,
     libcerror_error_t **error )
{
	libwrc_mui_values_t *mui_values = NULL;
	static char *function           = "libwrc_mui_get_utf16_fallback_language_size";

	if( libwrc_resource_get_value_by_language_identifier(
	     resource,
	     LIBWRC_RESOURCE_TYPE_MUI,
	     language_identifier,
	     0,
	     (intptr_t **) &mui_values,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve MUI values.",
		 function );

		return( -1 );
	}
/* TODO move to mui values function */
	if( mui_values->fallback_language_size == 0 )
	{
		return( 0 );
	}
	if( libuna_utf16_string_size_from_utf16_stream(
	     mui_values->fallback_language,
	     mui_values->fallback_language_size,
	     LIBUNA_ENDIAN_LITTLE,
	     utf16_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to determine size of fallback language string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the UTF-16 formatted fallback language
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libwrc_mui_get_utf16_fallback_language(
     libwrc_resource_t *resource,
     uint32_t language_identifier,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error )
{
	libwrc_mui_values_t *mui_values = NULL;
	static char *function           = "libwrc_mui_get_utf16_fallback_language";

	if( libwrc_resource_get_value_by_language_identifier(
	     resource,
	     LIBWRC_RESOURCE_TYPE_MUI,
	     language_identifier,
	     0,
	     (intptr_t **) &mui_values,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve MUI values.",
		 function );

		return( -1 );
	}
/* TODO move to mui values function */
	if( mui_values->fallback_language_size == 0 )
	{
		return( 0 );
	}
	if( libuna_utf16_string_copy_from_utf16_stream(
	     utf16_string,
	     utf16_string_size,
	     mui_values->fallback_language,
	     mui_values->fallback_language_size,
	     LIBUNA_ENDIAN_LITTLE,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set fallback language string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

