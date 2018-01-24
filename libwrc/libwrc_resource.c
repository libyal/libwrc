/*
 * Resource functions
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
#include "libwrc_io_handle.h"
#include "libwrc_language_entry.h"
#include "libwrc_language_table.h"
#include "libwrc_libbfio.h"
#include "libwrc_libcdata.h"
#include "libwrc_libcerror.h"
#include "libwrc_libcnotify.h"
#include "libwrc_libfvalue.h"
#include "libwrc_libfwevt.h"
#include "libwrc_libfwnt.h"
#include "libwrc_manifest_values.h"
#include "libwrc_message_table_values.h"
#include "libwrc_mui_values.h"
#include "libwrc_resource.h"
#include "libwrc_resource_values.h"
#include "libwrc_string_values.h"
#include "libwrc_version_values.h"
#include "libwrc_wevt_template_values.h"

/* Creates a resource
 * Make sure the value resource is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libwrc_resource_initialize(
     libwrc_resource_t **resource,
     libwrc_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     libcdata_tree_node_t *resource_node,
     uint8_t flags,
     libcerror_error_t **error )
{
	libwrc_internal_resource_t *internal_resource = NULL;
	libwrc_resource_values_t *resource_values     = NULL;
	static char *function                         = "libwrc_resource_initialize";

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
	if( *resource != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid resource value already set.",
		 function );

		return( -1 );
	}
	if( resource_node == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid resource node.",
		 function );

		return( -1 );
	}
	if( ( flags & ~( LIBWRC_RESOURCE_FLAG_MANAGED_FILE_IO_HANDLE ) ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported flags: 0x%02" PRIx8 ".",
		 function,
		 flags );

		return( -1 );
	}
	if( libcdata_tree_node_get_value(
	     resource_node,
	     (intptr_t **) &resource_values,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve value of resource node.",
		 function );

		goto on_error;
	}
	if( resource_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid resource values.",
		 function );

		goto on_error;
	}
	internal_resource = memory_allocate_structure(
	                     libwrc_internal_resource_t );

	if( internal_resource == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create resource.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     internal_resource,
	     0,
	     sizeof( libwrc_internal_resource_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear resource.",
		 function );

		memory_free(
		 internal_resource );

		return( -1 );
	}
	if( ( flags & LIBWRC_RESOURCE_FLAG_MANAGED_FILE_IO_HANDLE ) == 0 )
	{
		internal_resource->file_io_handle = file_io_handle;
	}
	else
	{
		if( libbfio_handle_clone(
		     &( internal_resource->file_io_handle ),
		     file_io_handle,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy file IO handle.",
			 function );

			goto on_error;
		}
		if( libbfio_handle_set_open_on_demand(
		     internal_resource->file_io_handle,
		     1,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to set open on demand in file IO handle.",
			 function );

			goto on_error;
		}
	}
	internal_resource->io_handle       = io_handle;
	internal_resource->resource_node   = resource_node;
	internal_resource->resource_values = resource_values;
	internal_resource->flags           = flags;

	*resource = (libwrc_resource_t *) internal_resource;

	return( 1 );

on_error:
	if( internal_resource != NULL )
	{
		if( ( flags & LIBWRC_RESOURCE_FLAG_MANAGED_FILE_IO_HANDLE ) != 0 )
		{
			if( internal_resource->file_io_handle != NULL )
			{
				libbfio_handle_free(
				 &( internal_resource->file_io_handle ),
				 NULL );
			}
		}
		memory_free(
		 internal_resource );
	}
	return( -1 );
}

/* Frees a resource
 * Returns 1 if successful or -1 on error
 */
int libwrc_resource_free(
     libwrc_resource_t **resource,
     libcerror_error_t **error )
{
	libwrc_internal_resource_t *internal_resource = NULL;
	static char *function                         = "libwrc_resource_free";
	int result                                    = 1;

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
	if( *resource != NULL )
	{
		internal_resource = (libwrc_internal_resource_t *) *resource;
		*resource         = NULL;

		/* The io_handle, resource_node and resource_values references are freed elsewhere
		 */
		if( ( internal_resource->flags & LIBWRC_RESOURCE_FLAG_MANAGED_FILE_IO_HANDLE ) != 0 )
		{
			if( internal_resource->file_io_handle != NULL )
			{
				if( libbfio_handle_close(
				     internal_resource->file_io_handle,
				     error ) != 0 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_IO,
					 LIBCERROR_IO_ERROR_CLOSE_FAILED,
					 "%s: unable to close file IO handle.",
					 function );

					result = -1;
				}
				if( libbfio_handle_free(
				     &( internal_resource->file_io_handle ),
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
					 "%s: unable to free file IO handle.",
					 function );

					result = -1;
				}
			}
		}
		if( internal_resource->value != NULL )
		{
			if( internal_resource->free_value != NULL )
			{
				if( internal_resource->free_value(
				     &( internal_resource->value ),
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
					 "%s: unable to free resource value.",
					 function );

					result = -1;
				}
			}
		}
		memory_free(
		 internal_resource );
	}
	return( result );
}

