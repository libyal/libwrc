/*
 * String table (VERSIONINFO) resource functions
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

#include "libwrc_debug.h"
#include "libwrc_definitions.h"
#include "libwrc_libcerror.h"
#include "libwrc_libcnotify.h"
#include "libwrc_libuna.h"
#include "libwrc_version_information_resource.h"

#include "wrc_version_information_resource.h"

uint8_t libwrc_version_information_resource_signature[ 32 ] = {
	'V', 0, 'S', 0, '_', 0, 'V', 0, 'E', 0, 'R', 0, 'S', 0, 'I', 0,
	'O', 0, 'N', 0, '_', 0, 'I', 0, 'N', 0, 'F', 0, 'O', 0, 0, 0 };

/* Creates a version information resource
 * Make sure the value version_information_resource is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libwrc_version_information_resource_initialize(
     libwrc_version_information_resource_t **version_information_resource,
     libcerror_error_t **error )
{
	libwrc_internal_version_information_resource_t *internal_version_information_resource = NULL;
	static char *function                                                                 = "libwrc_version_information_resource_initialize";

	if( version_information_resource == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid version information resource.",
		 function );

		return( -1 );
	}
	if( *version_information_resource != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid version information resource value already set.",
		 function );

		return( -1 );
	}
	internal_version_information_resource = memory_allocate_structure(
	                                         libwrc_internal_version_information_resource_t );

	if( internal_version_information_resource == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create version information resource.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     internal_version_information_resource,
	     0,
	     sizeof( libwrc_internal_version_information_resource_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear version information resource.",
		 function );

		goto on_error;
	}
	*version_information_resource = (libwrc_version_information_resource_t *) internal_version_information_resource;

	return( 1 );

on_error:
	if( internal_version_information_resource != NULL )
	{
		memory_free(
		 internal_version_information_resource );
	}
	return( -1 );
}

/* Frees a version information resource
 * Returns 1 if successful or -1 on error
 */
int libwrc_version_information_resource_free(
     libwrc_version_information_resource_t **version_information_resource,
     libcerror_error_t **error )
{
	libwrc_internal_version_information_resource_t *internal_version_information_resource = NULL;
	static char *function                                                                 = "libwrc_version_information_resource_free";

	if( version_information_resource == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid version information resource.",
		 function );

		return( -1 );
	}
	if( *version_information_resource != NULL )
	{
		internal_version_information_resource = (libwrc_internal_version_information_resource_t *) *version_information_resource;
		*version_information_resource         = NULL;

		memory_free(
		 internal_version_information_resource );
	}
	return( 1 );
}

/* Reads the version information resource string file information
 * Returns number of bytes read if successful or -1 on error
 */
ssize_t libwrc_internal_version_information_resource_read_string_file_information(
         libwrc_internal_version_information_resource_t *internal_version_information_resource,
         const uint8_t *data,
         size_t data_size,
         size_t data_offset,
         libcerror_error_t **error )
{
	const uint8_t *value_identifier_string = NULL;
	static char *function                  = "libwrc_internal_version_information_resource_read_string_file_information";
	size_t alignment_padding_size          = 0;
	size_t calculated_value_data_size      = 0;
	size_t data_start_offset               = 0;
	size_t trailing_data_size              = 0;
	size_t value_identifier_string_size    = 0;
	ssize_t read_count                     = 0;
	uint16_t string_data_size              = 0;
	uint16_t value_data_size               = 0;
	uint16_t value_data_type               = 0;

	if( internal_version_information_resource == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid version information resource.",
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
	if( data_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid data size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( data_offset >= data_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid data offset value out of bounds.",
		 function );

		return( -1 );
	}
	if( ( data_offset + 2 ) > data_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: invalid data value too small.",
		 function );

		return( -1 );
	}
	data_start_offset = data_offset;

	byte_stream_copy_to_uint16_little_endian(
	 &( data[ data_offset ] ),
	 string_data_size );

	data_offset += 2;

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: data size\t\t: %" PRIu16 "\n",
		 function,
		 string_data_size );
	}
