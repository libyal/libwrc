/*
 * Library to access the Windows Resource Compiler (WRC) format
 *
 * Copyright (C) 2011-2019, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _LIBWRC_H )
#define _LIBWRC_H

#include <libwrc/codepage.h>
#include <libwrc/definitions.h>
#include <libwrc/error.h>
#include <libwrc/extern.h>
#include <libwrc/features.h>
#include <libwrc/types.h>

#include <stdio.h>

#if defined( LIBWRC_HAVE_BFIO )
#include <libbfio.h>
#endif

#if defined( __cplusplus )
extern "C" {
#endif

/* -------------------------------------------------------------------------
 * Support functions
 * ------------------------------------------------------------------------- */

/* Returns the library version
 */
LIBWRC_EXTERN \
const char *libwrc_get_version(
             void );

/* Returns the access flags for reading
 */
LIBWRC_EXTERN \
int libwrc_get_access_flags_read(
     void );

/* Retrieves the narrow system string codepage
 * A value of 0 represents no codepage, UTF-8 encoding is used instead
 * Returns 1 if successful or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_get_codepage(
     int *codepage,
     libwrc_error_t **error );

/* Sets the narrow system string codepage
 * A value of 0 represents no codepage, UTF-8 encoding is used instead
 * Returns 1 if successful or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_set_codepage(
     int codepage,
     libwrc_error_t **error );

/* -------------------------------------------------------------------------
 * Notify functions
 * ------------------------------------------------------------------------- */

/* Sets the verbose notification
 */
LIBWRC_EXTERN \
void libwrc_notify_set_verbose(
      int verbose );

/* Sets the notification stream
 * Returns 1 if successful or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_notify_set_stream(
     FILE *stream,
     libwrc_error_t **error );

/* Opens the notification stream using a filename
 * The stream is opened in append mode
 * Returns 1 if successful or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_notify_stream_open(
     const char *filename,
     libwrc_error_t **error );

/* Closes the notification stream if opened using a filename
 * Returns 0 if successful or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_notify_stream_close(
     libwrc_error_t **error );

/* -------------------------------------------------------------------------
 * Error functions
 * ------------------------------------------------------------------------- */

/* Frees an error
 */
LIBWRC_EXTERN \
void libwrc_error_free(
      libwrc_error_t **error );

/* Prints a descriptive string of the error to the stream
 * Returns the number of printed characters if successful or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_error_fprint(
     libwrc_error_t *error,
     FILE *stream );

/* Prints a descriptive string of the error to the string
 * The end-of-string character is not included in the return value
 * Returns the number of printed characters if successful or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_error_sprint(
     libwrc_error_t *error,
     char *string,
     size_t size );

/* Prints a backtrace of the error to the stream
 * Returns the number of printed characters if successful or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_error_backtrace_fprint(
     libwrc_error_t *error,
     FILE *stream );

/* Prints a backtrace of the error to the string
 * The end-of-string character is not included in the return value
 * Returns the number of printed characters if successful or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_error_backtrace_sprint(
     libwrc_error_t *error,
     char *string,
     size_t size );

/* -------------------------------------------------------------------------
 * Stream functions
 * ------------------------------------------------------------------------- */

/* Creates a stream
 * Make sure the value stream is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_stream_initialize(
     libwrc_stream_t **stream,
     libwrc_error_t **error );

/* Frees a stream
 * Returns 1 if successful or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_stream_free(
     libwrc_stream_t **stream,
     libwrc_error_t **error );

/* Signals the stream to abort its current activity
 * Returns 1 if successful or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_stream_signal_abort(
     libwrc_stream_t *stream,
     libwrc_error_t **error );

/* Opens a stream
 * Returns 1 if successful or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_stream_open(
     libwrc_stream_t *stream,
     const char *filename,
     int access_flags,
     libwrc_error_t **error );

#if defined( LIBWRC_HAVE_WIDE_CHARACTER_TYPE )

/* Opens a stream
 * Returns 1 if successful or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_stream_open_wide(
     libwrc_stream_t *stream,
     const wchar_t *filename,
     int access_flags,
     libwrc_error_t **error );

#endif /* defined( LIBWRC_HAVE_WIDE_CHARACTER_TYPE ) */

