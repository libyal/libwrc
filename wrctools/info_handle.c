/*
 * Info handle
 *
 * Copyright (C) 2011-2021, Joachim Metz <joachim.metz@gmail.com>
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
#include <file_stream.h>
#include <memory.h>
#include <narrow_string.h>
#include <system_string.h>
#include <types.h>
#include <wide_string.h>

#include "info_handle.h"
#include "wrctools_libbfio.h"
#include "wrctools_libcerror.h"
#include "wrctools_libclocale.h"
#include "wrctools_libexe.h"
#include "wrctools_libfwnt.h"
#include "wrctools_libwrc.h"

#define INFO_HANDLE_NOTIFY_STREAM	stdout

#if !defined( LIBEXE_HAVE_BFIO )

LIBEXE_EXTERN \
int libexe_section_get_data_file_io_handle(
     libexe_section_t *section,
     libbfio_handle_t **file_io_handle,
     libcerror_error_t **error );

#endif /* !defined( LIBEXE_HAVE_BFIO ) */

#if !defined( LIBWRC_HAVE_BFIO )

extern \
int libwrc_stream_open_file_io_handle(
     libwrc_stream_t *stream,
     libbfio_handle_t *file_io_handle,
     int access_flags,
     libcerror_error_t **error );

#endif /* !defined( LIBWRC_HAVE_BFIO ) */

/* Creates an info handle
 * Make sure the value info_handle is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int info_handle_initialize(
     info_handle_t **info_handle,
     libcerror_error_t **error )
{
	static char *function = "info_handle_initialize";

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	if( *info_handle != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid info handle value already set.",
		 function );

		return( -1 );
	}
	*info_handle = memory_allocate_structure(
	                info_handle_t );

	if( *info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create info handle.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *info_handle,
	     0,
	     sizeof( info_handle_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear info handle.",
		 function );

		memory_free(
		 *info_handle );

		*info_handle = NULL;

		return( -1 );
	}
	if( libexe_file_initialize(
	     &( ( *info_handle )->input_exe_file ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to initialize input EXE file.",
		 function );

		goto on_error;
	}
	if( libwrc_stream_initialize(
	     &( ( *info_handle )->input_resource_stream ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to initialize input resource stream.",
		 function );

		goto on_error;
	}
	( *info_handle )->ascii_codepage = LIBWRC_CODEPAGE_WINDOWS_1252;
	( *info_handle )->notify_stream  = INFO_HANDLE_NOTIFY_STREAM;

	return( 1 );

on_error:
	if( *info_handle != NULL )
	{
		if( ( *info_handle )->input_resource_stream != NULL )
		{
			libwrc_stream_free(
			 &( ( *info_handle )->input_resource_stream ),
			 NULL );
		}
		if( ( *info_handle )->input_exe_file != NULL )
		{
			libexe_file_free(
			 &( ( *info_handle )->input_exe_file ),
			 NULL );
		}
		memory_free(
		 *info_handle );

		*info_handle = NULL;
	}
	return( -1 );
}

/* Frees an info handle
 * Returns 1 if successful or -1 on error
 */
int info_handle_free(
     info_handle_t **info_handle,
     libcerror_error_t **error )
{
	static char *function = "info_handle_free";
	int result            = 1;

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	if( *info_handle != NULL )
	{
		if( libwrc_stream_free(
		     &( ( *info_handle )->input_resource_stream ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free input resource stream.",
			 function );

			result = -1;
		}
		if( ( *info_handle )->resource_section_file_io_handle != NULL )
		{
			if( libbfio_handle_free(
			     &( ( *info_handle )->resource_section_file_io_handle ),
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
				 "%s: unable to free resource section file IO handle.",
				 function );

				result = -1;
			}
		}
		if( ( *info_handle )->resource_section != NULL )
		{
			if( libexe_section_free(
			     &( ( *info_handle )->resource_section ),
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
				 "%s: unable to free resource section.",
				 function );

				result = -1;
			}
		}
		if( libexe_file_free(
		     &( ( *info_handle )->input_exe_file ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free input EXE file.",
			 function );

			result = -1;
		}
		memory_free(
		 *info_handle );

		*info_handle = NULL;
	}
	return( result );
}

/* Signals the info handle to abort
 * Returns 1 if successful or -1 on error
 */
int info_handle_signal_abort(
     info_handle_t *info_handle,
     libcerror_error_t **error )
{
	static char *function = "info_handle_signal_abort";

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	info_handle->abort = 1;

	if( info_handle->input_resource_stream != NULL )
	{
		if( libwrc_stream_signal_abort(
		     info_handle->input_resource_stream,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to signal input resource stream to abort.",
			 function );

			return( -1 );
		}
		if( libexe_file_signal_abort(
		     info_handle->input_exe_file,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to signal input EXE file to abort.",
			 function );

			return( -1 );
		}
	}
	return( 1 );
}

/* Sets the ascii codepage
 * Returns 1 if successful or -1 on error
 */
int info_handle_set_ascii_codepage(
     info_handle_t *info_handle,
     const system_character_t *string,
     libcerror_error_t **error )
{
	static char *function  = "info_handle_set_ascii_codepage";
	size_t string_length   = 0;
	uint32_t feature_flags = 0;
	int result             = 0;

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	feature_flags = LIBCLOCALE_CODEPAGE_FEATURE_FLAG_HAVE_KOI8
	              | LIBCLOCALE_CODEPAGE_FEATURE_FLAG_HAVE_WINDOWS;

	string_length = system_string_length(
	                 string );

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libclocale_codepage_copy_from_string_wide(
	          &( info_handle->ascii_codepage ),
	          string,
	          string_length,
	          feature_flags,
	          error );
#else
	result = libclocale_codepage_copy_from_string(
	          &( info_handle->ascii_codepage ),
	          string,
	          string_length,
	          feature_flags,
	          error );
#endif
	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to determine ASCII codepage.",
		 function );

		return( -1 );
	}
	return( result );
}

/* Opens the input
 * Returns 1 if successful, 0 if no resource stream could be found or -1 on error
 */