#endif
	if( string_data_size != 0 )
	{
		if( ( string_data_size < 8 )
		 || ( string_data_size > ( data_size - ( data_offset - 2 ) ) ) )
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
		 &( data[ data_offset ] ),
		 value_data_size );

		data_offset += 2;

		byte_stream_copy_to_uint16_little_endian(
		 &( data[ data_offset ] ),
		 value_data_type );

		data_offset += 2;

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
		value_identifier_string      = &( data[ data_offset ] );
		value_identifier_string_size = 0;

		while( ( data_offset + 2 ) < data_size )
		{
			value_identifier_string_size += 2;

			if( ( data[ data_offset ] == 0 )
			 && ( data[ data_offset + 1 ] == 0 ) )
			{
				data_offset += 2;

				break;
			}
			data_offset += 2;
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
		if( ( data_offset % 4 ) != 0 )
		{
			alignment_padding_size = 4 - ( data_offset % 4 );

			if( alignment_padding_size > ( data_size - data_offset ) )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
				 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
				 "%s: invalid data size value too small.",
				 function );

				return( -1 );
			}
#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "%s: alignment padding:\n",
				 function );
				libcnotify_print_data(
				 &( data[ data_offset ] ),
				 alignment_padding_size,
				 0 );
			}
#endif
			data_offset += alignment_padding_size;
		}
		if( value_data_type == 1 )
		{
/* TODO check value_data_size == 0 ? */
			read_count = libwrc_internal_version_information_resource_read_string_table(
				      internal_version_information_resource,
				      data,
				      data_size,
				      data_offset,
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
			data_offset += read_count;
		}
/* TODO print unsupported type warning */
		calculated_value_data_size = data_offset - data_start_offset;

		if( calculated_value_data_size < string_data_size )
		{
			trailing_data_size = string_data_size - trailing_data_size;

#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "%s: trailing data:\n",
				 function );
				libcnotify_print_data(
				 &( data[ data_offset ] ),
				 trailing_data_size,
				 0 );
			}
#endif
			data_offset += trailing_data_size;
		}
	}
	return( (ssize_t) string_data_size );
}

/* Reads the version information resource string table
 * Returns number of bytes read if successful or -1 on error
 */
ssize_t libwrc_internal_version_information_resource_read_string_table(
         libwrc_internal_version_information_resource_t *internal_version_information_resource,
         const uint8_t *data,
         size_t data_size,
         size_t data_offset,
         libcerror_error_t **error )
{
	const uint8_t *value_identifier_string = NULL;
	static char *function                  = "libwrc_internal_version_information_resource_read_string_table";
	size_t alignment_padding_size          = 0;
	size_t calculated_value_data_size      = 0;
	size_t data_start_offset               = 0;
	size_t trailing_data_size              = 0;
	size_t value_identifier_string_size    = 0;
	ssize_t read_count                     = 0;
	uint16_t string_data_size              = 0;
	uint16_t value_data_size               = 0;
	uint16_t value_data_type               = 0;

	if( internal_version_information_resource == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid version information resource.",
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
	if( data_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid data size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( data_offset >= data_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid data offset value out of bounds.",
		 function );

		return( -1 );
	}
	if( ( data_offset + 2 ) > data_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: invalid data value too small.",
		 function );

		return( -1 );
	}
	data_start_offset = data_offset;

	byte_stream_copy_to_uint16_little_endian(
	 &( data[ data_offset ] ),
	 string_data_size );

	data_offset += 2;

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: data size\t\t\t: %" PRIu16 "\n",
		 function,
		 string_data_size );
	}