/* Retrieves the resource identifier
 * Returns 1 if successful or -1 on error
 */
int libwrc_resource_get_identifier(
     libwrc_resource_t *resource,
     uint32_t *identifier,
     libcerror_error_t **error )
{
	libwrc_internal_resource_t *internal_resource = NULL;
	static char *function                         = "libwrc_resource_get_identifier";

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

	if( libwrc_resource_values_get_identifier(
	     internal_resource->resource_values,
	     identifier,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve identifier.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the resource type
 * Returns 1 if successful or -1 on error
 */
int libwrc_resource_get_type(
     libwrc_resource_t *resource,
     int *type,
     libcerror_error_t **error )
{
	libwrc_internal_resource_t *internal_resource = NULL;
	static char *function                         = "libwrc_resource_get_type";

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

	if( libwrc_resource_values_get_type(
	     internal_resource->resource_values,
	     type,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve type.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Reads the resource
 * Returns 1 if successful or -1 on error
 */
int libwrc_resource_read(
     libwrc_resource_t *resource,
     libcerror_error_t **error )
{
	libwrc_internal_resource_t *internal_resource = NULL;
	static char *function                         = "libwrc_resource_read";

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
/* TODO
		if( internal_resource->value == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: invalid resource - missing value.",
			 function );

			return( -1 );
		}
*/
	}
	return( 1 );
}

/* Read the values
 * Returns 1 if successful or -1 on error
 */
int libwrc_resource_read_value(
     libwrc_internal_resource_t *internal_resource,
     libcerror_error_t **error )
{
	libcdata_tree_node_t *leaf_node                  = NULL;
	libcdata_tree_node_t *sub_node                   = NULL;
	libwrc_data_descriptor_t *data_descriptor        = NULL;
	libwrc_language_entry_t *existing_language_entry = NULL;
	libwrc_language_entry_t *language_entry          = NULL;
	libwrc_resource_values_t *leaf_resource_values   = NULL;
	libwrc_resource_values_t *sub_resource_values    = NULL;
	const char *resource_type_string                 = NULL;
	static char *function                            = "libwrc_resource_read_value";
	int entry_index                                  = 0;
	int leaf_node_index                              = 0;
	int number_of_leaf_nodes                         = 0;
	int number_of_sub_nodes                          = 0;
	int result                                       = 0;
	int sub_node_index                               = 0;

	if( internal_resource == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid resource.",
		 function );

		return( -1 );
	}
	if( internal_resource->resource_node == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid resource - missing resource node.",
		 function );

		return( -1 );
	}
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
	switch( internal_resource->resource_values->type )
	{
		case LIBWRC_RESOURCE_TYPE_STRING:
			resource_type_string = "string";

			result = libwrc_language_table_initialize(
			          (libwrc_language_table_t **) &( internal_resource->value ),
			          error );

			internal_resource->free_value = (int (*)(intptr_t **, libcerror_error_t **)) &libwrc_language_table_free;

			break;

		case LIBWRC_RESOURCE_TYPE_MESSAGE_TABLE:
			resource_type_string = "message table";

			result = libwrc_language_table_initialize(
			          (libwrc_language_table_t **) &( internal_resource->value ),
			          error );

			internal_resource->free_value = (int (*)(intptr_t **, libcerror_error_t **)) &libwrc_language_table_free;

			break;

		case LIBWRC_RESOURCE_TYPE_MANIFEST:
			resource_type_string = "manifest";

			result = libwrc_language_table_initialize(
			          (libwrc_language_table_t **) &( internal_resource->value ),
			          error );

			internal_resource->free_value = (int (*)(intptr_t **, libcerror_error_t **)) &libwrc_language_table_free;

			break;

		case LIBWRC_RESOURCE_TYPE_MUI:
			resource_type_string = "mui";

			result = libwrc_language_table_initialize(
			          (libwrc_language_table_t **) &( internal_resource->value ),
			          error );

			internal_resource->free_value = (int (*)(intptr_t **, libcerror_error_t **)) &libwrc_language_table_free;

			break;

		case LIBWRC_RESOURCE_TYPE_VERSION:
			resource_type_string = "version";

			result = libwrc_language_table_initialize(
			          (libwrc_language_table_t **) &( internal_resource->value ),
			          error );

			internal_resource->free_value = (int (*)(intptr_t **, libcerror_error_t **)) &libwrc_language_table_free;

			break;

		case LIBWRC_RESOURCE_TYPE_WEVT_TEMPLATE:
			resource_type_string = "event template";

			result = libwrc_language_table_initialize(
			          (libwrc_language_table_t **) &( internal_resource->value ),
			          error );

			internal_resource->free_value = (int (*)(intptr_t **, libcerror_error_t **)) &libwrc_language_table_free;

			break;

		default:
#if defined( HAVE_DEBUG_OUTPUT )
			resource_type_string = "UNKNOWN";

			result = 1;

			break;
#else
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
			 "%s: unsupported resource type: 0x%08" PRIx32 ".",
			 function,
			 internal_resource->resource_values->type );

			goto on_error;
#endif
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create %s resource.",
		 function,
		 resource_type_string );

		goto on_error;
	}
	if( libcdata_tree_node_get_number_of_sub_nodes(
	     internal_resource->resource_node,
	     &number_of_sub_nodes,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of sub nodes.",
		 function );

		goto on_error;
	}
	if( ( internal_resource->resource_values->type == LIBWRC_RESOURCE_TYPE_MESSAGE_TABLE )
	 || ( internal_resource->resource_values->type == LIBWRC_RESOURCE_TYPE_VERSION )
	 || ( internal_resource->resource_values->type == LIBWRC_RESOURCE_TYPE_MANIFEST )
	 || ( internal_resource->resource_values->type == LIBWRC_RESOURCE_TYPE_MUI )
	 || ( internal_resource->resource_values->type == LIBWRC_RESOURCE_TYPE_WEVT_TEMPLATE ) )
	{
		if( number_of_sub_nodes != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
			 "%s: unsupported number of sub nodes: %d.",
			 function,
			 number_of_sub_nodes );

			goto on_error;
		}
	}
	for( sub_node_index = 0;
	     sub_node_index < number_of_sub_nodes;
	     sub_node_index++ )
	{
		if( libcdata_tree_node_get_sub_node_by_index(
		     internal_resource->resource_node,
		     sub_node_index,
		     &sub_node,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve sub node: %d.",
			 function,
			 sub_node_index );

			goto on_error;
		}
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
		if( libcdata_tree_node_get_number_of_sub_nodes(
		     sub_node,
		     &number_of_leaf_nodes,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve number of leaf nodes.",
			 function );

			goto on_error;
		}
		for( leaf_node_index = 0;
		     leaf_node_index < number_of_leaf_nodes;
		     leaf_node_index++ )
		{
			if( libcdata_tree_node_get_sub_node_by_index(
			     sub_node,
			     leaf_node_index,
			     &leaf_node,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to retrieve leaf node: %d.",
				 function,
				 leaf_node_index );

				goto on_error;
			}
			if( libcdata_tree_node_get_value(
			     leaf_node,
			     (intptr_t **) &leaf_resource_values,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to retrieve value of leaf node: %d.",
				 function,
				 leaf_node_index );

				goto on_error;
			}
			if( leaf_resource_values == NULL )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
				 "%s: invalid leaf resource values: %d.",
				 function,
				 leaf_node_index );

				goto on_error;
			}
			if( leaf_resource_values->data_descriptor == NULL )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
				 "%s: invalid leaf resource values: 0x%08" PRIx32 " - missing data descriptor.",
				 function,
				 leaf_resource_values->identifier );

				goto on_error;
			}
			data_descriptor = leaf_resource_values->data_descriptor;

			switch( internal_resource->resource_values->type )
			{
				case LIBWRC_RESOURCE_TYPE_STRING:
					result = libwrc_language_table_get_entry_by_identifier(
						  (libwrc_language_table_t *) internal_resource->value,
						  leaf_resource_values->identifier,
						  &existing_language_entry,
						  error );

					if( result == -1 )
					{
						libcerror_error_set(
						 error,
						 LIBCERROR_ERROR_DOMAIN_RUNTIME,
						 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
						 "%s: unable to retrieve number of language entry: 0x%08" PRIx32 ".",
						 function );

						goto on_error;
					}
					if( existing_language_entry != NULL )
					{
						language_entry = existing_language_entry;
					}
					else
					{
						if( libwrc_language_entry_initialize(
						     &language_entry,
						     leaf_resource_values->identifier,
						     (int (*)(intptr_t **, libcerror_error_t **)) &libfvalue_value_free,
						     error ) != 1 )
						{
							libcerror_error_set(
							 error,
							 LIBCERROR_ERROR_DOMAIN_RUNTIME,
							 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
							 "%s: unable to create language entry.",
							 function );

							goto on_error;
						}
					}
					break;

				case LIBWRC_RESOURCE_TYPE_MANIFEST:
				case LIBWRC_RESOURCE_TYPE_MESSAGE_TABLE:
					if( libwrc_language_entry_initialize(
					     &language_entry,
					     leaf_resource_values->identifier,
					     (int (*)(intptr_t **, libcerror_error_t **)) &libfvalue_value_free,
					     error ) != 1 )
					{
						libcerror_error_set(
						 error,
						 LIBCERROR_ERROR_DOMAIN_RUNTIME,
						 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
						 "%s: unable to create language entry.",
						 function );

						goto on_error;
					}
					break;

				case LIBWRC_RESOURCE_TYPE_MUI:
					if( libwrc_language_entry_initialize(
					     &language_entry,
					     leaf_resource_values->identifier,
					     (int (*)(intptr_t **, libcerror_error_t **)) &libwrc_mui_values_free,
					     error ) != 1 )
					{
						libcerror_error_set(
						 error,
						 LIBCERROR_ERROR_DOMAIN_RUNTIME,
						 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
						 "%s: unable to create MUI values.",
						 function );

						goto on_error;
					}
					break;

				case LIBWRC_RESOURCE_TYPE_VERSION:
					if( libwrc_language_entry_initialize(
					     &language_entry,
					     leaf_resource_values->identifier,
					     (int (*)(intptr_t **, libcerror_error_t **)) &libwrc_version_values_free,
					     error ) != 1 )
					{
						libcerror_error_set(
						 error,
						 LIBCERROR_ERROR_DOMAIN_RUNTIME,
						 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
						 "%s: unable to create version values.",
						 function );

						goto on_error;
					}
					break;

				case LIBWRC_RESOURCE_TYPE_WEVT_TEMPLATE:
					if( libwrc_language_entry_initialize(
					     &language_entry,
					     leaf_resource_values->identifier,
					     (int (*)(intptr_t **, libcerror_error_t **)) &libfwevt_manifest_free,
					     error ) != 1 )
					{
						libcerror_error_set(
						 error,
						 LIBCERROR_ERROR_DOMAIN_RUNTIME,
						 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
						 "%s: unable to create event template values.",
						 function );

						goto on_error;
					}
					break;
			}
