/*
 * Version (resource) values functions
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
#include <types.h>

#include "libwrc_data_descriptor.h"
#include "libwrc_definitions.h"
#include "libwrc_io_handle.h"
#include "libwrc_language_entry.h"
#include "libwrc_libbfio.h"
#include "libwrc_libcerror.h"
#include "libwrc_libcnotify.h"
#include "libwrc_libfvalue.h"
#include "libwrc_version_values.h"

#include "wrc_version_information_resource.h"

uint8_t libwrc_version_information_value_identifier[ 32 ] = \
	{ 'V', 0, 'S', 0, '_', 0, 'V', 0, 'E', 0, 'R', 0, 'S', 0, 'I', 0, 'O', 0, 'N', 0, '_', 0, 'I', 0, 'N', 0, 'F', 0, 'O', 0, 0, 0 };

uint8_t libwrc_version_fixed_file_information_signature[ 4 ] = \
	{ 0xbd, 0x04, 0xef, 0xfe };

/* Creates version values
 * Make sure the value version_values is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libwrc_version_values_initialize(
     libwrc_version_values_t **version_values,
     libcerror_error_t **error )
{
	static char *function = "libwrc_version_values_initialize";

	if( version_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid version values.",
		 function );

		return( -1 );
	}
	if( *version_values != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid version values value already set.",
		 function );

		return( -1 );
	}
	*version_values = memory_allocate_structure(
	                   libwrc_version_values_t );

	if( *version_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create version values.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *version_values,
	     0,
	     sizeof( libwrc_version_values_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear version values.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *version_values != NULL )
	{
		memory_free(
		 *version_values );

		*version_values = NULL;
	}
	return( -1 );
}

/* Frees version values
 * Returns 1 if successful or -1 on error
 */
int libwrc_version_values_free(
     libwrc_version_values_t **version_values,
     libcerror_error_t **error )
{
	static char *function = "libwrc_version_values_free";

	if( version_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid version values.",
		 function );

		return( -1 );
	}
	if( *version_values != NULL )
	{
		memory_free(
		 *version_values );

		*version_values = NULL;
	}
	return( 1 );
}

/* Reads the version (resource) values
 * Returns 1 if successful or -1 on error
 */
int libwrc_version_values_read(
     libwrc_language_entry_t *language_entry,
     libwrc_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     libwrc_data_descriptor_t *data_descriptor,
     libcerror_error_t **error )
{
	libwrc_version_values_t *version_values = NULL;
	libfvalue_value_t *value_identifier     = NULL;
	uint8_t *resource_data                  = NULL;
	uint8_t *version_resource_data          = NULL;
	static char *function                   = "libwrc_version_values_read";
	off64_t file_offset                     = 0;
	size_t alignment_padding_size           = 0;
	size_t resource_data_offset             = 0;
	size_t resource_data_size               = 0;
	ssize_t read_count                      = 0;
	uint32_t value_32bit                    = 0;
	uint16_t value_data_size                = 0;
	uint16_t value_data_type                = 0;
	uint16_t version_resource_data_size     = 0;
	int value_index                         = 0;

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
	if( libwrc_version_values_initialize(
	     &version_values,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create version values.",
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
	version_resource_data = resource_data;

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: resource data:\n",
		 function );
		libcnotify_print_data(
		 version_resource_data,
		 resource_data_size,
		 0 );
	}
#endif
	byte_stream_copy_to_uint16_little_endian(
	 ( (wrc_version_value_header_t *) version_resource_data )->size,
	 version_resource_data_size );

	byte_stream_copy_to_uint16_little_endian(
	 ( (wrc_version_value_header_t *) version_resource_data )->value_data_size,
	 value_data_size );

	byte_stream_copy_to_uint16_little_endian(
	 ( (wrc_version_value_header_t *) version_resource_data )->value_data_type,
	 value_data_type );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: size\t\t\t\t\t: %" PRIu16 "\n",
		 function,
		 version_resource_data_size );

		libcnotify_printf(
		 "%s: value data size\t\t\t\t: %" PRIu16 "\n",
		 function,
		 value_data_size );

		libcnotify_printf(
		 "%s: value data type\t\t\t\t: %" PRIu16 "\n",
		 function,
		 value_data_type );

		libcnotify_printf(
		 "\n" );
	}
