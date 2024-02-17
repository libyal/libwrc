/*
 * Python object definition of the sequence and iterator object of resource items
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

#if !defined( _PYWRC_RESOURCE_ITEMS_H )
#define _PYWRC_RESOURCE_ITEMS_H

#include <common.h>
#include <types.h>

#include "pywrc_libwrc.h"
#include "pywrc_python.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct pywrc_resource_items pywrc_resource_items_t;

struct pywrc_resource_items
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

extern PyTypeObject pywrc_resource_items_type_object;

PyObject *pywrc_resource_items_new(
           PyObject *parent_object,
           PyObject* (*get_item_by_index)(
                        PyObject *parent_object,
                        int index ),
           int number_of_items );

int pywrc_resource_items_init(
     pywrc_resource_items_t *sequence_object );

void pywrc_resource_items_free(
      pywrc_resource_items_t *sequence_object );

Py_ssize_t pywrc_resource_items_len(
            pywrc_resource_items_t *sequence_object );

PyObject *pywrc_resource_items_getitem(
           pywrc_resource_items_t *sequence_object,
           Py_ssize_t item_index );

PyObject *pywrc_resource_items_iter(
           pywrc_resource_items_t *sequence_object );

PyObject *pywrc_resource_items_iternext(
           pywrc_resource_items_t *sequence_object );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _PYWRC_RESOURCE_ITEMS_H ) */