#if defined( HAVE_DEBUG_OUTPUT )
			switch( internal_resource->resource_values->type )
			{
				case LIBWRC_RESOURCE_TYPE_STRING:
					if( libcnotify_verbose != 0 )
					{
						libcnotify_printf(
						 "%s: reading string: 0x%08" PRIx32 " for language identifier: 0x%08" PRIx32 " (%s)\n",
						 function,
						 sub_resource_values->identifier - 1,
						 leaf_resource_values->identifier,
						 libfwnt_locale_identifier_language_tag_get_identifier(
						  leaf_resource_values->identifier & 0x0000ffffUL ) );
					}
					break;

				case LIBWRC_RESOURCE_TYPE_MANIFEST:
				case LIBWRC_RESOURCE_TYPE_MESSAGE_TABLE:
				case LIBWRC_RESOURCE_TYPE_MUI:
				case LIBWRC_RESOURCE_TYPE_VERSION:
				case LIBWRC_RESOURCE_TYPE_WEVT_TEMPLATE:
					if( libcnotify_verbose != 0 )
					{
						libcnotify_printf(
						 "%s: reading %s for language identifier: 0x%08" PRIx32 " (%s)\n",
						 function,
						 resource_type_string,
						 leaf_resource_values->identifier,
						 libfwnt_locale_identifier_language_tag_get_identifier(
						  leaf_resource_values->identifier & 0x0000ffffUL ) );
					}
					break;
			}
