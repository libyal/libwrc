/*
 * Python object definition of the libwrc MUI resource
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

#if !defined( _PYWRC_MUI_RESOURCE_H )
#define _PYWRC_MUI_RESOURCE_H

#include <common.h>
#include <types.h>

#include "pywrc_libwrc.h"
#include "pywrc_python.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct pywrc_mui_resource pywrc_mui_resource_t;

struct pywrc_mui_resource
{
	/* Python object initialization
	 */
	PyObject_HEAD

	/* The libwrc MUI resource
	 */
	libwrc_mui_resource_t *mui_resource;
};

extern PyMethodDef pywrc_mui_resource_object_methods[];
extern PyTypeObject pywrc_mui_resource_type_object;

int pywrc_mui_resource_init(
     pywrc_mui_resource_t *pywrc_mui_resource );

void pywrc_mui_resource_free(
      pywrc_mui_resource_t *pywrc_mui_resource );

PyObject *pywrc_mui_resource_copy_from_byte_stream(
           pywrc_mui_resource_t *pywrc_mui_resource,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pywrc_mui_resource_get_file_type(
           pywrc_mui_resource_t *pywrc_mui_resource,
           PyObject *arguments );

PyObject *pywrc_mui_resource_get_main_name(
           pywrc_mui_resource_t *pywrc_mui_resource,
           PyObject *arguments );

PyObject *pywrc_mui_resource_get_mui_name(
           pywrc_mui_resource_t *pywrc_mui_resource,
           PyObject *arguments );

PyObject *pywrc_mui_resource_get_language(
           pywrc_mui_resource_t *pywrc_mui_resource,
           PyObject *arguments );

PyObject *pywrc_mui_resource_get_fallback_language(
           pywrc_mui_resource_t *pywrc_mui_resource,
           PyObject *arguments );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _PYWRC_MUI_RESOURCE_H ) */