#if defined( LIBWRC_HAVE_BFIO )

/* Opens a stream using a Basic File IO (bfio) handle
 * Returns 1 if successful or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_stream_open_file_io_handle(
     libwrc_stream_t *stream,
     libbfio_handle_t *file_io_handle,
     int access_flags,
     libwrc_error_t **error );

#endif /* defined( LIBWRC_HAVE_BFIO ) */

/* Closes a stream
 * Returns 0 if successful or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_stream_close(
     libwrc_stream_t *stream,
     libwrc_error_t **error );

/* Retrieves the stream ASCII codepage
 * Returns 1 if successful or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_stream_get_ascii_codepage(
     libwrc_stream_t *stream,
     int *ascii_codepage,
     libwrc_error_t **error );

/* Sets the stream ASCII codepage
 * Returns 1 if successful or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_stream_set_ascii_codepage(
     libwrc_stream_t *stream,
     int ascii_codepage,
     libwrc_error_t **error );

/* Retrieves the virtual address
 * Returns 1 if successful or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_stream_get_virtual_address(
     libwrc_stream_t *stream,
     uint32_t *virtual_address,
     libwrc_error_t **error );

/* Set the virtual address
 * Returns 1 if successful or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_stream_set_virtual_address(
     libwrc_stream_t *stream,
     uint32_t virtual_address,
     libwrc_error_t **error );

/* Retrieves the number of resources
 * Returns 1 if successful or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_stream_get_number_of_resources(
     libwrc_stream_t *stream,
     int *number_of_resources,
     libwrc_error_t **error );

/* Retrieves a specific resource
 * Returns 1 if successful or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_stream_get_resource(
     libwrc_stream_t *stream,
     int resource_index,
     libwrc_resource_t **resource,
     libwrc_error_t **error );

/* Retrieves a specific resource by identifier
 * Returns 1 if successful, 0 if no such resource or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_stream_get_resource_by_identifier(
     libwrc_stream_t *stream,
     uint32_t identifier,
     libwrc_resource_t **resource,
     libwrc_error_t **error );

/* Retrieves a specific resource by type
 * Returns 1 if successful, 0 if no such resource or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_stream_get_resource_by_type(
     libwrc_stream_t *stream,
     int type,
     libwrc_resource_t **resource,
     libwrc_error_t **error );

/* Retrieves a specific resource by an UTF-8 formatted name
 * Returns 1 if successful, 0 if no such resource or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_stream_get_resource_by_utf8_name(
     libwrc_stream_t *stream,
     const uint8_t *utf8_string,
     size_t utf8_string_length,
     libwrc_resource_t **resource,
     libwrc_error_t **error );

/* Retrieves a specific resource by an UTF-16 formatted name
 * Returns 1 if successful, 0 if no such resource or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_stream_get_resource_by_utf16_name(
     libwrc_stream_t *stream,
     const uint16_t *utf16_string,
     size_t utf16_string_length,
     libwrc_resource_t **resource,
     libwrc_error_t **error );

/* -------------------------------------------------------------------------
 * Resource functions
 * ------------------------------------------------------------------------- */