#endif
	resource_data_offset += sizeof( wrc_version_value_header_t );

	if( libfvalue_value_type_initialize(
	     &value_identifier,
	     LIBFVALUE_VALUE_TYPE_STRING_UTF16,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create value identifier value.",
		 function );

		goto on_error;
	}
	read_count = libfvalue_value_type_set_data_string(
	              value_identifier,
	              &( version_resource_data[ resource_data_offset ] ),
	              resource_data_size,
	              LIBFVALUE_CODEPAGE_UTF16_LITTLE_ENDIAN,
	              LIBFVALUE_VALUE_DATA_FLAG_MANAGED,
	              error );

	if( read_count == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set data of value identifier value.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: value identifier\t\t\t\t: ",
		 function );

		if( libfvalue_value_print(
		     value_identifier,
		     0,
		     0,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
			 "%s: unable to print value identifier value.",
			 function );

			goto on_error;
		}
		libcnotify_printf(
		 "\n" );
	}
#endif
	if( ( read_count != 32 )
	 || ( memory_compare(
	       &( version_resource_data[ resource_data_offset ] ),
	       libwrc_version_information_value_identifier,
	       32 ) != 0 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported version resource value signature.",
		 function );

		goto on_error;
	}
	if( libfvalue_value_free(
	     &value_identifier,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free value identifier value.",
		 function );

		goto on_error;
	}
	resource_data_offset += read_count;

	if( ( resource_data_offset % 4 ) != 0 )
	{
		alignment_padding_size = 4 - ( resource_data_offset % 4 );

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: alignment padding:\n",
			 function );
			libcnotify_print_data(
			 &( version_resource_data[ resource_data_offset ] ),
			 alignment_padding_size,
			 0 );
		}
#endif
		resource_data_offset += alignment_padding_size;
	}
/* TODO refactor to separate function? */
	if( value_data_size > 0 )
	{
		if( value_data_size > resource_data_size )
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
			 "%s: value data:\n",
			 function );
			libcnotify_print_data(
			 &( version_resource_data[ resource_data_offset ] ),
			 value_data_size,
			 0 );
		}
