/*
 * Library to access the Windows Resource Compiler (WRC) format
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
int libwrc_stream_get_resource_by_index(
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

/* Retrieves the size of the UTF-8 encoded name
 * The returned size includes the end of string character
 * Returns 1 if successful, 0 if not available or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_resource_get_utf8_name_size(
     libwrc_resource_t *resource,
     size_t *utf8_string_size,
     libwrc_error_t **error );

/* Retrieves the UTF-8 encoded name
 * The size should include the end of string character
 * Returns 1 if successful, 0 if not available or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_resource_get_utf8_name(
     libwrc_resource_t *resource,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libwrc_error_t **error );

/* Retrieves the size of the UTF-16 encoded name
 * The returned size includes the end of string character
 * Returns 1 if successful, 0 if not available or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_resource_get_utf16_name_size(
     libwrc_resource_t *resource,
     size_t *utf16_string_size,
     libwrc_error_t **error );

/* Retrieves the UTF-16 encoded name
 * The size should include the end of string character
 * Returns 1 if successful, 0 if not available or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_resource_get_utf16_name(
     libwrc_resource_t *resource,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libwrc_error_t **error );

/* Retrieves the resource type
 * Returns 1 if successful or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_resource_get_type(
     libwrc_resource_t *resource,
     int *type,
     libwrc_error_t **error );

/* Retrieves the number of items
 * Returns 1 if successful or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_resource_get_number_of_items(
     libwrc_resource_t *resource,
     int *number_of_items,
     libwrc_error_t **error );

/* Retrieves a specific item
 * Returns 1 if successful or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_resource_get_item_by_index(
     libwrc_resource_t *resource,
     int item_index,
     libwrc_resource_item_t **resource_item,
     libwrc_error_t **error );

/* -------------------------------------------------------------------------
 * Resource item functions
 * ------------------------------------------------------------------------- */

/* Frees a resource item
 * Returns 1 if successful or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_resource_item_free(
     libwrc_resource_item_t **resource_item,
     libwrc_error_t **error );

/* Retrieves the resource item identifier
 * Returns 1 if successful or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_resource_item_get_identifier(
     libwrc_resource_item_t *resource_item,
     uint32_t *identifier,
     libwrc_error_t **error );

/* Retrieves the size of the UTF-8 encoded name
 * The returned size includes the end of string character
 * Returns 1 if successful, 0 if not available or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_resource_item_get_utf8_name_size(
     libwrc_resource_item_t *resource_item,
     size_t *utf8_string_size,
     libwrc_error_t **error );

/* Retrieves the UTF-8 encoded name
 * The size should include the end of string character
 * Returns 1 if successful, 0 if not available or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_resource_item_get_utf8_name(
     libwrc_resource_item_t *resource_item,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libwrc_error_t **error );

/* Retrieves the size of the UTF-16 encoded name
 * The returned size includes the end of string character
 * Returns 1 if successful, 0 if not available or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_resource_item_get_utf16_name_size(
     libwrc_resource_item_t *resource_item,
     size_t *utf16_string_size,
     libwrc_error_t **error );

/* Retrieves the UTF-16 encoded name
 * The size should include the end of string character
 * Returns 1 if successful, 0 if not available or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_resource_item_get_utf16_name(
     libwrc_resource_item_t *resource_item,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libwrc_error_t **error );

/* Reads resouce item data from the current offset into a buffer
 * Returns the number of bytes read or -1 on error
 */
LIBWRC_EXTERN \
ssize_t libwrc_resource_item_read_buffer(
         libwrc_resource_item_t *resource_item,
         uint8_t *buffer,
         size_t size,
         libwrc_error_t **error );

/* Reads resouce item data a specific offset into a buffer
 * Returns the number of bytes read or -1 on error
 */
ssize_t libwrc_resource_item_read_buffer_at_offset(
         libwrc_resource_item_t *resource_item,
         uint8_t *buffer,
         size_t buffer_size,
         off64_t offset,
         libwrc_error_t **error );

/* Seeks a certain offset of the resouce item data
 * Returns the offset if seek is successful or -1 on error
 */
LIBWRC_EXTERN \
off64_t libwrc_resource_item_seek_offset(
         libwrc_resource_item_t *resource_item,
         off64_t offset,
         int whence,
         libwrc_error_t **error );

