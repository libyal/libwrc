/*
 * Python object definition of the libwrc message table resource
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

#if !defined( _PYWRC_MESSAGE_TABLE_RESOURCE_H )
#define _PYWRC_MESSAGE_TABLE_RESOURCE_H

#include <common.h>
#include <types.h>

#include "pywrc_libwrc.h"
#include "pywrc_python.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct pywrc_message_table_resource pywrc_message_table_resource_t;

struct pywrc_message_table_resource
{
	/* Python object initialization
	 */
	PyObject_HEAD

	/* The libwrc message table resource
	 */
	libwrc_message_table_resource_t *message_table_resource;
};

extern PyMethodDef pywrc_message_table_resource_object_methods[];
extern PyTypeObject pywrc_message_table_resource_type_object;

int pywrc_message_table_resource_init(
     pywrc_message_table_resource_t *pywrc_message_table_resource );

void pywrc_message_table_resource_free(
      pywrc_message_table_resource_t *pywrc_message_table_resource );

PyObject *pywrc_message_table_resource_copy_from_byte_stream(
           pywrc_message_table_resource_t *pywrc_message_table_resource,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pywrc_message_table_resource_get_number_of_messages(
           pywrc_message_table_resource_t *pywrc_message_table_resource,
           PyObject *arguments );

PyObject *pywrc_message_table_resource_get_message_identifier(
           pywrc_message_table_resource_t *pywrc_message_table_resource,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pywrc_message_table_resource_get_string(
           pywrc_message_table_resource_t *pywrc_message_table_resource,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pywrc_message_table_resource_get_string_by_message_identifier(
           pywrc_message_table_resource_t *pywrc_message_table_resource,
           PyObject *arguments,
           PyObject *keywords );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _PYWRC_MESSAGE_TABLE_RESOURCE_H ) */