#endif
		byte_stream_copy_to_uint32_little_endian(
		 &( version_resource_data[ resource_data_offset + 8 ] ),
		 version_values->file_version );

		byte_stream_copy_to_uint32_little_endian(
		 &( version_resource_data[ resource_data_offset + 12 ] ),
		 value_32bit );

		version_values->file_version <<= 32;
		version_values->file_version  |= value_32bit;

		byte_stream_copy_to_uint32_little_endian(
		 &( version_resource_data[ resource_data_offset + 16 ] ),
		 version_values->product_version );

		byte_stream_copy_to_uint32_little_endian(
		 &( version_resource_data[ resource_data_offset + 20 ] ),
		 value_32bit );

		version_values->product_version <<= 32;
		version_values->product_version  |= value_32bit;

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			byte_stream_copy_to_uint32_little_endian(
			 &( version_resource_data[ resource_data_offset ] ),
			 value_32bit );
			libcnotify_printf(
			 "%s: signature\t\t\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );

			byte_stream_copy_to_uint32_little_endian(
			 &( version_resource_data[ resource_data_offset + 4 ] ),
			 value_32bit );
			libcnotify_printf(
			 "%s: version\t\t\t\t\t: %" PRIu32 ".%" PRIu32 "\n",
			 function,
			 value_32bit >> 16,
			 value_32bit & 0x0000ffffUL );

			byte_stream_copy_to_uint32_little_endian(
			 &( version_resource_data[ resource_data_offset + 8 ] ),
			 value_32bit );
			libcnotify_printf(
			 "%s: file version upper\t\t\t\t: %" PRIu32 ".%" PRIu32 "\n",
			 function,
			 value_32bit >> 16,
			 value_32bit & 0x0000ffffUL );

			byte_stream_copy_to_uint32_little_endian(
			 &( version_resource_data[ resource_data_offset + 12 ] ),
			 value_32bit );
			libcnotify_printf(
			 "%s: file version lower\t\t\t\t: %" PRIu32 ".%" PRIu32 "\n",
			 function,
			 value_32bit >> 16,
			 value_32bit & 0x0000ffffUL );

			byte_stream_copy_to_uint32_little_endian(
			 &( version_resource_data[ resource_data_offset + 16 ] ),
			 value_32bit );
			libcnotify_printf(
			 "%s: product version upper\t\t\t: %" PRIu32 ".%" PRIu32 "\n",
			 function,
			 value_32bit >> 16,
			 value_32bit & 0x0000ffffUL );

			byte_stream_copy_to_uint32_little_endian(
			 &( version_resource_data[ resource_data_offset + 20 ] ),
			 value_32bit );
			libcnotify_printf(
			 "%s: product version lower\t\t\t: %" PRIu32 ".%" PRIu32 "\n",
			 function,
			 value_32bit >> 16,
			 value_32bit & 0x0000ffffUL );

			byte_stream_copy_to_uint32_little_endian(
			 &( version_resource_data[ resource_data_offset + 24 ] ),
			 value_32bit );
			libcnotify_printf(
			 "%s: file flags bitmask\t\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );

			byte_stream_copy_to_uint32_little_endian(
			 &( version_resource_data[ resource_data_offset + 28 ] ),
			 value_32bit );
			libcnotify_printf(
			 "%s: file flags\t\t\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );

			byte_stream_copy_to_uint32_little_endian(
			 &( version_resource_data[ resource_data_offset + 32 ] ),
			 value_32bit );
			libcnotify_printf(
			 "%s: file operating system\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );

			byte_stream_copy_to_uint32_little_endian(
			 &( version_resource_data[ resource_data_offset + 36 ] ),
			 value_32bit );
			libcnotify_printf(
			 "%s: file type\t\t\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );

			byte_stream_copy_to_uint32_little_endian(
			 &( version_resource_data[ resource_data_offset + 40 ] ),
			 value_32bit );
			libcnotify_printf(
			 "%s: file sub type\t\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );

			byte_stream_copy_to_uint32_little_endian(
			 &( version_resource_data[ resource_data_offset + 44 ] ),
			 value_32bit );
			libcnotify_printf(
			 "%s: file time upper\t\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );

			byte_stream_copy_to_uint32_little_endian(
			 &( version_resource_data[ resource_data_offset + 48 ] ),
			 value_32bit );
			libcnotify_printf(
			 "%s: file time lower\t\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );

			libcnotify_printf(
			 "\n" );
		}
#endif
		resource_data_offset += value_data_size;
	}
	if( ( resource_data_offset % 4 ) != 0 )
	{
		alignment_padding_size = 4 - ( resource_data_offset % 4 );

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: alignment padding:\n",
			 function );
			libcnotify_print_data(
			 &( version_resource_data[ resource_data_offset ] ),
			 alignment_padding_size,
			 0 );
		}
#endif
		resource_data_offset += alignment_padding_size;
	}
	read_count = libwrc_version_values_read_string_file_information(
	              language_entry,
	              version_resource_data,
	              resource_data_size,
	              resource_data_offset,
	              error );

	if( read_count == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read string file information.",
		 function );

		goto on_error;
	}
	resource_data_offset += read_count;

	read_count = libwrc_version_values_read_variable_file_information(
	              language_entry,
	              version_resource_data,
	              resource_data_size,
	              resource_data_offset,
	              error );

	if( read_count == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read variable file information.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	resource_data_offset += read_count;
#endif

/* TODO */
	if( libwrc_language_entry_append_value(
	     language_entry,
	     &value_index,
	     (intptr_t *) version_values,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
		 "%s: unable to append version values.",
		 function );

		goto on_error;
	}
	version_values = NULL;

	memory_free(
	 resource_data );

	return( 1 );

on_error:
	if( value_identifier != NULL )
	{
		libfvalue_value_free(
		 &value_identifier,
		 NULL );
	}
	if( resource_data != NULL )
	{
		memory_free(
		 resource_data );
	}
	if( version_values != NULL )
	{
		libwrc_version_values_free(
		 &version_values,
		 NULL );
	}
	return( -1 );
}

/* Reads the version (resource) string file information
 * Returns number of bytes read if successful or -1 on error
 */
ssize_t libwrc_version_values_read_string_file_information(
         libwrc_language_entry_t *language_entry,
         const uint8_t *resource_data,
         size_t resource_data_size,
         size_t resource_data_offset,
         libcerror_error_t **error )
{
	uint8_t *value_identifier_string    = NULL;
	static char *function               = "libwrc_version_values_read_string_file_information";
	size_t alignment_padding_size       = 0;
	size_t calculated_value_data_size   = 0;
	size_t resource_data_start_offset   = 0;
	size_t trailing_data_size           = 0;
	size_t value_identifier_string_size = 0;
	ssize_t read_count                  = 0;
	uint16_t data_size                  = 0;
	uint16_t value_data_size            = 0;
	uint16_t value_data_type            = 0;

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
	if( resource_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid resource data.",
		 function );

		return( -1 );
	}
	if( resource_data_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid resource data size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( resource_data_offset >= resource_data_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid resource data offset value out of bounds.",
		 function );

		return( -1 );
	}
	if( ( resource_data_offset + 2 ) > resource_data_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: invalid resource data value too small.",
		 function );

		return( -1 );
	}
	resource_data_start_offset = resource_data_offset;

	byte_stream_copy_to_uint16_little_endian(
	 &( resource_data[ resource_data_offset ] ),
	 data_size );

	resource_data_offset += 2;

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: data size\t\t: %" PRIu16 "\n",
		 function,
		 data_size );
	}