/* Retrieves the current offset in the resouce item data
 * Returns 1 if successful or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_resource_item_get_offset(
     libwrc_resource_item_t *resource_item,
     off64_t *offset,
     libwrc_error_t **error );

/* Retrieves the size of the resource data
 * Returns 1 if successful or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_resource_item_get_size(
     libwrc_resource_item_t *resource_item,
     uint32_t *size,
     libwrc_error_t **error );

/* Retrieves the number of sub items
 * Returns 1 if successful or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_resource_item_get_number_of_sub_items(
     libwrc_resource_item_t *resource_item,
     int *number_of_sub_items,
     libwrc_error_t **error );

/* Retrieves a specific sub item
 * Returns 1 if successful or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_resource_item_get_sub_item_by_index(
     libwrc_resource_item_t *resource_item,
     int sub_item_index,
     libwrc_resource_item_t **resource_sub_item,
     libwrc_error_t **error );

/* -------------------------------------------------------------------------
 * Manifest resource functions
 * ------------------------------------------------------------------------- */

/* Creates a manifest resource
 * Make sure the value manifest_resource is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_manifest_resource_initialize(
     libwrc_manifest_resource_t **manifest_resource,
     libwrc_error_t **error );

/* Frees a manifest
 * Returns 1 if successful or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_manifest_resource_free(
     libwrc_manifest_resource_t **manifest_resource,
     libwrc_error_t **error );

/* Reads the manifest resource
 * Returns 1 if successful or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_manifest_resource_read(
     libwrc_manifest_resource_t *manifest_resource,
     const uint8_t *data,
     size_t data_size,
     libwrc_error_t **error );

/* Retrieves the size of a specific UTF-8 formatted manifest string
 * Returns 1 if successful or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_manifest_resource_get_utf8_string_size(
     libwrc_manifest_resource_t *manifest_resource,
     size_t *utf8_string_size,
     libwrc_error_t **error );

/* Retrieves a specific UTF-8 formatted manifest string
 * Returns 1 if successful or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_manifest_resource_get_utf8_string(
     libwrc_manifest_resource_t *manifest_resource,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libwrc_error_t **error );

/* Retrieves the size of a specific UTF-16 formatted manifest string
 * Returns 1 if successful or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_manifest_resource_get_utf16_string_size(
     libwrc_manifest_resource_t *manifest_resource,
     size_t *utf16_string_size,
     libwrc_error_t **error );

/* Retrieves a specific UTF-16 formatted manifest string
 * Returns 1 if successful or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_manifest_resource_get_utf16_string(
     libwrc_manifest_resource_t *manifest_resource,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libwrc_error_t **error );

/* -------------------------------------------------------------------------
 * Message table (MESSAGETABLE) resource functions
 * ------------------------------------------------------------------------- */

/* Creates a message table resource
 * Make sure the value message_table_resource is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_message_table_resource_initialize(
     libwrc_message_table_resource_t **message_table_resource,
     libwrc_error_t **error );

/* Frees a message table resource
 * Returns 1 if successful or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_message_table_resource_free(
     libwrc_message_table_resource_t **message_table_resource,
     libwrc_error_t **error );

/* Reads the message table resource
 * Returns 1 if successful or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_message_table_resource_read(
     libwrc_message_table_resource_t *message_table_resource,
     const uint8_t *data,
     size_t data_size,
     int ascii_codepage,
     libwrc_error_t **error );

/* Retrieves the number of messages
 * Returns 1 if successful or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_message_table_resource_get_number_of_messages(
     libwrc_message_table_resource_t *message_table_resource,
     int *number_of_messages,
     libwrc_error_t **error );

/* Retrieves a specific message identifier
 * Returns 1 if successful or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_message_table_resource_get_identifier(
     libwrc_message_table_resource_t *message_table_resource,
     int message_index,
     uint32_t *message_identifier,
     libwrc_error_t **error );

/* Retrieves the message index for a specific identifier
 * Returns 1 if successful, 0 if no such message identifier or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_message_table_resource_get_index_by_identifier(
     libwrc_message_table_resource_t *message_table_resource,
     uint32_t message_identifier,
     int *message_index,
     libwrc_error_t **error );

/* Retrieves the size of a specific UTF-8 formatted message string
 * Returns 1 if successful or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_message_table_resource_get_utf8_string_size(
     libwrc_message_table_resource_t *message_table_resource,
     int message_index,
     size_t *utf8_string_size,
     libwrc_error_t **error );

/* Retrieves a specific UTF-8 formatted message string
 * Returns 1 if successful or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_message_table_resource_get_utf8_string(
     libwrc_message_table_resource_t *message_table_resource,
     int message_index,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libwrc_error_t **error );

/* Retrieves the size of a specific UTF-16 formatted message string
 * Returns 1 if successful or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_message_table_resource_get_utf16_string_size(
     libwrc_message_table_resource_t *message_table_resource,
     int message_index,
     size_t *utf16_string_size,
     libwrc_error_t **error );

/* Retrieves a specific UTF-16 formatted message string
 * Returns 1 if successful or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_message_table_resource_get_utf16_string(
     libwrc_message_table_resource_t *message_table_resource,
     int message_index,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libwrc_error_t **error );

/* -------------------------------------------------------------------------
 * MUI resource functions
 * ------------------------------------------------------------------------- */