/* Frees a resource
 * Returns 1 if successful or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_resource_free(
     libwrc_resource_t **resource,
     libwrc_error_t **error );

/* Retrieves the resource identifier
 * Returns 1 if successful or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_resource_get_identifier(
     libwrc_resource_t *resource,
     uint32_t *identifier,
     libwrc_error_t **error );

/* Retrieves the resource type
 * Returns 1 if successful or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_resource_get_type(
     libwrc_resource_t *resource,
     int *type,
     libwrc_error_t **error );

/* Reads the resource
 * Returns 1 if successful or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_resource_read(
     libwrc_resource_t *resource,
     libwrc_error_t **error );

/* Retrieves the number of languages
 * Returns 1 if successful or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_resource_get_number_of_languages(
     libwrc_resource_t *resource,
     int *number_of_languages,
     libwrc_error_t **error );

/* Retrieves a specific language identifier
 * Returns 1 if successful or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_resource_get_language_identifier(
     libwrc_resource_t *resource,
     int language_index,
     uint32_t *language_identifier,
     libwrc_error_t **error );

/* -------------------------------------------------------------------------
 * Manifest resource functions
 * ------------------------------------------------------------------------- */

/* Retrieves the size of a specific UTF-8 formatted manifest string
 * Returns 1 if successful or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_manifest_get_utf8_string_size(
     libwrc_resource_t *resource,
     uint32_t language_identifier,
     size_t *utf8_string_size,
     libwrc_error_t **error );

/* Retrieves a specific UTF-8 formatted manifest string
 * Returns 1 if successful or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_manifest_get_utf8_string(
     libwrc_resource_t *resource,
     uint32_t language_identifier,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libwrc_error_t **error );

/* Retrieves the size of a specific UTF-16 formatted manifest string
 * Returns 1 if successful or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_manifest_get_utf16_string_size(
     libwrc_resource_t *resource,
     uint32_t language_identifier,
     size_t *utf16_string_size,
     libwrc_error_t **error );

/* Retrieves a specific UTF-16 formatted manifest string
 * Returns 1 if successful or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_manifest_get_utf16_string(
     libwrc_resource_t *resource,
     uint32_t language_identifier,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libwrc_error_t **error );

/* -------------------------------------------------------------------------
 * Message-table resource functions
 * ------------------------------------------------------------------------- */

/* Retrieves the number of messages
 * Returns 1 if successful or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_message_table_get_number_of_messages(
     libwrc_resource_t *resource,
     uint32_t language_identifier,
     int *number_of_messages,
     libwrc_error_t **error );

/* Retrieves a specific message identifier
 * Returns 1 if successful or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_message_table_get_identifier(
     libwrc_resource_t *resource,
     uint32_t language_identifier,
     int message_index,
     uint32_t *message_identifier,
     libwrc_error_t **error );

/* Retrieves the message index for a specific identifier
 * Returns 1 if successful, 0 if no such message identifier or -1 on error
 */
int libwrc_message_table_get_index_by_identifier(
     libwrc_resource_t *resource,
     uint32_t language_identifier,
     uint32_t message_identifier,
     int *message_index,
     libwrc_error_t **error );

/* Retrieves the size of a specific UTF-8 formatted message string
 * Returns 1 if successful or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_message_table_get_utf8_string_size(
     libwrc_resource_t *resource,
     uint32_t language_identifier,
     int message_index,
     size_t *utf8_string_size,
     libwrc_error_t **error );

/* Retrieves a specific UTF-8 formatted message string
 * Returns 1 if successful or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_message_table_get_utf8_string(
     libwrc_resource_t *resource,
     uint32_t language_identifier,
     int message_index,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libwrc_error_t **error );

/* Retrieves the size of a specific UTF-16 formatted message string
 * Returns 1 if successful or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_message_table_get_utf16_string_size(
     libwrc_resource_t *resource,
     uint32_t language_identifier,
     int message_index,
     size_t *utf16_string_size,
     libwrc_error_t **error );

/* Retrieves a specific UTF-16 formatted message string
 * Returns 1 if successful or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_message_table_get_utf16_string(
     libwrc_resource_t *resource,
     uint32_t language_identifier,
     int message_index,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libwrc_error_t **error );

/* -------------------------------------------------------------------------
 * MUI resource functions
 * ------------------------------------------------------------------------- */

