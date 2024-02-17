/*
 * Python object wrapper of libwrc_stream_t
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

#if !defined( _PYWRC_STREAM_H )
#define _PYWRC_STREAM_H

#include <common.h>
#include <types.h>

#include "pywrc_libbfio.h"
#include "pywrc_libwrc.h"
#include "pywrc_python.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct pywrc_stream pywrc_stream_t;

struct pywrc_stream
{
	/* Python object initialization
	 */
	PyObject_HEAD

	/* The libwrc stream
	 */
	libwrc_stream_t *stream;

	/* The libbfio file IO handle
	 */
	libbfio_handle_t *file_io_handle;
};

extern PyMethodDef pywrc_stream_object_methods[];
extern PyTypeObject pywrc_stream_type_object;

int pywrc_stream_init(
     pywrc_stream_t *pywrc_stream );

void pywrc_stream_free(
      pywrc_stream_t *pywrc_stream );

PyObject *pywrc_stream_signal_abort(
           pywrc_stream_t *pywrc_stream,
           PyObject *arguments );

PyObject *pywrc_stream_open(
           pywrc_stream_t *pywrc_stream,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pywrc_stream_open_file_object(
           pywrc_stream_t *pywrc_stream,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pywrc_stream_close(
           pywrc_stream_t *pywrc_stream,
           PyObject *arguments );

PyObject *pywrc_stream_get_ascii_codepage(
           pywrc_stream_t *pywrc_stream,
           PyObject *arguments );

int pywrc_stream_set_ascii_codepage_from_string(
     pywrc_stream_t *pywrc_stream,
     const char *codepage_string );

PyObject *pywrc_stream_set_ascii_codepage(
           pywrc_stream_t *pywrc_stream,
           PyObject *arguments,
           PyObject *keywords );

int pywrc_stream_set_ascii_codepage_setter(
     pywrc_stream_t *pywrc_stream,
     PyObject *string_object,
     void *closure );

PyObject *pywrc_stream_get_virtual_address(
           pywrc_stream_t *pywrc_stream,
           PyObject *arguments );

PyObject *pywrc_stream_set_virtual_address(
           pywrc_stream_t *pywrc_stream,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pywrc_stream_get_number_of_resources(
           pywrc_stream_t *pywrc_stream,
           PyObject *arguments );

PyObject *pywrc_stream_get_resource_by_index(
           PyObject *pywrc_stream,
           int resource_index );

PyObject *pywrc_stream_get_resource(
           pywrc_stream_t *pywrc_stream,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pywrc_stream_get_resources(
           pywrc_stream_t *pywrc_stream,
           PyObject *arguments );

PyObject *pywrc_stream_get_resource_by_identifier(
           pywrc_stream_t *pywrc_stream,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pywrc_stream_get_resource_by_type(
           pywrc_stream_t *pywrc_stream,
           PyObject *arguments );

PyObject *pywrc_stream_get_resource_by_name(
           pywrc_stream_t *pywrc_stream,
           PyObject *arguments,
           PyObject *keywords );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _PYWRC_STREAM_H ) */

