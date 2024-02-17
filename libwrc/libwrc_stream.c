/*
 * Strea, functions
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
#include <memory.h>
#include <narrow_string.h>
#include <types.h>
#include <wide_string.h>

#include "libwrc_codepage.h"
#include "libwrc_debug.h"
#include "libwrc_definitions.h"
#include "libwrc_io_handle.h"
#include "libwrc_libbfio.h"
#include "libwrc_libcdata.h"
#include "libwrc_libcerror.h"
#include "libwrc_libcnotify.h"
#include "libwrc_libuna.h"
#include "libwrc_resource.h"
#include "libwrc_resource_node_entry.h"
#include "libwrc_resource_node_tree.h"
#include "libwrc_stream.h"

/* Creates a stream
 * Make sure the value stream is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libwrc_stream_initialize(
     libwrc_stream_t **stream,
     libcerror_error_t **error )
{
	libwrc_internal_stream_t *internal_stream = NULL;
	static char *function                     = "libwrc_stream_initialize";

	if( stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid stream.",
		 function );

		return( -1 );
	}
	if( *stream != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid stream value already set.",
		 function );

		return( -1 );
	}
	internal_stream = memory_allocate_structure(
	                   libwrc_internal_stream_t );

	if( internal_stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create stream.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     internal_stream,
	     0,
	     sizeof( libwrc_internal_stream_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear stream.",
		 function );

		memory_free(
		 internal_stream );

		return( -1 );
	}
	if( libwrc_io_handle_initialize(
	     &( internal_stream->io_handle ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create IO handle.",
		 function );

		goto on_error;
	}
	*stream = (libwrc_stream_t *) internal_stream;

	return( 1 );

on_error:
	if( internal_stream != NULL )
	{
		memory_free(
		 internal_stream );
	}
	return( -1 );
}

/* Frees a stream
 * Returns 1 if successful or -1 on error
 */
int libwrc_stream_free(
     libwrc_stream_t **stream,
     libcerror_error_t **error )
{
	libwrc_internal_stream_t *internal_stream = NULL;
	static char *function                     = "libwrc_stream_free";
	int result                                = 1;

	if( stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid stream.",
		 function );

		return( -1 );
	}
	if( *stream != NULL )
	{
		internal_stream = (libwrc_internal_stream_t *) *stream;

		if( internal_stream->file_io_handle != NULL )
		{
			if( libwrc_stream_close(
			     *stream,
			     error ) != 0 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_CLOSE_FAILED,
				 "%s: unable to close stream.",
				 function );

				result = -1;
			}
		}
		*stream = NULL;

		if( libwrc_io_handle_free(
		     &( internal_stream->io_handle ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free IO handle.",
			 function );

			result = -1;
		}
		memory_free(
		 internal_stream );
	}
	return( result );
}

/* Signals the stream to abort its current activity
 * Returns 1 if successful or -1 on error
 */
int libwrc_stream_signal_abort(
     libwrc_stream_t *stream,
     libcerror_error_t **error )
{
	libwrc_internal_stream_t *internal_stream = NULL;
	static char *function                     = "libwrc_stream_signal_abort";

	if( stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid stream.",
		 function );

		return( -1 );
	}
	internal_stream = (libwrc_internal_stream_t *) stream;

	if( internal_stream->io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid stream - missing IO handle.",
		 function );

		return( -1 );
	}
	internal_stream->io_handle->abort = 1;

	return( 1 );
}

/* Opens a stream
 * Returns 1 if successful or -1 on error
 */