/* Retrieves the file type
 * Returns 1 if successful or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_mui_get_file_type(
     libwrc_resource_t *resource,
     uint32_t language_identifier,
     uint32_t *file_type,
     libwrc_error_t **error );

/* Retrieves the size of the UTF-8 formatted main name
 * Returns 1 if successful, 0 if not available or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_mui_get_utf8_main_name_size(
     libwrc_resource_t *resource,
     uint32_t language_identifier,
     size_t *utf8_string_size,
     libwrc_error_t **error );

/* Retrieves the UTF-8 formatted main name
 * Returns 1 if successful, 0 if not available or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_mui_get_utf8_main_name(
     libwrc_resource_t *resource,
     uint32_t language_identifier,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libwrc_error_t **error );

/* Retrieves the size of the UTF-16 formatted main name
 * Returns 1 if successful, 0 if not available or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_mui_get_utf16_main_name_size(
     libwrc_resource_t *resource,
     uint32_t language_identifier,
     size_t *utf16_string_size,
     libwrc_error_t **error );

/* Retrieves the UTF-16 formatted main name
 * Returns 1 if successful, 0 if not available or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_mui_get_utf16_main_name(
     libwrc_resource_t *resource,
     uint32_t language_identifier,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libwrc_error_t **error );

/* Retrieves the size of the UTF-8 formatted MUI name
 * Returns 1 if successful, 0 if not available or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_mui_get_utf8_mui_name_size(
     libwrc_resource_t *resource,
     uint32_t language_identifier,
     size_t *utf8_string_size,
     libwrc_error_t **error );

/* Retrieves the UTF-8 formatted MUI name
 * Returns 1 if successful, 0 if not available or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_mui_get_utf8_mui_name(
     libwrc_resource_t *resource,
     uint32_t language_identifier,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libwrc_error_t **error );

/* Retrieves the size of the UTF-16 formatted MUI name
 * Returns 1 if successful, 0 if not available or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_mui_get_utf16_mui_name_size(
     libwrc_resource_t *resource,
     uint32_t language_identifier,
     size_t *utf16_string_size,
     libwrc_error_t **error );

/* Retrieves the UTF-16 formatted MUI name
 * Returns 1 if successful, 0 if not available or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_mui_get_utf16_mui_name(
     libwrc_resource_t *resource,
     uint32_t language_identifier,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libwrc_error_t **error );

/* Retrieves the size of the UTF-8 formatted language
 * Returns 1 if successful, 0 if not available or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_mui_get_utf8_language_size(
     libwrc_resource_t *resource,
     uint32_t language_identifier,
     size_t *utf8_string_size,
     libwrc_error_t **error );

/* Retrieves the UTF-8 formatted language
 * Returns 1 if successful, 0 if not available or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_mui_get_utf8_language(
     libwrc_resource_t *resource,
     uint32_t language_identifier,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libwrc_error_t **error );

/* Retrieves the size of the UTF-16 formatted language
 * Returns 1 if successful, 0 if not available or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_mui_get_utf16_language_size(
     libwrc_resource_t *resource,
     uint32_t language_identifier,
     size_t *utf16_string_size,
     libwrc_error_t **error );

/* Retrieves the UTF-16 formatted language
 * Returns 1 if successful, 0 if not available or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_mui_get_utf16_language(
     libwrc_resource_t *resource,
     uint32_t language_identifier,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libwrc_error_t **error );

/* Retrieves the size of the UTF-8 formatted fallback language
 * Returns 1 if successful, 0 if not available or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_mui_get_utf8_fallback_language_size(
     libwrc_resource_t *resource,
     uint32_t language_identifier,
     size_t *utf8_string_size,
     libwrc_error_t **error );

/* Retrieves the UTF-8 formatted fallback language
 * Returns 1 if successful, 0 if not available or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_mui_get_utf8_fallback_language(
     libwrc_resource_t *resource,
     uint32_t language_identifier,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libwrc_error_t **error );

/* Retrieves the size of the UTF-16 formatted fallback language
 * Returns 1 if successful, 0 if not available or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_mui_get_utf16_fallback_language_size(
     libwrc_resource_t *resource,
     uint32_t language_identifier,
     size_t *utf16_string_size,
     libwrc_error_t **error );

/* Retrieves the UTF-16 formatted fallback language
 * Returns 1 if successful, 0 if not available or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_mui_get_utf16_fallback_language(
     libwrc_resource_t *resource,
     uint32_t language_identifier,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libwrc_error_t **error );

/* -------------------------------------------------------------------------
 * String resource functions
 * ------------------------------------------------------------------------- */

