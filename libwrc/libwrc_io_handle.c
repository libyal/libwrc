/*
 * Input/Output (IO) handle functions
 *
 * Copyright (C) 2011-2022, Joachim Metz <joachim.metz@gmail.com>
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
#include "libwrc_resource_node_entry.h"
#include "libwrc_resource_node_header.h"
#include "libwrc_unused.h"

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
		 (int (*)(intptr_t **, libcerror_error_t **)) &libwrc_resource_node_entry_free,
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
	libcdata_tree_node_t *sub_node                        = NULL;
	libwrc_resource_node_entry_t *resource_node_entry     = NULL;
	libwrc_resource_node_entry_t *sub_resource_node_entry = NULL;
	libwrc_resource_node_header_t *resource_node_header   = NULL;
	static char *function                                 = "libwrc_io_handle_read_resource_node";
	uint32_t entry_index                                  = 0;
	uint32_t number_of_entries                            = 0;
	int number_of_sub_nodes                               = 0;
	int resource_node_entry_index                         = 0;
	int result                                            = 0;
	int sub_node_index                                    = 0;

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
	if( ( node_level < 1 )
	 || ( node_level > LIBWRC_MAXIMUM_RESOURCE_NODE_RECURSION_DEPTH ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid node level value out of bounds.",
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
	if( libwrc_resource_node_header_initialize(
	     &resource_node_header,
	     error ) == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create resource node header.",
		 function );

		goto on_error;
	}
	if( libwrc_resource_node_header_read_file_io_handle(
	     resource_node_header,
	     file_io_handle,
	     file_offset,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read resource node header at offset: %" PRIi64 " (0x%08" PRIx64 ").",
		 function,
		 file_offset,
		 file_offset );

		goto on_error;
	}
	file_offset += sizeof( wrc_resource_node_header_t );

	number_of_entries = (uint32_t) resource_node_header->number_of_named_entries + (uint32_t) resource_node_header->number_of_unnamed_entries;

	if( libwrc_resource_node_header_free(
	     &resource_node_header,
	     error ) == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free resource node header.",
		 function );

		goto on_error;
	}
	for( entry_index = 0;
	     entry_index < number_of_entries;
	     entry_index++ )
	{
		if( libwrc_resource_node_entry_initialize(
		     &resource_node_entry,
		     error ) == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create resource node entry.",
			 function );

			goto on_error;
		}
		if( libwrc_resource_node_entry_read_file_io_handle(
		     resource_node_entry,
		     file_io_handle,
		     file_offset,
		     node_level,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read resource node entry at offset: %" PRIi64 " (0x%08" PRIx64 ").",
			 function,
			 file_offset,
			 file_offset );

			goto on_error;
		}
		file_offset += sizeof( wrc_resource_node_entry_t );

		result = libwrc_resource_node_entry_read_name_file_io_handle(
		          resource_node_entry,
		          file_io_handle,
		          error );

		if( result == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read resource node name.",
			 function );

			goto on_error;
		}
		if( node_level == 1 )
		{
			if( ( resource_node_entry->identifier & LIBWRC_RESOURCE_IDENTIFIER_FLAG_HAS_NAME ) == 0 )
			{
				switch( resource_node_entry->identifier )
				{
					case LIBWRC_RESOURCE_IDENTIFIER_CURSOR:
						resource_node_entry->type = LIBWRC_RESOURCE_TYPE_CURSOR;
						break;

					case LIBWRC_RESOURCE_IDENTIFIER_BITMAP:
						resource_node_entry->type = LIBWRC_RESOURCE_TYPE_BITMAP;
						break;

					case LIBWRC_RESOURCE_IDENTIFIER_ICON:
						resource_node_entry->type = LIBWRC_RESOURCE_TYPE_ICON;
						break;

					case LIBWRC_RESOURCE_IDENTIFIER_MENU:
						resource_node_entry->type = LIBWRC_RESOURCE_TYPE_MENU;
						break;

					case LIBWRC_RESOURCE_IDENTIFIER_DIALOG:
						resource_node_entry->type = LIBWRC_RESOURCE_TYPE_DIALOG;
						break;

					case LIBWRC_RESOURCE_IDENTIFIER_STRING:
						resource_node_entry->type = LIBWRC_RESOURCE_TYPE_STRING;
						break;

					case LIBWRC_RESOURCE_IDENTIFIER_FONT_DIRECTORY:
						resource_node_entry->type = LIBWRC_RESOURCE_TYPE_FONT_DIRECTORY;
						break;

					case LIBWRC_RESOURCE_IDENTIFIER_FONT:
						resource_node_entry->type = LIBWRC_RESOURCE_TYPE_FONT;
						break;

					case LIBWRC_RESOURCE_IDENTIFIER_ACCELERATOR:
						resource_node_entry->type = LIBWRC_RESOURCE_TYPE_ACCELERATOR;
						break;

					case LIBWRC_RESOURCE_IDENTIFIER_RAW_DATA:
						resource_node_entry->type = LIBWRC_RESOURCE_TYPE_RAW_DATA;
						break;

					case LIBWRC_RESOURCE_IDENTIFIER_MESSAGE_TABLE:
						resource_node_entry->type = LIBWRC_RESOURCE_TYPE_MESSAGE_TABLE;
						break;

					case LIBWRC_RESOURCE_IDENTIFIER_GROUP_CURSOR:
						resource_node_entry->type = LIBWRC_RESOURCE_TYPE_GROUP_CURSOR;
						break;

					case LIBWRC_RESOURCE_IDENTIFIER_GROUP_ICON:
						resource_node_entry->type = LIBWRC_RESOURCE_TYPE_GROUP_ICON;
						break;

					case LIBWRC_RESOURCE_IDENTIFIER_VERSION:
						resource_node_entry->type = LIBWRC_RESOURCE_TYPE_VERSION;
						break;

					case LIBWRC_RESOURCE_IDENTIFIER_DIALOG_INCLUDE:
						resource_node_entry->type = LIBWRC_RESOURCE_TYPE_DIALOG_INCLUDE;
						break;

					case LIBWRC_RESOURCE_IDENTIFIER_PLUG_AND_PLAY:
						resource_node_entry->type = LIBWRC_RESOURCE_TYPE_PLUG_AND_PLAY;
						break;

					case LIBWRC_RESOURCE_IDENTIFIER_VXD:
						resource_node_entry->type = LIBWRC_RESOURCE_TYPE_VXD;
						break;

					case LIBWRC_RESOURCE_IDENTIFIER_ANIMATED_CURSOR:
						resource_node_entry->type = LIBWRC_RESOURCE_TYPE_ANIMATED_CURSOR;
						break;

					case LIBWRC_RESOURCE_IDENTIFIER_ANIMATED_ICON:
						resource_node_entry->type = LIBWRC_RESOURCE_TYPE_ANIMATED_ICON;
						break;

					case LIBWRC_RESOURCE_IDENTIFIER_HTML:
						resource_node_entry->type = LIBWRC_RESOURCE_TYPE_HTML;
						break;

					case LIBWRC_RESOURCE_IDENTIFIER_MANIFEST:
						resource_node_entry->type = LIBWRC_RESOURCE_TYPE_MANIFEST;
						break;
				}
			}
			else
			{
				if( resource_node_entry->name_string_size == 6 )
				{
					if( memory_compare(
					     resource_node_entry->name_string,
					     libwrc_resource_name_mui,
					     6 ) == 0 )
					{
						resource_node_entry->type = LIBWRC_RESOURCE_TYPE_MUI;
					}
				}
				else if( resource_node_entry->name_string_size == 26 )
				{
					if( memory_compare(
					     resource_node_entry->name_string,
					     libwrc_resource_name_wevt_template,
					     26 ) == 0 )
					{
						resource_node_entry->type = LIBWRC_RESOURCE_TYPE_WEVT_TEMPLATE;
					}
				}
			}
		}
		if( libcdata_tree_node_insert_value(
		     node,
		     (intptr_t *) resource_node_entry,
		     (int (*)(intptr_t *, intptr_t *, libcerror_error_t **)) &libwrc_resource_node_entry_compare,
		     LIBCDATA_INSERT_FLAG_NON_UNIQUE_ENTRIES,
		     error ) == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
			 "%s: unable to insert resource node: %d.",
			 function,
			 resource_node_entry_index );

			goto on_error;
		}
		resource_node_entry = NULL;

		resource_node_entry_index++;

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "\n" );
		}
#endif
	}
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
		     (intptr_t **) &sub_resource_node_entry,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve resource sub node: %d entry.",
			 function,
			 sub_node_index );

			goto on_error;
		}
		if( sub_resource_node_entry == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: invalid resource sub node: %d entry.",
			 function,
			 sub_node_index );

			goto on_error;
		}
		if( ( sub_resource_node_entry->offset & 0x80000000UL ) != 0 )
		{
			if( libwrc_io_handle_read_resource_node(
			     io_handle,
			     file_io_handle,
			     (off64_t) ( sub_resource_node_entry->offset & 0x7fffffffUL ),
			     node_level + 1,
			     sub_node,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_READ_FAILED,
				 "%s: unable to read sub resource node: %d at offset: %" PRIu32 " (0x%08" PRIx32 ").",
				 function,
				 sub_node_index,
				 sub_resource_node_entry->offset,
				 sub_resource_node_entry->offset );

				goto on_error;
			}
		}
		else
		{
			if( libwrc_data_descriptor_initialize(
			     &( sub_resource_node_entry->data_descriptor ),
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
			if( libwrc_data_descriptor_read_file_io_handle(
			     sub_resource_node_entry->data_descriptor,
			     file_io_handle,
			     (off64_t) sub_resource_node_entry->offset,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_READ_FAILED,
				 "%s: unable to read data descriptor: %d at offset: %" PRIu32 " (0x%08" PRIx32 ").",
				 function,
				 sub_node_index,
				 sub_resource_node_entry->offset,
				 sub_resource_node_entry->offset );

				goto on_error;
			}
			if( ( sub_resource_node_entry->data_descriptor->virtual_address < io_handle->virtual_address )
			 || ( (size64_t) sub_resource_node_entry->data_descriptor->virtual_address >= ( io_handle->virtual_address + io_handle->stream_size ) ) )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
				 "%s: invalid data descriptor: %d - virtual address out of bounds.",
				 function,
				 sub_node_index );

				goto on_error;
			}
			if( (size64_t) ( sub_resource_node_entry->data_descriptor->virtual_address + sub_resource_node_entry->data_descriptor->size ) > ( io_handle->virtual_address + io_handle->stream_size ) )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
				 "%s: invalid data descriptor: %d - size out of bounds.",
				 function,
				 sub_node_index );

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
	if( resource_node_entry != NULL )
	{
		libwrc_resource_node_entry_free(
		 &resource_node_entry,
		 NULL );
	}
	if( resource_node_header != NULL )
	{
		libwrc_resource_node_header_free(
		 &resource_node_header,
		 NULL );
	}
	return( -1 );
}

