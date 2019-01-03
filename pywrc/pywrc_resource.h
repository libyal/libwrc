/*
 * Python object wrapper of libwrc_resource_t
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

#if !defined( _PYWRC_RESOURCE_H )
#define _PYWRC_RESOURCE_H

#include <common.h>
#include <types.h>

#include "pywrc_libwrc.h"
#include "pywrc_python.h"
#include "pywrc_stream.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct pywrc_resource pywrc_resource_t;

struct pywrc_resource
{
	/* Python object initialization
	 */
	PyObject_HEAD

	/* The libwrc resource
	 */
	libwrc_resource_t *resource;

	/* The stream object
	 */
	pywrc_stream_t *stream_object;
};

extern PyMethodDef pywrc_resource_object_methods[];
extern PyTypeObject pywrc_resource_type_object;

PyObject *pywrc_resource_new(
           PyTypeObject *type_object,
           libwrc_resource_t *resource,
           pywrc_stream_t *stream_object );

int pywrc_resource_init(
     pywrc_resource_t *pywrc_resource );

void pywrc_resource_free(
      pywrc_resource_t *pywrc_resource );

PyObject *pywrc_resource_get_identifier(
           pywrc_resource_t *pywrc_resource,
           PyObject *arguments );

PyObject *pywrc_resource_get_number_of_languages(
           pywrc_resource_t *pywrc_resource,
           PyObject *arguments );

PyObject *pywrc_resource_get_language_identifier_by_index(
           pywrc_resource_t *pywrc_resource,
           int language_identifier_index );

PyObject *pywrc_resource_get_language_identifier(
           pywrc_resource_t *pywrc_resource,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pywrc_resource_get_language_identifiers(
           pywrc_resource_t *pywrc_resource,
           PyObject *arguments );

#if defined( __cplusplus )
}
#endif

#endif