/* Retrieves the number of strings
 * Returns 1 if successful or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_string_get_number_of_strings(
     libwrc_resource_t *resource,
     uint32_t language_identifier,
     int *number_of_strings,
     libwrc_error_t **error );

/* Retrieves a specific string identifier
 * Returns 1 if successful or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_string_get_identifier(
     libwrc_resource_t *resource,
     uint32_t language_identifier,
     int string_index,
     uint32_t *string_identifier,
     libwrc_error_t **error );

/* Retrieves the string index for a specific identifier
 * Returns 1 if successful, 0 if no such string identifier or -1 on error
 */
int libwrc_string_get_index_by_identifier(
     libwrc_resource_t *resource,
     uint32_t language_identifier,
     uint32_t string_identifier,
     int *string_index,
     libwrc_error_t **error );

/* Retrieves the size of a specific UTF-8 formatted string
 * Returns 1 if successful or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_string_get_utf8_string_size(
     libwrc_resource_t *resource,
     uint32_t language_identifier,
     int string_index,
     size_t *utf8_string_size,
     libwrc_error_t **error );

/* Retrieves a specific UTF-8 formatted string
 * Returns 1 if successful or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_string_get_utf8_string(
     libwrc_resource_t *resource,
     uint32_t language_identifier,
     int string_index,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libwrc_error_t **error );

/* Retrieves the size of a specific UTF-16 formatted string
 * Returns 1 if successful or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_string_get_utf16_string_size(
     libwrc_resource_t *resource,
     uint32_t language_identifier,
     int string_index,
     size_t *utf16_string_size,
     libwrc_error_t **error );

/* Retrieves a specific UTF-16 formatted string
 * Returns 1 if successful or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_string_get_utf16_string(
     libwrc_resource_t *resource,
     uint32_t language_identifier,
     int string_index,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libwrc_error_t **error );

/* -------------------------------------------------------------------------
 * Version resource functions
 * ------------------------------------------------------------------------- */

/* Retrieves the file version
 * Returns 1 if successful or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_version_get_file_version(
     libwrc_resource_t *resource,
     uint32_t language_identifier,
     uint64_t *version,
     libwrc_error_t **error );

/* Retrieves the product version
 * Returns 1 if successful or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_version_get_product_version(
     libwrc_resource_t *resource,
     uint32_t language_identifier,
     uint64_t *version,
     libwrc_error_t **error );

/* -------------------------------------------------------------------------
 * WEVT_TEMPLATE resource functions
 * ------------------------------------------------------------------------- */

/* Retrieves the number of providers
 * Returns 1 if successful or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_wevt_template_get_number_of_providers(
     libwrc_resource_t *resource,
     uint32_t language_identifier,
     int *number_of_providers,
     libwrc_error_t **error );

/* Retrieves a specific provider
 * Returns 1 if successful or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_wevt_template_get_provider(
     libwrc_resource_t *resource,
     uint32_t language_identifier,
     int provider_index,
     libwrc_wevt_provider_t **provider,
     libwrc_error_t **error );

/* Retrieves a specific provider by identifier (GUID)
 * Returns 1 if successful, 0 if not available or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_wevt_template_get_provider_by_identifier(
     libwrc_resource_t *resource,
     uint32_t language_identifier,
     const uint8_t *provider_identifier,
     size_t provider_identifier_size,
     libwrc_wevt_provider_t **provider,
     libwrc_error_t **error );

/* -------------------------------------------------------------------------
 * WEVT_TEMPLATE provider functions
 * ------------------------------------------------------------------------- */

