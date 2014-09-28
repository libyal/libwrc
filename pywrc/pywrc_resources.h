/*
 * Python object definition of the resources sequence and iterator
 *
 * Copyright (c) 2011-2014, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _PYWRC_RESOURCES_H )
#define _PYWRC_RESOURCES_H

#include <common.h>
#include <types.h>

#include "pywrc_libwrc.h"
#include "pywrc_python.h"
#include "pywrc_stream.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct pywrc_resources pywrc_resources_t;

struct pywrc_resources
{
	/* Python object initialization
	 */
	PyObject_HEAD

	/* The stream object
	 */
	pywrc_stream_t *stream_object;

	/* The get resource by index callback function
	 */
	PyObject* (*get_resource_by_index)(
	             pywrc_stream_t *stream_object,
	             int resource_index );

	/* The (current) resource index
	 */
	int resource_index;

	/* The number of resources
	 */
	int number_of_resources;
};

extern PyTypeObject pywrc_resources_type_object;

PyObject *pywrc_resources_new(
           pywrc_stream_t *stream_object,
           PyObject* (*get_resource_by_index)(
                        pywrc_stream_t *stream_object,
                        int resource_index ),
           int number_of_resources );

int pywrc_resources_init(
     pywrc_resources_t *pywrc_resources );

void pywrc_resources_free(
      pywrc_resources_t *pywrc_resources );

Py_ssize_t pywrc_resources_len(
            pywrc_resources_t *pywrc_resources );

PyObject *pywrc_resources_getitem(
           pywrc_resources_t *pywrc_resources,
           Py_ssize_t item_index );

PyObject *pywrc_resources_iter(
           pywrc_resources_t *pywrc_resources );

PyObject *pywrc_resources_iternext(
           pywrc_resources_t *pywrc_resources );

#if defined( __cplusplus )
}
#endif

#endif

