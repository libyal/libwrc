/*
 * Shows information obtained from a Windows Resource (RC) stream
 * of the .rsrc section of a MZ, PE/COFF executable
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
#include <file_stream.h>
#include <memory.h>
#include <system_string.h>
#include <types.h>

#if defined( HAVE_UNISTD_H )
#include <unistd.h>
#endif

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "info_handle.h"
#include "wrctools_getopt.h"
#include "wrctools_libcerror.h"
#include "wrctools_libclocale.h"
#include "wrctools_libcnotify.h"
#include "wrctools_libwrc.h"
#include "wrctools_output.h"
#include "wrctools_signal.h"
#include "wrctools_unused.h"

enum WRCINFO_MODES
{
	WRCINFO_MODE_RESOURCE_HIERARCHY,
	WRCINFO_MODE_OVERVIEW
};

info_handle_t *wrcinfo_info_handle = NULL;
int wrcinfo_abort                  = 0;

/* Prints the executable usage information
 */
void usage_fprint(
      FILE *stream )
{
	if( stream == NULL )
	{
		return;
	}
	fprintf( stream, "Use wrcinfo to determine information about a Windows\n"
	                 "Resource (RC) streams in the .rsrc section of a PE/COFF\n"
	                 "executable.\n\n" );

	fprintf( stream, "Usage: wrcinfo [ -c codepage ] [ -hHvV ] source\n\n" );

	fprintf( stream, "\tsource: the source file containing the stream\n\n" );

	fprintf( stream, "\t-c:     codepage of ASCII strings, options: ascii, windows-874,\n"
	                 "\t        windows-932, windows-936, windows-949, windows-950,\n"
	                 "\t        windows-1250, windows-1251, windows-1252 (default),\n"
	                 "\t        windows-1253, windows-1254, windows-1255, windows-1256\n"
	                 "\t        windows-1257 or windows-1258\n" );
	fprintf( stream, "\t-h:     shows this help\n" );
	fprintf( stream, "\t-H:     shows the resource hierarchy\n" );
	fprintf( stream, "\t-v:     verbose output to stderr\n" );
	fprintf( stream, "\t-V:     print version\n" );
}

/* Signal handler for wrcinfo
 */
void wrcinfo_signal_handler(
      wrctools_signal_t signal WRCTOOLS_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error = NULL;
	static char *function    = "wrcinfo_signal_handler";

	WRCTOOLS_UNREFERENCED_PARAMETER( signal )

	wrcinfo_abort = 1;

	if( wrcinfo_info_handle != NULL )
	{
		if( info_handle_signal_abort(
		     wrcinfo_info_handle,
		     &error ) != 1 )
		{
			libcnotify_printf(
			 "%s: unable to signal info handle to abort.\n",
			 function );

			libcnotify_print_error_backtrace(
			 error );
			libcerror_error_free(
			 &error );
		}
	}
	/* Force stdin to close otherwise any function reading it will remain blocked
	 */
#if defined( WINAPI ) && !defined( __CYGWIN__ )
	if( _close(
	     0 ) != 0 )
#else
	if( close(
	     0 ) != 0 )
#endif
	{
		libcnotify_printf(
		 "%s: unable to close stdin.\n",
		 function );
	}
}

