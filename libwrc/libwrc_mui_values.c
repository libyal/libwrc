/*
 * Multilingual User Interface (MUI) (resource) values functions
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

#include "libwrc_data_descriptor.h"
#include "libwrc_definitions.h"
#include "libwrc_io_handle.h"
#include "libwrc_language_entry.h"
#include "libwrc_libbfio.h"
#include "libwrc_libcerror.h"
#include "libwrc_libcnotify.h"
#include "libwrc_libuna.h"
#include "libwrc_mui_values.h"

#include "wrc_mui_resource.h"

uint8_t libwrc_mui_signature[ 4 ] = {
	0xcd, 0xfe, 0xcd, 0xfe };

/* Creates MUI values
 * Make sure the value mui_values is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libwrc_mui_values_initialize(
     libwrc_mui_values_t **mui_values,
     libcerror_error_t **error )
{
	static char *function = "libwrc_mui_values_initialize";

	if( mui_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid MUI values.",
		 function );

		return( -1 );
	}
	if( *mui_values != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid MUI values value already set.",
		 function );

		return( -1 );
	}
	*mui_values = memory_allocate_structure(
	               libwrc_mui_values_t );

	if( *mui_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create MUI values.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *mui_values,
	     0,
	     sizeof( libwrc_mui_values_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear MUI values.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *mui_values != NULL )
	{
		memory_free(
		 *mui_values );

		*mui_values = NULL;
	}
	return( -1 );
}

/* Frees MUI values
 * Returns 1 if successful or -1 on error
 */
int libwrc_mui_values_free(
     libwrc_mui_values_t **mui_values,
     libcerror_error_t **error )
{
	static char *function = "libwrc_mui_values_free";

	if( mui_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid MUI values.",
		 function );

		return( -1 );
	}
	if( *mui_values != NULL )
	{
		if( ( *mui_values )->main_name != NULL )
		{
			memory_free(
			 ( *mui_values )->main_name );
		}
		if( ( *mui_values )->mui_name != NULL )
		{
			memory_free(
			 ( *mui_values )->mui_name );
		}
		if( ( *mui_values )->language != NULL )
		{
			memory_free(
			 ( *mui_values )->language );
		}
		if( ( *mui_values )->fallback_language != NULL )
		{
			memory_free(
			 ( *mui_values )->fallback_language );
		}
		memory_free(
		 *mui_values );

		*mui_values = NULL;
	}
	return( 1 );
}

/* Reads the MUI (resource) values
 * Returns 1 if successful or -1 on error
 */
int libwrc_mui_values_read(
     libwrc_language_entry_t *language_entry,
     libwrc_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     libwrc_data_descriptor_t *data_descriptor,
     libcerror_error_t **error )
{
	libwrc_mui_values_t *mui_values  = NULL;
	uint8_t *resource_data           = NULL;
	uint8_t *mui_resource_data       = NULL;
	static char *function            = "libwrc_mui_values_read";
	off64_t file_offset              = 0;
	size_t resource_data_offset      = 0;
	size_t resource_data_size        = 0;
	ssize_t read_count               = 0;
	uint32_t data_size               = 0;
	uint32_t value_data_offset       = 0;
	uint32_t value_data_size         = 0;
	int value_index                  = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	system_character_t *value_string = NULL;
	size_t value_string_size         = 0;
	uint32_t value_32bit             = 0;
	int result                       = 0;
#endif

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
	if( io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid IO handle.",
		 function );

		return( -1 );
	}
	if( data_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data descriptor.",
		 function );

		return( -1 );
	}
	if( libwrc_mui_values_initialize(
	     &mui_values,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create MUI values.",
		 function );

		goto on_error;
	}
	resource_data_size = (size_t) data_descriptor->size;

	if( ( resource_data_size == 0 )
	 || ( resource_data_size > (size_t) MEMORY_MAXIMUM_ALLOCATION_SIZE ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid resource data size value out of bounds.",
		 function );

		goto on_error;
	}
	resource_data = (uint8_t *) memory_allocate(
	                             sizeof( uint8_t ) * resource_data_size );

	if( resource_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create resource data.",
		 function );

		goto on_error;
	}
	file_offset = data_descriptor->virtual_address - io_handle->virtual_address;

	read_count = libbfio_handle_read_buffer_at_offset(
	              file_io_handle,
	              resource_data,
	              resource_data_size,
	              file_offset,
	              error );

	if( read_count != (ssize_t) resource_data_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read resource data at offset: %" PRIi64 " (0x%08" PRIx64 ").",
		 function,
		 file_offset,
		 file_offset );

		goto on_error;
	}
	mui_resource_data = resource_data;

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: resource data:\n",
		 function );
		libcnotify_print_data(
		 mui_resource_data,
		 resource_data_size,
		 0 );
	}