int libwrc_stream_open(
     libwrc_stream_t *stream,
     const char *filename,
     int access_flags,
     libcerror_error_t **error )
{
	libbfio_handle_t *file_io_handle          = NULL;
	libwrc_internal_stream_t *internal_stream = NULL;
	static char *function                     = "libwrc_stream_open";
	size_t filename_length                    = 0;

	if( stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid stream.",
		 function );

		return( -1 );
	}
	internal_stream = (libwrc_internal_stream_t *) stream;

	if( filename == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid filename.",
		 function );

		return( -1 );
	}
	if( ( ( access_flags & LIBWRC_ACCESS_FLAG_READ ) == 0 )
	 && ( ( access_flags & LIBWRC_ACCESS_FLAG_WRITE ) == 0 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported access flags.",
		 function );

		return( -1 );
	}
	if( ( access_flags & LIBWRC_ACCESS_FLAG_WRITE ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: write access currently not supported.",
		 function );

		return( -1 );
	}
	if( libbfio_file_initialize(
	     &file_io_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create file IO handle.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libbfio_handle_set_track_offsets_read(
	     file_io_handle,
	     1,
	     error ) != 1 )
	{
                libcerror_error_set(
                 error,
                 LIBCERROR_ERROR_DOMAIN_RUNTIME,
                 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
                 "%s: unable to set track offsets read in file IO handle.",
                 function );

		goto on_error;
	}
#endif
	filename_length = narrow_string_length(
	                   filename );

	if( libbfio_file_set_name(
	     file_io_handle,
	     filename,
	     filename_length + 1,
	     error ) != 1 )
	{
                libcerror_error_set(
                 error,
                 LIBCERROR_ERROR_DOMAIN_RUNTIME,
                 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
                 "%s: unable to set filename in file IO handle.",
                 function );

		goto on_error;
	}
	if( libwrc_stream_open_file_io_handle(
	     stream,
	     file_io_handle,
	     access_flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open stream: %s.",
		 function,
		 filename );

		goto on_error;
	}
	internal_stream->file_io_handle_created_in_library = 1;

	return( 1 );

on_error:
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
		 NULL );
	}
	return( -1 );
}

#if defined( HAVE_WIDE_CHARACTER_TYPE )

/* Opens a stream
 * Returns 1 if successful or -1 on error
 */
int libwrc_stream_open_wide(
     libwrc_stream_t *stream,
     const wchar_t *filename,
     int access_flags,
     libcerror_error_t **error )
{
	libbfio_handle_t *file_io_handle          = NULL;
	libwrc_internal_stream_t *internal_stream = NULL;
	static char *function                     = "libwrc_stream_open_wide";
	size_t filename_length                    = 0;

	if( stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid stream.",
		 function );

		return( -1 );
	}
	internal_stream = (libwrc_internal_stream_t *) stream;

	if( filename == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid filename.",
		 function );

		return( -1 );
	}
	if( ( ( access_flags & LIBWRC_ACCESS_FLAG_READ ) == 0 )
	 && ( ( access_flags & LIBWRC_ACCESS_FLAG_WRITE ) == 0 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported access flags.",
		 function );

		return( -1 );
	}
	if( ( access_flags & LIBWRC_ACCESS_FLAG_WRITE ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: write access currently not supported.",
		 function );

		return( -1 );
	}
	if( libbfio_file_initialize(
	     &file_io_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create file IO handle.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libbfio_handle_set_track_offsets_read(
	     file_io_handle,
	     1,
	     error ) != 1 )
	{
                libcerror_error_set(
                 error,
                 LIBCERROR_ERROR_DOMAIN_RUNTIME,
                 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
                 "%s: unable to set track offsets read in file IO handle.",
                 function );

		goto on_error;
	}
#endif
	filename_length = wide_string_length(
	                   filename );

	if( libbfio_file_set_name_wide(
	     file_io_handle,
	     filename,
	     filename_length + 1,
	     error ) != 1 )
	{
                libcerror_error_set(
                 error,
                 LIBCERROR_ERROR_DOMAIN_RUNTIME,
                 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
                 "%s: unable to set filename in file IO handle.",
                 function );

		goto on_error;
	}
	if( libwrc_stream_open_file_io_handle(
	     stream,
	     file_io_handle,
	     access_flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open stream: %ls.",
		 function,
		 filename );

		goto on_error;
	}
	internal_stream->file_io_handle_created_in_library = 1;

	return( 1 );

on_error:
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
		 NULL );
	}
	return( -1 );
}

#endif

/* Opens a stream using a Basic File IO (bfio) handle
 * Returns 1 if successful or -1 on error
 */
