/*
 * MUI resource functions
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
#include <byte_stream.h>
#include <memory.h>
#include <narrow_string.h>
#include <system_string.h>
#include <types.h>
#include <wide_string.h>

#include "libwrc_debug.h"
#include "libwrc_definitions.h"
#include "libwrc_libcerror.h"
#include "libwrc_libcnotify.h"
#include "libwrc_libuna.h"
#include "libwrc_mui_resource.h"

#include "wrc_mui_resource.h"

uint8_t libwrc_mui_resource_signature[ 4 ] = { 0xcd, 0xfe, 0xcd, 0xfe };

/* Creates a MUI resource
 * Make sure the value mui_resource is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libwrc_mui_resource_initialize(
     libwrc_mui_resource_t **mui_resource,
     libcerror_error_t **error )
{
	libwrc_internal_mui_resource_t *internal_mui_resource = NULL;
	static char *function                                 = "libwrc_mui_resource_initialize";

	if( mui_resource == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid MUI resource.",
		 function );

		return( -1 );
	}
	if( *mui_resource != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid MUI resource value already set.",
		 function );

		return( -1 );
	}
	internal_mui_resource = memory_allocate_structure(
	                         libwrc_internal_mui_resource_t );

	if( internal_mui_resource == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create MUI resource.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     internal_mui_resource,
	     0,
	     sizeof( libwrc_internal_mui_resource_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear MUI resource.",
		 function );

		goto on_error;
	}
	*mui_resource = (libwrc_mui_resource_t *) internal_mui_resource;

	return( 1 );

on_error:
	if( internal_mui_resource != NULL )
	{
		memory_free(
		 internal_mui_resource );
	}
	return( -1 );
}

/* Frees a MUI resource
 * Returns 1 if successful or -1 on error
 */
int libwrc_mui_resource_free(
     libwrc_mui_resource_t **mui_resource,
     libcerror_error_t **error )
{
	libwrc_internal_mui_resource_t *internal_mui_resource = NULL;
	static char *function                                 = "libwrc_mui_resource_free";

	if( mui_resource == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid MUI resource.",
		 function );

		return( -1 );
	}
	if( *mui_resource != NULL )
	{
		internal_mui_resource = (libwrc_internal_mui_resource_t *) *mui_resource;
		*mui_resource         = NULL;

		if( internal_mui_resource->main_name != NULL )
		{
			memory_free(
			 internal_mui_resource->main_name );
		}
		if( internal_mui_resource->mui_name != NULL )
		{
			memory_free(
			 internal_mui_resource->mui_name );
		}
		if( internal_mui_resource->language != NULL )
		{
			memory_free(
			 internal_mui_resource->language );
		}
		if( internal_mui_resource->fallback_language != NULL )
		{
			memory_free(
			 internal_mui_resource->fallback_language );
		}
		memory_free(
		 internal_mui_resource );
	}
	return( 1 );
}

/* Reads the MUI resource
 * Returns 1 if successful or -1 on error
 */
int libwrc_mui_resource_read(
     libwrc_mui_resource_t *mui_resource,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error )
{
	libwrc_internal_mui_resource_t *internal_mui_resource = NULL;
	static char *function                                 = "libwrc_mui_resource_read";
	size_t data_offset                                    = 0;
	uint32_t mui_resource_data_size                       = 0;
	uint32_t value_data_offset                            = 0;
	uint32_t value_data_size                              = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	system_character_t *value_string                      = NULL;
	size_t value_string_size                              = 0;
	uint32_t value_32bit                                  = 0;
	int result                                            = 0;
#endif

	if( mui_resource == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid MUI resource.",
		 function );

		return( -1 );
	}
	internal_mui_resource = (libwrc_internal_mui_resource_t *) mui_resource;

	if( internal_mui_resource->main_name != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid MUI resource - main name value already set.",
		 function );

		return( -1 );
	}
	if( internal_mui_resource->mui_name != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid MUI resource - MUI name value already set.",
		 function );

		return( -1 );
	}
	if( internal_mui_resource->language != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid MUI resource - language value already set.",
		 function );

		return( -1 );
	}
	if( internal_mui_resource->fallback_language != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid MUI resource - fallback language value already set.",
		 function );

		return( -1 );
	}
	if( data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data.",
		 function );

		return( -1 );
	}
	if( ( data_size < sizeof( wrc_mui_header_t ) )
	 || ( data_size > (size_t) SSIZE_MAX ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid data size value out of bounds.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: data:\n",
		 function );
		libcnotify_print_data(
		 data,
		 data_size,
		 0 );
	}