#endif
	if( data_size != 0 )
	{
		if( ( data_size < 8 )
		 || ( data_size > ( resource_data_size - ( resource_data_offset - 2 ) ) ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: data size value out of bounds.",
			 function );

			return( -1 );
		}
		byte_stream_copy_to_uint16_little_endian(
		 &( resource_data[ resource_data_offset ] ),
		 value_data_size );

		resource_data_offset += 2;

		byte_stream_copy_to_uint16_little_endian(
		 &( resource_data[ resource_data_offset ] ),
		 value_data_type );

		resource_data_offset += 2;

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: value data size\t: %" PRIu16 "\n",
			 function,
			 value_data_size );

			libcnotify_printf(
			 "%s: value data type\t: %" PRIu16 "\n",
			 function,
			 value_data_type );
		}
#endif
		value_identifier_string      = (uint8_t *) &( resource_data[ resource_data_offset ] );
		value_identifier_string_size = 0;

		while( ( resource_data_offset + 2 ) < resource_data_size )
		{
			value_identifier_string_size += 2;

			if( ( resource_data[ resource_data_offset ] == 0 )
			 && ( resource_data[ resource_data_offset + 1 ] == 0 ) )
			{
				resource_data_offset += 2;

				break;
			}
			resource_data_offset += 2;
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: value identifier string data:\n",
			 function );
			libcnotify_print_data(
			 value_identifier_string,
			 value_identifier_string_size,
			 0 );
		}
#endif
/* TODO convert string */
		if( ( resource_data_offset % 4 ) != 0 )
		{
			alignment_padding_size = 4 - ( resource_data_offset % 4 );

#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "%s: alignment padding:\n",
				 function );
				libcnotify_print_data(
				 &( resource_data[ resource_data_offset ] ),
				 alignment_padding_size,
				 0 );
			}
#endif
			resource_data_offset += alignment_padding_size;
		}
		if( value_data_type == 1 )
		{
/* TODO check value_data_size == 0 ? */
			read_count = libwrc_version_values_read_string_table(
				      language_entry,
				      resource_data,
				      resource_data_size,
				      resource_data_offset,
				      error );

			if( read_count == -1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_READ_FAILED,
				 "%s: unable to read string table.",
				 function );

				return( -1 );
			}
			resource_data_offset += read_count;
		}
/* TODO print unsupported type warning */
		calculated_value_data_size = resource_data_offset - resource_data_start_offset;

		if( calculated_value_data_size < data_size )
		{
			trailing_data_size = data_size - trailing_data_size;

#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "%s: trailing data:\n",
				 function );
				libcnotify_print_data(
				 &( resource_data[ resource_data_offset ] ),
				 trailing_data_size,
				 0 );
			}
#endif
			resource_data_offset += trailing_data_size;
		}
	}
	return( (ssize_t) data_size );
}

/* Reads the version (resource) string table
 * Returns number of bytes read if successful or -1 on error
 */
ssize_t libwrc_version_values_read_string_table(
         libwrc_language_entry_t *language_entry,
         const uint8_t *resource_data,
         size_t resource_data_size,
         size_t resource_data_offset,
         libcerror_error_t **error )
{
	uint8_t *value_identifier_string    = NULL;
	static char *function               = "libwrc_version_values_read_string_table";
	size_t alignment_padding_size       = 0;
	size_t calculated_value_data_size   = 0;
	size_t resource_data_start_offset   = 0;
	size_t trailing_data_size           = 0;
	size_t value_identifier_string_size = 0;
	ssize_t read_count                  = 0;
	uint16_t data_size                  = 0;
	uint16_t value_data_size            = 0;
	uint16_t value_data_type            = 0;

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
	if( resource_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid resource data.",
		 function );

		return( -1 );
	}
	if( resource_data_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid resource data size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( resource_data_offset >= resource_data_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid resource data offset value out of bounds.",
		 function );

		return( -1 );
	}
	if( ( resource_data_offset + 2 ) > resource_data_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: invalid resource data value too small.",
		 function );

		return( -1 );
	}
	resource_data_start_offset = resource_data_offset;

	byte_stream_copy_to_uint16_little_endian(
	 &( resource_data[ resource_data_offset ] ),
	 data_size );

	resource_data_offset += 2;

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: data size\t\t\t: %" PRIu16 "\n",
		 function,
		 data_size );
	}
