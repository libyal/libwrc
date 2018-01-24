/*
 * Message table (resource) functions
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
#include <types.h>

#include "libwrc_definitions.h"
#include "libwrc_language_entry.h"
#include "libwrc_language_table.h"
#include "libwrc_libcerror.h"
#include "libwrc_libfvalue.h"
#include "libwrc_message_table.h"
#include "libwrc_resource.h"
#include "libwrc_resource_values.h"

/* Retrieves the number of messages
 * Returns 1 if successful or -1 on error
 */
int libwrc_message_table_get_number_of_messages(
     libwrc_resource_t *resource,
     uint32_t language_identifier,
     int *number_of_messages,
     libcerror_error_t **error )
{
	libwrc_internal_resource_t *internal_resource = NULL;
	static char *function                         = "libwrc_message_table_get_number_of_messages";

	if( resource == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid resource.",
		 function );

		return( -1 );
	}
	internal_resource = (libwrc_internal_resource_t *) resource;

	if( internal_resource->resource_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid resource - missing resource values.",
		 function );

		return( -1 );
	}
	if( internal_resource->resource_values->identifier != LIBWRC_RESOURCE_IDENTIFIER_MESSAGE_TABLE )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported resource type: 0x%08" PRIx32 ".",
		 function,
		 internal_resource->resource_values->identifier );

		return( -1 );
	}
	if( internal_resource->value == NULL )
	{
		if( libwrc_resource_read_value(
		     internal_resource,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read resource value.",
			 function );

			return( -1 );
		}
	}
	if( libwrc_language_table_get_number_of_values(
	     (libwrc_language_table_t *) internal_resource->value,
	     language_identifier,
	     number_of_messages,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of values for language identifier: 0x%08" PRIx32 ".",
		 function,
		 language_identifier );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves a specific message identifier
 * Returns 1 if successful or -1 on error
 */
int libwrc_message_table_get_identifier(
     libwrc_resource_t *resource,
     uint32_t language_identifier,
     int message_index,
     uint32_t *message_identifier,
     libcerror_error_t **error )
{
	libfvalue_value_t *message_table_values    = NULL;
	uint8_t *message_table_value_identifier    = NULL;
	static char *function                      = "libwrc_message_table_get_identifier";
	size_t message_table_value_identifier_size = 0;

	if( libwrc_resource_get_value_by_language_identifier(
	     resource,
	     LIBWRC_RESOURCE_IDENTIFIER_MESSAGE_TABLE,
	     language_identifier,
	     message_index,
	     (intptr_t **) &message_table_values,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve message table values.",
		 function );

		return( -1 );
	}
/* TODO move to message table values function */
	if( message_identifier == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid message identifier.",
		 function );

		return( -1 );
	}
	if( libfvalue_value_get_identifier(
	     message_table_values,
	     &message_table_value_identifier,
	     &message_table_value_identifier_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve message table value: %d identifier.",
		 function,
		 message_index );

		return( -1 );
	}
	if( message_table_value_identifier == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: missing message table value identifier.",
		 function );

		return( -1 );
	}
	if( message_table_value_identifier_size != 4 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: message table value identifier size value out of bound.",
		 function );

		return( -1 );
	}
	byte_stream_copy_to_uint32_little_endian(
	 message_table_value_identifier,
	 *message_identifier );

	return( 1 );
}

/* Retrieves the message index for a specific identifier
 * Returns 1 if successful, 0 if no such message identifier or -1 on error
 */
int libwrc_message_table_get_index_by_identifier(
     libwrc_resource_t *resource,
     uint32_t language_identifier,
     uint32_t message_identifier,
     int *message_index,
     libcerror_error_t **error )
{
	libfvalue_value_t *message_table_value        = NULL;
	libwrc_internal_resource_t *internal_resource = NULL;
	libwrc_language_entry_t *language_entry       = NULL;
	uint8_t *message_table_value_identifier       = NULL;
	static char *function                         = "libwrc_message_table_get_index_by_identifier";
	size_t message_table_value_identifier_size    = 0;
	uint32_t identifier                           = 0;
	int number_of_messages                        = 0;

	if( resource == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid resource.",
		 function );

		return( -1 );
	}
	internal_resource = (libwrc_internal_resource_t *) resource;

	if( internal_resource->resource_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid resource - missing resource values.",
		 function );

		return( -1 );
	}
	if( internal_resource->resource_values->identifier != LIBWRC_RESOURCE_IDENTIFIER_MESSAGE_TABLE )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported resource type: 0x%08" PRIx32 ".",
		 function,
		 internal_resource->resource_values->identifier );

		return( -1 );
	}
	if( internal_resource->value == NULL )
	{
		if( libwrc_resource_read_value(
		     internal_resource,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read resource value.",
			 function );

			return( -1 );
		}
	}
	if( libwrc_language_table_get_entry_by_identifier(
	     (libwrc_language_table_t *) internal_resource->value,
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
	     &number_of_messages,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of messages.",
		 function );

		return( -1 );
	}
	for( *message_index = 0;
	     *message_index < number_of_messages;
	     *message_index += 1 )
	{
		if( libwrc_language_entry_get_value_by_index(
		     language_entry,
		     *message_index,
		     (intptr_t **) &message_table_value,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve message table value: %d.",
			 function,
			 message_index );

			return( -1 );
		}
		if( libfvalue_value_get_identifier(
		     message_table_value,
		     &message_table_value_identifier,
		     &message_table_value_identifier_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve message table value: %d identifier.",
			 function,
			 message_index );

			return( -1 );
		}
		if( message_table_value_identifier == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: missing message table value identifier.",
			 function );

			return( -1 );
		}
		if( message_table_value_identifier_size != 4 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: message table size value out of bound.",
			 function );

			return( -1 );
		}
		byte_stream_copy_to_uint32_little_endian(
		 message_table_value_identifier,
		 identifier );

		if( identifier == message_identifier )
		{
			return( 1 );
		}
	}
	return( 0 );
}