int info_handle_open_input(
     info_handle_t *info_handle,
     const system_character_t *filename,
     libcerror_error_t **error )
{
	static char *function    = "info_handle_open_input";
	uint32_t virtual_address = 0;
	int result               = 0;

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	if( libexe_file_open_wide(
	     info_handle->input_exe_file,
	     filename,
	     LIBEXE_OPEN_READ,
	     error ) != 1 )
#else
	if( libexe_file_open(
	     info_handle->input_exe_file,
	     filename,
	     LIBEXE_OPEN_READ,
	     error ) != 1 )
#endif
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open input EXE file.",
		 function );

		goto on_error;
	}
	result = libexe_file_get_section_by_name(
	          info_handle->input_exe_file,
	          ".rsrc",
	          5,
	          &( info_handle->resource_section ),
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve resource section.",
		 function );

		goto on_error;
	}
	else if( result != 0 )
	{
		if( libexe_section_get_virtual_address(
		     info_handle->resource_section,
		     &virtual_address,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve resource section virtual adress.",
			 function );

			goto on_error;
		}
		if( libexe_section_get_data_file_io_handle(
		     info_handle->resource_section,
		     &( info_handle->resource_section_file_io_handle ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve resource section file IO handle.",
			 function );

			goto on_error;
		}
		if( libwrc_stream_set_virtual_address(
		     info_handle->input_resource_stream,
		     virtual_address,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to set input resource stream virtual adress.",
			 function );

			goto on_error;
		}
		if( libwrc_stream_open_file_io_handle(
		     info_handle->input_resource_stream,
		     info_handle->resource_section_file_io_handle,
		     LIBWRC_OPEN_READ,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_OPEN_FAILED,
			 "%s: unable to open input resource stream.",
			 function );

			goto on_error;
		}
	}
	return( result );

on_error:
	if( info_handle->resource_section_file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &( info_handle->resource_section_file_io_handle ),
		 NULL );
	}
	if( info_handle->resource_section != NULL )
	{
		libexe_section_free(
		 &( info_handle->resource_section ),
		 NULL );
	}
	libexe_file_close(
	 info_handle->input_exe_file,
	 NULL );

	return( -1 );
}

/* Closes the input
 * Returns the 0 if succesful or -1 on error
 */
int info_handle_close_input(
     info_handle_t *info_handle,
     libcerror_error_t **error )
{
	static char *function = "info_handle_close_input";

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	if( libwrc_stream_close(
	     info_handle->input_resource_stream,
	     error ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_CLOSE_FAILED,
		 "%s: unable to close input resource stream.",
		 function );

		return( -1 );
	}
	if( libexe_file_close(
	     info_handle->input_exe_file,
	     error ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_CLOSE_FAILED,
		 "%s: unable to close input EXE file.",
		 function );

		return( -1 );
	}
	return( 0 );
}

/* Prints the manifest string information
 * Returns 1 if successful or -1 on error
 */
int info_handle_manifest_string_fprint(
     info_handle_t *info_handle,
     libwrc_resource_t *manifest_resource,
     uint32_t language_identifier,
     libcerror_error_t **error )
{
	system_character_t *value_string = NULL;
	static char *function            = "info_handle_manifest_string_fprint";
	size_t value_string_size         = 0;
	int result                       = 0;

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libwrc_manifest_get_utf16_string_size(
	          manifest_resource,
	          language_identifier,
	          &value_string_size,
	          error );
#else
	result = libwrc_manifest_get_utf8_string_size(
	          manifest_resource,
	          language_identifier,
	          &value_string_size,
	          error );
#endif
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve manifest string size.",
		 function );

		goto on_error;
	}
	if( value_string_size > 0 )
	{
		value_string = system_string_allocate(
		                value_string_size );

		if( value_string == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create value string.",
			 function );

			goto on_error;
		}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
		result = libwrc_manifest_get_utf16_string(
		          manifest_resource,
		          language_identifier,
		          (uint16_t *) value_string,
		          value_string_size,
		          error );
#else
		result = libwrc_manifest_get_utf8_string(
		          manifest_resource,
		          language_identifier,
		          (uint8_t *) value_string,
		          value_string_size,
		          error );
#endif
		if( result != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve manifest string.",
			 function );

			goto on_error;
		}
		fprintf(
		 info_handle->notify_stream,
		 "\tdata\t\t\t: %" PRIs_SYSTEM "\n",
		 value_string );

		memory_free(
		 value_string );

		value_string = NULL;
	}
	fprintf(
	 info_handle->notify_stream,
	 "\n" );

	return( 1 );

on_error:
	if( value_string != NULL )
	{
		memory_free(
		 value_string );
	}
	return( -1 );
}

/* Prints the manifest resource information
 * Returns 1 if successful or -1 on error
 */
int info_handle_manifest_resource_fprint(
     info_handle_t *info_handle,
     libcerror_error_t **error )
{
	libwrc_resource_t *manifest_resource = NULL;
	static char *function                = "info_handle_manifest_resource_fprint";
	uint32_t language_identifier         = 0;
	int language_index                   = 0;
	int number_of_languages              = 0;
	int result                           = 0;

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	result = libwrc_stream_get_resource_by_identifier(
	          info_handle->input_resource_stream,
	          LIBWRC_RESOURCE_IDENTIFIER_MANIFEST,
	          &manifest_resource,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve manifest resource.",
		 function );

		goto on_error;
	}
	else if( result != 0 )
	{
		fprintf(
		 info_handle->notify_stream,
		 "Manifest resource:\n" );

		if( libwrc_resource_get_number_of_languages(
		     manifest_resource,
		     &number_of_languages,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve number of languages.",
			 function );

			goto on_error;
		}
		fprintf(
		 info_handle->notify_stream,
		 "\tnumber of languages\t: %d\n",
		 number_of_languages );

		fprintf(
		 info_handle->notify_stream,
		 "\n" );

		for( language_index = 0;
		     language_index < number_of_languages;
		     language_index++ )
		{
			if( libwrc_resource_get_language_identifier(
			     manifest_resource,
			     language_index,
			     &language_identifier,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to retrieve language identifier: %d.",
				 function,
				 language_index );

				goto on_error;
			}
			fprintf(
			 info_handle->notify_stream,
			 "\tlanguage identifier\t: 0x%08" PRIx32 " (%s)\n",
			 language_identifier,
			 libfwnt_locale_identifier_language_tag_get_identifier(
			  language_identifier & 0x0000ffffUL ) );

			if( info_handle_manifest_string_fprint(
			     info_handle,
			     manifest_resource,
			     language_identifier,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
				 "%s: unable to print manifest string for language identifier: 0x%08" PRIx32 ".",
				 function,
				 language_identifier );

				goto on_error;
			}
		}
		if( libwrc_resource_free(
		     &manifest_resource,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free manifest resource.",
			 function );

			goto on_error;
		}
	}
	return( 1 );

on_error:
	if( manifest_resource != NULL )
	{
		libwrc_resource_free(
		 &manifest_resource,
		 NULL );
	}
	return( -1 );
}

/* Prints the message table string information
 * Returns 1 if successful or -1 on error
 */
