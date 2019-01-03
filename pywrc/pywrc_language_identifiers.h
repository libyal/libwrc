/*
 * Python object definition of the language identifiers sequence and iterator
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

#if !defined( _PYWRC_LANGUAGE_IDENTIFIERS_H )
#define _PYWRC_LANGUAGE_IDENTIFIERS_H

#include <common.h>
#include <types.h>

#include "pywrc_libwrc.h"
#include "pywrc_python.h"
#include "pywrc_resource.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct pywrc_language_identifiers pywrc_language_identifiers_t;

struct pywrc_language_identifiers
{
	/* Python object initialization
	 */
	PyObject_HEAD

	/* The resource object
	 */
	pywrc_resource_t *resource_object;

	/* The get language identifier by index callback function
	 */
	PyObject* (*get_language_identifier_by_index)(
	             pywrc_resource_t *resource_object,
	             int language_identifier_index );

	/* The (current) language identifier index
	 */
	int language_identifier_index;

	/* The number of languages
	 */
	int number_of_languages;
};

extern PyTypeObject pywrc_language_identifiers_type_object;

PyObject *pywrc_language_identifiers_new(
           pywrc_resource_t *resource_object,
           PyObject* (*get_language_identifier_by_index)(
                        pywrc_resource_t *resource_object,
                        int language_identifier_index ),
           int number_of_languages );

int pywrc_language_identifiers_init(
     pywrc_language_identifiers_t *pywrc_language_identifiers );

void pywrc_language_identifiers_free(
      pywrc_language_identifiers_t *pywrc_language_identifiers );

Py_ssize_t pywrc_language_identifiers_len(
            pywrc_language_identifiers_t *pywrc_language_identifiers );

PyObject *pywrc_language_identifiers_getitem(
           pywrc_language_identifiers_t *pywrc_language_identifiers,
           Py_ssize_t item_index );

PyObject *pywrc_language_identifiers_iter(
           pywrc_language_identifiers_t *pywrc_language_identifiers );

PyObject *pywrc_language_identifiers_iternext(
           pywrc_language_identifiers_t *pywrc_language_identifiers );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _PYWRC_LANGUAGE_IDENTIFIERS_H ) */