int libwrc_stream_open_file_io_handle(
     libwrc_stream_t *stream,
     libbfio_handle_t *file_io_handle,
     int access_flags,
     libcerror_error_t **error )
{
	libwrc_internal_stream_t *internal_stream = NULL;
	static char *function                     = "libwrc_stream_open_file_io_handle";
	int bfio_access_flags                     = 0;
	int file_io_handle_is_open                = 0;

	if( stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid stream.",
		 function );

		return( -1 );
	}
	internal_stream = (libwrc_internal_stream_t *) stream;

	if( internal_stream->file_io_handle != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid stream - file IO handle already set.",
		 function );

		return( -1 );
	}
	if( file_io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file IO handle.",
		 function );

		return( -1 );
	}
	if( ( ( access_flags & LIBWRC_ACCESS_FLAG_READ ) == 0 )
	 && ( ( access_flags & LIBWRC_ACCESS_FLAG_WRITE ) == 0 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported access flags.",
		 function );

		return( -1 );
	}
	if( ( access_flags & LIBWRC_ACCESS_FLAG_WRITE ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: write access currently not supported.",
		 function );

		return( -1 );
	}
	if( ( access_flags & LIBWRC_ACCESS_FLAG_READ ) != 0 )
	{
		bfio_access_flags = LIBBFIO_ACCESS_FLAG_READ;
	}
	file_io_handle_is_open = libbfio_handle_is_open(
	                          file_io_handle,
	                          error );

	if( file_io_handle_is_open == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to determine if file IO handle is open.",
		 function );

		goto on_error;
	}
	else if( file_io_handle_is_open == 0 )
	{
		if( libbfio_handle_open(
		     file_io_handle,
		     bfio_access_flags,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_OPEN_FAILED,
			 "%s: unable to open file IO handle.",
			 function );

			goto on_error;
		}
		internal_stream->file_io_handle_opened_in_library = 1;
	}
	if( libwrc_internal_stream_open_read(
	     internal_stream,
	     file_io_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read from file handle.",
		 function );

		goto on_error;
	}
	internal_stream->file_io_handle = file_io_handle;

	return( 1 );

on_error:
	if( ( file_io_handle_is_open == 0 )
	 && ( internal_stream->file_io_handle_opened_in_library != 0 ) )
	{
		libbfio_handle_close(
		 file_io_handle,
		 error );

		internal_stream->file_io_handle_opened_in_library = 0;
	}
	internal_stream->file_io_handle = NULL;

	return( -1 );
}

/* Closes a stream
 * Returns 0 if successful or -1 on error
 */
int libwrc_stream_close(
     libwrc_stream_t *stream,
     libcerror_error_t **error )
{
	libwrc_internal_stream_t *internal_stream = NULL;
	static char *function                     = "libwrc_stream_close";
	int result                                = 0;

	if( stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid stream.",
		 function );

		return( -1 );
	}
	internal_stream = (libwrc_internal_stream_t *) stream;

	if( internal_stream->file_io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid stream - missing file IO handle.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		if( internal_stream->file_io_handle_created_in_library != 0 )
		{
			if( libwrc_debug_print_read_offsets(
			     internal_stream->file_io_handle,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
				 "%s: unable to print the read offsets.",
				 function );

				result = -1;
			}
		}
	}