int info_handle_message_table_string_fprint(
     info_handle_t *info_handle,
     libwrc_resource_t *message_table_resource,
     uint32_t language_identifier,
     int message_index,
     libcerror_error_t **error )
{
	system_character_t *value_string = NULL;
	static char *function            = "info_handle_message_table_string_fprint";
	size_t value_string_size         = 0;
	uint32_t message_identifier      = 0;
	int result                       = 0;

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	if( libwrc_message_table_get_identifier(
	     message_table_resource,
	     language_identifier,
	     message_index,
	     &message_identifier,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve message identifier: %d.",
		 function,
		 message_index );

		goto on_error;
	}
	fprintf(
	 info_handle->notify_stream,
	 "\tmessage\t\t\t: %d\n",
	 message_index );

	fprintf(
	 info_handle->notify_stream,
	 "\tidentifier\t\t: 0x%08" PRIx32 "\n",
	 message_identifier );

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libwrc_message_table_get_utf16_string_size(
	          message_table_resource,
	          language_identifier,
	          message_index,
	          &value_string_size,
	          error );
#else
	result = libwrc_message_table_get_utf8_string_size(
	          message_table_resource,
	          language_identifier,
	          message_index,
	          &value_string_size,
	          error );
#endif
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve message table string: %d size.",
		 function,
		 message_index );

		goto on_error;
	}
	if( value_string_size > 0 )
	{
		value_string = system_string_allocate(
		                value_string_size );

		if( value_string == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create value string.",
			 function );

			goto on_error;
		}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
		result = libwrc_message_table_get_utf16_string(
		          message_table_resource,
		          language_identifier,
		          message_index,
		          (uint16_t *) value_string,
		          value_string_size,
		          error );
#else
		result = libwrc_message_table_get_utf8_string(
		          message_table_resource,
		          language_identifier,
		          message_index,
		          (uint8_t *) value_string,
		          value_string_size,
		          error );
#endif
		if( result != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve message table string: %d.",
			 function,
			 message_index );

			goto on_error;
		}
		fprintf(
		 info_handle->notify_stream,
		 "\tdata\t\t\t: %" PRIs_SYSTEM "",
		 value_string );

		memory_free(
		 value_string );

		value_string = NULL;
	}
	fprintf(
	 info_handle->notify_stream,
	 "\n" );

	return( 1 );

on_error:
	if( value_string != NULL )
	{
		memory_free(
		 value_string );
	}
	return( -1 );
}

/* Prints the message table resource information
 * Returns 1 if successful or -1 on error
 */
int info_handle_message_table_resource_fprint(
     info_handle_t *info_handle,
     libcerror_error_t **error )
{
	libwrc_resource_t *message_table_resource = NULL;
	static char *function                     = "info_handle_message_table_resource_fprint";
	uint32_t language_identifier              = 0;
	int language_index                        = 0;
	int message_index                         = 0;
	int number_of_languages                   = 0;
	int number_of_messages                    = 0;
	int result                                = 0;

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	result = libwrc_stream_get_resource_by_identifier(
	          info_handle->input_resource_stream,
	          LIBWRC_RESOURCE_IDENTIFIER_MESSAGE_TABLE,
	          &message_table_resource,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve message table resource.",
		 function );

		goto on_error;
	}
	else if( result != 0 )
	{
		fprintf(
		 info_handle->notify_stream,
		 "Message-table resource:\n" );

		if( libwrc_resource_get_number_of_languages(
		     message_table_resource,
		     &number_of_languages,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve number of languages.",
			 function );

			goto on_error;
		}
		fprintf(
		 info_handle->notify_stream,
		 "\tnumber of languages\t: %d\n",
		 number_of_languages );

		fprintf(
		 info_handle->notify_stream,
		 "\n" );

		for( language_index = 0;
		     language_index < number_of_languages;
		     language_index++ )
		{
			if( libwrc_resource_get_language_identifier(
			     message_table_resource,
			     language_index,
			     &language_identifier,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to retrieve language identifier: %d.",
				 function,
				 language_index );

				goto on_error;
			}
			fprintf(
			 info_handle->notify_stream,
			 "\tlanguage identifier\t: 0x%08" PRIx32 " (%s)\n",
			 language_identifier,
			 libfwnt_locale_identifier_language_tag_get_identifier(
			  language_identifier & 0x0000ffffUL ) );

			if( libwrc_message_table_get_number_of_messages(
			     message_table_resource,
			     language_identifier,
			     &number_of_messages,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to retrieve number of messages for language identifier: 0x%08" PRIx32 ".",
				 function,
				 language_identifier );

				goto on_error;
			}
			fprintf(
			 info_handle->notify_stream,
			 "\tnumber of messages\t: %d\n",
			 number_of_messages );

			fprintf(
			 info_handle->notify_stream,
			 "\n" );

			for( message_index = 0;
			     message_index < number_of_messages;
			     message_index++ )
			{
				if( info_handle_message_table_string_fprint(
				     info_handle,
				     message_table_resource,
				     language_identifier,
				     message_index,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
					 "%s: unable to print message table string: %d for language identifier: 0x%08" PRIx32 ".",
					 function,
					 message_index,
					 language_identifier );

					goto on_error;
				}
			}
		}
		if( libwrc_resource_free(
		     &message_table_resource,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free message table resource.",
			 function );

			goto on_error;
		}
	}
	return( 1 );

on_error:
	if( message_table_resource != NULL )
	{
		libwrc_resource_free(
		 &message_table_resource,
		 NULL );
	}
	return( -1 );
}

/* Prints the MUI values information
 * Returns 1 if successful or -1 on error
 */
int info_handle_mui_values_fprint(
     info_handle_t *info_handle,
     libwrc_resource_t *mui_resource,
     uint32_t language_identifier,
     libcerror_error_t **error )
{
	system_character_t *value_string = NULL;
	static char *function            = "info_handle_mui_values_fprint";
	size_t value_string_size         = 0;
	uint32_t file_type               = 0;
	int result                       = 0;

	if( libwrc_mui_get_file_type(
	     mui_resource,
	     language_identifier,
	     &file_type,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve file type.",
		 function );

		goto on_error;
	}
	fprintf(
	 info_handle->notify_stream,
	 "\tfile type\t\t: 0x%08" PRIx32 "\n",
	 file_type );

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libwrc_mui_get_utf16_main_name_size(
		  mui_resource,
		  language_identifier,
		  &value_string_size,
		  error );
#else
	result = libwrc_mui_get_utf8_main_name_size(
		  mui_resource,
		  language_identifier,
		  &value_string_size,
		  error );
#endif
	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve main name size.",
		 function );

		goto on_error;
	}
	if( ( result != 0 )
	 && ( value_string_size > 0 ) )
	{
		value_string = system_string_allocate(
		                value_string_size );

		if( value_string == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create value string.",
			 function );

			goto on_error;
		}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
		result = libwrc_mui_get_utf16_main_name(
			  mui_resource,
		          language_identifier,
			  (uint16_t *) value_string,
			  value_string_size,
			  error );
#else
		result = libwrc_mui_get_utf8_main_name(
			  mui_resource,
		          language_identifier,
			  (uint8_t *) value_string,
			  value_string_size,
			  error );
#endif
		if( result != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve main name.",
			 function );

			goto on_error;
		}
		fprintf(
		 info_handle->notify_stream,
		 "\tmain name\t\t: %" PRIs_SYSTEM "\n",
		 value_string );

		memory_free(
		 value_string );

		value_string = NULL;
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libwrc_mui_get_utf16_mui_name_size(
		  mui_resource,
	          language_identifier,
		  &value_string_size,
		  error );
#else
	result = libwrc_mui_get_utf8_mui_name_size(
		  mui_resource,
	          language_identifier,
		  &value_string_size,
		  error );