#endif
	if( data_size != 0 )
	{
		if( ( data_size < 8 )
		 || ( data_size > ( resource_data_size - ( resource_data_offset - 2 ) ) ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: data size value out of bounds.",
			 function );

			return( -1 );
		}
		byte_stream_copy_to_uint16_little_endian(
		 &( resource_data[ resource_data_offset ] ),
		 value_data_size );

		resource_data_offset += 2;

		byte_stream_copy_to_uint16_little_endian(
		 &( resource_data[ resource_data_offset ] ),
		 value_data_type );

		resource_data_offset += 2;

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: value data size\t\t: %" PRIu16 "\n",
			 function,
			 value_data_size );

			libcnotify_printf(
			 "%s: value data type\t\t: %" PRIu16 "\n",
			 function,
			 value_data_type );
		}
#endif
		value_identifier_string      = (uint8_t *) &( resource_data[ resource_data_offset ] );
		value_identifier_string_size = 0;

		while( ( resource_data_offset + 2 ) < resource_data_size )
		{
			value_identifier_string_size += 2;

			if( ( resource_data[ resource_data_offset ] == 0 )
			 && ( resource_data[ resource_data_offset + 1 ] == 0 ) )
			{
				resource_data_offset += 2;

				break;
			}
			resource_data_offset += 2;
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: value identifier string data:\n",
			 function );
			libcnotify_print_data(
			 value_identifier_string,
			 value_identifier_string_size,
			 0 );
		}
#endif
/* TODO convert string */
		if( ( resource_data_offset % 4 ) != 0 )
		{
			alignment_padding_size = 4 - ( resource_data_offset % 4 );

#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "%s: alignment padding:\n",
				 function );
				libcnotify_print_data(
				 &( resource_data[ resource_data_offset ] ),
				 alignment_padding_size,
				 0 );
			}
#endif
			resource_data_offset += alignment_padding_size;
		}
		if( value_data_type == 0 )
		{
/* TODO check value data size is in bounds */
#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "%s: value data:\n",
				 function );
				libcnotify_print_data(
				 &( resource_data[ resource_data_offset ] ),
				 value_data_size,
				 0 );
			}
#endif
			resource_data_offset += value_data_size;
		}
		else if( value_data_type == 1 )
		{
/* TODO check value_data_size == 0 ? */
			while( ( resource_data_offset + 2 ) < ( resource_data_start_offset + data_size ) )
			{
				read_count = libwrc_version_values_read_string(
					      language_entry,
					      resource_data,
					      resource_data_size,
					      resource_data_offset,
					      error );

				if( read_count == -1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_IO,
					 LIBCERROR_IO_ERROR_READ_FAILED,
					 "%s: unable to read string.",
					 function );

					return( -1 );
				}
				else if( read_count == 0 )
				{
					break;
				}
				resource_data_offset += read_count;

				if( ( resource_data_offset % 4 ) != 0 )
				{
					alignment_padding_size = 4 - ( resource_data_offset % 4 );

					if( ( resource_data_offset + alignment_padding_size ) < ( resource_data_start_offset + data_size ) )
					{
#if defined( HAVE_DEBUG_OUTPUT )
						if( libcnotify_verbose != 0 )
						{
							libcnotify_printf(
							 "%s: alignment padding:\n",
							 function );
							libcnotify_print_data(
							 &( resource_data[ resource_data_offset ] ),
							 alignment_padding_size,
							 0 );
						}
#endif
						resource_data_offset += alignment_padding_size;
					}
				}
			}
		}
/* TODO print unsupported type warning */
		calculated_value_data_size = resource_data_offset - resource_data_start_offset;

		if( calculated_value_data_size < data_size )
		{
			trailing_data_size = data_size - calculated_value_data_size;

#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "%s: trailing data:\n",
				 function );
				libcnotify_print_data(
				 &( resource_data[ resource_data_offset ] ),
				 trailing_data_size,
				 0 );
			}
#endif
			resource_data_offset += trailing_data_size;
		}
	}
	return( (ssize_t) data_size );
}

/* Reads the version (resource) string
 * Returns number of bytes read if successful or -1 on error
 */