#endif
			switch( internal_resource->resource_values->type )
			{
				case LIBWRC_RESOURCE_TYPE_STRING:
					result = libwrc_string_values_read(
					          language_entry,
					          internal_resource->io_handle,
					          internal_resource->file_io_handle,
					          sub_resource_values->identifier - 1,
					          data_descriptor,
					          error );
					break;

				case LIBWRC_RESOURCE_TYPE_MESSAGE_TABLE:
					result = libwrc_message_table_values_read(
					          language_entry,
					          internal_resource->io_handle,
					          internal_resource->file_io_handle,
					          data_descriptor,
					          error );
					break;

				case LIBWRC_RESOURCE_TYPE_MANIFEST:
					result = libwrc_manifest_values_read(
					          language_entry,
					          internal_resource->io_handle,
					          internal_resource->file_io_handle,
					          data_descriptor,
					          error );
					break;

				case LIBWRC_RESOURCE_TYPE_MUI:
					result = libwrc_mui_values_read(
					          language_entry,
					          internal_resource->io_handle,
					          internal_resource->file_io_handle,
					          data_descriptor,
					          error );
					break;

				case LIBWRC_RESOURCE_TYPE_VERSION:
					result = libwrc_version_values_read(
					          language_entry,
					          internal_resource->io_handle,
					          internal_resource->file_io_handle,
					          data_descriptor,
					          error );
					break;

				case LIBWRC_RESOURCE_TYPE_WEVT_TEMPLATE:
					result = libwrc_wevt_template_values_read(
					          language_entry,
					          internal_resource->io_handle,
					          internal_resource->file_io_handle,
					          data_descriptor,
					          error );
					break;

#if defined( HAVE_DEBUG_OUTPUT )
				default:
					if( libwrc_resource_read_data_descriptor(
					     internal_resource,
					     internal_resource->io_handle,
					     internal_resource->file_io_handle,
					     data_descriptor,
					     error ) != 1 )
					{
						libcerror_error_set(
						 error,
						 LIBCERROR_ERROR_DOMAIN_IO,
						 LIBCERROR_IO_ERROR_READ_FAILED,
						 "%s: unable to read unknown resource.",
						 function );

						goto on_error;
					}
					break;
#endif
			}
			switch( internal_resource->resource_values->type )
			{
				case LIBWRC_RESOURCE_TYPE_STRING:
					if( result != 1 )
					{
						libcerror_error_set(
						 error,
						 LIBCERROR_ERROR_DOMAIN_IO,
						 LIBCERROR_IO_ERROR_READ_FAILED,
						 "%s: unable to read %s: 0x%08" PRIx32 " for language identifier: 0x%08" PRIx32 ".",
						 function,
						 resource_type_string,
						 sub_resource_values->identifier,
						 leaf_resource_values->identifier );

						goto on_error;
					}
					if( language_entry != existing_language_entry )
					{
						if( libwrc_language_table_append_entry(
						     (libwrc_language_table_t *) internal_resource->value,
						     &entry_index,
						     language_entry,
						     error ) != 1 )
						{
							libcerror_error_set(
							 error,
							 LIBCERROR_ERROR_DOMAIN_RUNTIME,
							 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
							 "%s: unable to append messages for language identifier: 0x%08" PRIx32 " to languages array.",
							 function,
							 leaf_resource_values->identifier );

							goto on_error;
						}
					}
					language_entry = NULL;

					break;

				case LIBWRC_RESOURCE_TYPE_MANIFEST:
				case LIBWRC_RESOURCE_TYPE_MESSAGE_TABLE:
				case LIBWRC_RESOURCE_TYPE_MUI:
				case LIBWRC_RESOURCE_TYPE_VERSION:
				case LIBWRC_RESOURCE_TYPE_WEVT_TEMPLATE:
					if( result != 1 )
					{
						libcerror_error_set(
						 error,
						 LIBCERROR_ERROR_DOMAIN_IO,
						 LIBCERROR_IO_ERROR_READ_FAILED,
						 "%s: unable to read %s for language identifier: 0x%08" PRIx32 ".",
						 function,
						 resource_type_string,
						 leaf_resource_values->identifier );

						goto on_error;
					}
					if( libwrc_language_table_append_entry(
					     (libwrc_language_table_t *) internal_resource->value,
					     &entry_index,
					     language_entry,
					     error ) != 1 )
					{
						libcerror_error_set(
						 error,
						 LIBCERROR_ERROR_DOMAIN_RUNTIME,
						 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
						 "%s: unable to append %s for language identifier: 0x%08" PRIx32 " to languages array.",
						 function,
						 resource_type_string,
						 leaf_resource_values->identifier );

						goto on_error;
					}
					language_entry = NULL;

					break;
			}
		}
	}
	return( 1 );