#endif
	if( memory_compare(
	     ( (wrc_mui_header_t *) data )->signature,
	     libwrc_mui_resource_signature,
	     4 ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported signature.",
		 function );

		goto on_error;
	}
	byte_stream_copy_to_uint32_little_endian(
	 ( (wrc_mui_header_t *) data )->size,
	 mui_resource_data_size );

	byte_stream_copy_to_uint32_little_endian(
	 ( (wrc_mui_header_t *) data )->file_type,
	 internal_mui_resource->file_type );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		byte_stream_copy_to_uint32_little_endian(
		 ( (wrc_mui_header_t *) data )->signature,
		 value_32bit );
		libcnotify_printf(
		 "%s: signature\t\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		libcnotify_printf(
		 "%s: size\t\t\t\t\t\t: %" PRIu32 "\n",
		 function,
		 mui_resource_data_size );

		byte_stream_copy_to_uint32_little_endian(
		 ( (wrc_mui_header_t *) data )->version,
		 value_32bit );
		libcnotify_printf(
		 "%s: version\t\t\t\t\t: %" PRIu32 ".%" PRIu32 "\n",
		 function,
		 value_32bit >> 16,
		 value_32bit & 0x0000ffffUL );

		byte_stream_copy_to_uint32_little_endian(
		 ( (wrc_mui_header_t *) data )->unknown1,
		 value_32bit );
		libcnotify_printf(
		 "%s: unknown1\t\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		libcnotify_printf(
		 "%s: file type\t\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 internal_mui_resource->file_type );

		byte_stream_copy_to_uint32_little_endian(
		 ( (wrc_mui_header_t *) data )->system_attributes,
		 value_32bit );
		libcnotify_printf(
		 "%s: system attributes\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 ( (wrc_mui_header_t *) data )->ultimate_fallback_location,
		 value_32bit );
		libcnotify_printf(
		 "%s: ultimate fallback location\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		libcnotify_printf(
		 "%s: service checksum:\n",
		 function );
		libcnotify_print_data(
		 ( (wrc_mui_header_t *) data )->service_checksum,
		 16,
		 0 );

		libcnotify_printf(
		 "%s: checksum:\n",
		 function );
		libcnotify_print_data(
		 ( (wrc_mui_header_t *) data )->checksum,
		 16,
		 0 );

		libcnotify_printf(
		 "%s: unknown2:\n",
		 function );
		libcnotify_print_data(
		 ( (wrc_mui_header_t *) data )->unknown2,
		 24,
		 0 );
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	if( (size_t) mui_resource_data_size > data_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid MUI resource data size value out of bounds.",
		 function );

		goto on_error;
	}
	data_offset = sizeof( wrc_mui_header_t );

	if( data_offset > ( data_size - 8 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: invalid data size value too small.",
		 function );

		goto on_error;
	}
	byte_stream_copy_to_uint32_little_endian(
	 &( data[ data_offset ] ),
	 value_data_offset );

	byte_stream_copy_to_uint32_little_endian(
	 &( data[ data_offset + 4 ] ),
	 value_data_size );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: main name type data offset\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_data_offset );

		libcnotify_printf(
		 "%s: main name type data size\t\t\t: %" PRIu32 "\n",
		 function,
		 value_data_size );
	}
#endif
	data_offset += 8;

	if( value_data_size > 0 )
	{
		if( ( (size_t) value_data_offset < 0x84 )
		 || ( (size_t) value_data_offset >= data_size ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid value data offset value out of bounds.",
			 function );

			goto on_error;
		}
		if( ( value_data_size == 0 )
		 || ( value_data_size > (size_t) MEMORY_MAXIMUM_ALLOCATION_SIZE )
		 || ( value_data_size > ( data_size - value_data_offset ) ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid value data size value out of bounds.",
			 function );

			goto on_error;
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: main name type data:\n",
			 function );
			libcnotify_print_data(
			 &( data[ value_data_offset ] ),
			 value_data_size,
			 0 );
		}
#endif
		internal_mui_resource->main_name = (uint8_t *) memory_allocate(
		                                                sizeof( uint8_t ) * value_data_size );

		if( internal_mui_resource->main_name == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create main name.",
			 function );

			goto on_error;
		}
		if( memory_copy(
		     internal_mui_resource->main_name,
		     &( data[ value_data_offset ] ),
		     value_data_size ) == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
			 "%s: unable to copy main name.",
			 function );

			goto on_error;
		}
		internal_mui_resource->main_name_size = value_data_size;

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
			result = libuna_utf16_string_size_from_utf16_stream(
				  internal_mui_resource->main_name,
				  internal_mui_resource->main_name_size,
				  LIBUNA_ENDIAN_LITTLE,
				  &value_string_size,
				  error );
#else
			result = libuna_utf8_string_size_from_utf16_stream(
				  internal_mui_resource->main_name,
				  internal_mui_resource->main_name_size,
				  LIBUNA_ENDIAN_LITTLE,
				  &value_string_size,
				  error );
#endif
			if( result != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to determine size of main name string.",
				 function );

				goto on_error;
			}
			if( value_string_size > ( (size_t) MEMORY_MAXIMUM_ALLOCATION_SIZE / sizeof( system_character_t ) ) )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
				 "%s: invalid main name string size value exceeds maximum.",
				 function );

				goto on_error;
			}
			value_string = system_string_allocate(
					value_string_size );

			if( value_string == NULL )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_MEMORY,
				 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
				 "%s: unable to create main name string.",
				 function );

				goto on_error;
			}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
			result = libuna_utf16_string_copy_from_utf16_stream(
				  (libuna_utf16_character_t *) value_string,
				  value_string_size,
				  internal_mui_resource->main_name,
				  internal_mui_resource->main_name_size,
				  LIBUNA_ENDIAN_LITTLE,
				  error );
#else
			result = libuna_utf8_string_copy_from_utf16_stream(
				  (libuna_utf8_character_t *) value_string,
				  value_string_size,
				  internal_mui_resource->main_name,
				  internal_mui_resource->main_name_size,
				  LIBUNA_ENDIAN_LITTLE,
				  error );
#endif
			if( result != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
				 "%s: unable to set main name string.",
				 function );

				goto on_error;
			}
			libcnotify_printf(
			 "%s: main name\t\t\t\t\t: %" PRIs_SYSTEM "\n",
			 function,
			 value_string );

			memory_free(
			 value_string );

			value_string = NULL;
		}