/* Creates a MUI resource
 * Make sure the value mui_resource is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_mui_resource_initialize(
     libwrc_mui_resource_t **mui_resource,
     libwrc_error_t **error );

/* Frees a MUI resource
 * Returns 1 if successful or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_mui_resource_free(
     libwrc_mui_resource_t **mui_resource,
     libwrc_error_t **error );

/* Reads the MUI resource
 * Returns 1 if successful or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_mui_resource_read(
     libwrc_mui_resource_t *mui_resource,
     const uint8_t *data,
     size_t data_size,
     libwrc_error_t **error );

/* Retrieves the file type
 * Returns 1 if successful or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_mui_resource_get_file_type(
     libwrc_mui_resource_t *mui_resource,
     uint32_t *file_type,
     libwrc_error_t **error );

/* Retrieves the size of the UTF-8 formatted main name
 * Returns 1 if successful, 0 if not available or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_mui_resource_get_utf8_main_name_size(
     libwrc_mui_resource_t *mui_resource,
     size_t *utf8_string_size,
     libwrc_error_t **error );

/* Retrieves the UTF-8 formatted main name
 * Returns 1 if successful, 0 if not available or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_mui_resource_get_utf8_main_name(
     libwrc_mui_resource_t *mui_resource,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libwrc_error_t **error );

/* Retrieves the size of the UTF-16 formatted main name
 * Returns 1 if successful, 0 if not available or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_mui_resource_get_utf16_main_name_size(
     libwrc_mui_resource_t *mui_resource,
     size_t *utf16_string_size,
     libwrc_error_t **error );

/* Retrieves the UTF-16 formatted main name
 * Returns 1 if successful, 0 if not available or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_mui_resource_get_utf16_main_name(
     libwrc_mui_resource_t *mui_resource,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libwrc_error_t **error );

/* Retrieves the size of the UTF-8 formatted MUI name
 * Returns 1 if successful, 0 if not available or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_mui_resource_get_utf8_mui_name_size(
     libwrc_mui_resource_t *mui_resource,
     size_t *utf8_string_size,
     libwrc_error_t **error );

/* Retrieves the UTF-8 formatted MUI name
 * Returns 1 if successful, 0 if not available or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_mui_resource_get_utf8_mui_name(
     libwrc_mui_resource_t *mui_resource,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libwrc_error_t **error );

/* Retrieves the size of the UTF-16 formatted MUI name
 * Returns 1 if successful, 0 if not available or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_mui_resource_get_utf16_mui_name_size(
     libwrc_mui_resource_t *mui_resource,
     size_t *utf16_string_size,
     libwrc_error_t **error );

/* Retrieves the UTF-16 formatted MUI name
 * Returns 1 if successful, 0 if not available or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_mui_resource_get_utf16_mui_name(
     libwrc_mui_resource_t *mui_resource,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libwrc_error_t **error );

/* Retrieves the size of the UTF-8 formatted language
 * Returns 1 if successful, 0 if not available or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_mui_resource_get_utf8_language_size(
     libwrc_mui_resource_t *mui_resource,
     size_t *utf8_string_size,
     libwrc_error_t **error );

/* Retrieves the UTF-8 formatted language
 * Returns 1 if successful, 0 if not available or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_mui_resource_get_utf8_language(
     libwrc_mui_resource_t *mui_resource,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libwrc_error_t **error );

/* Retrieves the size of the UTF-16 formatted language
 * Returns 1 if successful, 0 if not available or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_mui_resource_get_utf16_language_size(
     libwrc_mui_resource_t *mui_resource,
     size_t *utf16_string_size,
     libwrc_error_t **error );

/* Retrieves the UTF-16 formatted language
 * Returns 1 if successful, 0 if not available or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_mui_resource_get_utf16_language(
     libwrc_mui_resource_t *mui_resource,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libwrc_error_t **error );

/* Retrieves the size of the UTF-8 formatted fallback language
 * Returns 1 if successful, 0 if not available or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_mui_resource_get_utf8_fallback_language_size(
     libwrc_mui_resource_t *mui_resource,
     size_t *utf8_string_size,
     libwrc_error_t **error );

/* Retrieves the UTF-8 formatted fallback language
 * Returns 1 if successful, 0 if not available or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_mui_resource_get_utf8_fallback_language(
     libwrc_mui_resource_t *mui_resource,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libwrc_error_t **error );

/* Retrieves the size of the UTF-16 formatted fallback language
 * Returns 1 if successful, 0 if not available or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_mui_resource_get_utf16_fallback_language_size(
     libwrc_mui_resource_t *mui_resource,
     size_t *utf16_string_size,
     libwrc_error_t **error );

/* Retrieves the UTF-16 formatted fallback language
 * Returns 1 if successful, 0 if not available or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_mui_resource_get_utf16_fallback_language(
     libwrc_mui_resource_t *mui_resource,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libwrc_error_t **error );

/* -------------------------------------------------------------------------
 * String table (STRINGTABLE) resource functions
 * ------------------------------------------------------------------------- */