#endif
	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve MUI name size.",
		 function );

		goto on_error;
	}
	if( ( result != 0 )
	 && ( value_string_size > 0 ) )
	{
		value_string = system_string_allocate(
		                value_string_size );

		if( value_string == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create value string.",
			 function );

			goto on_error;
		}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
		result = libwrc_mui_get_utf16_mui_name(
			  mui_resource,
		          language_identifier,
			  (uint16_t *) value_string,
			  value_string_size,
			  error );
#else
		result = libwrc_mui_get_utf8_mui_name(
			  mui_resource,
		          language_identifier,
			  (uint8_t *) value_string,
			  value_string_size,
			  error );
#endif
		if( result != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve MUI name.",
			 function );

			goto on_error;
		}
		fprintf(
		 info_handle->notify_stream,
		 "\tMUI name\t\t: %" PRIs_SYSTEM "\n",
		 value_string );

		memory_free(
		 value_string );

		value_string = NULL;
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libwrc_mui_get_utf16_language_size(
		  mui_resource,
	          language_identifier,
		  &value_string_size,
		  error );
#else
	result = libwrc_mui_get_utf8_language_size(
		  mui_resource,
	          language_identifier,
		  &value_string_size,
		  error );
#endif
	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve language size.",
		 function );

		goto on_error;
	}
	if( ( result != 0 )
	 && ( value_string_size > 0 ) )
	{
		value_string = system_string_allocate(
		                value_string_size );

		if( value_string == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create value string.",
			 function );

			goto on_error;
		}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
		result = libwrc_mui_get_utf16_language(
			  mui_resource,
		          language_identifier,
			  (uint16_t *) value_string,
			  value_string_size,
			  error );
#else
		result = libwrc_mui_get_utf8_language(
			  mui_resource,
		          language_identifier,
			  (uint8_t *) value_string,
			  value_string_size,
			  error );
#endif
		if( result != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve language.",
			 function );

			goto on_error;
		}
		fprintf(
		 info_handle->notify_stream,
		 "\tlanguage\t\t: %" PRIs_SYSTEM "\n",
		 value_string );

		memory_free(
		 value_string );

		value_string = NULL;
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libwrc_mui_get_utf16_fallback_language_size(
		  mui_resource,
	          language_identifier,
		  &value_string_size,
		  error );
#else
	result = libwrc_mui_get_utf8_fallback_language_size(
		  mui_resource,
	          language_identifier,
		  &value_string_size,
		  error );
#endif
	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve fallback language size.",
		 function );

		goto on_error;
	}
	if( ( result != 0 )
	 && ( value_string_size > 0 ) )
	{
		value_string = system_string_allocate(
		                value_string_size );

		if( value_string == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create value string.",
			 function );

			goto on_error;
		}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
		result = libwrc_mui_get_utf16_fallback_language(
			  mui_resource,
		          language_identifier,
			  (uint16_t *) value_string,
			  value_string_size,
			  error );
#else
		result = libwrc_mui_get_utf8_fallback_language(
			  mui_resource,
		          language_identifier,
			  (uint8_t *) value_string,
			  value_string_size,
			  error );
#endif
		if( result != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve fallback language.",
			 function );

			goto on_error;
		}
		fprintf(
		 info_handle->notify_stream,
		 "\tfallback language\t: %" PRIs_SYSTEM "\n",
		 value_string );

		memory_free(
		 value_string );

		value_string = NULL;
	}
	fprintf(
	 info_handle->notify_stream,
	 "\n" );

	return( 1 );

on_error:
	if( value_string != NULL )
	{
		memory_free(
		 value_string );
	}
	return( -1 );
}

/* Prints the MUI resource information
 * Returns 1 if successful or -1 on error
 */
int info_handle_mui_resource_fprint(
     info_handle_t *info_handle,
     libcerror_error_t **error )
{
	libwrc_resource_t *mui_resource = NULL;
	static char *function           = "info_handle_mui_resource_fprint";
	uint32_t language_identifier    = 0;
	int language_index              = 0;
	int number_of_languages         = 0;
	int result                      = 0;

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	result = libwrc_stream_get_resource_by_utf8_name(
	          info_handle->input_resource_stream,
	          (uint8_t *) "MUI",
	          3,
	          &mui_resource,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve MUI resource.",
		 function );

		goto on_error;
	}
	else if( result != 0 )
	{
		fprintf(
		 info_handle->notify_stream,
		 "MUI resource:\n" );

		if( libwrc_resource_get_number_of_languages(
		     mui_resource,
		     &number_of_languages,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve number of languages.",
			 function );

			goto on_error;
		}
		fprintf(
		 info_handle->notify_stream,
		 "\tnumber of languages\t: %d\n",
		 number_of_languages );

		fprintf(
		 info_handle->notify_stream,
		 "\n" );

		for( language_index = 0;
		     language_index < number_of_languages;
		     language_index++ )
		{
			if( libwrc_resource_get_language_identifier(
			     mui_resource,
			     language_index,
			     &language_identifier,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to retrieve language identifier: %d.",
				 function,
				 language_index );

				goto on_error;
			}
			fprintf(
			 info_handle->notify_stream,
			 "\tlanguage identifier\t: 0x%08" PRIx32 " (%s)\n",
			 language_identifier,
			 libfwnt_locale_identifier_language_tag_get_identifier(
			  language_identifier & 0x0000ffffUL ) );

			if( info_handle_mui_values_fprint(
			     info_handle,
			     mui_resource,
			     language_identifier,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
				 "%s: unable to print MUI values for language identifier: 0x%08" PRIx32 ".",
				 function,
				 language_identifier );

				goto on_error;
			}
		}
		if( libwrc_resource_free(
		     &mui_resource,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free MUI resource.",
			 function );

			goto on_error;
		}
	}
	return( 1 );

on_error:
	if( mui_resource != NULL )
	{
		libwrc_resource_free(
		 &mui_resource,
		 NULL );
	}
	return( -1 );
}

/* Prints the string information
 * Returns 1 if successful or -1 on error
 */
int info_handle_string_fprint(
     info_handle_t *info_handle,
     libwrc_resource_t *string_resource,
     uint32_t language_identifier,
     int string_index,
     libcerror_error_t **error )
{
	system_character_t *value_string = NULL;
	static char *function            = "info_handle_string_fprint";
	size_t value_string_size         = 0;
	uint32_t string_identifier       = 0;
	int result                       = 0;

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	if( libwrc_string_get_identifier(
	     string_resource,
	     language_identifier,
	     string_index,
	     &string_identifier,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve string identifier: %d.",
		 function,
		 string_index );

		goto on_error;
	}
	fprintf(
	 info_handle->notify_stream,
	 "\tstring\t\t\t: %d\n",
	 string_index );

	fprintf(
	 info_handle->notify_stream,
	 "\tidentifier\t\t: 0x%08" PRIx32 "\n",
	 string_identifier );

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libwrc_string_get_utf16_string_size(
	          string_resource,
	          language_identifier,
	          string_index,
	          &value_string_size,
	          error );
#else
	result = libwrc_string_get_utf8_string_size(
	          string_resource,
	          language_identifier,
	          string_index,
	          &value_string_size,
	          error );
#endif
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve string: %d size.",
		 function,
		 string_index );

		goto on_error;
	}
	if( value_string_size > 0 )
	{
		value_string = system_string_allocate(
		                value_string_size );

		if( value_string == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create value string.",
			 function );

			goto on_error;
		}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
		result = libwrc_string_get_utf16_string(
		          string_resource,
		          language_identifier,
		          string_index,
		          (uint16_t *) value_string,
		          value_string_size,
		          error );