#endif
	}
	if( data_offset > ( data_size - 8 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: invalid data size value too small.",
		 function );

		goto on_error;
	}
	byte_stream_copy_to_uint32_little_endian(
	 &( data[ data_offset ] ),
	 value_data_offset );

	byte_stream_copy_to_uint32_little_endian(
	 &( data[ data_offset + 4 ] ),
	 value_data_size );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: main identifier type data offset\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_data_offset );

		libcnotify_printf(
		 "%s: main identifier type data size\t\t: %" PRIu32 "\n",
		 function,
		 value_data_size );
	}
#endif
	data_offset += 8;

	if( value_data_size > 0 )
	{
		if( ( (size_t) value_data_offset < 0x84 )
		 || ( (size_t) value_data_offset >= data_size ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: value data offset value out of bounds.",
			 function );

			goto on_error;
		}
		if( (size_t) ( value_data_offset + value_data_size ) > data_size )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: value data size value out of bounds.",
			 function );

			goto on_error;
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: main identifier type data:\n",
			 function );
			libcnotify_print_data(
			 &( data[ value_data_offset ] ),
			 value_data_size,
			 0 );
		}
#endif
	}
	if( data_offset > ( data_size - 8 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: invalid data size value too small.",
		 function );

		goto on_error;
	}
	byte_stream_copy_to_uint32_little_endian(
	 &( data[ data_offset ] ),
	 value_data_offset );

	byte_stream_copy_to_uint32_little_endian(
	 &( data[ data_offset + 4 ] ),
	 value_data_size );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: MUI name type data offset\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_data_offset );

		libcnotify_printf(
		 "%s: MUI name type data size\t\t\t: %" PRIu32 "\n",
		 function,
		 value_data_size );
	}
#endif
	data_offset += 8;

	if( value_data_size > 0 )
	{
		if( ( (size_t) value_data_offset < 0x84 )
		 || ( (size_t) value_data_offset >= data_size ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: value data offset value out of bounds.",
			 function );

			goto on_error;
		}
		if( ( value_data_size == 0 )
		 || ( value_data_size > (size_t) MEMORY_MAXIMUM_ALLOCATION_SIZE )
		 || ( value_data_size > ( data_size - value_data_offset ) ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid value data size value out of bounds.",
			 function );

			goto on_error;
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: MUI name type data:\n",
			 function );
			libcnotify_print_data(
			 &( data[ value_data_offset ] ),
			 value_data_size,
			 0 );
		}
#endif
		internal_mui_resource->mui_name = (uint8_t *) memory_allocate(
		                                               sizeof( uint8_t ) * value_data_size );

		if( internal_mui_resource->mui_name == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create MUI name.",
			 function );

			goto on_error;
		}
		if( memory_copy(
		     internal_mui_resource->mui_name,
		     &( data[ value_data_offset ] ),
		     value_data_size ) == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
			 "%s: unable to copy MUI name.",
			 function );

			goto on_error;
		}
		internal_mui_resource->mui_name_size = value_data_size;

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
			result = libuna_utf16_string_size_from_utf16_stream(
				  internal_mui_resource->mui_name,
				  internal_mui_resource->mui_name_size,
				  LIBUNA_ENDIAN_LITTLE,
				  &value_string_size,
				  error );
#else
			result = libuna_utf8_string_size_from_utf16_stream(
				  internal_mui_resource->mui_name,
				  internal_mui_resource->mui_name_size,
				  LIBUNA_ENDIAN_LITTLE,
				  &value_string_size,
				  error );
#endif
			if( result != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to determine size of MUI name string.",
				 function );

				goto on_error;
			}
			if( value_string_size > ( (size_t) MEMORY_MAXIMUM_ALLOCATION_SIZE / sizeof( system_character_t ) ) )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
				 "%s: invalid MUI name string size value exceeds maximum.",
				 function );

				goto on_error;
			}
			value_string = system_string_allocate(
					value_string_size );

			if( value_string == NULL )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_MEMORY,
				 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
				 "%s: unable to create MUI name string.",
				 function );

				goto on_error;
			}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
			result = libuna_utf16_string_copy_from_utf16_stream(
				  (libuna_utf16_character_t *) value_string,
				  value_string_size,
				  internal_mui_resource->mui_name,
				  internal_mui_resource->mui_name_size,
				  LIBUNA_ENDIAN_LITTLE,
				  error );
#else
			result = libuna_utf8_string_copy_from_utf16_stream(
				  (libuna_utf8_character_t *) value_string,
				  value_string_size,
				  internal_mui_resource->mui_name,
				  internal_mui_resource->mui_name_size,
				  LIBUNA_ENDIAN_LITTLE,
				  error );
#endif
			if( result != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
				 "%s: unable to set MUI name string.",
				 function );

				goto on_error;
			}
			libcnotify_printf(
			 "%s: MUI name\t\t\t\t\t: %" PRIs_SYSTEM "\n",
			 function,
			 value_string );

			memory_free(
			 value_string );

			value_string = NULL;
		}
#endif
	}
	if( data_offset > ( data_size - 8 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: invalid data size value too small.",
		 function );

		goto on_error;
	}
	byte_stream_copy_to_uint32_little_endian(
	 &( data[ data_offset ] ),
	 value_data_offset );

	byte_stream_copy_to_uint32_little_endian(
	 &( data[ data_offset + 4 ] ),
	 value_data_size );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: MUI identifier type data offset\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_data_offset );

		libcnotify_printf(
		 "%s: MUI identifier type data size\t\t\t: %" PRIu32 "\n",
		 function,
		 value_data_size );
	}