#endif
	if( memory_compare(
	     ( (wrc_mui_header_t *) mui_resource_data )->signature,
	     libwrc_mui_signature,
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
	 ( (wrc_mui_header_t *) mui_resource_data )->size,
	 data_size );

	byte_stream_copy_to_uint32_little_endian(
	 ( (wrc_mui_header_t *) mui_resource_data )->file_type,
	 mui_values->file_type );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		byte_stream_copy_to_uint32_little_endian(
		 ( (wrc_mui_header_t *) mui_resource_data )->signature,
		 value_32bit );
		libcnotify_printf(
		 "%s: signature\t\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		libcnotify_printf(
		 "%s: size\t\t\t\t\t\t: %" PRIu32 "\n",
		 function,
		 data_size );

		byte_stream_copy_to_uint32_little_endian(
		 ( (wrc_mui_header_t *) mui_resource_data )->version,
		 value_32bit );
		libcnotify_printf(
		 "%s: version\t\t\t\t\t\t: %" PRIu32 ".%" PRIu32 "\n",
		 function,
		 value_32bit >> 16,
		 value_32bit & 0x0000ffffUL );

		byte_stream_copy_to_uint32_little_endian(
		 ( (wrc_mui_header_t *) mui_resource_data )->unknown1,
		 value_32bit );
		libcnotify_printf(
		 "%s: unknown1\t\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		libcnotify_printf(
		 "%s: file type\t\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 mui_values->file_type );

		byte_stream_copy_to_uint32_little_endian(
		 ( (wrc_mui_header_t *) mui_resource_data )->system_attributes,
		 value_32bit );
		libcnotify_printf(
		 "%s: system attributes\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 ( (wrc_mui_header_t *) mui_resource_data )->ultimate_fallback_location,
		 value_32bit );
		libcnotify_printf(
		 "%s: ultimate fallback location\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		libcnotify_printf(
		 "%s: service checksum:\n",
		 function );
		libcnotify_print_data(
		 ( (wrc_mui_header_t *) mui_resource_data )->service_checksum,
		 16,
		 0 );

		libcnotify_printf(
		 "%s: checksum:\n",
		 function );
		libcnotify_print_data(
		 ( (wrc_mui_header_t *) mui_resource_data )->checksum,
		 16,
		 0 );

		libcnotify_printf(
		 "%s: unknown2:\n",
		 function );
		libcnotify_print_data(
		 ( (wrc_mui_header_t *) mui_resource_data )->unknown2,
		 24,
		 0 );
	}
#endif
	resource_data_offset = sizeof( wrc_mui_header_t );

	if( (size_t) data_size > resource_data_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: data size value out of bounds.",
		 function );

		goto on_error;
	}
	byte_stream_copy_to_uint32_little_endian(
	 &( mui_resource_data[ resource_data_offset ] ),
	 value_data_offset );

	byte_stream_copy_to_uint32_little_endian(
	 &( mui_resource_data[ resource_data_offset + 4 ] ),
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
	resource_data_offset += 8;

	if( value_data_size > 0 )
	{
		if( ( (size_t) value_data_offset < 0x84 )
		 || ( (size_t) value_data_offset >= resource_data_size ) )
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
		 || ( value_data_size > ( resource_data_size - value_data_offset ) ) )
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
			 &( mui_resource_data[ value_data_offset ] ),
			 value_data_size,
			 0 );
		}
#endif
		mui_values->main_name = (uint8_t *) memory_allocate(
		                                     sizeof( uint8_t ) * value_data_size );

		if( mui_values->main_name == NULL )
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
		     mui_values->main_name,
		     &( mui_resource_data[ value_data_offset ] ),
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
		mui_values->main_name_size = value_data_size;

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
			result = libuna_utf16_string_size_from_utf16_stream(
				  mui_values->main_name,
				  mui_values->main_name_size,
				  LIBUNA_ENDIAN_LITTLE,
				  &value_string_size,
				  error );
#else
			result = libuna_utf8_string_size_from_utf16_stream(
				  mui_values->main_name,
				  mui_values->main_name_size,
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
			if( ( value_string_size > (size_t) SSIZE_MAX )
			 || ( ( sizeof( system_character_t ) * value_string_size )  > (size_t) SSIZE_MAX ) )
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
				  mui_values->main_name,
				  mui_values->main_name_size,
				  LIBUNA_ENDIAN_LITTLE,
				  error );
