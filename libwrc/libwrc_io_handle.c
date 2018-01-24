/*
 * Input/Output (IO) handle functions
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
#include <narrow_string.h>
#include <system_string.h>
#include <types.h>
#include <wide_string.h>

#include "libwrc_codepage.h"
#include "libwrc_data_descriptor.h"
#include "libwrc_debug.h"
#include "libwrc_definitions.h"
#include "libwrc_io_handle.h"
#include "libwrc_libbfio.h"
#include "libwrc_libcdata.h"
#include "libwrc_libcerror.h"
#include "libwrc_libcnotify.h"
#include "libwrc_libuna.h"
#include "libwrc_resource_values.h"
#include "libwrc_unused.h"

#include "wrc_data_descriptor.h"
#include "wrc_resource_node.h"

uint8_t libwrc_resource_name_mui[ 6 ] = {
	'M', 0, 'U', 0, 'I', 0 };

uint8_t libwrc_resource_name_wevt_template[ 26 ] = {
	'W', 0, 'E', 0, 'V', 0, 'T', 0, '_', 0, 'T', 0, 'E', 0, 'M', 0, 'P', 0, 'L', 0, 'A', 0, 'T', 0, 'E', 0 };

/* Creates an IO handle
 * Make sure the value io_handle is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libwrc_io_handle_initialize(
     libwrc_io_handle_t **io_handle,
     libcerror_error_t **error )
{
	static char *function = "libwrc_io_handle_initialize";

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
	if( *io_handle != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid IO handle value already set.",
		 function );

		return( -1 );
	}
	*io_handle = memory_allocate_structure(
	              libwrc_io_handle_t );

	if( *io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create IO handle.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *io_handle,
	     0,
	     sizeof( libwrc_io_handle_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear file.",
		 function );

		goto on_error;
	}
	( *io_handle )->ascii_codepage = LIBWRC_CODEPAGE_WINDOWS_1252;

	return( 1 );

on_error:
	if( *io_handle != NULL )
	{
		memory_free(
		 *io_handle );

		*io_handle = NULL;
	}
	return( -1 );
}

/* Frees an IO handle
 * Returns 1 if successful or -1 on error
 */
int libwrc_io_handle_free(
     libwrc_io_handle_t **io_handle,
     libcerror_error_t **error )
{
	static char *function = "libwrc_io_handle_free";

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
	if( *io_handle != NULL )
	{
		memory_free(
		 *io_handle );

		*io_handle = NULL;
	}
	return( 1 );
}

/* Clears the IO handle
 * Returns 1 if successful or -1 on error
 */
int libwrc_io_handle_clear(
     libwrc_io_handle_t *io_handle,
     libcerror_error_t **error )
{
	static char *function = "libwrc_io_handle_clear";

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
	if( memory_set(
	     io_handle,
	     0,
	     sizeof( libwrc_io_handle_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear IO handle.",
		 function );

		return( -1 );
	}
	io_handle->ascii_codepage = LIBWRC_CODEPAGE_WINDOWS_1252;

	return( 1 );
}

/* Reads the resource nods
 * Returns 1 if successful or -1 on error
 */
int libwrc_io_handle_read_resource_nodes(
     libwrc_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     libcdata_tree_node_t **root_node,
     libcerror_error_t **error )
{
	static char *function = "libwrc_io_handle_read_resource_nodes";

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
	if( root_node == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid root node.",
		 function );

		return( -1 );
	}
	if( *root_node != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: root node already set.",
		 function );

		return( -1 );
	}
	if( libbfio_handle_get_size(
	     file_io_handle,
	     &( io_handle->stream_size ),
	     error ) == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to retrieve stream size.",
		 function );

		goto on_error;
	}
	if( libcdata_tree_node_initialize(
	     root_node,
	     error ) == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create root node.",
		 function );

		goto on_error;
	}
	if( libwrc_io_handle_read_resource_node(
	     io_handle,
	     file_io_handle,
	     0,
	     1,
	     *root_node,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read root resource node.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *root_node != NULL )
	{
		libcdata_tree_node_free(
		 root_node,
		 (int (*)(intptr_t **, libcerror_error_t **)) &libwrc_resource_values_free,
		 NULL );
	}
	return( -1 );
}