#endif
	if( string_data_size != 0 )
	{
		if( ( string_data_size < 8 )
		 || ( string_data_size > ( data_size - ( data_offset - 2 ) ) ) )
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
		 &( data[ data_offset ] ),
		 value_data_size );

		data_offset += 2;

		byte_stream_copy_to_uint16_little_endian(
		 &( data[ data_offset ] ),
		 value_data_type );

		data_offset += 2;

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
		value_identifier_string      = &( data[ data_offset ] );
		value_identifier_string_size = 0;

		while( ( data_offset + 2 ) < data_size )
		{
			value_identifier_string_size += 2;

			if( ( data[ data_offset ] == 0 )
			 && ( data[ data_offset + 1 ] == 0 ) )
			{
				data_offset += 2;

				break;
			}
			data_offset += 2;
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
		if( ( data_offset % 4 ) != 0 )
		{
			alignment_padding_size = 4 - ( data_offset % 4 );

			if( alignment_padding_size > ( data_size - data_offset ) )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
				 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
				 "%s: invalid data size value too small.",
				 function );

				return( -1 );
			}
#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "%s: alignment padding:\n",
				 function );
				libcnotify_print_data(
				 &( data[ data_offset ] ),
				 alignment_padding_size,
				 0 );
			}
#endif
			data_offset += alignment_padding_size;
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
				 &( data[ data_offset ] ),
				 value_data_size,
				 0 );
			}
#endif
			data_offset += value_data_size;
		}
		else if( value_data_type == 1 )
		{
/* TODO check value_data_size == 0 ? */
			while( ( data_offset + 2 ) < ( data_start_offset + string_data_size ) )
			{
				read_count = libwrc_internal_version_information_resource_read_string(
					      internal_version_information_resource,
					      data,
					      data_size,
					      data_offset,
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
				data_offset += read_count;

				if( ( data_offset % 4 ) != 0 )
				{
					alignment_padding_size = 4 - ( data_offset % 4 );

					if( ( data_offset + alignment_padding_size ) < ( data_start_offset + string_data_size ) )
					{
						if( alignment_padding_size > ( data_size - data_offset ) )
						{
							libcerror_error_set(
							 error,
							 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
							 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
							 "%s: invalid data size value too small.",
							 function );

							return( -1 );
						}
#if defined( HAVE_DEBUG_OUTPUT )
						if( libcnotify_verbose != 0 )
						{
							libcnotify_printf(
							 "%s: alignment padding:\n",
							 function );
							libcnotify_print_data(
							 &( data[ data_offset ] ),
							 alignment_padding_size,
							 0 );
						}
#endif
						data_offset += alignment_padding_size;
					}
				}
			}
		}
/* TODO print unsupported type warning */
		calculated_value_data_size = data_offset - data_start_offset;

		if( calculated_value_data_size < string_data_size )
		{
			trailing_data_size = string_data_size - calculated_value_data_size;

#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "%s: trailing data:\n",
				 function );
				libcnotify_print_data(
				 &( data[ data_offset ] ),
				 trailing_data_size,
				 0 );
			}
#endif
			data_offset += trailing_data_size;
		}
	}
	return( (ssize_t) string_data_size );
}

/* Reads the version information resource string
 * Returns number of bytes read if successful or -1 on error
 */