#else
			result = libuna_utf8_string_copy_from_utf16_stream(
				  (libuna_utf8_character_t *) value_string,
				  value_string_size,
				  mui_values->main_name,
				  mui_values->main_name_size,
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
	byte_stream_copy_to_uint32_little_endian(
	 &( mui_resource_data[ resource_data_offset ] ),
	 value_data_offset );

	byte_stream_copy_to_uint32_little_endian(
	 &( mui_resource_data[ resource_data_offset + 4 ] ),
	 value_data_size );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: main identifier type data offset\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_data_offset );

		libcnotify_printf(
		 "%s: main identifier type data size\t\t\t: %" PRIu32 "\n",
		 function,
		 value_data_size );
	}
#endif
	resource_data_offset += 8;

	if( value_data_size > 0 )
	{
		if( ( (size_t) value_data_offset < 0x84 )
		 || ( (size_t) value_data_offset >= resource_data_size ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: value data offset value out of bounds.",
			 function );

			goto on_error;
		}
		if( (size_t) ( value_data_offset + value_data_size ) > resource_data_size )
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
			 &( mui_resource_data[ value_data_offset ] ),
			 value_data_size,
			 0 );
		}
#endif
	}
	byte_stream_copy_to_uint32_little_endian(
	 &( mui_resource_data[ resource_data_offset ] ),
	 value_data_offset );

	byte_stream_copy_to_uint32_little_endian(
	 &( mui_resource_data[ resource_data_offset + 4 ] ),
	 value_data_size );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: MUI name type data offset\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_data_offset );

		libcnotify_printf(
		 "%s: MUI name type data size\t\t\t\t: %" PRIu32 "\n",
		 function,
		 value_data_size );
	}
#endif
	resource_data_offset += 8;

	if( value_data_size > 0 )
	{
		if( ( (size_t) value_data_offset < 0x84 )
		 || ( (size_t) value_data_offset >= resource_data_size ) )
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
		 || ( value_data_size > ( resource_data_size - value_data_offset ) ) )
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
			 &( mui_resource_data[ value_data_offset ] ),
			 value_data_size,
			 0 );
		}
#endif
		mui_values->mui_name = (uint8_t *) memory_allocate(
		                                    sizeof( uint8_t ) * value_data_size );

		if( mui_values->mui_name == NULL )
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
		     mui_values->mui_name,
		     &( mui_resource_data[ value_data_offset ] ),
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
		mui_values->mui_name_size = value_data_size;

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
			result = libuna_utf16_string_size_from_utf16_stream(
				  mui_values->mui_name,
				  mui_values->mui_name_size,
				  LIBUNA_ENDIAN_LITTLE,
				  &value_string_size,
				  error );
#else
			result = libuna_utf8_string_size_from_utf16_stream(
				  mui_values->mui_name,
				  mui_values->mui_name_size,
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
			if( ( value_string_size > (size_t) SSIZE_MAX )
			 || ( ( sizeof( system_character_t ) * value_string_size )  > (size_t) SSIZE_MAX ) )
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
				  mui_values->mui_name,
				  mui_values->mui_name_size,
				  LIBUNA_ENDIAN_LITTLE,
				  error );
#else
			result = libuna_utf8_string_copy_from_utf16_stream(
				  (libuna_utf8_character_t *) value_string,
				  value_string_size,
				  mui_values->mui_name,
				  mui_values->mui_name_size,
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
	byte_stream_copy_to_uint32_little_endian(
	 &( mui_resource_data[ resource_data_offset ] ),
	 value_data_offset );

	byte_stream_copy_to_uint32_little_endian(
	 &( mui_resource_data[ resource_data_offset + 4 ] ),
	 value_data_size );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: MUI identifier type data offset\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_data_offset );

		libcnotify_printf(
		 "%s: MUI identifier type data size\t\t\t: %" PRIu32 "\n",
		 function,
		 value_data_size );
	}
#endif
	resource_data_offset += 8;

	if( value_data_size > 0 )
	{
		if( ( (size_t) value_data_offset < 0x84 )
		 || ( (size_t) value_data_offset >= resource_data_size ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: value data offset value out of bounds.",
			 function );

			goto on_error;
		}
		if( (size_t) ( value_data_offset + value_data_size ) > resource_data_size )
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
			 &( mui_resource_data[ value_data_offset ] ),
			 value_data_size,
			 0 );
		}
