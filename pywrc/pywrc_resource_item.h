/*
 * Python object wrapper of libwrc_resource_item_t
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

#if !defined( _PYWRC_RESOURCE_ITEM_H )
#define _PYWRC_RESOURCE_ITEM_H

#include <common.h>
#include <types.h>

#include "pywrc_libwrc.h"
#include "pywrc_python.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct pywrc_resource_item pywrc_resource_item_t;

struct pywrc_resource_item
{
	/* Python object initialization
	 */
	PyObject_HEAD

	/* The libwrc resource item
	 */
	libwrc_resource_item_t *resource_item;

	/* The parent object
	 */
	PyObject *parent_object;
};

extern PyMethodDef pywrc_resource_item_object_methods[];
extern PyTypeObject pywrc_resource_item_type_object;

PyObject *pywrc_resource_item_new(
           libwrc_resource_item_t *resource_item,
           PyObject *parent_object );

int pywrc_resource_item_init(
     pywrc_resource_item_t *pywrc_resource_item );

void pywrc_resource_item_free(
      pywrc_resource_item_t *pywrc_resource_item );

PyObject *pywrc_resource_item_get_identifier(
           pywrc_resource_item_t *pywrc_resource_item,
           PyObject *arguments );

PyObject *pywrc_resource_item_get_name(
           pywrc_resource_item_t *pywrc_resource_item,
           PyObject *arguments );

PyObject *pywrc_resource_item_read_buffer(
           pywrc_resource_item_t *pywrc_resource_item,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pywrc_resource_item_read_buffer_at_offset(
           pywrc_resource_item_t *pywrc_resource_item,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pywrc_resource_item_seek_offset(
           pywrc_resource_item_t *pywrc_resource_item,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pywrc_resource_item_get_offset(
           pywrc_resource_item_t *pywrc_resource_item,
           PyObject *arguments );

PyObject *pywrc_resource_item_get_number_of_sub_items(
           pywrc_resource_item_t *pywrc_resource_item,
           PyObject *arguments );

PyObject *pywrc_resource_item_get_sub_item_by_index(
           PyObject *pywrc_resource_item,
           int sub_item_index );

PyObject *pywrc_resource_item_get_sub_item(
           pywrc_resource_item_t *pywrc_resource_item,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pywrc_resource_item_get_sub_items(
           pywrc_resource_item_t *pywrc_resource_item,
           PyObject *arguments );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _PYWRC_RESOURCE_ITEM_H ) */