#endif
	if( internal_stream->file_io_handle_opened_in_library != 0 )
	{
		if( libbfio_handle_close(
		     internal_stream->file_io_handle,
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
		internal_stream->file_io_handle_opened_in_library = 0;
	}
	if( internal_stream->file_io_handle_created_in_library != 0 )
	{
		if( libbfio_handle_free(
		     &( internal_stream->file_io_handle ),
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
		internal_stream->file_io_handle_created_in_library = 0;
	}
	internal_stream->file_io_handle = NULL;

	if( libwrc_io_handle_clear(
	     internal_stream->io_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to clear IO handle.",
		 function );

		result = -1;
	}
	if( libcdata_tree_node_free(
	     &( internal_stream->resources_root_node ),
	     (int (*)(intptr_t **, libcerror_error_t **)) &libwrc_resource_node_entry_free,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free resources root node.",
		 function );

		result = -1;
	}
	return( result );
}

/* Opens a stream for reading
 * Returns 1 if successful or -1 on error
 */
int libwrc_internal_stream_open_read(
     libwrc_internal_stream_t *internal_stream,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error )
{
	static char *function = "libwrc_internal_stream_open_read";

	if( internal_stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid stream.",
		 function );

		return( -1 );
	}
	if( internal_stream->io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid stream - missing IO handle.",
		 function );

		return( -1 );
	}
	if( internal_stream->io_handle->abort != 0 )
	{
		internal_stream->io_handle->abort = 0;
	}
	internal_stream->io_handle->virtual_address = internal_stream->virtual_address;

	if( libbfio_handle_get_size(
	     file_io_handle,
	     &( internal_stream->io_handle->stream_size ),
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
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "Reading resource node tree:\n" );
	}
#endif
	if( libcdata_tree_node_initialize(
	     &( internal_stream->resources_root_node ),
	     error ) == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create resources root node.",
		 function );

		goto on_error;
	}
	if( libwrc_resource_node_tree_read_node(
	     internal_stream->resources_root_node,
	     internal_stream->io_handle,
	     file_io_handle,
	     0,
	     1,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read resources root node.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( internal_stream->resources_root_node != NULL )
	{
		libcdata_tree_node_free(
		 &( internal_stream->resources_root_node ),
		 (int (*)(intptr_t **, libcerror_error_t **)) &libwrc_resource_node_entry_free,
		 NULL );
	}
	return( -1 );
}

/* Retrieves the stream ASCII codepage
 * Returns 1 if successful or -1 on error
 */
int libwrc_stream_get_ascii_codepage(
     libwrc_stream_t *stream,
     int *ascii_codepage,
     libcerror_error_t **error )
{
	libwrc_internal_stream_t *internal_stream = NULL;
	static char *function                     = "libwrc_stream_get_ascii_codepage";

	if( stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid stream.",
		 function );

		return( -1 );
	}
	internal_stream = (libwrc_internal_stream_t *) stream;

	if( internal_stream->io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid stream - missing IO handle.",
		 function );

		return( -1 );
	}
	if( ascii_codepage == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid ASCII codepage.",
		 function );

		return( -1 );
	}
	*ascii_codepage = internal_stream->io_handle->ascii_codepage;

	return( 1 );
}

/* Sets the stream ASCII codepage
 * Returns 1 if successful or -1 on error
 */
int libwrc_stream_set_ascii_codepage(
     libwrc_stream_t *stream,
     int ascii_codepage,
     libcerror_error_t **error )
{
	libwrc_internal_stream_t *internal_stream = NULL;
	static char *function                     = "libwrc_stream_set_ascii_codepage";

	if( stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid stream.",
		 function );

		return( -1 );
	}
	internal_stream = (libwrc_internal_stream_t *) stream;

	if( internal_stream->io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid stream - missing IO handle.",
		 function );

		return( -1 );
	}
	if( ( ascii_codepage != LIBWRC_CODEPAGE_ASCII )
	 && ( ascii_codepage != LIBWRC_CODEPAGE_WINDOWS_874 )
	 && ( ascii_codepage != LIBWRC_CODEPAGE_WINDOWS_932 )
	 && ( ascii_codepage != LIBWRC_CODEPAGE_WINDOWS_936 )
	 && ( ascii_codepage != LIBWRC_CODEPAGE_WINDOWS_949 )
	 && ( ascii_codepage != LIBWRC_CODEPAGE_WINDOWS_950 )
	 && ( ascii_codepage != LIBWRC_CODEPAGE_WINDOWS_1250 )
	 && ( ascii_codepage != LIBWRC_CODEPAGE_WINDOWS_1251 )
	 && ( ascii_codepage != LIBWRC_CODEPAGE_WINDOWS_1252 )
	 && ( ascii_codepage != LIBWRC_CODEPAGE_WINDOWS_1253 )
	 && ( ascii_codepage != LIBWRC_CODEPAGE_WINDOWS_1254 )
	 && ( ascii_codepage != LIBWRC_CODEPAGE_WINDOWS_1255 )
	 && ( ascii_codepage != LIBWRC_CODEPAGE_WINDOWS_1256 )
	 && ( ascii_codepage != LIBWRC_CODEPAGE_WINDOWS_1257 )
	 && ( ascii_codepage != LIBWRC_CODEPAGE_WINDOWS_1258 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported ASCII codepage.",
		 function );

		return( -1 );
	}
	internal_stream->io_handle->ascii_codepage = ascii_codepage;

	return( 1 );
}

/* Retrieves the virtual address
 * Returns 1 if successful or -1 on error
 */