#else
		result = libwrc_string_get_utf8_string(
		          string_resource,
		          language_identifier,
		          string_index,
		          (uint8_t *) value_string,
		          value_string_size,
		          error );
#endif
		if( result != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve string: %d.",
			 function,
			 string_index );

			goto on_error;
		}
		fprintf(
		 info_handle->notify_stream,
		 "\tdata\t\t\t: %" PRIs_SYSTEM "\n",
		 value_string );

		memory_free(
		 value_string );

		value_string = NULL;
	}
	fprintf(
	 info_handle->notify_stream,
	 "\n" );

	return( 1 );

on_error:
	if( value_string != NULL )
	{
		memory_free(
		 value_string );
	}
	return( -1 );
}

/* Prints the strings resource information
 * Returns 1 if successful or -1 on error
 */
int info_handle_string_resource_fprint(
     info_handle_t *info_handle,
     libcerror_error_t **error )
{
	libwrc_resource_t *string_resource = NULL;
	static char *function              = "info_handle_string_resource_fprint";
	uint32_t language_identifier       = 0;
	int language_index                 = 0;
	int number_of_languages            = 0;
	int number_of_strings              = 0;
	int result                         = 0;
	int string_index                   = 0;

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	result = libwrc_stream_get_resource_by_identifier(
	          info_handle->input_resource_stream,
	          LIBWRC_RESOURCE_IDENTIFIER_STRING,
	          &string_resource,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve string resource.",
		 function );

		goto on_error;
	}
	else if( result != 0 )
	{
		fprintf(
		 info_handle->notify_stream,
		 "String resource:\n" );

		if( libwrc_resource_get_number_of_languages(
		     string_resource,
		     &number_of_languages,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve number of languages.",
			 function );

			goto on_error;
		}
		fprintf(
		 info_handle->notify_stream,
		 "\tnumber of languages\t: %d\n",
		 number_of_languages );

		fprintf(
		 info_handle->notify_stream,
		 "\n" );

		for( language_index = 0;
		     language_index < number_of_languages;
		     language_index++ )
		{
			if( libwrc_resource_get_language_identifier(
			     string_resource,
			     language_index,
			     &language_identifier,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to retrieve language identifier: %d.",
				 function,
				 language_index );

				goto on_error;
			}
			fprintf(
			 info_handle->notify_stream,
			 "\tlanguage identifier\t: 0x%08" PRIx32 " (%s)\n",
			 language_identifier,
			 libfwnt_locale_identifier_language_tag_get_identifier(
			  language_identifier & 0x0000ffffUL ) );

			if( libwrc_string_get_number_of_strings(
			     string_resource,
			     language_identifier,
			     &number_of_strings,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to retrieve number of strings for language identifier: 0x%08" PRIx32 ".",
				 function,
				 language_identifier );

				goto on_error;
			}
			fprintf(
			 info_handle->notify_stream,
			 "\tnumber of strings\t: %d\n",
			 number_of_strings );

			fprintf(
			 info_handle->notify_stream,
			 "\n" );

			for( string_index = 0;
			     string_index < number_of_strings;
			     string_index++ )
			{
				if( info_handle_string_fprint(
				     info_handle,
				     string_resource,
				     language_identifier,
				     string_index,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
					 "%s: unable to print string: %d for language identifier: 0x%08" PRIx32 ".",
					 function,
					 string_index,
					 language_identifier );

					goto on_error;
				}

			}
		}
		if( libwrc_resource_free(
		     &string_resource,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free string resource.",
			 function );

			goto on_error;
		}
	}
	return( 1 );

on_error:
	if( string_resource != NULL )
	{
		libwrc_resource_free(
		 &string_resource,
		 NULL );
	}
	return( -1 );
}

/* Prints the version values information
 * Returns 1 if successful or -1 on error
 */
int info_handle_version_values_fprint(
     info_handle_t *info_handle,
     libwrc_resource_t *version_resource,
     uint32_t language_identifier,
     libcerror_error_t **error )
{
	static char *function = "info_handle_version_values_fprint";
	uint64_t value_64bit  = 0;

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	if( libwrc_version_get_file_version(
	     version_resource,
	     language_identifier,
	     &value_64bit,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve file version.",
		 function );

		return( -1 );
	}
	fprintf(
	 info_handle->notify_stream,
	 "\tfile version\t\t: %" PRIu64 ".%" PRIu64 ".%" PRIu64 ".%" PRIu64 "\n",
	 ( value_64bit >> 48 ) & 0xffff,
	 ( value_64bit >> 32 ) & 0xffff,
	 ( value_64bit >> 16 ) & 0xffff,
	 value_64bit & 0xffff );

	if( libwrc_version_get_product_version(
	     version_resource,
	     language_identifier,
	     &value_64bit,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve product version.",
		 function );

		return( -1 );
	}
	fprintf(
	 info_handle->notify_stream,
	 "\tproduct version\t\t: %" PRIu64 ".%" PRIu64 ".%" PRIu64 ".%" PRIu64 "\n",
	 ( value_64bit >> 48 ) & 0xffff,
	 ( value_64bit >> 32 ) & 0xffff,
	 ( value_64bit >> 16 ) & 0xffff,
	 value_64bit & 0xffff );

/* TODO add more info */
	fprintf(
	 info_handle->notify_stream,
	 "\n" );

	return( 1 );
}

/* Prints the version resource information
 * Returns 1 if successful or -1 on error
 */
