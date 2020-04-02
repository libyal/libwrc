/*
 * Python object definition of the sequence and iterator object of resources
 *
 * Copyright (C) 2011-2020, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _PYWRC_RESOURCES_H )
#define _PYWRC_RESOURCES_H

#include <common.h>
#include <types.h>

#include "pywrc_libwrc.h"
#include "pywrc_python.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct pywrc_resources pywrc_resources_t;

struct pywrc_resources
{
	/* Python object initialization
	 */
	PyObject_HEAD

	/* The parent object
	 */
	PyObject *parent_object;

	/* The get item by index callback function
	 */
	PyObject* (*get_item_by_index)(
	             PyObject *parent_object,
	             int index );

	/* The current index
	 */
	int current_index;

	/* The number of items
	 */
	int number_of_items;
};

extern PyTypeObject pywrc_resources_type_object;

PyObject *pywrc_resources_new(
           PyObject *parent_object,
           PyObject* (*get_item_by_index)(
                        PyObject *parent_object,
                        int index ),
           int number_of_items );

int pywrc_resources_init(
     pywrc_resources_t *resources_object );

void pywrc_resources_free(
      pywrc_resources_t *resources_object );

Py_ssize_t pywrc_resources_len(
            pywrc_resources_t *resources_object );

PyObject *pywrc_resources_getitem(
           pywrc_resources_t *resources_object,
           Py_ssize_t item_index );

PyObject *pywrc_resources_iter(
           pywrc_resources_t *resources_object );

PyObject *pywrc_resources_iternext(
           pywrc_resources_t *resources_object );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _PYWRC_RESOURCES_H ) */