/* Reads a resource node
 * Returns 1 if successful or -1 on error
 */
int libwrc_io_handle_read_resource_node(
     libwrc_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     off64_t file_offset,
     int node_level,
     libcdata_tree_node_t *node,
     libcerror_error_t **error )
{
	uint8_t resource_name_size_data[ 2 ];
	wrc_resource_node_header_t resource_node_header;

	libcdata_tree_node_t *sub_node                = NULL;
	libwrc_resource_values_t *resource_values     = NULL;
	libwrc_resource_values_t *sub_resource_values = NULL;
	uint8_t *resource_node_data                   = NULL;
	static char *function                         = "libwrc_io_handle_read_resource_node";
	size_t resource_node_data_offset              = 0;
	size_t resource_node_data_size                = 0;
	ssize_t read_count                            = 0;
	uint32_t flags                                = 0;
	uint16_t number_of_named_entries              = 0;
	uint16_t number_of_unnamed_entries            = 0;
	int number_of_sub_nodes                       = 0;
	int resource_node_entry                       = 0;
	int sub_node_index                            = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	system_character_t *value_string              = NULL;
	size_t value_string_size                      = 0;
	uint32_t value_32bit                          = 0;
	uint16_t value_16bit                          = 0;
	int result                                    = 0;
#endif

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
	if( node_level < 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: node level value out of bounds.",
		 function );

		return( -1 );
	}
	if( node == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid node.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading resource node header at offset: %" PRIi64 " (0x%08" PRIx64 ")\n",
		 function,
		 file_offset,
		 file_offset );
	}
#endif
	if( libbfio_handle_seek_offset(
	     file_io_handle,
	     file_offset,
	     SEEK_SET,
	     error ) == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to seek resource node header offset: %" PRIi64 ".",
		 function,
		 file_offset );

		goto on_error;
	}
	read_count = libbfio_handle_read_buffer(
	              file_io_handle,
	              (uint8_t *) &resource_node_header,
	              sizeof( wrc_resource_node_header_t ),
	              error );

	if( read_count != (ssize_t) sizeof( wrc_resource_node_header_t ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read resource node header.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: resource node header data:\n",
		 function );
		libcnotify_print_data(
		 (uint8_t *) &resource_node_header,
		 sizeof( wrc_resource_node_header_t ),
		 0 );
	}
#endif
	byte_stream_copy_to_uint32_little_endian(
	 resource_node_header.flags,
	 flags );

	byte_stream_copy_to_uint16_little_endian(
	 resource_node_header.number_of_named_entries,
	 number_of_named_entries );

	byte_stream_copy_to_uint16_little_endian(
	 resource_node_header.number_of_unnamed_entries,
	 number_of_unnamed_entries );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: flags\t\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 resource_node_header.flags,
		 value_32bit );
		libcnotify_printf(
		 "%s: creation time\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint16_little_endian(
		 resource_node_header.major_version,
		 value_16bit );
		libcnotify_printf(
		 "%s: major version\t\t\t\t: %" PRIu16 "\n",
		 function,
		 value_16bit );

		byte_stream_copy_to_uint16_little_endian(
		 resource_node_header.minor_version,
		 value_16bit );
		libcnotify_printf(
		 "%s: minor version\t\t\t\t: %" PRIu16 "\n",
		 function,
		 value_16bit );

		libcnotify_printf(
		 "%s: number of named entries\t\t\t: %" PRIu16 "\n",
		 function,
		 number_of_named_entries );

		libcnotify_printf(
		 "%s: number of unnamed entries\t\t\t: %" PRIu16 "\n",
		 function,
		 number_of_unnamed_entries );

		libcnotify_printf(
		 "\n" );
	}