int info_handle_version_resource_fprint(
     info_handle_t *info_handle,
     libcerror_error_t **error )
{
	libwrc_resource_t *version_resource = NULL;
	static char *function               = "info_handle_version_resource_fprint";
	uint32_t language_identifier        = 0;
	int language_index                  = 0;
	int number_of_languages             = 0;
	int result                          = 0;

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	result = libwrc_stream_get_resource_by_identifier(
	          info_handle->input_resource_stream,
	          LIBWRC_RESOURCE_IDENTIFIER_VERSION,
	          &version_resource,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve version resource.",
		 function );

		goto on_error;
	}
	else if( result != 0 )
	{
		fprintf(
		 info_handle->notify_stream,
		 "Version resource:\n" );

		if( libwrc_resource_get_number_of_languages(
		     version_resource,
		     &number_of_languages,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve number of languages.",
			 function );

			goto on_error;
		}
		fprintf(
		 info_handle->notify_stream,
		 "\tnumber of languages\t: %d\n",
		 number_of_languages );

		fprintf(
		 info_handle->notify_stream,
		 "\n" );

		for( language_index = 0;
		     language_index < number_of_languages;
		     language_index++ )
		{
			if( libwrc_resource_get_language_identifier(
			     version_resource,
			     language_index,
			     &language_identifier,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to retrieve language identifier: %d.",
				 function,
				 language_index );

				goto on_error;
			}
			fprintf(
			 info_handle->notify_stream,
			 "\tlanguage identifier\t: 0x%08" PRIx32 " (%s)\n",
			 language_identifier,
			 libfwnt_locale_identifier_language_tag_get_identifier(
			  language_identifier & 0x0000ffffUL ) );

			if( info_handle_version_values_fprint(
			     info_handle,
			     version_resource,
			     language_identifier,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
				 "%s: unable to print version values for language identifier: 0x%08" PRIx32 ".",
				 function,
				 language_identifier );

				goto on_error;
			}
		}
		if( libwrc_resource_free(
		     &version_resource,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free version resource.",
			 function );

			goto on_error;
		}
	}
	return( 1 );

on_error:
	if( version_resource != NULL )
	{
		libwrc_resource_free(
		 &version_resource,
		 NULL );
	}
	return( -1 );
}

/* Prints resource item information as part of the resource hierarchy
 * Returns 1 if successful or -1 on error
 */
int info_handle_resource_hierarchy_fprint_resource_item(
     info_handle_t *info_handle,
     libwrc_resource_item_t *resource_item,
     int indentation_level,
     libcerror_error_t **error )
{
	libwrc_resource_item_t *resource_sub_item = NULL;
	system_character_t *value_string          = NULL;
	static char *function                     = "info_handle_resource_hierarchy_fprint_resource_item";
	size_t value_string_size                  = 0;
	uint32_t identifier                       = 0;
	int indentation_level_iterator            = 0;
	int number_of_resource_sub_items          = 0;
	int resource_sub_item_index               = 0;
	int result                                = 0;

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libwrc_resource_item_get_utf16_name_size(
	          resource_item,
	          &value_string_size,
	          error );
#else
	result = libwrc_resource_item_get_utf8_name_size(
	          resource_item,
	          &value_string_size,
	          error );
#endif
	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve name string size.",
		 function );

		goto on_error;
	}
	else if( result == 0 )
	{
		if( libwrc_resource_item_get_identifier(
		     resource_item,
		     &identifier,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve identifier.",
			 function );

			goto on_error;
		}
		for( indentation_level_iterator = 0;
		     indentation_level_iterator < indentation_level;
		     indentation_level_iterator++ )
		{
			fprintf(
			 info_handle->notify_stream,
			 " " );
		}
		fprintf(
		 info_handle->notify_stream,
		 "0x%08" PRIx32 "\n",
		 identifier );
	}
	else if( value_string_size > 0 )
	{
		value_string = system_string_allocate(
		                value_string_size );

		if( value_string == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create name string.",
			 function );

			goto on_error;
		}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
		result = libwrc_resource_item_get_utf16_name(
		          resource_item,
		          (uint16_t *) value_string,
		          value_string_size,
		          error );
#else
		result = libwrc_resource_item_get_utf8_name(
		          resource_item,
		          (uint8_t *) value_string,
		          value_string_size,
		          error );
#endif
		if( result != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve name string.",
			 function );

			goto on_error;
		}
		for( indentation_level_iterator = 0;
		     indentation_level_iterator < indentation_level;
		     indentation_level_iterator++ )
		{
			fprintf(
			 info_handle->notify_stream,
			 " " );
		}
		fprintf(
		 info_handle->notify_stream,
		 "%" PRIs_SYSTEM "\n",
		 value_string );

		memory_free(
		 value_string );

		value_string = NULL;
	}
	if( libwrc_resource_item_get_number_of_sub_items(
	     resource_item,
	     &number_of_resource_sub_items,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of resource sub items.",
		 function );

		goto on_error;
	}
	for( resource_sub_item_index = 0;
	     resource_sub_item_index < number_of_resource_sub_items;
	     resource_sub_item_index++ )
	{
		if( libwrc_resource_item_get_sub_item_by_index(
		     resource_item,
		     resource_sub_item_index,
		     &resource_sub_item,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve resource sub item: %d.",
			 function,
			 resource_sub_item_index );

			goto on_error;
		}
		if( info_handle_resource_hierarchy_fprint_resource_item(
		     info_handle,
		     resource_sub_item,
		     indentation_level + 1,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
			 "%s: unable to print resource sub item: %d.",
			 function,
			 resource_sub_item_index );

			goto on_error;
		}
		if( libwrc_resource_item_free(
		     &resource_sub_item,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free resource sub item: %d.",
			 function,
			 resource_sub_item_index );

			goto on_error;
		}
	}
	return( 1 );

on_error:
	if( resource_sub_item != NULL )
	{
		libwrc_resource_item_free(
		 &resource_sub_item,
		 NULL );
	}
	if( value_string != NULL )
	{
		memory_free(
		 value_string );
	}
	return( -1 );
}

/* Prints the resource hierarchy information
 * Returns 1 if successful or -1 on error
 */