ssize_t libwrc_version_values_read_string(
         libwrc_language_entry_t *language_entry,
         const uint8_t *resource_data,
         size_t resource_data_size,
         size_t resource_data_offset,
         libcerror_error_t **error )
{
	static char *function             = "libwrc_version_values_read_string";
	size_t alignment_padding_size     = 0;
	size_t value_string_size          = 0;
	uint16_t data_size                = 0;
	uint16_t value_data_size          = 0;
	uint16_t value_data_type          = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	size_t resource_data_start_offset = 0;
	size_t trailing_data_size         = 0;
	size_t value_string_offset        = 0;
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
	if( resource_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid resource data.",
		 function );

		return( -1 );
	}
	if( resource_data_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid resource data size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( resource_data_offset >= resource_data_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid resource data offset value out of bounds.",
		 function );

		return( -1 );
	}
	if( ( resource_data_offset + 2 ) > resource_data_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: invalid resource data value too small.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	resource_data_start_offset = resource_data_offset;
#endif

	byte_stream_copy_to_uint16_little_endian(
	 &( resource_data[ resource_data_offset ] ),
	 data_size );

	resource_data_offset += 2;

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: data size\t\t\t\t: %" PRIu16 "\n",
		 function,
		 data_size );
	}
#endif
	if( data_size != 0 )
	{
		if( ( data_size < 8 )
		 || ( data_size > ( resource_data_size - ( resource_data_offset - 2 ) ) ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: data size value out of bounds.",
			 function );

			return( -1 );
		}
		byte_stream_copy_to_uint16_little_endian(
		 &( resource_data[ resource_data_offset ] ),
		 value_data_size );

		resource_data_offset += 2;

		byte_stream_copy_to_uint16_little_endian(
		 &( resource_data[ resource_data_offset ] ),
		 value_data_type );

		resource_data_offset += 2;

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: value data size\t\t\t: %" PRIu16 "\n",
			 function,
			 value_data_size );

			libcnotify_printf(
			 "%s: value data type\t\t\t: %" PRIu16 "\n",
			 function,
			 value_data_type );
		}
#endif
/* TODO check value_data_size == 0 ? */
/* TODO handle value_data_type != 1 */
#if defined( HAVE_DEBUG_OUTPUT )
		value_string_offset = resource_data_offset;
#endif

		value_string_size = 0;

		while( ( resource_data_offset + 2 ) < resource_data_size )
		{
			value_string_size += 2;

			if( ( resource_data[ resource_data_offset ] == 0 )
			 && ( resource_data[ resource_data_offset + 1 ] == 0 ) )
			{
				resource_data_offset += 2;

				break;
			}
			resource_data_offset += 2;
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: value identifier string data:\n",
			 function );
			libcnotify_print_data(
			 &( resource_data[ value_string_offset ] ),
			 value_string_size,
			 0 );
		}
#endif
/* TODO convert string */
		if( ( resource_data_offset % 4 ) != 0 )
		{
			alignment_padding_size = 4 - ( resource_data_offset % 4 );

#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "%s: alignment padding:\n",
				 function );
				libcnotify_print_data(
				 &( resource_data[ resource_data_offset ] ),
				 alignment_padding_size,
				 0 );
			}
#endif
			resource_data_offset += alignment_padding_size;
		}
#if defined( HAVE_DEBUG_OUTPUT )
		value_string_offset = resource_data_offset;
		value_string_size   = 0;

		while( ( resource_data_offset + 2 ) < resource_data_size )
		{
			value_string_size += 2;

			if( ( resource_data[ resource_data_offset ] == 0 )
			 && ( resource_data[ resource_data_offset + 1 ] == 0 ) )
			{
				resource_data_offset += 2;

				break;
			}
			resource_data_offset += 2;
		}
#endif
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: value string data:\n",
			 function );
			libcnotify_print_data(
			 &( resource_data[ value_string_offset ] ),
			 value_string_size,
			 0 );
		}
#endif
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			trailing_data_size = resource_data_offset - resource_data_start_offset;

			if( trailing_data_size < data_size )
			{
				trailing_data_size = data_size - trailing_data_size;

				libcnotify_printf(
				 "%s: trailing data:\n",
				 function );
				libcnotify_print_data(
				 &( resource_data[ resource_data_offset ] ),
				 trailing_data_size,
				 0 );
			}
		}
#endif
	}
	return( (ssize_t) data_size );
}

/* Reads the version (resource) variable file information
 * Returns number of bytes read if successful or -1 on error
 */