#endif
	if( flags != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported flags: 0x%08" PRIx32 ".",
		 function,
		 flags );

		return( -1 );
	}
	resource_node_data_size = ( (size_t) number_of_named_entries + (size_t) number_of_unnamed_entries ) * 8;

	if( resource_node_data_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid resource node data size value exceeds maximum.",
		 function );

		goto on_error;
	}
	resource_node_data = (uint8_t *) memory_allocate(
	                                  sizeof( uint8_t ) * resource_node_data_size );

	if( resource_node_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create resource node data.",
		 function );

		goto on_error;
	}
	read_count = libbfio_handle_read_buffer(
	              file_io_handle,
	              resource_node_data,
	              resource_node_data_size,
	              error );

	if( read_count != (ssize_t) resource_node_data_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read resource node data.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: resource node data:\n",
		 function );
		libcnotify_print_data(
		 resource_node_data,
		 resource_node_data_size,
		 0 );
	}
#endif
	while( ( resource_node_data_offset + 8 ) <= resource_node_data_size )
	{
		if( libwrc_resource_values_initialize(
		     &resource_values,
		     error ) == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create resource values: %d.",
			 function,
			 resource_node_entry );

			goto on_error;
		}
		if( resource_values == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: invalid resource values: %d.",
			 function,
			 resource_node_entry );

			goto on_error;
		}
		byte_stream_copy_to_uint32_little_endian(
		 &( resource_node_data[ resource_node_data_offset ] ),
		 resource_values->identifier );

		resource_node_data_offset += 4;

		byte_stream_copy_to_uint32_little_endian(
		 &( resource_node_data[ resource_node_data_offset ] ),
		 resource_values->offset );

		resource_node_data_offset += 4;

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: resource node entry: %03d identifier\t: 0x%08" PRIx32 "",
			 function,
			 resource_node_entry,
			 resource_values->identifier );

			if( ( node_level == 1 )
			 && ( ( resource_values->identifier & LIBWRC_RESOURCE_IDENTIFIER_FLAG_HAS_NAME ) == 0 ) )
			{
				libcnotify_printf(
				 " (%s)",
				 libwrc_debug_get_resource_identifier(
				  resource_values->identifier ) );
			}
			libcnotify_printf(
			 "\n" );

			libcnotify_printf(
			 "%s: resource node entry: %03d offset\t\t: 0x%08" PRIx32 "\n",
			 function,
			 resource_node_entry,
			 resource_values->offset );
		}