on_error:
	if( ( language_entry != NULL )
	 && ( language_entry != existing_language_entry ) )
	{
		libwrc_language_entry_free(
		 &language_entry,
		 NULL );
	}
	if( internal_resource->value != NULL )
	{
		if( internal_resource->free_value != NULL )
		{
			internal_resource->free_value(
			 &( internal_resource->value ),
			 NULL );
		}
		internal_resource->free_value = NULL;
	}
	return( -1 );
}

/* Reads a data descriptor
 * Returns 1 if successful or -1 on error
 */
int libwrc_resource_read_data_descriptor(
     libwrc_internal_resource_t *internal_resource,
     libwrc_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     libwrc_data_descriptor_t *data_descriptor,
     libcerror_error_t **error )
{
	uint8_t *resource_data    = NULL;
	static char *function     = "libwrc_resource_read_data_descriptor";
	off64_t file_offset       = 0;
	size_t resource_data_size = 0;
	ssize_t read_count        = 0;

	if( internal_resource == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid resource.",
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
	file_offset = data_descriptor->virtual_address
	            - io_handle->virtual_address;

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
		 "%s: unable to seek resource data offset: %" PRIi64 ".",
		 function,
		 file_offset );

		goto on_error;
	}
	resource_data_size = (size_t) data_descriptor->size;

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
	read_count = libbfio_handle_read_buffer(
	              file_io_handle,
	              resource_data,
	              resource_data_size,
	              error );

	if( read_count != (ssize_t) resource_data_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read resource data.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: resource data:\n",
		 function );
		libcnotify_print_data(
		 resource_data,
		 resource_data_size,
		 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
	}