int info_handle_resource_hierarchy_fprint(
     info_handle_t *info_handle,
     libcerror_error_t **error )
{
	libwrc_resource_t *resource           = NULL;
	libwrc_resource_item_t *resource_item = NULL;
	system_character_t *resource_name     = NULL;
	system_character_t *value_string      = NULL;
	static char *function                 = "info_handle_resource_hierarchy_fprint";
	size_t value_string_size              = 0;
	int number_of_resource_items          = 0;
	int number_of_resources               = 0;
	int resource_index                    = 0;
	int resource_item_index               = 0;
	int resource_type                     = 0;
	int result                            = 0;

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	fprintf(
	 info_handle->notify_stream,
	 "Windows Resource (RC) information:\n\n" );

	fprintf(
	 info_handle->notify_stream,
	 "Resource item hierarchy:\n" );

	if( libwrc_stream_get_number_of_resources(
	     info_handle->input_resource_stream,
	     &number_of_resources,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of resources.",
		 function );

		goto on_error;
	}
	for( resource_index = 0;
	     resource_index < number_of_resources;
	     resource_index++ )
	{
		if( libwrc_stream_get_resource_by_index(
		     info_handle->input_resource_stream,
		     resource_index,
		     &resource,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve resource: %d.",
			 function,
			 resource_index );

			goto on_error;
		}
		if( libwrc_resource_get_type(
		     resource,
		     &resource_type,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to retrieve resource: %d type.",
			 function,
			 resource_index );

			goto on_error;
		}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
		result = libwrc_resource_get_utf16_name_size(
		          resource,
		          &value_string_size,
		          error );
#else
		result = libwrc_resource_get_utf8_name_size(
		          resource,
		          &value_string_size,
		          error );
#endif
		if( result == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve name string size.",
			 function );

			goto on_error;
		}
		else if( result == 0 )
		{
			switch( resource_type )
			{
				case LIBWRC_RESOURCE_TYPE_CURSOR:
					resource_name = _SYSTEM_STRING( "CURSOR" );
					break;

				case LIBWRC_RESOURCE_TYPE_BITMAP:
					resource_name = _SYSTEM_STRING( "BITMAP" );
					break;

				case LIBWRC_RESOURCE_TYPE_ICON:
					resource_name = _SYSTEM_STRING( "ICON" );
					break;

				case LIBWRC_RESOURCE_TYPE_MENU:
					resource_name = _SYSTEM_STRING( "MENU" );
					break;

				case LIBWRC_RESOURCE_TYPE_DIALOG:
/* TODO determine if there is a better name to map e.g. POPUP */
					resource_name = _SYSTEM_STRING( "DIALOG" );
					break;

				case LIBWRC_RESOURCE_TYPE_STRING:
					resource_name = _SYSTEM_STRING( "STRINGTABLE" );
					break;

				case LIBWRC_RESOURCE_TYPE_FONT_DIRECTORY:
/* TODO determine if there is a better name to map to */
					resource_name = _SYSTEM_STRING( "FONT_DIRECTORY" );
					break;

				case LIBWRC_RESOURCE_TYPE_FONT:
					resource_name = _SYSTEM_STRING( "FONT" );
					break;

				case LIBWRC_RESOURCE_TYPE_ACCELERATOR:
					resource_name = _SYSTEM_STRING( "ACCELERATORS" );
					break;

				case LIBWRC_RESOURCE_TYPE_RAW_DATA:
/* TODO determine if there is a better name to map e.g. RCDATA */
					resource_name = _SYSTEM_STRING( "RAW_DATA" );
					break;

				case LIBWRC_RESOURCE_TYPE_MESSAGE_TABLE:
					resource_name = _SYSTEM_STRING( "MESSAGETABLE" );
					break;

				case LIBWRC_RESOURCE_TYPE_GROUP_CURSOR:
/* TODO determine if there is a better name to map to */
					resource_name = _SYSTEM_STRING( "GROUP_CURSOR" );
					break;

				case LIBWRC_RESOURCE_TYPE_GROUP_ICON:
/* TODO determine if there is a better name to map to */
					resource_name = _SYSTEM_STRING( "GROUP_ICON" );
					break;

				case LIBWRC_RESOURCE_TYPE_VERSION:
					resource_name = _SYSTEM_STRING( "VERSIONINFO" );
					break;

				case LIBWRC_RESOURCE_TYPE_DIALOG_INCLUDE:
/* TODO determine if there is a better name to map to */
					resource_name = _SYSTEM_STRING( "DIALOG_INCLUDE" );
					break;

				case LIBWRC_RESOURCE_TYPE_PLUG_AND_PLAY:
					resource_name = _SYSTEM_STRING ("PLUGPLAY" );
					break;

				case LIBWRC_RESOURCE_TYPE_VXD:
					resource_name = _SYSTEM_STRING( "VXD" );
					break;

				case LIBWRC_RESOURCE_TYPE_ANIMATED_CURSOR:
/* TODO determine if there is a better name to map to */
					resource_name = _SYSTEM_STRING( "ANIMATED_CURSOR" );
					break;

				case LIBWRC_RESOURCE_TYPE_ANIMATED_ICON:
/* TODO determine if there is a better name to map to */
					resource_name = _SYSTEM_STRING( "ANIMATED_ICON" );
					break;

				case LIBWRC_RESOURCE_TYPE_HTML:
					resource_name = _SYSTEM_STRING( "HTML" );
					break;

				case LIBWRC_RESOURCE_TYPE_MANIFEST:
/* TODO determine if there is a better name to map to */
					resource_name = _SYSTEM_STRING( "MANIFEST" );
					break;

				default:
					resource_name = _SYSTEM_STRING( "UNKNOWN" );
					break;
			}
			fprintf(
			 info_handle->notify_stream,
			 "%d (%" PRIs_SYSTEM ")\n",
			 resource_type,
			 resource_name );
		}
		else if( value_string_size > 0 )
		{
			value_string = system_string_allocate(
			                value_string_size );

			if( value_string == NULL )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_MEMORY,
				 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
				 "%s: unable to create name string.",
				 function );

				goto on_error;
			}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
			result = libwrc_resource_get_utf16_name(
			          resource,
			          (uint16_t *) value_string,
			          value_string_size,
			          error );
#else
			result = libwrc_resource_get_utf8_name(
			          resource,
			          (uint8_t *) value_string,
			          value_string_size,
			          error );
#endif
			if( result != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to retrieve name string.",
				 function );

				goto on_error;
			}
			fprintf(
			 info_handle->notify_stream,
			 "%" PRIs_SYSTEM "\n",
			 value_string );

			memory_free(
			 value_string );

			value_string = NULL;
		}
		if( libwrc_resource_get_number_of_items(
		     resource,
		     &number_of_resource_items,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve number of resource items.",
			 function );

			goto on_error;
		}
		for( resource_item_index = 0;
		     resource_item_index < number_of_resource_items;
		     resource_item_index++ )
		{
			if( libwrc_resource_get_item_by_index(
			     resource,
			     resource_item_index,
			     &resource_item,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to retrieve resource item: %d.",
				 function,
				 resource_item_index );

				goto on_error;
			}
			if( info_handle_resource_hierarchy_fprint_resource_item(
			     info_handle,
			     resource_item,
			     1,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
				 "%s: unable to print resource item: %d.",
				 function,
				 resource_item_index );

				goto on_error;
			}
			if( libwrc_resource_item_free(
			     &resource_item,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
				 "%s: unable to free resource item: %d.",
				 function,
				 resource_item_index );

				goto on_error;
			}
		}
		if( libwrc_resource_free(
		     &resource,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free resource: %d.",
			 function,
			 resource_index );

			goto on_error;
		}
	}
	fprintf(
	 info_handle->notify_stream,
	 "\n" );

	return( 1 );

on_error:
	if( resource_item != NULL )
	{
		libwrc_resource_item_free(
		 &resource_item,
		 NULL );
	}
	if( value_string != NULL )
	{
		memory_free(
		 value_string );
	}
	if( resource != NULL )
	{
		libwrc_resource_free(
		 &resource,
		 NULL );
	}
	return( -1 );
}

/* Prints the stream information
 * Returns 1 if successful or -1 on error
 */