#endif
		if( node_level == 1 )
		{
			if( ( resource_values->identifier & LIBWRC_RESOURCE_IDENTIFIER_FLAG_HAS_NAME ) == 0 )
			{
				switch( resource_values->identifier )
				{
					case LIBWRC_RESOURCE_IDENTIFIER_CURSOR:
						resource_values->type = LIBWRC_RESOURCE_TYPE_CURSOR;
						break;

					case LIBWRC_RESOURCE_IDENTIFIER_BITMAP:
						resource_values->type = LIBWRC_RESOURCE_TYPE_BITMAP;
						break;

					case LIBWRC_RESOURCE_IDENTIFIER_ICON:
						resource_values->type = LIBWRC_RESOURCE_TYPE_ICON;
						break;

					case LIBWRC_RESOURCE_IDENTIFIER_MENU:
						resource_values->type = LIBWRC_RESOURCE_TYPE_MENU;
						break;

					case LIBWRC_RESOURCE_IDENTIFIER_DIALOG:
						resource_values->type = LIBWRC_RESOURCE_TYPE_DIALOG;
						break;

					case LIBWRC_RESOURCE_IDENTIFIER_STRING:
						resource_values->type = LIBWRC_RESOURCE_TYPE_STRING;
						break;

					case LIBWRC_RESOURCE_IDENTIFIER_FONT_DIRECTORY:
						resource_values->type = LIBWRC_RESOURCE_TYPE_FONT_DIRECTORY;
						break;

					case LIBWRC_RESOURCE_IDENTIFIER_FONT:
						resource_values->type = LIBWRC_RESOURCE_TYPE_FONT;
						break;

					case LIBWRC_RESOURCE_IDENTIFIER_ACCELERATOR:
						resource_values->type = LIBWRC_RESOURCE_TYPE_ACCELERATOR;
						break;

					case LIBWRC_RESOURCE_IDENTIFIER_RAW_DATA:
						resource_values->type = LIBWRC_RESOURCE_TYPE_RAW_DATA;
						break;

					case LIBWRC_RESOURCE_IDENTIFIER_MESSAGE_TABLE:
						resource_values->type = LIBWRC_RESOURCE_TYPE_MESSAGE_TABLE;
						break;

					case LIBWRC_RESOURCE_IDENTIFIER_GROUP_CURSOR:
						resource_values->type = LIBWRC_RESOURCE_TYPE_GROUP_CURSOR;
						break;

					case LIBWRC_RESOURCE_IDENTIFIER_GROUP_ICON:
						resource_values->type = LIBWRC_RESOURCE_TYPE_GROUP_ICON;
						break;

					case LIBWRC_RESOURCE_IDENTIFIER_VERSION:
						resource_values->type = LIBWRC_RESOURCE_TYPE_VERSION;
						break;

					case LIBWRC_RESOURCE_IDENTIFIER_DIALOG_INCLUDE:
						resource_values->type = LIBWRC_RESOURCE_TYPE_DIALOG_INCLUDE;
						break;

					case LIBWRC_RESOURCE_IDENTIFIER_PLUG_AND_PLAY:
						resource_values->type = LIBWRC_RESOURCE_TYPE_PLUG_AND_PLAY;
						break;

					case LIBWRC_RESOURCE_IDENTIFIER_VXD:
						resource_values->type = LIBWRC_RESOURCE_TYPE_VXD;
						break;

					case LIBWRC_RESOURCE_IDENTIFIER_ANIMATED_CURSOR:
						resource_values->type = LIBWRC_RESOURCE_TYPE_ANIMATED_CURSOR;
						break;

					case LIBWRC_RESOURCE_IDENTIFIER_ANIMATED_ICON:
						resource_values->type = LIBWRC_RESOURCE_TYPE_ANIMATED_ICON;
						break;

					case LIBWRC_RESOURCE_IDENTIFIER_HTML:
						resource_values->type = LIBWRC_RESOURCE_TYPE_HTML;
						break;

					case LIBWRC_RESOURCE_IDENTIFIER_MANIFEST:
						resource_values->type = LIBWRC_RESOURCE_TYPE_MANIFEST;
						break;
				}
			}
			else
			{
				if( libbfio_handle_seek_offset(
				     file_io_handle,
				     (off64_t) ( resource_values->identifier & 0x7fffffffUL ),
				     SEEK_SET,
				     error ) == -1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_IO,
					 LIBCERROR_IO_ERROR_SEEK_FAILED,
					 "%s: unable to seek resource name string offset: %" PRIi64 ".",
					 function,
					 file_offset );

					goto on_error;
				}
				read_count = libbfio_handle_read_buffer(
					      file_io_handle,
					      resource_name_size_data,
					      2,
					      error );

				if( read_count != (ssize_t) 2 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_IO,
					 LIBCERROR_IO_ERROR_READ_FAILED,
					 "%s: unable to read resource name string size.",
					 function );

					goto on_error;
				}
				byte_stream_copy_to_uint16_little_endian(
				 resource_name_size_data,
				 resource_values->name_string_size );

#if defined( HAVE_DEBUG_OUTPUT )
				if( libcnotify_verbose != 0 )
				{
					libcnotify_printf(
					 "%s: resource node entry: %03d name string size\t: %" PRIzd "\n",
					 function,
					 resource_node_entry,
					 resource_values->name_string_size );

				}
#endif
				resource_values->name_string_size *= 2;

				if( ( resource_values->name_string_size > (size_t) SSIZE_MAX )
				 || ( ( sizeof( system_character_t ) * resource_values->name_string_size )  > (size_t) SSIZE_MAX ) )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
					 "%s: invalid name string size value exceeds maximum.",
					 function );

					goto on_error;
				}
				resource_values->name_string = (uint8_t *) memory_allocate(
				                                            sizeof( uint8_t ) * resource_values->name_string_size );

				if( resource_values->name_string == NULL )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_MEMORY,
					 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
					 "%s: unable to create resource node name string.",
					 function );

					goto on_error;
				}
				read_count = libbfio_handle_read_buffer(
					      file_io_handle,
					      resource_values->name_string,
					      resource_values->name_string_size,
					      error );

				if( read_count != (ssize_t) resource_values->name_string_size )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_IO,
					 LIBCERROR_IO_ERROR_READ_FAILED,
					 "%s: unable to read resource node name string.",
					 function );

					goto on_error;
				}