/* Creates a string table resource
 * Make sure the value string_table_resource is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_string_table_resource_initialize(
     libwrc_string_table_resource_t **string_table_resource,
     libwrc_error_t **error );

/* Frees a string table resource
 * Returns 1 if successful or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_string_table_resource_free(
     libwrc_string_table_resource_t **string_table_resource,
     libwrc_error_t **error );

/* Reads the string table resource
 * Returns 1 if successful or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_string_table_resource_read(
     libwrc_string_table_resource_t *string_table_resource,
     const uint8_t *data,
     size_t data_size,
     uint32_t base_identifier,
     libwrc_error_t **error );

/* Retrieves the number of strings
 * Returns 1 if successful or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_string_table_resource_get_number_of_strings(
     libwrc_string_table_resource_t *string_table_resource,
     int *number_of_strings,
     libwrc_error_t **error );

/* Retrieves a specific string identifier
 * Returns 1 if successful or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_string_table_resource_get_identifier(
     libwrc_string_table_resource_t *string_table_resource,
     int string_index,
     uint32_t *string_identifier,
     libwrc_error_t **error );

/* Retrieves the string index for a specific identifier
 * Returns 1 if successful, 0 if no such string identifier or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_string_table_resource_get_index_by_identifier(
     libwrc_string_table_resource_t *string_table_resource,
     uint32_t string_identifier,
     int *string_index,
     libwrc_error_t **error );

/* Retrieves the size of a specific UTF-8 formatted string
 * Returns 1 if successful or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_string_table_resource_get_utf8_string_size(
     libwrc_string_table_resource_t *string_table_resource,
     int string_index,
     size_t *utf8_string_size,
     libwrc_error_t **error );

/* Retrieves a specific UTF-8 formatted string
 * Returns 1 if successful or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_string_table_resource_get_utf8_string(
     libwrc_string_table_resource_t *string_table_resource,
     int string_index,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libwrc_error_t **error );

/* Retrieves the size of a specific UTF-16 formatted string
 * Returns 1 if successful or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_string_table_resource_get_utf16_string_size(
     libwrc_string_table_resource_t *string_table_resource,
     int string_index,
     size_t *utf16_string_size,
     libwrc_error_t **error );

/* Retrieves a specific UTF-16 formatted string
 * Returns 1 if successful or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_string_table_resource_get_utf16_string(
     libwrc_string_table_resource_t *string_table_resource,
     int string_index,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libwrc_error_t **error );

/* -------------------------------------------------------------------------
 * Version information (VERSIONINFO) resource functions
 * ------------------------------------------------------------------------- */

/* Creates a version information resource
 * Make sure the value version_information_resource is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_version_information_resource_initialize(
     libwrc_version_information_resource_t **version_information_resource,
     libwrc_error_t **error );

/* Frees a version information resource
 * Returns 1 if successful or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_version_information_resource_free(
     libwrc_version_information_resource_t **version_information_resource,
     libwrc_error_t **error );

/* Reads the version information resource
 * Returns 1 if successful or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_version_information_resource_read(
     libwrc_version_information_resource_t *version_information_resource,
     const uint8_t *data,
     size_t data_size,
     libwrc_error_t **error );

/* Retrieves the file version
 * Returns 1 if successful or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_version_information_resource_get_file_version(
     libwrc_version_information_resource_t *version_information_resource,
     uint64_t *file_version,
     libwrc_error_t **error );

/* Retrieves the product version
 * Returns 1 if successful or -1 on error
 */
LIBWRC_EXTERN \
int libwrc_version_information_resource_get_product_version(
     libwrc_version_information_resource_t *version_information_resource,
     uint64_t *product_version,
     libwrc_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBWRC_H ) */