int info_handle_stream_fprint(
     info_handle_t *info_handle,
     libcerror_error_t **error )
{
	libwrc_resource_t *resource       = NULL;
	system_character_t *resource_name = NULL;
	system_character_t *value_string  = NULL;
	static char *function             = "info_handle_stream_fprint";
	size_t value_string_size          = 0;
	int number_of_resources           = 0;
	int resource_index                = 0;
	int resource_type                 = 0;
	int result                        = 0;

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	fprintf(
	 info_handle->notify_stream,
	 "Windows Resource (RC) information:\n\n" );

	fprintf(
	 info_handle->notify_stream,
	 "Resources:\n" );

	if( libwrc_stream_get_number_of_resources(
	     info_handle->input_resource_stream,
	     &number_of_resources,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of resources.",
		 function );

		goto on_error;
	}
	for( resource_index = 0;
	     resource_index < number_of_resources;
	     resource_index++ )
	{
		if( libwrc_stream_get_resource_by_index(
		     info_handle->input_resource_stream,
		     resource_index,
		     &resource,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve resource: %d.",
			 function,
			 resource_index );

			goto on_error;
		}
		if( libwrc_resource_get_type(
		     resource,
		     &resource_type,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to retrieve resource: %d type.",
			 function,
			 resource_index );

			goto on_error;
		}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
		result = libwrc_resource_get_utf16_name_size(
		          resource,
		          &value_string_size,
		          error );
#else
		result = libwrc_resource_get_utf8_name_size(
		          resource,
		          &value_string_size,
		          error );
#endif
		if( result == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve name string size.",
			 function );

			goto on_error;
		}
		else if( result == 0 )
		{
			switch( resource_type )
			{
				case LIBWRC_RESOURCE_TYPE_CURSOR:
					resource_name = _SYSTEM_STRING( "CURSOR" );
					break;

				case LIBWRC_RESOURCE_TYPE_BITMAP:
					resource_name = _SYSTEM_STRING( "BITMAP" );
					break;

				case LIBWRC_RESOURCE_TYPE_ICON:
					resource_name = _SYSTEM_STRING( "ICON" );
					break;

				case LIBWRC_RESOURCE_TYPE_MENU:
					resource_name = _SYSTEM_STRING( "MENU" );
					break;

				case LIBWRC_RESOURCE_TYPE_DIALOG:
/* TODO determine if there is a better name to map e.g. POPUP */
					resource_name = _SYSTEM_STRING( "DIALOG" );
					break;

				case LIBWRC_RESOURCE_TYPE_STRING:
					resource_name = _SYSTEM_STRING( "STRINGTABLE" );
					break;

				case LIBWRC_RESOURCE_TYPE_FONT_DIRECTORY:
/* TODO determine if there is a better name to map to */
					resource_name = _SYSTEM_STRING( "FONT_DIRECTORY" );
					break;

				case LIBWRC_RESOURCE_TYPE_FONT:
					resource_name = _SYSTEM_STRING( "FONT" );
					break;

				case LIBWRC_RESOURCE_TYPE_ACCELERATOR:
					resource_name = _SYSTEM_STRING( "ACCELERATORS" );
					break;

				case LIBWRC_RESOURCE_TYPE_RAW_DATA:
/* TODO determine if there is a better name to map e.g. RCDATA */
					resource_name = _SYSTEM_STRING( "RAW_DATA" );
					break;

				case LIBWRC_RESOURCE_TYPE_MESSAGE_TABLE:
					resource_name = _SYSTEM_STRING( "MESSAGETABLE" );
					break;

				case LIBWRC_RESOURCE_TYPE_GROUP_CURSOR:
/* TODO determine if there is a better name to map to */
					resource_name = _SYSTEM_STRING( "GROUP_CURSOR" );
					break;

				case LIBWRC_RESOURCE_TYPE_GROUP_ICON:
/* TODO determine if there is a better name to map to */
					resource_name = _SYSTEM_STRING( "GROUP_ICON" );
					break;

				case LIBWRC_RESOURCE_TYPE_VERSION:
					resource_name = _SYSTEM_STRING( "VERSIONINFO" );
					break;

				case LIBWRC_RESOURCE_TYPE_DIALOG_INCLUDE:
/* TODO determine if there is a better name to map to */
					resource_name = _SYSTEM_STRING( "DIALOG_INCLUDE" );
					break;

				case LIBWRC_RESOURCE_TYPE_PLUG_AND_PLAY:
					resource_name = _SYSTEM_STRING ("PLUGPLAY" );
					break;

				case LIBWRC_RESOURCE_TYPE_VXD:
					resource_name = _SYSTEM_STRING( "VXD" );
					break;

				case LIBWRC_RESOURCE_TYPE_ANIMATED_CURSOR:
/* TODO determine if there is a better name to map to */
					resource_name = _SYSTEM_STRING( "ANIMATED_CURSOR" );
					break;

				case LIBWRC_RESOURCE_TYPE_ANIMATED_ICON:
/* TODO determine if there is a better name to map to */
					resource_name = _SYSTEM_STRING( "ANIMATED_ICON" );
					break;

				case LIBWRC_RESOURCE_TYPE_HTML:
					resource_name = _SYSTEM_STRING( "HTML" );
					break;

				case LIBWRC_RESOURCE_TYPE_MANIFEST:
/* TODO determine if there is a better name to map to */
					resource_name = _SYSTEM_STRING( "MANIFEST" );
					break;

				default:
					resource_name = _SYSTEM_STRING( "UNKNOWN" );
					break;
			}
			fprintf(
			 info_handle->notify_stream,
			 "\t%d (%" PRIs_SYSTEM ")\n",
			 resource_type,
			 resource_name );
		}
		else if( value_string_size > 0 )
		{
			value_string = system_string_allocate(
			                value_string_size );

			if( value_string == NULL )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_MEMORY,
				 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
				 "%s: unable to create name string.",
				 function );

				goto on_error;
			}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
			result = libwrc_resource_get_utf16_name(
			          resource,
			          (uint16_t *) value_string,
			          value_string_size,
			          error );
#else
			result = libwrc_resource_get_utf8_name(
			          resource,
			          (uint8_t *) value_string,
			          value_string_size,
			          error );
#endif
			if( result != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to retrieve name string.",
				 function );

				goto on_error;
			}
			fprintf(
			 info_handle->notify_stream,
			 "\t%" PRIs_SYSTEM "\n",
			 value_string );

			memory_free(
			 value_string );

			value_string = NULL;
		}
		if( libwrc_resource_free(
		     &resource,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free resource: %d.",
			 function,
			 resource_index );

			goto on_error;
		}
	}
	fprintf(
	 info_handle->notify_stream,
	 "\n" );

	if( info_handle_version_resource_fprint(
	     info_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
		 "%s: unable to print version resource.",
		 function );

		goto on_error;
	}
	if( info_handle_mui_resource_fprint(
	     info_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
		 "%s: unable to print MUI resource.",
		 function );

		goto on_error;
	}
	if( info_handle_string_resource_fprint(
	     info_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
		 "%s: unable to print string resource.",
		 function );

		goto on_error;
	}
	if( info_handle_message_table_resource_fprint(
	     info_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
		 "%s: unable to print message table resource.",
		 function );

		goto on_error;
	}
	if( info_handle_manifest_resource_fprint(
	     info_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
		 "%s: unable to print manifest resource.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( value_string != NULL )
	{
		memory_free(
		 value_string );
	}
	if( resource != NULL )
	{
		libwrc_resource_free(
		 &resource,
		 NULL );
	}
	return( -1 );
}