#if defined( HAVE_DEBUG_OUTPUT )
				if( libcnotify_verbose != 0 )
				{
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
					result = libuna_utf16_string_size_from_utf16_stream(
						  resource_values->name_string,
						  resource_values->name_string_size,
						  LIBUNA_ENDIAN_LITTLE,
						  &value_string_size,
						  error );
#else
					result = libuna_utf8_string_size_from_utf16_stream(
						  resource_values->name_string,
						  resource_values->name_string_size,
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
						 "%s: unable to determine size of data string.",
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
						 "%s: invalid data string size value exceeds maximum.",
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
						 "%s: unable to create data string.",
						 function );

						goto on_error;
					}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
					result = libuna_utf16_string_copy_from_utf16_stream(
						  (libuna_utf16_character_t *) value_string,
						  value_string_size,
						  resource_values->name_string,
						  resource_values->name_string_size,
						  LIBUNA_ENDIAN_LITTLE,
						  error );
#else
					result = libuna_utf8_string_copy_from_utf16_stream(
						  (libuna_utf8_character_t *) value_string,
						  value_string_size,
						  resource_values->name_string,
						  resource_values->name_string_size,
						  LIBUNA_ENDIAN_LITTLE,
						  error );
#endif
					if( result != 1 )
					{
						libcerror_error_set(
						 error,
						 LIBCERROR_ERROR_DOMAIN_RUNTIME,
						 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
						 "%s: unable to set data string.",
						 function );

						goto on_error;
					}
					libcnotify_printf(
					 "%s: resource node entry: %03d name string\t: %" PRIs_SYSTEM "\n",
					 function,
					 resource_node_entry,
					 value_string );

					memory_free(
					 value_string );

					value_string = NULL;
				}
#endif
			}
			if( resource_values->name_string_size == 6 )
			{
				if( memory_compare(
				     resource_values->name_string,
				     libwrc_resource_name_mui,
				     6 ) == 0 )
				{
					resource_values->type = LIBWRC_RESOURCE_TYPE_MUI;
				}
			}
			else if( resource_values->name_string_size == 26 )
			{
				if( memory_compare(
				     resource_values->name_string,
				     libwrc_resource_name_wevt_template,
				     26 ) == 0 )
				{
					resource_values->type = LIBWRC_RESOURCE_TYPE_WEVT_TEMPLATE;
				}
			}
		}
		if( libcdata_tree_node_insert_value(
		     node,
		     (intptr_t *) resource_values,
		     (int (*)(intptr_t *, intptr_t *, libcerror_error_t **)) &libwrc_resource_values_compare,
		     LIBCDATA_INSERT_FLAG_NON_UNIQUE_ENTRIES,
		     error ) == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
			 "%s: unable to insert resource node: %d.",
			 function,
			 resource_node_entry );

			goto on_error;
		}
		resource_values = NULL;

		resource_node_entry++;

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "\n" );
		}