ssize_t libwrc_version_values_read_variable_file_information(
         libwrc_language_entry_t *language_entry,
         const uint8_t *resource_data,
         size_t resource_data_size,
         size_t resource_data_offset,
         libcerror_error_t **error )
{
	static char *function             = "libwrc_version_values_read_variable_file_information";
	size_t alignment_padding_size     = 0;
	size_t resource_data_start_offset = 0;
	size_t value_string_size          = 0;
	ssize_t read_count                = 0;
	uint16_t data_size                = 0;
	uint16_t value_data_size          = 0;
	uint16_t value_data_type          = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	size_t trailing_data_size         = 0;
	size_t value_string_offset        = 0;
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
	if( resource_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid resource data.",
		 function );

		return( -1 );
	}
	if( resource_data_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid resource data size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( resource_data_offset >= resource_data_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid resource data offset value out of bounds.",
		 function );

		return( -1 );
	}
	if( ( resource_data_offset + 2 ) > resource_data_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: invalid resource data value too small.",
		 function );

		return( -1 );
	}
	resource_data_start_offset = resource_data_offset;

	byte_stream_copy_to_uint16_little_endian(
	 &( resource_data[ resource_data_offset ] ),
	 data_size );

	resource_data_offset += 2;

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: data size\t\t: %" PRIu16 "\n",
		 function,
		 data_size );
	}
#endif
	if( data_size != 0 )
	{
		if( ( data_size < 8 )
		 || ( data_size > ( resource_data_size - ( resource_data_offset - 2 ) ) ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: data size value out of bounds.",
			 function );

			return( -1 );
		}
		byte_stream_copy_to_uint16_little_endian(
		 &( resource_data[ resource_data_offset ] ),
		 value_data_size );

		resource_data_offset += 2;

		byte_stream_copy_to_uint16_little_endian(
		 &( resource_data[ resource_data_offset ] ),
		 value_data_type );

		resource_data_offset += 2;

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: value data size\t: %" PRIu16 "\n",
			 function,
			 value_data_size );

			libcnotify_printf(
			 "%s: value data type\t: %" PRIu16 "\n",
			 function,
			 value_data_type );
		}
#endif
/* TODO check value_data_size == 0 ? */
/* TODO handle value_data_type != 1 */
#if defined( HAVE_DEBUG_OUTPUT )
		value_string_offset = resource_data_offset;
#endif

		value_string_size  = 0;

		while( ( resource_data_offset + 2 ) < resource_data_size )
		{
			value_string_size += 2;

			if( ( resource_data[ resource_data_offset ] == 0 )
			 && ( resource_data[ resource_data_offset + 1 ] == 0 ) )
			{
				resource_data_offset += 2;

				break;
			}
			resource_data_offset += 2;
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: value identifier string data:\n",
			 function );
			libcnotify_print_data(
			 &( resource_data[ value_string_offset ] ),
			 value_string_size,
			 0 );
		}
#endif
/* TODO convert string */
		if( ( resource_data_offset % 4 ) != 0 )
		{
			alignment_padding_size = 4 - ( resource_data_offset % 4 );

#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "%s: alignment padding:\n",
				 function );
				libcnotify_print_data(
				 &( resource_data[ resource_data_offset ] ),
				 alignment_padding_size,
				 0 );
			}
#endif
			resource_data_offset += alignment_padding_size;
		}
		while( ( resource_data_offset + 2 ) < ( resource_data_start_offset + data_size ) )
		{
			read_count = libwrc_version_values_read_variable(
				      language_entry,
				      resource_data,
				      resource_data_size,
				      resource_data_offset,
				      error );

			if( read_count == -1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_READ_FAILED,
				 "%s: unable to read variable.",
				 function );

				return( -1 );
			}
			else if( read_count == 0 )
			{
				break;
			}
			resource_data_offset += read_count;
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			trailing_data_size = resource_data_offset - resource_data_start_offset;

			if( trailing_data_size < data_size )
			{
				trailing_data_size = data_size - trailing_data_size;

				libcnotify_printf(
				 "%s: trailing data:\n",
				 function );
				libcnotify_print_data(
				 &( resource_data[ resource_data_offset ] ),
				 trailing_data_size,
				 0 );
			}
		}
#endif
	}
	return( (ssize_t) data_size );
}

/* Reads the version (resource) variable
 * Returns number of bytes read if successful or -1 on error
 */