#endif
	data_offset += 8;

	if( value_data_size > 0 )
	{
		if( ( (size_t) value_data_offset < 0x84 )
		 || ( (size_t) value_data_offset >= data_size ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: value data offset value out of bounds.",
			 function );

			goto on_error;
		}
		if( (size_t) ( value_data_offset + value_data_size ) > data_size )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: value data size value out of bounds.",
			 function );

			goto on_error;
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: MUI identifier type data:\n",
			 function );
			libcnotify_print_data(
			 &( data[ value_data_offset ] ),
			 value_data_size,
			 0 );
		}
#endif
	}
	if( data_offset > ( data_size - 8 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: invalid data size value too small.",
		 function );

		goto on_error;
	}
	byte_stream_copy_to_uint32_little_endian(
	 &( data[ data_offset ] ),
	 value_data_offset );

	byte_stream_copy_to_uint32_little_endian(
	 &( data[ data_offset + 4 ] ),
	 value_data_size );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: language data offset\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_data_offset );

		libcnotify_printf(
		 "%s: language data size\t\t\t\t: %" PRIu32 "\n",
		 function,
		 value_data_size );
	}
#endif
	data_offset += 8;

	if( data_offset > ( data_size - 8 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: invalid data size value too small.",
		 function );

		goto on_error;
	}
	byte_stream_copy_to_uint32_little_endian(
	 &( data[ data_offset ] ),
	 value_data_offset );

	byte_stream_copy_to_uint32_little_endian(
	 &( data[ data_offset + 4 ] ),
	 value_data_size );

	if( value_data_size > 0 )
	{
		if( ( (size_t) value_data_offset < 0x84 )
		 || ( (size_t) value_data_offset >= data_size ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: value data offset value out of bounds.",
			 function );

			goto on_error;
		}
		if( ( value_data_size == 0 )
		 || ( value_data_size > (size_t) MEMORY_MAXIMUM_ALLOCATION_SIZE )
		 || ( value_data_size > ( data_size - value_data_offset ) ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid value data size value out of bounds.",
			 function );

			goto on_error;
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: ultimate language data:\n",
			 function );
			libcnotify_print_data(
			 &( data[ value_data_offset ] ),
			 value_data_size,
			 0 );
		}
#endif
		internal_mui_resource->language = (uint8_t *) memory_allocate(
		                                               sizeof( uint8_t ) * value_data_size );

		if( internal_mui_resource->language == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create language.",
			 function );

			goto on_error;
		}
		if( memory_copy(
		     internal_mui_resource->language,
		     &( data[ value_data_offset ] ),
		     value_data_size ) == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
			 "%s: unable to copy language identifier.",
			 function );

			goto on_error;
		}
		internal_mui_resource->language_size = value_data_size;

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
			result = libuna_utf16_string_size_from_utf16_stream(
				  internal_mui_resource->language,
				  internal_mui_resource->language_size,
				  LIBUNA_ENDIAN_LITTLE,
				  &value_string_size,
				  error );
#else
			result = libuna_utf8_string_size_from_utf16_stream(
				  internal_mui_resource->language,
				  internal_mui_resource->language_size,
				  LIBUNA_ENDIAN_LITTLE,
				  &value_string_size,
				  error );
#endif
			if( result != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to determine size of language string.",
				 function );

				goto on_error;
			}
			if( value_string_size > ( (size_t) MEMORY_MAXIMUM_ALLOCATION_SIZE / sizeof( system_character_t ) ) )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
				 "%s: invalid language string size value exceeds maximum.",
				 function );

				goto on_error;
			}
			value_string = system_string_allocate(
					value_string_size );

			if( value_string == NULL )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_MEMORY,
				 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
				 "%s: unable to create language string.",
				 function );

				goto on_error;
			}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
			result = libuna_utf16_string_copy_from_utf16_stream(
				  (libuna_utf16_character_t *) value_string,
				  value_string_size,
				  internal_mui_resource->language,
				  internal_mui_resource->language_size,
				  LIBUNA_ENDIAN_LITTLE,
				  error );
#else
			result = libuna_utf8_string_copy_from_utf16_stream(
				  (libuna_utf8_character_t *) value_string,
				  value_string_size,
				  internal_mui_resource->language,
				  internal_mui_resource->language_size,
				  LIBUNA_ENDIAN_LITTLE,
				  error );
#endif
			if( result != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
				 "%s: unable to set language string.",
				 function );

				goto on_error;
			}
			libcnotify_printf(
			 "%s: language\t\t\t\t\t: %" PRIs_SYSTEM "\n",
			 function,
			 value_string );

			memory_free(
			 value_string );

			value_string = NULL;
		}
#endif
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: ultimate fallback language data offset\t: 0x%08" PRIx32 "\n",
		 function,
		 value_data_offset );

		libcnotify_printf(
		 "%s: ultimate fallback language data size\t\t: %" PRIu32 "\n",
		 function,
		 value_data_size );
	}
#endif
	if( value_data_size > 0 )
	{
		if( ( (size_t) value_data_offset < 0x84 )
		 || ( (size_t) value_data_offset >= data_size ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: value data offset value out of bounds.",
			 function );

			goto on_error;
		}
		if( ( value_data_size == 0 )
		 || ( value_data_size > (size_t) MEMORY_MAXIMUM_ALLOCATION_SIZE )
		 || ( value_data_size > ( data_size - value_data_offset ) ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid value data size value out of bounds.",
			 function );

			goto on_error;
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: ultimate fallback language data:\n",
			 function );
			libcnotify_print_data(
			 &( data[ value_data_offset ] ),
			 value_data_size,
			 0 );
		}