#endif
	}
	memory_free(
	 resource_node_data );

	resource_node_data = NULL;

	if( libcdata_tree_node_get_number_of_sub_nodes(
	     node,
	     &number_of_sub_nodes,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to retrieve number of sub nodes.",
		 function );

		goto on_error;
	}
	if( libcdata_tree_node_get_sub_node_by_index(
	     node,
	     0,
	     &sub_node,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve first sub node.",
		 function );

		goto on_error;
	}
	for( sub_node_index = 0;
	     sub_node_index < number_of_sub_nodes;
	     sub_node_index++ )
	{
		if( libcdata_tree_node_get_value(
		     sub_node,
		     (intptr_t **) &sub_resource_values,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve value of sub node: %d.",
			 function,
			 sub_node_index );

			goto on_error;
		}
		if( sub_resource_values == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: invalid sub resource values: %d.",
			 function,
			 sub_node_index );

			goto on_error;
		}
		if( ( sub_resource_values->offset & 0x80000000UL ) != 0 )
		{
			if( libwrc_io_handle_read_resource_node(
			     io_handle,
			     file_io_handle,
			     (off64_t) ( sub_resource_values->offset & 0x7fffffffUL ),
			     node_level + 1,
			     sub_node,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_READ_FAILED,
				 "%s: unable to read sub resource node: %d at offset: 0x%08" PRIx32 ".",
				 function,
				 sub_node_index,
				 sub_resource_values->offset );

				goto on_error;
			}
		}
		else
		{
			if( libwrc_data_descriptor_initialize(
			     &( sub_resource_values->data_descriptor ),
			     error ) == -1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
				 "%s: unable to create data descriptor: %d.",
				 function,
				 sub_node_index );

				goto on_error;
			}
			if( libwrc_io_handle_read_data_descriptor(
			     io_handle,
			     file_io_handle,
			     (off64_t) sub_resource_values->offset,
			     sub_resource_values->data_descriptor,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_READ_FAILED,
				 "%s: unable to read data descriptor: %d at offset: 0x%08" PRIx32 ".",
				 function,
				 sub_node_index,
				 sub_resource_values->offset );

				goto on_error;
			}
		}
		if( libcdata_tree_node_get_next_node(
		     sub_node,
		     &sub_node,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve next node of sub node: %d.",
			 function,
			 sub_node_index );

			goto on_error;
		}
	}
	return( 1 );

on_error:
#if defined( HAVE_DEBUG_OUTPUT )
	if( value_string != NULL )
	{
		memory_free(
		 value_string );
	}
#endif
	if( resource_values != NULL )
	{
		libwrc_resource_values_free(
		 &resource_values,
		 NULL );
	}
	if( resource_node_data != NULL )
	{
		memory_free(
		 resource_node_data );
	}
	return( -1 );
}

/* Reads a data descriptor
 * Returns 1 if successful or -1 on error
 */
int libwrc_io_handle_read_data_descriptor(
     libwrc_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     off64_t file_offset,
     libwrc_data_descriptor_t *data_descriptor,
     libcerror_error_t **error )
{
	wrc_data_descriptor_t data_descriptor_data;

	static char *function = "libwrc_io_handle_read_data_descriptor";
	ssize_t read_count    = 0;

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
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading data descriptor at offset: %" PRIi64 " (0x%08" PRIx64 ")\n",
		 function,
		 file_offset,
		 file_offset );
	}
#endif
	if( libbfio_handle_seek_offset(
	     file_io_handle,
	     file_offset,
	     SEEK_SET,
	     error ) == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to seek data descriptor offset: %" PRIi64 ".",
		 function,
		 file_offset );

		return( -1 );
	}
	read_count = libbfio_handle_read_buffer(
	              file_io_handle,
	              (uint8_t *) &data_descriptor_data,
	              sizeof( wrc_data_descriptor_t ),
	              error );

	if( read_count != (ssize_t) sizeof( wrc_data_descriptor_t ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read data descriptor.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: data descriptor data:\n",
		 function );
		libcnotify_print_data(
		 (uint8_t *) &data_descriptor_data,
		 sizeof( wrc_data_descriptor_t ),
		 0 );
	}
#endif
	byte_stream_copy_to_uint32_little_endian(
	 data_descriptor_data.virtual_address,
	 data_descriptor->virtual_address );

	byte_stream_copy_to_uint32_little_endian(
	 data_descriptor_data.size,
	 data_descriptor->size );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: virtual address\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 data_descriptor->virtual_address );

		libcnotify_printf(
		 "%s: size\t\t\t\t: %" PRIu32 "\n",
		 function,
		 data_descriptor->size );

		libcnotify_printf(
		 "\n" );
	}
#endif
	if( ( data_descriptor->virtual_address < io_handle->virtual_address )
	 || ( (size64_t) data_descriptor->virtual_address >= ( io_handle->virtual_address + io_handle->stream_size ) ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: virtual address out of bounds.",
		 function );

		return( -1 );
	}
	if( (size64_t) ( data_descriptor->virtual_address + data_descriptor->size ) > ( io_handle->virtual_address + io_handle->stream_size ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: size out of bounds.",
		 function );

		return( -1 );
	}
	return( 1 );
}