ssize_t libwrc_version_values_read_variable(
         libwrc_language_entry_t *language_entry,
         const uint8_t *resource_data,
         size_t resource_data_size,
         size_t resource_data_offset,
         libcerror_error_t **error )
{
	static char *function             = "libwrc_version_values_read_variable";
	size_t alignment_padding_size     = 0;
	size_t value_string_size          = 0;
	uint16_t data_size                = 0;
	uint16_t value_data_size          = 0;
	uint16_t value_data_type          = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	size_t resource_data_start_offset = 0;
	size_t trailing_data_size         = 0;
	size_t value_string_offset        = 0;
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
	if( resource_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid resource data.",
		 function );

		return( -1 );
	}
	if( resource_data_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid resource data size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( resource_data_offset >= resource_data_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid resource data offset value out of bounds.",
		 function );

		return( -1 );
	}
	if( ( resource_data_offset + 2 ) > resource_data_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: invalid resource data value too small.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	resource_data_start_offset = resource_data_offset;
#endif

	byte_stream_copy_to_uint16_little_endian(
	 &( resource_data[ resource_data_offset ] ),
	 data_size );

	resource_data_offset += 2;

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: data size\t\t\t\t: %" PRIu16 "\n",
		 function,
		 data_size );
	}
#endif
	if( data_size != 0 )
	{
		if( ( data_size < 8 )
		 || ( data_size > ( resource_data_size - ( resource_data_offset - 2 ) ) ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: data size value out of bounds.",
			 function );

			return( -1 );
		}
		byte_stream_copy_to_uint16_little_endian(
		 &( resource_data[ resource_data_offset ] ),
		 value_data_size );

		resource_data_offset += 2;

		byte_stream_copy_to_uint16_little_endian(
		 &( resource_data[ resource_data_offset ] ),
		 value_data_type );

		resource_data_offset += 2;

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: value data size\t\t\t: %" PRIu16 "\n",
			 function,
			 value_data_size );

			libcnotify_printf(
			 "%s: value data type\t\t\t: %" PRIu16 "\n",
			 function,
			 value_data_type );
		}
#endif
/* TODO check value_data_size == 0 ? */
/* TODO handle value_data_type != 1 */
#if defined( HAVE_DEBUG_OUTPUT )
		value_string_offset = resource_data_offset;
#endif

		value_string_size = 0;

		while( ( resource_data_offset + 2 ) < resource_data_size )
		{
			value_string_size += 2;

			if( ( resource_data[ resource_data_offset ] == 0 )
			 && ( resource_data[ resource_data_offset + 1 ] == 0 ) )
			{
				resource_data_offset += 2;

				break;
			}
			resource_data_offset += 2;
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: value identifier string data:\n",
			 function );
			libcnotify_print_data(
			 &( resource_data[ value_string_offset ] ),
			 value_string_size,
			 0 );
		}
#endif
/* TODO convert string */
		if( ( resource_data_offset % 4 ) != 0 )
		{
			alignment_padding_size = 4 - ( resource_data_offset % 4 );

#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "%s: alignment padding:\n",
				 function );
				libcnotify_print_data(
				 &( resource_data[ resource_data_offset ] ),
				 alignment_padding_size,
				 0 );
			}
#endif
			resource_data_offset += alignment_padding_size;
		}
/* TODO */

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			trailing_data_size = resource_data_offset - resource_data_start_offset;

			if( trailing_data_size < data_size )
			{
				trailing_data_size = data_size - trailing_data_size;

				libcnotify_printf(
				 "%s: trailing data:\n",
				 function );
				libcnotify_print_data(
				 &( resource_data[ resource_data_offset ] ),
				 trailing_data_size,
				 0 );
			}
		}
#endif
	}
	return( (ssize_t) data_size );
}

/* Retrieves the file version
 * Returns 1 if successful or -1 on error
 */
int libwrc_version_values_get_file_version(
     libwrc_version_values_t *version_values,
     uint64_t *file_version,
     libcerror_error_t **error )
{
	static char *function = "libwrc_version_values_get_file_version";

	if( version_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid version values.",
		 function );

		return( -1 );
	}
	if( file_version == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file version.",
		 function );

		return( -1 );
	}
	*file_version = version_values->file_version;

	return( 1 );
}

/* Retrieves the product version
 * Returns 1 if successful or -1 on error
 */
int libwrc_version_values_get_product_version(
     libwrc_version_values_t *version_values,
     uint64_t *product_version,
     libcerror_error_t **error )
{
	static char *function = "libwrc_version_values_get_product_version";

	if( version_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid version values.",
		 function );

		return( -1 );
	}
	if( product_version == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid product version.",
		 function );

		return( -1 );
	}
	*product_version = version_values->product_version;

	return( 1 );
}