ssize_t libwrc_internal_version_information_resource_read_string(
         libwrc_internal_version_information_resource_t *internal_version_information_resource,
         const uint8_t *data,
         size_t data_size,
         size_t data_offset,
         libcerror_error_t **error )
{
	static char *function         = "libwrc_internal_version_information_resource_read_string";
	size_t alignment_padding_size = 0;
	size_t value_string_size      = 0;
	uint16_t string_data_size     = 0;
	uint16_t value_data_size      = 0;
	uint16_t value_data_type      = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	size_t data_start_offset      = 0;
	size_t trailing_data_size     = 0;
	size_t value_string_offset    = 0;
#endif

	if( internal_version_information_resource == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid version information resource.",
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
	if( data_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid data size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( data_offset >= data_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid data offset value out of bounds.",
		 function );

		return( -1 );
	}
	if( ( data_offset + 2 ) > data_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: invalid data value too small.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	data_start_offset = data_offset;
#endif

	byte_stream_copy_to_uint16_little_endian(
	 &( data[ data_offset ] ),
	 string_data_size );

	data_offset += 2;

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: data size\t\t\t\t: %" PRIu16 "\n",
		 function,
		 string_data_size );
	}
#endif
	if( string_data_size != 0 )
	{
		if( ( string_data_size < 8 )
		 || ( string_data_size > ( data_size - ( data_offset - 2 ) ) ) )
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
		 &( data[ data_offset ] ),
		 value_data_size );

		data_offset += 2;

		byte_stream_copy_to_uint16_little_endian(
		 &( data[ data_offset ] ),
		 value_data_type );

		data_offset += 2;

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
		value_string_offset = data_offset;
#endif

		value_string_size = 0;

		while( ( data_offset + 2 ) < data_size )
		{
			value_string_size += 2;

			if( ( data[ data_offset ] == 0 )
			 && ( data[ data_offset + 1 ] == 0 ) )
			{
				data_offset += 2;

				break;
			}
			data_offset += 2;
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: value identifier string data:\n",
			 function );
			libcnotify_print_data(
			 &( data[ value_string_offset ] ),
			 value_string_size,
			 0 );
		}
#endif
/* TODO convert string */
		if( ( data_offset % 4 ) != 0 )
		{
			if( alignment_padding_size > ( data_size - data_offset ) )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
				 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
				 "%s: invalid data size value too small.",
				 function );

				return( -1 );
			}
			alignment_padding_size = 4 - ( data_offset % 4 );

#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "%s: alignment padding:\n",
				 function );
				libcnotify_print_data(
				 &( data[ data_offset ] ),
				 alignment_padding_size,
				 0 );
			}
#endif
			data_offset += alignment_padding_size;
		}
#if defined( HAVE_DEBUG_OUTPUT )
		value_string_offset = data_offset;
		value_string_size   = 0;

		while( ( data_offset + 2 ) < data_size )
		{
			value_string_size += 2;

			if( ( data[ data_offset ] == 0 )
			 && ( data[ data_offset + 1 ] == 0 ) )
			{
				data_offset += 2;

				break;
			}
			data_offset += 2;
		}
#endif
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: value string data:\n",
			 function );
			libcnotify_print_data(
			 &( data[ value_string_offset ] ),
			 value_string_size,
			 0 );
		}
#endif
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			trailing_data_size = data_offset - data_start_offset;

			if( trailing_data_size < string_data_size )
			{
				trailing_data_size = string_data_size - trailing_data_size;

				libcnotify_printf(
				 "%s: trailing data:\n",
				 function );
				libcnotify_print_data(
				 &( data[ data_offset ] ),
				 trailing_data_size,
				 0 );
			}
		}
#endif
	}
	return( (ssize_t) string_data_size );
}

/* Reads the version information resource variable file information
 * Returns number of bytes read if successful or -1 on error
 */
ssize_t libwrc_internal_version_information_resource_read_variable_file_information(
         libwrc_internal_version_information_resource_t *internal_version_information_resource,
         const uint8_t *data,
         size_t data_size,
         size_t data_offset,
         libcerror_error_t **error )
{
	static char *function         = "libwrc_internal_version_information_resource_read_variable_file_information";
	size_t alignment_padding_size = 0;
	size_t data_start_offset      = 0;
	size_t value_string_size      = 0;
	ssize_t read_count            = 0;
	uint16_t string_data_size     = 0;
	uint16_t value_data_size      = 0;
	uint16_t value_data_type      = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	size_t trailing_data_size     = 0;
	size_t value_string_offset    = 0;
#endif

	if( internal_version_information_resource == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid version information resource.",
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
	if( data_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid data size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( data_offset >= data_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid data offset value out of bounds.",
		 function );

		return( -1 );
	}
	if( ( data_offset + 2 ) > data_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: invalid data value too small.",
		 function );

		return( -1 );
	}
	data_start_offset = data_offset;

	byte_stream_copy_to_uint16_little_endian(
	 &( data[ data_offset ] ),
	 string_data_size );

	data_offset += 2;

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: data size\t\t: %" PRIu16 "\n",
		 function,
		 string_data_size );
	}