#endif
	}
	byte_stream_copy_to_uint32_little_endian(
	 &( mui_resource_data[ resource_data_offset ] ),
	 value_data_offset );

	byte_stream_copy_to_uint32_little_endian(
	 &( mui_resource_data[ resource_data_offset + 4 ] ),
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
	resource_data_offset += 8;

	byte_stream_copy_to_uint32_little_endian(
	 &( mui_resource_data[ resource_data_offset ] ),
	 value_data_offset );

	byte_stream_copy_to_uint32_little_endian(
	 &( mui_resource_data[ resource_data_offset + 4 ] ),
	 value_data_size );

	if( value_data_size > 0 )
	{
		if( ( (size_t) value_data_offset < 0x84 )
		 || ( (size_t) value_data_offset >= resource_data_size ) )
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
		 || ( value_data_size > ( resource_data_size - value_data_offset ) ) )
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
			 &( mui_resource_data[ value_data_offset ] ),
			 value_data_size,
			 0 );
		}
#endif
		mui_values->language = (uint8_t *) memory_allocate(
		                                    sizeof( uint8_t ) * value_data_size );

		if( mui_values->language == NULL )
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
		     mui_values->language,
		     &( mui_resource_data[ value_data_offset ] ),
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
		mui_values->language_size = value_data_size;

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
			result = libuna_utf16_string_size_from_utf16_stream(
				  mui_values->language,
				  mui_values->language_size,
				  LIBUNA_ENDIAN_LITTLE,
				  &value_string_size,
				  error );
#else
			result = libuna_utf8_string_size_from_utf16_stream(
				  mui_values->language,
				  mui_values->language_size,
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
			if( ( value_string_size > (size_t) SSIZE_MAX )
			 || ( ( sizeof( system_character_t ) * value_string_size )  > (size_t) SSIZE_MAX ) )
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
				  mui_values->language,
				  mui_values->language_size,
				  LIBUNA_ENDIAN_LITTLE,
				  error );
#else
			result = libuna_utf8_string_copy_from_utf16_stream(
				  (libuna_utf8_character_t *) value_string,
				  value_string_size,
				  mui_values->language,
				  mui_values->language_size,
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
		 "%s: ultimate fallback language data offset\t\t: 0x%08" PRIx32 "\n",
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
		 || ( (size_t) value_data_offset >= resource_data_size ) )
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
		 || ( value_data_size > ( resource_data_size - value_data_offset ) ) )
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
			 &( mui_resource_data[ value_data_offset ] ),
			 value_data_size,
			 0 );
		}
#endif
		mui_values->fallback_language = (uint8_t *) memory_allocate(
		                                             sizeof( uint8_t ) * value_data_size );

		if( mui_values->fallback_language == NULL )
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
		     mui_values->fallback_language,
		     &( mui_resource_data[ value_data_offset ] ),
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
		mui_values->fallback_language_size = value_data_size;

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
			result = libuna_utf16_string_size_from_utf16_stream(
				  mui_values->fallback_language,
				  mui_values->fallback_language_size,
				  LIBUNA_ENDIAN_LITTLE,
				  &value_string_size,
				  error );
#else
			result = libuna_utf8_string_size_from_utf16_stream(
				  mui_values->fallback_language,
				  mui_values->fallback_language_size,
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
			if( ( value_string_size > (size_t) SSIZE_MAX )
			 || ( ( sizeof( system_character_t ) * value_string_size )  > (size_t) SSIZE_MAX ) )
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
				  mui_values->fallback_language,
				  mui_values->fallback_language_size,
				  LIBUNA_ENDIAN_LITTLE,
				  error );
#else
			result = libuna_utf8_string_copy_from_utf16_stream(
				  (libuna_utf8_character_t *) value_string,
				  value_string_size,
				  mui_values->fallback_language,
				  mui_values->fallback_language_size,
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
	if( libwrc_language_entry_append_value(
	     language_entry,
	     &value_index,
	     (intptr_t *) mui_values,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
		 "%s: unable to append MUI values.",
		 function );

		goto on_error;
	}
	mui_values = NULL;

	memory_free(
	 resource_data );

	return( 1 );

on_error:
#if defined( HAVE_DEBUG_OUTPUT )
	if( value_string != NULL )
	{
		memory_free(
		 value_string );
	}
#endif
	if( resource_data != NULL )
	{
		memory_free(
		 resource_data );
	}
	if( mui_values != NULL )
	{
		libwrc_mui_values_free(
		 &mui_values,
		 NULL );
	}
	return( -1 );
}

/* Retrieves the file type
 * Returns 1 if successful or -1 on error
 */
int libwrc_mui_values_get_file_type(
     libwrc_mui_values_t *mui_values,
     uint32_t *file_type,
     libcerror_error_t **error )
{
	static char *function = "libwrc_mui_values_get_file_type";

	if( mui_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid MUI values.",
		 function );

		return( -1 );
	}
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
	*file_type = mui_values->file_type;

	return( 1 );
}