int libwrc_stream_get_virtual_address(
     libwrc_stream_t *stream,
     uint32_t *virtual_address,
     libcerror_error_t **error )
{
	libwrc_internal_stream_t *internal_stream = NULL;
	static char *function                     = "libwrc_stream_get_virtual_address";

	if( stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid stream.",
		 function );

		return( -1 );
	}
	internal_stream = (libwrc_internal_stream_t *) stream;

	if( virtual_address == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid virtual address.",
		 function );

		return( -1 );
	}
	*virtual_address = internal_stream->virtual_address;

	return( 1 );
}

/* Sets the virtual address
 * Returns 1 if successful or -1 on error
 */
int libwrc_stream_set_virtual_address(
     libwrc_stream_t *stream,
     uint32_t virtual_address,
     libcerror_error_t **error )
{
	libwrc_internal_stream_t *internal_stream = NULL;
	static char *function                     = "libwrc_stream_set_virtual_address";

	if( stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid stream.",
		 function );

		return( -1 );
	}
	internal_stream = (libwrc_internal_stream_t *) stream;

	internal_stream->virtual_address = virtual_address;

	return( 1 );
}

/* Retrieves the number of resources
 * Returns 1 if successful or -1 on error
 */
int libwrc_stream_get_number_of_resources(
     libwrc_stream_t *stream,
     int *number_of_resources,
     libcerror_error_t **error )
{
	libwrc_internal_stream_t *internal_stream = NULL;
	static char *function                     = "libwrc_stream_get_number_of_resources";

	if( stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid stream.",
		 function );

		return( -1 );
	}
	internal_stream = (libwrc_internal_stream_t *) stream;

	if( libcdata_tree_node_get_number_of_sub_nodes(
	     internal_stream->resources_root_node,
	     number_of_resources,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of resources.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves a specific resource
 * Returns 1 if successful or -1 on error
 */
int libwrc_stream_get_resource_by_index(
     libwrc_stream_t *stream,
     int resource_index,
     libwrc_resource_t **resource,
     libcerror_error_t **error )
{
	libcdata_tree_node_t *resource_node       = NULL;
	libwrc_internal_stream_t *internal_stream = NULL;
	static char *function                     = "libwrc_stream_get_resource_by_index";

	if( stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid stream.",
		 function );

		return( -1 );
	}
	internal_stream = (libwrc_internal_stream_t *) stream;

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
	if( libcdata_tree_node_get_sub_node_by_index(
	     internal_stream->resources_root_node,
	     resource_index,
	     &resource_node,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve event resource node: %d.",
		 function,
		 resource_index );

		return( -1 );
	}
	if( libwrc_resource_initialize(
	     resource,
	     internal_stream->io_handle,
	     internal_stream->file_io_handle,
	     resource_node,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create resource.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves a specific resource by identifier
 * Returns 1 if successful, 0 if no such resource or -1 on error
 */
int libwrc_stream_get_resource_by_identifier(
     libwrc_stream_t *stream,
     uint32_t identifier,
     libwrc_resource_t **resource,
     libcerror_error_t **error )
{
	libcdata_tree_node_t *resource_node               = NULL;
	libwrc_internal_stream_t *internal_stream         = NULL;
	libwrc_resource_node_entry_t *resource_node_entry = NULL;
	static char *function                             = "libwrc_stream_get_resource_by_identifier";
	int number_of_resources                           = 0;
	int resource_index                                = 0;

	if( stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid stream.",
		 function );

		return( -1 );
	}
	internal_stream = (libwrc_internal_stream_t *) stream;

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
	if( internal_stream->resources_root_node != NULL )
	{
		if( libcdata_tree_node_get_number_of_sub_nodes(
		     internal_stream->resources_root_node,
		     &number_of_resources,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve number of resources.",
			 function );

			return( -1 );
		}
		if( libcdata_tree_node_get_sub_node_by_index(
		     internal_stream->resources_root_node,
		     0,
		     &resource_node,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve first resource node.",
			 function );

			return( -1 );
		}
		for( resource_index = 0;
		     resource_index < number_of_resources;
		     resource_index++ )
		{
			if( libcdata_tree_node_get_value(
			     resource_node,
			     (intptr_t **) &resource_node_entry,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to retrieve resource node: %d entry.",
				 function,
				 resource_index );

				return( -1 );
			}
			if( resource_node_entry == NULL )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
				 "%s: missing resource node: %d entry.",
				 function,
				 resource_index );

				return( -1 );
			}
			if( identifier == resource_node_entry->identifier )
			{
				if( libwrc_resource_initialize(
				     resource,
				     internal_stream->io_handle,
				     internal_stream->file_io_handle,
				     resource_node,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
					 "%s: unable to create resource.",
					 function );

					return( -1 );
				}
				return( 1 );
			}
			if( libcdata_tree_node_get_next_node(
			     resource_node,
			     &resource_node,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to retrieve next node of resource node: %d.",
				 function,
				 resource_index );

				return( -1 );
			}
		}
	}
	return( 0 );
}

/* Retrieves a specific resource by type
 * Returns 1 if successful, 0 if no such resource or -1 on error
 */
int libwrc_stream_get_resource_by_type(
     libwrc_stream_t *stream,
     int type,
     libwrc_resource_t **resource,
     libcerror_error_t **error )
{
	libcdata_tree_node_t *resource_node               = NULL;
	libwrc_internal_stream_t *internal_stream         = NULL;
	libwrc_resource_node_entry_t *resource_node_entry = NULL;
	static char *function                             = "libwrc_stream_get_resource_by_type";
	int number_of_resources                           = 0;
	int resource_index                                = 0;

	if( stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid stream.",
		 function );

		return( -1 );
	}
	internal_stream = (libwrc_internal_stream_t *) stream;

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
	if( libcdata_tree_node_get_number_of_sub_nodes(
	     internal_stream->resources_root_node,
	     &number_of_resources,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of resources.",
		 function );

		return( -1 );
	}
	if( libcdata_tree_node_get_sub_node_by_index(
	     internal_stream->resources_root_node,
	     0,
	     &resource_node,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve first resource node.",
		 function );

		return( -1 );
	}
	for( resource_index = 0;
	     resource_index < number_of_resources;
	     resource_index++ )
	{
		if( libcdata_tree_node_get_value(
		     resource_node,
		     (intptr_t **) &resource_node_entry,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve resource node: %d entry.",
			 function,
			 resource_index );

			return( -1 );
		}
		if( resource_node_entry == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: missing resource node: %d entry.",
			 function,
			 resource_index );

			return( -1 );
		}
		if( type == resource_node_entry->type )
		{
			if( libwrc_resource_initialize(
			     resource,
			     internal_stream->io_handle,
			     internal_stream->file_io_handle,
			     resource_node,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
				 "%s: unable to create resource.",
				 function );

				return( -1 );
			}
			return( 1 );
		}
		if( libcdata_tree_node_get_next_node(
		     resource_node,
		     &resource_node,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve next node of resource node: %d.",
			 function,
			 resource_index );

			return( -1 );
		}
	}
	return( 0 );
}