#endif
	if( string_data_size != 0 )
	{
		if( ( string_data_size < 8 )
		 || ( string_data_size > ( data_size - ( data_offset - 2 ) ) ) )
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
		 &( data[ data_offset ] ),
		 value_data_size );

		data_offset += 2;

		byte_stream_copy_to_uint16_little_endian(
		 &( data[ data_offset ] ),
		 value_data_type );

		data_offset += 2;

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
		value_string_offset = data_offset;
#endif

		value_string_size  = 0;

		while( ( data_offset + 2 ) < data_size )
		{
			value_string_size += 2;

			if( ( data[ data_offset ] == 0 )
			 && ( data[ data_offset + 1 ] == 0 ) )
			{
				data_offset += 2;

				break;
			}
			data_offset += 2;
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: value identifier string data:\n",
			 function );
			libcnotify_print_data(
			 &( data[ value_string_offset ] ),
			 value_string_size,
			 0 );
		}
#endif
/* TODO convert string */
		if( ( data_offset % 4 ) != 0 )
		{
			alignment_padding_size = 4 - ( data_offset % 4 );

			if( alignment_padding_size > ( data_size - data_offset ) )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
				 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
				 "%s: invalid data size value too small.",
				 function );

				return( -1 );
			}
#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "%s: alignment padding:\n",
				 function );
				libcnotify_print_data(
				 &( data[ data_offset ] ),
				 alignment_padding_size,
				 0 );
			}
#endif
			data_offset += alignment_padding_size;
		}
		while( ( data_offset + 2 ) < ( data_start_offset + string_data_size ) )
		{
			read_count = libwrc_internal_version_information_resource_read_variable(
				      internal_version_information_resource,
				      data,
				      data_size,
				      data_offset,
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
			data_offset += read_count;
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			trailing_data_size = data_offset - data_start_offset;

			if( trailing_data_size < string_data_size )
			{
				trailing_data_size = string_data_size - trailing_data_size;

				libcnotify_printf(
				 "%s: trailing data:\n",
				 function );
				libcnotify_print_data(
				 &( data[ data_offset ] ),
				 trailing_data_size,
				 0 );
			}
		}
#endif
	}
	return( (ssize_t) string_data_size );
}

/* Reads the version information resource variable
 * Returns number of bytes read if successful or -1 on error
 */
ssize_t libwrc_internal_version_information_resource_read_variable(
         libwrc_internal_version_information_resource_t *internal_version_information_resource,
         const uint8_t *data,
         size_t data_size,
         size_t data_offset,
         libcerror_error_t **error )
{
	static char *function         = "libwrc_internal_version_information_resource_read_variable";
	size_t alignment_padding_size = 0;
	size_t value_string_size      = 0;
	uint16_t string_data_size     = 0;
	uint16_t value_data_size      = 0;
	uint16_t value_data_type      = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	size_t data_start_offset      = 0;
	size_t trailing_data_size     = 0;
	size_t value_string_offset    = 0;
#endif

	if( internal_version_information_resource == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid version information resource.",
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
	if( data_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid data size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( data_offset >= data_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid data offset value out of bounds.",
		 function );

		return( -1 );
	}
	if( ( data_offset + 2 ) > data_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: invalid data value too small.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	data_start_offset = data_offset;
#endif

	byte_stream_copy_to_uint16_little_endian(
	 &( data[ data_offset ] ),
	 string_data_size );

	data_offset += 2;

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: data size\t\t\t\t: %" PRIu16 "\n",
		 function,
		 string_data_size );
	}
#endif
	if( string_data_size != 0 )
	{
		if( ( string_data_size < 8 )
		 || ( string_data_size > ( data_size - ( data_offset - 2 ) ) ) )
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
		 &( data[ data_offset ] ),
		 value_data_size );

		data_offset += 2;

		byte_stream_copy_to_uint16_little_endian(
		 &( data[ data_offset ] ),
		 value_data_type );

		data_offset += 2;

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
		value_string_offset = data_offset;
#endif

		value_string_size = 0;

		while( ( data_offset + 2 ) < data_size )
		{
			value_string_size += 2;

			if( ( data[ data_offset ] == 0 )
			 && ( data[ data_offset + 1 ] == 0 ) )
			{
				data_offset += 2;

				break;
			}
			data_offset += 2;
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: value identifier string data:\n",
			 function );
			libcnotify_print_data(
			 &( data[ value_string_offset ] ),
			 value_string_size,
			 0 );
		}
