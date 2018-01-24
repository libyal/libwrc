/*
 * Python object definition of the libwrc message table resource
 *
 * Copyright (C) 2011-2018, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _PYWRC_MESSAGE_TABLE_H )
#define _PYWRC_MESSAGE_TABLE_H

#include <common.h>
#include <types.h>

#include "pywrc_python.h"
#include "pywrc_resource.h"

#if defined( __cplusplus )
extern "C" {
#endif

extern PyMethodDef pywrc_message_table_object_methods[];
extern PyTypeObject pywrc_message_table_type_object;

PyObject *pywrc_message_table_get_number_of_messages(
           pywrc_resource_t *pywrc_resource,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pywrc_message_table_get_message_identifier(
           pywrc_resource_t *pywrc_resource,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pywrc_message_table_get_string(
           pywrc_resource_t *pywrc_resource,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pywrc_message_table_get_string_by_message_identifier(
           pywrc_resource_t *pywrc_resource,
           PyObject *arguments,
           PyObject *keywords );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _PYWRC_MESSAGE_TABLE_H ) */