/* Retrieves a specific resource by an UTF-8 formatted name
 * Returns 1 if successful, 0 if no such resource or -1 on error
 */
int libwrc_stream_get_resource_by_utf8_name(
     libwrc_stream_t *stream,
     const uint8_t *utf8_string,
     size_t utf8_string_length,
     libwrc_resource_t **resource,
     libcerror_error_t **error )
{
	libcdata_tree_node_t *resource_node               = NULL;
	libwrc_internal_stream_t *internal_stream         = NULL;
	libwrc_resource_node_entry_t *resource_node_entry = NULL;
	static char *function                             = "libwrc_stream_get_resource_by_type";
	int number_of_resources                           = 0;
	int resource_index                                = 0;
	int result                                        = 0;

	if( stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid stream.",
		 function );

		return( -1 );
	}
	internal_stream = (libwrc_internal_stream_t *) stream;

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
	if( libcdata_tree_node_get_number_of_sub_nodes(
	     internal_stream->resources_root_node,
	     &number_of_resources,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of resources.",
		 function );

		return( -1 );
	}
	if( libcdata_tree_node_get_sub_node_by_index(
	     internal_stream->resources_root_node,
	     0,
	     &resource_node,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve first resource node.",
		 function );

		return( -1 );
	}
	for( resource_index = 0;
	     resource_index < number_of_resources;
	     resource_index++ )
	{
		if( libcdata_tree_node_get_value(
		     resource_node,
		     (intptr_t **) &resource_node_entry,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve resource node: %d entry.",
			 function,
			 resource_index );

			return( -1 );
		}
		if( resource_node_entry == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: missing resource node: %d entry.",
			 function,
			 resource_index );

			return( -1 );
		}
		if( resource_node_entry->name_string_size > 0 )
		{
			result = libuna_utf8_string_compare_with_utf16_stream(
			          utf8_string,
			          utf8_string_length + 1,
			          resource_node_entry->name_string,
			          resource_node_entry->name_string_size,
			          LIBUNA_ENDIAN_LITTLE,
			          error );

			if( result == -1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GENERIC,
				 "%s: unable to compare name of resource node: %d.",
				 function,
				 resource_index );

				return( -1 );
			}
			else if( result == LIBUNA_COMPARE_EQUAL )
			{
				if( libwrc_resource_initialize(
				     resource,
				     internal_stream->io_handle,
				     internal_stream->file_io_handle,
				     resource_node,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
					 "%s: unable to create resource.",
					 function );

					return( -1 );
				}
				return( 1 );
			}
		}
		if( libcdata_tree_node_get_next_node(
		     resource_node,
		     &resource_node,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve next node of resource node: %d.",
			 function,
			 resource_index );

			return( -1 );
		}
	}
	return( 0 );
}