#endif
		internal_mui_resource->fallback_language = (uint8_t *) memory_allocate(
		                                                        sizeof( uint8_t ) * value_data_size );

		if( internal_mui_resource->fallback_language == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create fallback language.",
			 function );

			goto on_error;
		}
		if( memory_copy(
		     internal_mui_resource->fallback_language,
		     &( data[ value_data_offset ] ),
		     value_data_size ) == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
			 "%s: unable to copy fallback language.",
			 function );

			goto on_error;
		}
		internal_mui_resource->fallback_language_size = value_data_size;

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
			result = libuna_utf16_string_size_from_utf16_stream(
				  internal_mui_resource->fallback_language,
				  internal_mui_resource->fallback_language_size,
				  LIBUNA_ENDIAN_LITTLE,
				  &value_string_size,
				  error );
#else
			result = libuna_utf8_string_size_from_utf16_stream(
				  internal_mui_resource->fallback_language,
				  internal_mui_resource->fallback_language_size,
				  LIBUNA_ENDIAN_LITTLE,
				  &value_string_size,
				  error );
#endif
			if( result != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to determine size of fallback language string.",
				 function );

				goto on_error;
			}
			if( value_string_size > ( (size_t) MEMORY_MAXIMUM_ALLOCATION_SIZE / sizeof( system_character_t ) ) )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
				 "%s: invalid fallback language string size value exceeds maximum.",
				 function );

				goto on_error;
			}
			value_string = system_string_allocate(
					value_string_size );

			if( value_string == NULL )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_MEMORY,
				 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
				 "%s: unable to create fallback language string.",
				 function );

				goto on_error;
			}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
			result = libuna_utf16_string_copy_from_utf16_stream(
				  (libuna_utf16_character_t *) value_string,
				  value_string_size,
				  internal_mui_resource->fallback_language,
				  internal_mui_resource->fallback_language_size,
				  LIBUNA_ENDIAN_LITTLE,
				  error );
#else
			result = libuna_utf8_string_copy_from_utf16_stream(
				  (libuna_utf8_character_t *) value_string,
				  value_string_size,
				  internal_mui_resource->fallback_language,
				  internal_mui_resource->fallback_language_size,
				  LIBUNA_ENDIAN_LITTLE,
				  error );
#endif
			if( result != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
				 "%s: unable to set fallback language string.",
				 function );

				goto on_error;
			}
			libcnotify_printf(
			 "%s: fallback language\t\t\t\t: %" PRIs_SYSTEM "\n",
			 function,
			 value_string );

			memory_free(
			 value_string );

			value_string = NULL;
		}
#endif
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "\n" );
	}
#endif
/* TODO print trailing data */

	return( 1 );

on_error:
#if defined( HAVE_DEBUG_OUTPUT )
	if( value_string != NULL )
	{
		memory_free(
		 value_string );
	}
#endif
	if( internal_mui_resource->fallback_language != NULL )
	{
		memory_free(
		 internal_mui_resource->fallback_language );

		internal_mui_resource->fallback_language = NULL;
	}
	internal_mui_resource->fallback_language_size = 0;

	if( internal_mui_resource->language != NULL )
	{
		memory_free(
		 internal_mui_resource->language );

		internal_mui_resource->language = NULL;
	}
	internal_mui_resource->language_size = 0;

	if( internal_mui_resource->mui_name != NULL )
	{
		memory_free(
		 internal_mui_resource->mui_name );

		internal_mui_resource->mui_name = NULL;
	}
	internal_mui_resource->mui_name_size = 0;

	if( internal_mui_resource->main_name != NULL )
	{
		memory_free(
		 internal_mui_resource->main_name );

		internal_mui_resource->main_name = NULL;
	}
	internal_mui_resource->main_name_size = 0;

	return( -1 );
}

/* Retrieves the file type
 * Returns 1 if successful or -1 on error
 */
int libwrc_mui_resource_get_file_type(
     libwrc_mui_resource_t *mui_resource,
     uint32_t *file_type,
     libcerror_error_t **error )
{
	libwrc_internal_mui_resource_t *internal_mui_resource = NULL;
	static char *function                                 = "libwrc_mui_resource_get_file_type";

	if( mui_resource == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid MUI resource.",
		 function );

		return( -1 );
	}
	internal_mui_resource = (libwrc_internal_mui_resource_t *) mui_resource;

	if( file_type == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file type.",
		 function );

		return( -1 );
	}
	*file_type = internal_mui_resource->file_type;

	return( 1 );
}