/* Frees a provider
 * Returns 1 if successful or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_wevt_provider_free(
     libwrc_wevt_provider_t **provider,
     libwrc_error_t **error );

/* Retrieves the number of events
 * Returns 1 if successful or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_wevt_provider_get_number_of_events(
     libwrc_wevt_provider_t *provider,
     int *number_of_events,
     libwrc_error_t **error );

/* Retrieves a specific event
 * Returns 1 if successful or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_wevt_provider_get_event(
     libwrc_wevt_provider_t *provider,
     int event_index,
     libwrc_wevt_event_t **event,
     libwrc_error_t **error );

/* Retrieves a specific event by identifier
 * Returns 1 if successful, 0 if not available or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_wevt_provider_get_event_by_identifier(
     libwrc_wevt_provider_t *provider,
     uint32_t event_identifier,
     libwrc_wevt_event_t **event,
     libwrc_error_t **error );

/* -------------------------------------------------------------------------
 * WEVT_TEMPLATE channel functions
 * ------------------------------------------------------------------------- */

/* Frees a channel
 * Returns 1 if successful or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_wevt_channel_free(
     libwrc_wevt_channel_t **channel,
     libwrc_error_t **error );

/* -------------------------------------------------------------------------
 * WEVT_TEMPLATE event functions
 * ------------------------------------------------------------------------- */

/* Frees an event
 * Returns 1 if successful or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_wevt_event_free(
     libwrc_wevt_event_t **event,
     libwrc_error_t **error );

/* Retrieves the identifier
 * Returns 1 if successful or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_wevt_event_get_identifier(
     libwrc_wevt_event_t *event,
     uint32_t *identifier,
     libwrc_error_t **error );

/* Retrieves the message identifier
 * Returns 1 if successful or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_wevt_event_get_message_identifier(
     libwrc_wevt_event_t *event,
     uint32_t *message_identifier,
     libwrc_error_t **error );

/* -------------------------------------------------------------------------
 * WEVT_TEMPLATE keyword functions
 * ------------------------------------------------------------------------- */

/* Frees a keyword
 * Returns 1 if successful or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_wevt_keyword_free(
     libwrc_wevt_keyword_t **keyword,
     libwrc_error_t **error );

/* -------------------------------------------------------------------------
 * WEVT_TEMPLATE level functions
 * ------------------------------------------------------------------------- */

/* Frees a level
 * Returns 1 if successful or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_wevt_level_free(
     libwrc_wevt_level_t **level,
     libwrc_error_t **error );

/* -------------------------------------------------------------------------
 * WEVT_TEMPLATE map functions
 * ------------------------------------------------------------------------- */

/* Frees a map
 * Returns 1 if successful or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_wevt_map_free(
     libwrc_wevt_map_t **map,
     libwrc_error_t **error );

/* -------------------------------------------------------------------------
 * WEVT_TEMPLATE opcode functions
 * ------------------------------------------------------------------------- */

/* Frees an opcode
 * Returns 1 if successful or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_wevt_opcode_free(
     libwrc_wevt_opcode_t **opcode,
     libwrc_error_t **error );

/* -------------------------------------------------------------------------
 * WEVT_TEMPLATE task functions
 * ------------------------------------------------------------------------- */

/* Frees a task
 * Returns 1 if successful or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_wevt_task_free(
     libwrc_wevt_task_t **task,
     libwrc_error_t **error );

/* -------------------------------------------------------------------------
 * WEVT_TEMPLATE template definition functions
 * ------------------------------------------------------------------------- */

/* Frees a template definition
 * Returns 1 if successful or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_wevt_template_definition_free(
     libwrc_wevt_template_definition_t **template_definition,
     libwrc_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBWRC_H ) */