/* The main program
 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
int wmain( int argc, wchar_t * const argv[] )
#else
int main( int argc, char * const argv[] )
#endif
{
	libcerror_error_t *error                  = NULL;
	system_character_t *option_ascii_codepage = NULL;
	system_character_t *source                = NULL;
	char *program                             = "wrcinfo";
	system_integer_t option                   = 0;
	int option_mode                           = WRCINFO_MODE_OVERVIEW;
	int result                                = 0;
	int verbose                               = 0;

	libcnotify_stream_set(
	 stderr,
	 NULL );
	libcnotify_verbose_set(
	 1 );

	if( libclocale_initialize(
	     "wrctools",
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to initialize locale values.\n" );

		goto on_error;
	}
	if( wrctools_output_initialize(
	     _IONBF,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to initialize system values.\n" );

		goto on_error;
	}
	wrctools_output_version_fprint(
	 stdout,
	 program );

	while( ( option = wrctools_getopt(
	                   argc,
	                   argv,
	                   _SYSTEM_STRING( "c:hHvV" ) ) ) != (system_integer_t) -1 )
	{
		switch( option )
		{
			case (system_integer_t) '?':
			default:
				fprintf(
				 stderr,
				 "Invalid argument: %" PRIs_SYSTEM "\n",
				 argv[ optind - 1 ] );

				usage_fprint(
				 stdout );

				return( EXIT_FAILURE );

			case (system_integer_t) 'c':
				option_ascii_codepage = optarg;

				break;

			case (system_integer_t) 'h':
				usage_fprint(
				 stdout );

				return( EXIT_SUCCESS );

			case (system_integer_t) 'H':
				option_mode = WRCINFO_MODE_RESOURCE_HIERARCHY;

				break;

			case (system_integer_t) 'v':
				verbose = 1;

				break;

			case (system_integer_t) 'V':
				wrctools_output_copyright_fprint(
				 stdout );

				return( EXIT_SUCCESS );
		}
	}
	if( optind == argc )
	{
		fprintf(
		 stderr,
		 "Missing source file.\n" );

		usage_fprint(
		 stdout );

		return( EXIT_FAILURE );
	}
	source = argv[ optind ];

	libcnotify_verbose_set(
	 verbose );
	libwrc_notify_set_stream(
	 stderr,
	 NULL );
	libwrc_notify_set_verbose(
	 verbose );

	if( info_handle_initialize(
	     &wrcinfo_info_handle,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to initialize info handle.\n" );

		goto on_error;
	}
	if( option_ascii_codepage != NULL )
	{
		result = info_handle_set_ascii_codepage(
		          wrcinfo_info_handle,
		          option_ascii_codepage,
		          &error );

		if( result == -1 )
		{
			fprintf(
			 stderr,
			 "Unable to set ASCII codepage in info handle.\n" );

			goto on_error;
		}
		else if( result == 0 )
		{
			fprintf(
			 stderr,
			 "Unsupported ASCII codepage defaulting to: windows-1252.\n" );
		}
	}
	result = info_handle_open_input(
	          wrcinfo_info_handle,
	          source,
	          &error );

	if( result == -1 )
	{
		fprintf(
		 stderr,
		 "Unable to open: %" PRIs_SYSTEM ".\n",
		 source );

		goto on_error;
	}
	else if( result == 0 )
	{
		fprintf(
		 stderr,
		 "No resource stream.\n" );

		goto on_error;
	}
	switch( option_mode )
	{
		case WRCINFO_MODE_RESOURCE_HIERARCHY:
			if( info_handle_resource_hierarchy_fprint(
			     wrcinfo_info_handle,
			     &error ) != 1 )
			{
				fprintf(
				 stderr,
				 "Unable to print resource hierarchy information.\n" );

				goto on_error;
			}
			break;

		case WRCINFO_MODE_OVERVIEW:
		default:
			if( info_handle_stream_fprint(
			     wrcinfo_info_handle,
			     &error ) != 1 )
			{
				fprintf(
				 stderr,
				 "Unable to print stream information.\n" );

				goto on_error;
			}
			break;
	}
	if( info_handle_close_input(
	     wrcinfo_info_handle,
	     &error ) != 0 )
	{
		fprintf(
		 stderr,
		 "Unable to close info handle.\n" );

		goto on_error;
	}
	if( info_handle_free(
	     &wrcinfo_info_handle,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to free info handle.\n" );

		goto on_error;
	}
	return( EXIT_SUCCESS );

on_error:
	if( error != NULL )
	{
		libcnotify_print_error_backtrace(
		 error );
		libcerror_error_free(
		 &error );
	}
	if( wrcinfo_info_handle != NULL )
	{
		info_handle_free(
		 &wrcinfo_info_handle,
		 NULL );
	}
	return( EXIT_FAILURE );
}