/* Retrieves the size of a specific UTF-8 formatted main name
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libwrc_mui_resource_get_utf8_main_name_size(
     libwrc_mui_resource_t *mui_resource,
     size_t *utf8_string_size,
     libcerror_error_t **error )
{
	libwrc_internal_mui_resource_t *internal_mui_resource = NULL;
	static char *function                                 = "libwrc_mui_resource_get_utf8_main_name_size";

	if( mui_resource == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid MUI resource.",
		 function );

		return( -1 );
	}
	internal_mui_resource = (libwrc_internal_mui_resource_t *) mui_resource;

	if( utf8_string_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-8 string size.",
		 function );

		return( -1 );
	}
	if( ( internal_mui_resource->main_name == NULL )
	 || ( internal_mui_resource->main_name_size == 0 ) )
	{
		return( 0 );
	}
	if( libuna_utf8_string_size_from_utf16_stream(
	     internal_mui_resource->main_name,
	     internal_mui_resource->main_name_size,
	     LIBUNA_ENDIAN_LITTLE,
	     utf8_string_size,
	     error ) != 1 )
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

/* Retrieves a specific UTF-8 formatted main name
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libwrc_mui_resource_get_utf8_main_name(
     libwrc_mui_resource_t *mui_resource,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error )
{
	libwrc_internal_mui_resource_t *internal_mui_resource = NULL;
	static char *function                                 = "libwrc_mui_resource_get_utf8_main_name";

	if( mui_resource == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid MUI resource.",
		 function );

		return( -1 );
	}
	internal_mui_resource = (libwrc_internal_mui_resource_t *) mui_resource;

	if( utf8_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-8 string.",
		 function );

		return( -1 );
	}
	if( utf8_string_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-8 string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( ( internal_mui_resource->main_name == NULL )
	 || ( internal_mui_resource->main_name_size == 0 ) )
	{
		return( 0 );
	}
	if( libuna_utf8_string_copy_from_utf16_stream(
	     utf8_string,
	     utf8_string_size,
	     internal_mui_resource->main_name,
	     internal_mui_resource->main_name_size,
	     LIBUNA_ENDIAN_LITTLE,
	     error ) != 1 )
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

/* Retrieves the size of a specific UTF-16 formatted main name
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libwrc_mui_resource_get_utf16_main_name_size(
     libwrc_mui_resource_t *mui_resource,
     size_t *utf16_string_size,
     libcerror_error_t **error )
{
	libwrc_internal_mui_resource_t *internal_mui_resource = NULL;
	static char *function                                 = "libwrc_mui_resource_get_utf16_main_name_size";

	if( mui_resource == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid MUI resource.",
		 function );

		return( -1 );
	}
	internal_mui_resource = (libwrc_internal_mui_resource_t *) mui_resource;

	if( utf16_string_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 string size.",
		 function );

		return( -1 );
	}
	if( ( internal_mui_resource->main_name == NULL )
	 || ( internal_mui_resource->main_name_size == 0 ) )
	{
		return( 0 );
	}
	if( libuna_utf16_string_size_from_utf16_stream(
	     internal_mui_resource->main_name,
	     internal_mui_resource->main_name_size,
	     LIBUNA_ENDIAN_LITTLE,
	     utf16_string_size,
	     error ) != 1 )
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

/* Retrieves a specific UTF-16 formatted main name
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libwrc_mui_resource_get_utf16_main_name(
     libwrc_mui_resource_t *mui_resource,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error )
{
	libwrc_internal_mui_resource_t *internal_mui_resource = NULL;
	static char *function                                 = "libwrc_mui_resource_get_utf16_main_name";

	if( mui_resource == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid MUI resource.",
		 function );

		return( -1 );
	}
	internal_mui_resource = (libwrc_internal_mui_resource_t *) mui_resource;

	if( utf16_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 string.",
		 function );

		return( -1 );
	}
	if( utf16_string_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-16 string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( ( internal_mui_resource->main_name == NULL )
	 || ( internal_mui_resource->main_name_size == 0 ) )
	{
		return( 0 );
	}
	if( libuna_utf16_string_copy_from_utf16_stream(
	     utf16_string,
	     utf16_string_size,
	     internal_mui_resource->main_name,
	     internal_mui_resource->main_name_size,
	     LIBUNA_ENDIAN_LITTLE,
	     error ) != 1 )
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

/* Retrieves the size of a specific UTF-8 formatted MUI name
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libwrc_mui_resource_get_utf8_mui_name_size(
     libwrc_mui_resource_t *mui_resource,
     size_t *utf8_string_size,
     libcerror_error_t **error )
{
	libwrc_internal_mui_resource_t *internal_mui_resource = NULL;
	static char *function                                 = "libwrc_mui_resource_get_utf8_mui_name_size";

	if( mui_resource == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid MUI resource.",
		 function );

		return( -1 );
	}
	internal_mui_resource = (libwrc_internal_mui_resource_t *) mui_resource;

	if( utf8_string_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-8 string size.",
		 function );

		return( -1 );
	}
	if( ( internal_mui_resource->mui_name == NULL )
	 || ( internal_mui_resource->mui_name_size == 0 ) )
	{
		return( 0 );
	}
	if( libuna_utf8_string_size_from_utf16_stream(
	     internal_mui_resource->mui_name,
	     internal_mui_resource->mui_name_size,
	     LIBUNA_ENDIAN_LITTLE,
	     utf8_string_size,
	     error ) != 1 )
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

/* Retrieves a specific UTF-8 formatted MUI name
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libwrc_mui_resource_get_utf8_mui_name(
     libwrc_mui_resource_t *mui_resource,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error )
{
	libwrc_internal_mui_resource_t *internal_mui_resource = NULL;
	static char *function                                 = "libwrc_mui_resource_get_utf8_mui_name";

	if( mui_resource == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid MUI resource.",
		 function );

		return( -1 );
	}
	internal_mui_resource = (libwrc_internal_mui_resource_t *) mui_resource;

	if( utf8_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-8 string.",
		 function );

		return( -1 );
	}
	if( utf8_string_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-8 string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( ( internal_mui_resource->mui_name == NULL )
	 || ( internal_mui_resource->mui_name_size == 0 ) )
	{
		return( 0 );
	}
	if( libuna_utf8_string_copy_from_utf16_stream(
	     utf8_string,
	     utf8_string_size,
	     internal_mui_resource->mui_name,
	     internal_mui_resource->mui_name_size,
	     LIBUNA_ENDIAN_LITTLE,
	     error ) != 1 )
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

/* Retrieves the size of a specific UTF-16 formatted MUI name
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libwrc_mui_resource_get_utf16_mui_name_size(
     libwrc_mui_resource_t *mui_resource,
     size_t *utf16_string_size,
     libcerror_error_t **error )
{
	libwrc_internal_mui_resource_t *internal_mui_resource = NULL;
	static char *function                                 = "libwrc_mui_resource_get_utf16_mui_name_size";

	if( mui_resource == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid MUI resource.",
		 function );

		return( -1 );
	}
	internal_mui_resource = (libwrc_internal_mui_resource_t *) mui_resource;

	if( utf16_string_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 string size.",
		 function );

		return( -1 );
	}
	if( ( internal_mui_resource->mui_name == NULL )
	 || ( internal_mui_resource->mui_name_size == 0 ) )
	{
		return( 0 );
	}
	if( libuna_utf16_string_size_from_utf16_stream(
	     internal_mui_resource->mui_name,
	     internal_mui_resource->mui_name_size,
	     LIBUNA_ENDIAN_LITTLE,
	     utf16_string_size,
	     error ) != 1 )
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

/* Retrieves a specific UTF-16 formatted MUI name
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libwrc_mui_resource_get_utf16_mui_name(
     libwrc_mui_resource_t *mui_resource,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error )
{
	libwrc_internal_mui_resource_t *internal_mui_resource = NULL;
	static char *function                                 = "libwrc_mui_resource_get_utf16_mui_name";

	if( mui_resource == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid MUI resource.",
		 function );

		return( -1 );
	}
	internal_mui_resource = (libwrc_internal_mui_resource_t *) mui_resource;

	if( utf16_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 string.",
		 function );

		return( -1 );
	}
	if( utf16_string_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-16 string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( ( internal_mui_resource->mui_name == NULL )
	 || ( internal_mui_resource->mui_name_size == 0 ) )
	{
		return( 0 );
	}
	if( libuna_utf16_string_copy_from_utf16_stream(
	     utf16_string,
	     utf16_string_size,
	     internal_mui_resource->mui_name,
	     internal_mui_resource->mui_name_size,
	     LIBUNA_ENDIAN_LITTLE,
	     error ) != 1 )
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

/* Retrieves the size of a specific UTF-8 formatted language
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libwrc_mui_resource_get_utf8_language_size(
     libwrc_mui_resource_t *mui_resource,
     size_t *utf8_string_size,
     libcerror_error_t **error )
{
	libwrc_internal_mui_resource_t *internal_mui_resource = NULL;
	static char *function                                 = "libwrc_mui_resource_get_utf8_language_size";

	if( mui_resource == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid MUI resource.",
		 function );

		return( -1 );
	}
	internal_mui_resource = (libwrc_internal_mui_resource_t *) mui_resource;

	if( utf8_string_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-8 string size.",
		 function );

		return( -1 );
	}
	if( ( internal_mui_resource->language == NULL )
	 || ( internal_mui_resource->language_size == 0 ) )
	{
		return( 0 );
	}
	if( libuna_utf8_string_size_from_utf16_stream(
	     internal_mui_resource->language,
	     internal_mui_resource->language_size,
	     LIBUNA_ENDIAN_LITTLE,
	     utf8_string_size,
	     error ) != 1 )
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

/* Retrieves a specific UTF-8 formatted language
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libwrc_mui_resource_get_utf8_language(
     libwrc_mui_resource_t *mui_resource,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error )
{
	libwrc_internal_mui_resource_t *internal_mui_resource = NULL;
	static char *function                                 = "libwrc_mui_resource_get_utf8_language";

	if( mui_resource == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid MUI resource.",
		 function );

		return( -1 );
	}
	internal_mui_resource = (libwrc_internal_mui_resource_t *) mui_resource;

	if( utf8_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-8 string.",
		 function );

		return( -1 );
	}
	if( utf8_string_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-8 string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( ( internal_mui_resource->language == NULL )
	 || ( internal_mui_resource->language_size == 0 ) )
	{
		return( 0 );
	}
	if( libuna_utf8_string_copy_from_utf16_stream(
	     utf8_string,
	     utf8_string_size,
	     internal_mui_resource->language,
	     internal_mui_resource->language_size,
	     LIBUNA_ENDIAN_LITTLE,
	     error ) != 1 )
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

/* Retrieves the size of a specific UTF-16 formatted language
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libwrc_mui_resource_get_utf16_language_size(
     libwrc_mui_resource_t *mui_resource,
     size_t *utf16_string_size,
     libcerror_error_t **error )
{
	libwrc_internal_mui_resource_t *internal_mui_resource = NULL;
	static char *function                                 = "libwrc_mui_resource_get_utf16_language_size";

	if( mui_resource == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid MUI resource.",
		 function );

		return( -1 );
	}
	internal_mui_resource = (libwrc_internal_mui_resource_t *) mui_resource;

	if( utf16_string_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 string size.",
		 function );

		return( -1 );
	}
	if( ( internal_mui_resource->language == NULL )
	 || ( internal_mui_resource->language_size == 0 ) )
	{
		return( 0 );
	}
	if( libuna_utf16_string_size_from_utf16_stream(
	     internal_mui_resource->language,
	     internal_mui_resource->language_size,
	     LIBUNA_ENDIAN_LITTLE,
	     utf16_string_size,
	     error ) != 1 )
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

/* Retrieves a specific UTF-16 formatted language
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libwrc_mui_resource_get_utf16_language(
     libwrc_mui_resource_t *mui_resource,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error )
{
	libwrc_internal_mui_resource_t *internal_mui_resource = NULL;
	static char *function                                 = "libwrc_mui_resource_get_utf16_language";

	if( mui_resource == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid MUI resource.",
		 function );

		return( -1 );
	}
	internal_mui_resource = (libwrc_internal_mui_resource_t *) mui_resource;

	if( utf16_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 string.",
		 function );

		return( -1 );
	}
	if( utf16_string_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-16 string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( ( internal_mui_resource->language == NULL )
	 || ( internal_mui_resource->language_size == 0 ) )
	{
		return( 0 );
	}
	if( libuna_utf16_string_copy_from_utf16_stream(
	     utf16_string,
	     utf16_string_size,
	     internal_mui_resource->language,
	     internal_mui_resource->language_size,
	     LIBUNA_ENDIAN_LITTLE,
	     error ) != 1 )
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

/* Retrieves the size of a specific UTF-8 formatted fallback language
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libwrc_mui_resource_get_utf8_fallback_language_size(
     libwrc_mui_resource_t *mui_resource,
     size_t *utf8_string_size,
     libcerror_error_t **error )
{
	libwrc_internal_mui_resource_t *internal_mui_resource = NULL;
	static char *function                                 = "libwrc_mui_resource_get_utf8_fallback_language_size";

	if( mui_resource == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid MUI resource.",
		 function );

		return( -1 );
	}
	internal_mui_resource = (libwrc_internal_mui_resource_t *) mui_resource;

	if( utf8_string_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-8 string size.",
		 function );

		return( -1 );
	}
	if( ( internal_mui_resource->fallback_language == NULL )
	 || ( internal_mui_resource->fallback_language_size == 0 ) )
	{
		return( 0 );
	}
	if( libuna_utf8_string_size_from_utf16_stream(
	     internal_mui_resource->fallback_language,
	     internal_mui_resource->fallback_language_size,
	     LIBUNA_ENDIAN_LITTLE,
	     utf8_string_size,
	     error ) != 1 )
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

/* Retrieves a specific UTF-8 formatted fallback language
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libwrc_mui_resource_get_utf8_fallback_language(
     libwrc_mui_resource_t *mui_resource,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error )
{
	libwrc_internal_mui_resource_t *internal_mui_resource = NULL;
	static char *function                                 = "libwrc_mui_resource_get_utf8_fallback_language";

	if( mui_resource == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid MUI resource.",
		 function );

		return( -1 );
	}
	internal_mui_resource = (libwrc_internal_mui_resource_t *) mui_resource;

	if( utf8_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-8 string.",
		 function );

		return( -1 );
	}
	if( utf8_string_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-8 string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( ( internal_mui_resource->fallback_language == NULL )
	 || ( internal_mui_resource->fallback_language_size == 0 ) )
	{
		return( 0 );
	}
	if( libuna_utf8_string_copy_from_utf16_stream(
	     utf8_string,
	     utf8_string_size,
	     internal_mui_resource->fallback_language,
	     internal_mui_resource->fallback_language_size,
	     LIBUNA_ENDIAN_LITTLE,
	     error ) != 1 )
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

/* Retrieves the size of a specific UTF-16 formatted fallback language
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libwrc_mui_resource_get_utf16_fallback_language_size(
     libwrc_mui_resource_t *mui_resource,
     size_t *utf16_string_size,
     libcerror_error_t **error )
{
	libwrc_internal_mui_resource_t *internal_mui_resource = NULL;
	static char *function                                 = "libwrc_mui_resource_get_utf16_fallback_language_size";

	if( mui_resource == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid MUI resource.",
		 function );

		return( -1 );
	}
	internal_mui_resource = (libwrc_internal_mui_resource_t *) mui_resource;

	if( utf16_string_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 string size.",
		 function );

		return( -1 );
	}
	if( ( internal_mui_resource->fallback_language == NULL )
	 || ( internal_mui_resource->fallback_language_size == 0 ) )
	{
		return( 0 );
	}
	if( libuna_utf16_string_size_from_utf16_stream(
	     internal_mui_resource->fallback_language,
	     internal_mui_resource->fallback_language_size,
	     LIBUNA_ENDIAN_LITTLE,
	     utf16_string_size,
	     error ) != 1 )
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

/* Retrieves a specific UTF-16 formatted fallback language
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libwrc_mui_resource_get_utf16_fallback_language(
     libwrc_mui_resource_t *mui_resource,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error )
{
	libwrc_internal_mui_resource_t *internal_mui_resource = NULL;
	static char *function                                 = "libwrc_mui_resource_get_utf16_fallback_language";

	if( mui_resource == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid MUI resource.",
		 function );

		return( -1 );
	}
	internal_mui_resource = (libwrc_internal_mui_resource_t *) mui_resource;

	if( utf16_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 string.",
		 function );

		return( -1 );
	}
	if( utf16_string_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-16 string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( ( internal_mui_resource->fallback_language == NULL )
	 || ( internal_mui_resource->fallback_language_size == 0 ) )
	{
		return( 0 );
	}
	if( libuna_utf16_string_copy_from_utf16_stream(
	     utf16_string,
	     utf16_string_size,
	     internal_mui_resource->fallback_language,
	     internal_mui_resource->fallback_language_size,
	     LIBUNA_ENDIAN_LITTLE,
	     error ) != 1 )
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