/* Retrieves the size of a specific UTF-8 formatted message string
 * Returns 1 if successful or -1 on error
 */
int libwrc_message_table_get_utf8_string_size(
     libwrc_resource_t *resource,
     uint32_t language_identifier,
     int message_index,
     size_t *utf8_string_size,
     libcerror_error_t **error )
{
	libfvalue_value_t *message_table_values = NULL;
	static char *function                   = "libwrc_message_table_get_utf8_string_size";

	if( libwrc_resource_get_value_by_language_identifier(
	     resource,
	     LIBWRC_RESOURCE_IDENTIFIER_MESSAGE_TABLE,
	     language_identifier,
	     message_index,
	     (intptr_t **) &message_table_values,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve message table values.",
		 function );

		return( -1 );
	}
	if( libfvalue_value_get_utf8_string_size(
	     message_table_values,
	     0,
	     utf8_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve UTF-8 string size of message table value: %d.",
		 function,
		 message_index );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves a specific UTF-8 formatted message string
 * Returns 1 if successful or -1 on error
 */
int libwrc_message_table_get_utf8_string(
     libwrc_resource_t *resource,
     uint32_t language_identifier,
     int message_index,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error )
{
	libfvalue_value_t *message_table_values = NULL;
	static char *function                   = "libwrc_message_table_get_utf8_string";

	if( libwrc_resource_get_value_by_language_identifier(
	     resource,
	     LIBWRC_RESOURCE_IDENTIFIER_MESSAGE_TABLE,
	     language_identifier,
	     message_index,
	     (intptr_t **) &message_table_values,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve message table values.",
		 function );

		return( -1 );
	}
	if( libfvalue_value_copy_to_utf8_string(
	     message_table_values,
	     0,
	     utf8_string,
	     utf8_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy message table value: %d to UTF-8 string.",
		 function,
		 message_index );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the size of a specific UTF-16 formatted message string
 * Returns 1 if successful or -1 on error
 */
int libwrc_message_table_get_utf16_string_size(
     libwrc_resource_t *resource,
     uint32_t language_identifier,
     int message_index,
     size_t *utf16_string_size,
     libcerror_error_t **error )
{
	libfvalue_value_t *message_table_values = NULL;
	static char *function                   = "libwrc_message_table_get_utf16_string_size";

	if( libwrc_resource_get_value_by_language_identifier(
	     resource,
	     LIBWRC_RESOURCE_IDENTIFIER_MESSAGE_TABLE,
	     language_identifier,
	     message_index,
	     (intptr_t **) &message_table_values,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve message table values.",
		 function );

		return( -1 );
	}
	if( libfvalue_value_get_utf16_string_size(
	     message_table_values,
	     0,
	     utf16_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve UTF-16 string size of message table value: %d.",
		 function,
		 message_index );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves a specific UTF-16 formatted message string
 * Returns 1 if successful or -1 on error
 */
int libwrc_message_table_get_utf16_string(
     libwrc_resource_t *resource,
     uint32_t language_identifier,
     int message_index,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error )
{
	libfvalue_value_t *message_table_values = NULL;
	static char *function                   = "libwrc_message_table_get_utf16_string";

	if( libwrc_resource_get_value_by_language_identifier(
	     resource,
	     LIBWRC_RESOURCE_IDENTIFIER_MESSAGE_TABLE,
	     language_identifier,
	     message_index,
	     (intptr_t **) &message_table_values,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve message table values.",
		 function );

		return( -1 );
	}
	if( libfvalue_value_copy_to_utf16_string(
	     message_table_values,
	     0,
	     utf16_string,
	     utf16_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy message table value: %d to UTF-16 string.",
		 function,
		 message_index );

		return( -1 );
	}
	return( 1 );
}