#endif
	memory_free(
	 resource_data );

	return( 1 );

on_error:
	if( resource_data != NULL )
	{
		memory_free(
		 resource_data );
	}
	return( -1 );
}

/* Retrieves the number of languages
 * Returns 1 if successful or -1 on error
 */
int libwrc_resource_get_number_of_languages(
     libwrc_resource_t *resource,
     int *number_of_languages,
     libcerror_error_t **error )
{
	libwrc_internal_resource_t *internal_resource = NULL;
	static char *function                         = "libwrc_resource_get_number_of_languages";

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
	if( libwrc_language_table_get_number_of_entries(
	     (libwrc_language_table_t *) internal_resource->value,
	     number_of_languages,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of languages.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves a specific language identifier
 * Returns 1 if successful or -1 on error
 */
int libwrc_resource_get_language_identifier(
     libwrc_resource_t *resource,
     int language_index,
     uint32_t *language_identifier,
     libcerror_error_t **error )
{
	libwrc_internal_resource_t *internal_resource = NULL;
	static char *function                         = "libwrc_resource_get_language_identifier";

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
	if( libwrc_language_table_get_identifier(
	     (libwrc_language_table_t *) internal_resource->value,
	     language_index,
	     language_identifier,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve identifier for language: %d.",
		 function,
		 language_index );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the language specific value
 * Returns 1 if successful or -1 on error
 */
int libwrc_resource_get_value_by_language_identifier(
     libwrc_resource_t *resource,
     int resource_type,
     uint32_t language_identifier,
     int value_index,
     intptr_t **value,
     libcerror_error_t **error )
{
	libwrc_internal_resource_t *internal_resource = NULL;
	libwrc_language_entry_t *language_entry       = NULL;
	static char *function                         = "libwrc_resource_get_value_by_language_identifier";

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
	if( internal_resource->resource_values->type != resource_type )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported resource type: 0x%08" PRIx32 ".",
		 function,
		 internal_resource->resource_values->type );

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
	if( libwrc_language_entry_get_value_by_index(
	     language_entry,
	     value_index,
	     value,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve value: %d.",
		 function,
		 value_index );

		return( -1 );
	}
	return( 1 );
}