/* Retrieves a specific resource by an UTF-16 formatted name
 * Returns 1 if successful, 0 if no such resource or -1 on error
 */
int libwrc_stream_get_resource_by_utf16_name(
     libwrc_stream_t *stream,
     const uint16_t *utf16_string,
     size_t utf16_string_length,
     libwrc_resource_t **resource,
     libcerror_error_t **error )
{
	libcdata_tree_node_t *resource_node               = NULL;
	libwrc_internal_stream_t *internal_stream         = NULL;
	libwrc_resource_node_entry_t *resource_node_entry = NULL;
	static char *function                             = "libwrc_stream_get_resource_by_type";
	int number_of_resources                           = 0;
	int resource_index                                = 0;
	int result                                        = 0;

	if( stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid stream.",
		 function );

		return( -1 );
	}
	internal_stream = (libwrc_internal_stream_t *) stream;

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
	if( libcdata_tree_node_get_number_of_sub_nodes(
	     internal_stream->resources_root_node,
	     &number_of_resources,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of resources.",
		 function );

		return( -1 );
	}
	if( libcdata_tree_node_get_sub_node_by_index(
	     internal_stream->resources_root_node,
	     0,
	     &resource_node,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve first resource node.",
		 function );

		return( -1 );
	}
	for( resource_index = 0;
	     resource_index < number_of_resources;
	     resource_index++ )
	{
		if( libcdata_tree_node_get_value(
		     resource_node,
		     (intptr_t **) &resource_node_entry,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve resource node: %d entry.",
			 function,
			 resource_index );

			return( -1 );
		}
		if( resource_node_entry == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: missing resource node: %d entry.",
			 function,
			 resource_index );

			return( -1 );
		}
		if( resource_node_entry->name_string_size > 0 )
		{
			result = libuna_utf16_string_compare_with_utf16_stream(
			          utf16_string,
			          utf16_string_length + 1,
			          resource_node_entry->name_string,
			          resource_node_entry->name_string_size,
			          LIBUNA_ENDIAN_LITTLE,
			          error );

			if( result == -1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GENERIC,
				 "%s: unable to compare name of resource node: %d.",
				 function,
				 resource_index );

				return( -1 );
			}
			else if( result == LIBUNA_COMPARE_EQUAL )
			{
				if( libwrc_resource_initialize(
				     resource,
				     internal_stream->io_handle,
				     internal_stream->file_io_handle,
				     resource_node,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
					 "%s: unable to create resource.",
					 function );

					return( -1 );
				}
				return( 1 );
			}
		}
		if( libcdata_tree_node_get_next_node(
		     resource_node,
		     &resource_node,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve next node of resource node: %d.",
			 function,
			 resource_index );

			return( -1 );
		}
	}
	return( 0 );
}