#endif
/* TODO convert string */
		if( ( data_offset % 4 ) != 0 )
		{
			alignment_padding_size = 4 - ( data_offset % 4 );

			if( alignment_padding_size > ( data_size - data_offset ) )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
				 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
				 "%s: invalid data size value too small.",
				 function );

				return( -1 );
			}
#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "%s: alignment padding:\n",
				 function );
				libcnotify_print_data(
				 &( data[ data_offset ] ),
				 alignment_padding_size,
				 0 );
			}
#endif
			data_offset += alignment_padding_size;
		}
/* TODO */

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			trailing_data_size = data_offset - data_start_offset;

			if( trailing_data_size < string_data_size )
			{
				trailing_data_size = string_data_size - trailing_data_size;

				libcnotify_printf(
				 "%s: trailing data:\n",
				 function );
				libcnotify_print_data(
				 &( data[ data_offset ] ),
				 trailing_data_size,
				 0 );
			}
		}
#endif
	}
	return( (ssize_t) string_data_size );
}

/* Reads the version information resource
 * Returns 1 if successful or -1 on error
 */
int libwrc_version_information_resource_read(
     libwrc_version_information_resource_t *version_information_resource,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error )
{
	libwrc_internal_version_information_resource_t *internal_version_information_resource = NULL;
	const uint8_t *value_identifier_string                                                = NULL;
	static char *function                                                                 = "libwrc_version_information_resource_read";
	size_t alignment_padding_size                                                         = 0;
	size_t data_offset                                                                    = 0;
	size_t value_identifier_string_size                                                   = 0;
	ssize_t read_count                                                                    = 0;
	uint32_t value_32bit                                                                  = 0;
	uint16_t resource_data_size                                                           = 0;
	uint16_t value_data_size                                                              = 0;
	uint16_t value_data_type                                                              = 0;

	if( version_information_resource == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid version information resource.",
		 function );

		return( -1 );
	}
	internal_version_information_resource = (libwrc_internal_version_information_resource_t *) version_information_resource;

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
	if( ( data_size < sizeof( wrc_version_value_header_t ) )
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
	byte_stream_copy_to_uint16_little_endian(
	 ( (wrc_version_value_header_t *) data )->size,
	 resource_data_size );

	byte_stream_copy_to_uint16_little_endian(
	 ( (wrc_version_value_header_t *) data )->value_data_size,
	 value_data_size );

	byte_stream_copy_to_uint16_little_endian(
	 ( (wrc_version_value_header_t *) data )->value_data_type,
	 value_data_type );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: size\t\t\t\t: %" PRIu16 "\n",
		 function,
		 resource_data_size );

		libcnotify_printf(
		 "%s: value data size\t\t: %" PRIu16 "\n",
		 function,
		 value_data_size );

		libcnotify_printf(
		 "%s: value data type\t\t: %" PRIu16 "\n",
		 function,
		 value_data_type );

		libcnotify_printf(
		 "\n" );
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	data_offset = sizeof( wrc_version_value_header_t );

	value_identifier_string      = &( data[ data_offset ] );
	value_identifier_string_size = 0;

	while( data_offset < ( data_size - 2 ) )
	{
		value_identifier_string_size += 2;

		if( ( data[ data_offset ] == 0 )
		 && ( data[ data_offset + 1 ] == 0 ) )
		{
			data_offset += 2;

			break;
		}
		data_offset += 2;
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
	if( ( value_identifier_string_size != 32 )
	 || ( memory_compare(
	       value_identifier_string,
	       libwrc_version_information_resource_signature,
	       32 ) != 0 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported version resource value signature.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		if( libwrc_debug_print_utf16_string_value(
		     function,
		     "value identifier\t\t",
		     value_identifier_string,
		     value_identifier_string_size,
		     LIBUNA_ENDIAN_LITTLE,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
			 "%s: unable to print UTF-16 string value.",
			 function );

			return( -1 );
		}
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	if( ( data_offset % 4 ) != 0 )
	{
		alignment_padding_size = 4 - ( data_offset % 4 );

		if( alignment_padding_size > ( data_size - data_offset ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
			 "%s: invalid data size value too small.",
			 function );

			return( -1 );
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: alignment padding:\n",
			 function );
			libcnotify_print_data(
			 &( data[ data_offset ] ),
			 alignment_padding_size,
			 0 );
		}
#endif
		data_offset += alignment_padding_size;
	}
/* TODO refactor to separate function? */
	if( value_data_size > 0 )
	{
		if( ( value_data_size < 52 )
		 || ( value_data_size > ( data_size - data_offset ) ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid value data size value out of bounds.",
			 function );

			return( -1 );
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: value data:\n",
			 function );
			libcnotify_print_data(
			 &( data[ data_offset ] ),
			 value_data_size,
			 0 );
		}
#endif
		byte_stream_copy_to_uint32_little_endian(
		 &( data[ data_offset + 8 ] ),
		 internal_version_information_resource->file_version );

		byte_stream_copy_to_uint32_little_endian(
		 &( data[ data_offset + 12 ] ),
		 value_32bit );

		internal_version_information_resource->file_version <<= 32;
		internal_version_information_resource->file_version  |= value_32bit;

		byte_stream_copy_to_uint32_little_endian(
		 &( data[ data_offset + 16 ] ),
		 internal_version_information_resource->product_version );

		byte_stream_copy_to_uint32_little_endian(
		 &( data[ data_offset + 20 ] ),
		 value_32bit );

		internal_version_information_resource->product_version <<= 32;
		internal_version_information_resource->product_version  |= value_32bit;

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			byte_stream_copy_to_uint32_little_endian(
			 &( data[ data_offset ] ),
			 value_32bit );
			libcnotify_printf(
			 "%s: signature\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );

			byte_stream_copy_to_uint32_little_endian(
			 &( data[ data_offset + 4 ] ),
			 value_32bit );
			libcnotify_printf(
			 "%s: version\t\t\t: %" PRIu32 ".%" PRIu32 "\n",
			 function,
			 value_32bit >> 16,
			 value_32bit & 0x0000ffffUL );

			byte_stream_copy_to_uint32_little_endian(
			 &( data[ data_offset + 8 ] ),
			 value_32bit );
			libcnotify_printf(
			 "%s: file version upper\t\t: %" PRIu32 ".%" PRIu32 "\n",
			 function,
			 value_32bit >> 16,
			 value_32bit & 0x0000ffffUL );

			byte_stream_copy_to_uint32_little_endian(
			 &( data[ data_offset + 12 ] ),
			 value_32bit );
			libcnotify_printf(
			 "%s: file version lower\t\t: %" PRIu32 ".%" PRIu32 "\n",
			 function,
			 value_32bit >> 16,
			 value_32bit & 0x0000ffffUL );

			byte_stream_copy_to_uint32_little_endian(
			 &( data[ data_offset + 16 ] ),
			 value_32bit );
			libcnotify_printf(
			 "%s: product version upper\t\t: %" PRIu32 ".%" PRIu32 "\n",
			 function,
			 value_32bit >> 16,
			 value_32bit & 0x0000ffffUL );

			byte_stream_copy_to_uint32_little_endian(
			 &( data[ data_offset + 20 ] ),
			 value_32bit );
			libcnotify_printf(
			 "%s: product version lower\t\t: %" PRIu32 ".%" PRIu32 "\n",
			 function,
			 value_32bit >> 16,
			 value_32bit & 0x0000ffffUL );

			byte_stream_copy_to_uint32_little_endian(
			 &( data[ data_offset + 24 ] ),
			 value_32bit );
			libcnotify_printf(
			 "%s: file flags bitmask\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );

			byte_stream_copy_to_uint32_little_endian(
			 &( data[ data_offset + 28 ] ),
			 value_32bit );
			libcnotify_printf(
			 "%s: file flags\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );

			byte_stream_copy_to_uint32_little_endian(
			 &( data[ data_offset + 32 ] ),
			 value_32bit );
			libcnotify_printf(
			 "%s: file operating system\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );

			byte_stream_copy_to_uint32_little_endian(
			 &( data[ data_offset + 36 ] ),
			 value_32bit );
			libcnotify_printf(
			 "%s: file type\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );

			byte_stream_copy_to_uint32_little_endian(
			 &( data[ data_offset + 40 ] ),
			 value_32bit );
			libcnotify_printf(
			 "%s: file sub type\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );

			byte_stream_copy_to_uint32_little_endian(
			 &( data[ data_offset + 44 ] ),
			 value_32bit );
			libcnotify_printf(
			 "%s: file time upper\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );

			byte_stream_copy_to_uint32_little_endian(
			 &( data[ data_offset + 48 ] ),
			 value_32bit );
			libcnotify_printf(
			 "%s: file time lower\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );

			libcnotify_printf(
			 "\n" );
		}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

		data_offset += value_data_size;
	}
	if( ( data_offset % 4 ) != 0 )
	{
		alignment_padding_size = 4 - ( data_offset % 4 );

		if( alignment_padding_size > ( data_size - data_offset ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
			 "%s: invalid data size value too small.",
			 function );

			return( -1 );
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: alignment padding:\n",
			 function );
			libcnotify_print_data(
			 &( data[ data_offset ] ),
			 alignment_padding_size,
			 0 );
		}
#endif
		data_offset += alignment_padding_size;
	}
	read_count = libwrc_internal_version_information_resource_read_string_file_information(
	              internal_version_information_resource,
	              data,
	              data_size,
	              data_offset,
	              error );

	if( read_count == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read string file information.",
		 function );

		return( -1 );
	}
	data_offset += read_count;

	read_count = libwrc_internal_version_information_resource_read_variable_file_information(
	              internal_version_information_resource,
	              data,
	              data_size,
	              data_offset,
	              error );

	if( read_count == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read variable file information.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the file version
 * Returns 1 if successful or -1 on error
 */
int libwrc_version_information_resource_get_file_version(
     libwrc_version_information_resource_t *version_information_resource,
     uint64_t *file_version,
     libcerror_error_t **error )
{
	libwrc_internal_version_information_resource_t *internal_version_information_resource = NULL;
	static char *function                                                                 = "libwrc_version_information_resource_get_file_version";

	if( version_information_resource == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid version information resource.",
		 function );

		return( -1 );
	}
	internal_version_information_resource = (libwrc_internal_version_information_resource_t *) version_information_resource;

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
	*file_version = internal_version_information_resource->file_version;

	return( 1 );
}

/* Retrieves the product version
 * Returns 1 if successful or -1 on error
 */
int libwrc_version_information_resource_get_product_version(
     libwrc_version_information_resource_t *version_information_resource,
     uint64_t *product_version,
     libcerror_error_t **error )
{
	libwrc_internal_version_information_resource_t *internal_version_information_resource = NULL;
	static char *function                                                                 = "libwrc_version_information_resource_get_product_version";

	if( version_information_resource == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid version information resource.",
		 function );

		return( -1 );
	}
	internal_version_information_resource = (libwrc_internal_version_information_resource_t *) version_information_resource;

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
	*product_version = internal_version_information_resource->product_version;

	return( 1 );
}

