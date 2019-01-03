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

#include <common.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( HAVE_WINAPI )
#include <stdlib.h>
#endif

#include "pywrc_language_identifiers.h"
#include "pywrc_libcerror.h"
#include "pywrc_libwrc.h"
#include "pywrc_python.h"
#include "pywrc_resource.h"

PySequenceMethods pywrc_language_identifiers_sequence_methods = {
	/* sq_length */
	(lenfunc) pywrc_language_identifiers_len,
	/* sq_concat */
	0,
	/* sq_repeat */
	0,
	/* sq_item */
	(ssizeargfunc) pywrc_language_identifiers_getitem,
	/* sq_slice */
	0,
	/* sq_ass_item */
	0,
	/* sq_ass_slice */
	0,
	/* sq_contains */
	0,
	/* sq_inplace_concat */
	0,
	/* sq_inplace_repeat */
	0
};

PyTypeObject pywrc_language_identifiers_type_object = {
	PyVarObject_HEAD_INIT( NULL, 0 )

	/* tp_name */
	"pywrc._language_identifiers",
	/* tp_basicsize */
	sizeof( pywrc_language_identifiers_t ),
	/* tp_itemsize */
	0,
	/* tp_dealloc */
	(destructor) pywrc_language_identifiers_free,
	/* tp_print */
	0,
	/* tp_getattr */
	0,
	/* tp_setattr */
	0,
	/* tp_compare */
	0,
	/* tp_repr */
	0,
	/* tp_as_number */
	0,
	/* tp_as_sequence */
	&pywrc_language_identifiers_sequence_methods,
	/* tp_as_mapping */
	0,
	/* tp_hash */
	0,
	/* tp_call */
	0,
	/* tp_str */
	0,
	/* tp_getattro */
	0,
	/* tp_setattro */
	0,
	/* tp_as_buffer */
	0,
	/* tp_flags */
	Py_TPFLAGS_DEFAULT | Py_TPFLAGS_HAVE_ITER,
	/* tp_doc */
	"internal pywrc language identifiers sequence and iterator object",
	/* tp_traverse */
	0,
	/* tp_clear */
	0,
	/* tp_richcompare */
	0,
	/* tp_weaklistoffset */
	0,
	/* tp_iter */
	(getiterfunc) pywrc_language_identifiers_iter,
	/* tp_iternext */
	(iternextfunc) pywrc_language_identifiers_iternext,
	/* tp_methods */
	0,
	/* tp_members */
	0,
	/* tp_getset */
	0,
	/* tp_base */
	0,
	/* tp_dict */
	0,
	/* tp_descr_get */
	0,
	/* tp_descr_set */
	0,
	/* tp_dictoffset */
	0,
	/* tp_init */
	(initproc) pywrc_language_identifiers_init,
	/* tp_alloc */
	0,
	/* tp_new */
	0,
	/* tp_free */
	0,
	/* tp_is_gc */
	0,
	/* tp_bases */
	NULL,
	/* tp_mro */
	NULL,
	/* tp_cache */
	NULL,
	/* tp_subclasses */
	NULL,
	/* tp_weaklist */
	NULL,
	/* tp_del */
	0
};

/* Creates a new language identifiers object
 * Returns a Python object if successful or NULL on error
 */
PyObject *pywrc_language_identifiers_new(
           pywrc_resource_t *resource_object,
           PyObject* (*get_language_identifier_by_index)(
                        pywrc_resource_t *resource_object,
                        int language_identifier_index ),
           int number_of_languages )
{
	pywrc_language_identifiers_t *pywrc_language_identifiers = NULL;
	static char *function                                    = "pywrc_language_identifiers_new";

	if( resource_object == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid resource object.",
		 function );

		return( NULL );
	}
	if( get_language_identifier_by_index == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid get language identifier by index function.",
		 function );

		return( NULL );
	}
	/* Make sure the language identifiers values are initialized
	 */
	pywrc_language_identifiers = PyObject_New(
	                              struct pywrc_language_identifiers,
	                              &pywrc_language_identifiers_type_object );

	if( pywrc_language_identifiers == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize language identifiers.",
		 function );

		goto on_error;
	}
	if( pywrc_language_identifiers_init(
	     pywrc_language_identifiers ) != 0 )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize language identifiers.",
		 function );

		goto on_error;
	}
	pywrc_language_identifiers->resource_object                  = resource_object;
	pywrc_language_identifiers->get_language_identifier_by_index = get_language_identifier_by_index;
	pywrc_language_identifiers->number_of_languages              = number_of_languages;

	Py_IncRef(
	 (PyObject *) pywrc_language_identifiers->resource_object );

	return( (PyObject *) pywrc_language_identifiers );

on_error:
	if( pywrc_language_identifiers != NULL )
	{
		Py_DecRef(
		 (PyObject *) pywrc_language_identifiers );
	}
	return( NULL );
}

/* Intializes a language identifiers object
 * Returns 0 if successful or -1 on error
 */
int pywrc_language_identifiers_init(
     pywrc_language_identifiers_t *pywrc_language_identifiers )
{
	static char *function = "pywrc_language_identifiers_init";

	if( pywrc_language_identifiers == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid language identifiers.",
		 function );

		return( -1 );
	}
	/* Make sure the language identifiers values are initialized
	 */
	pywrc_language_identifiers->resource_object                  = NULL;
	pywrc_language_identifiers->get_language_identifier_by_index = NULL;
	pywrc_language_identifiers->language_identifier_index        = 0;
	pywrc_language_identifiers->number_of_languages              = 0;

	return( 0 );
}

/* Frees a language identifiers object
 */
void pywrc_language_identifiers_free(
      pywrc_language_identifiers_t *pywrc_language_identifiers )
{
	struct _typeobject *ob_type = NULL;
	static char *function       = "pywrc_language_identifiers_free";

	if( pywrc_language_identifiers == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid language identifiers.",
		 function );

		return;
	}
	ob_type = Py_TYPE(
	           pywrc_language_identifiers );

	if( ob_type == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: missing ob_type.",
		 function );

		return;
	}
	if( ob_type->tp_free == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid ob_type - missing tp_free.",
		 function );

		return;
	}
	if( pywrc_language_identifiers->resource_object != NULL )
	{
		Py_DecRef(
		 (PyObject *) pywrc_language_identifiers->resource_object );
	}
	ob_type->tp_free(
	 (PyObject*) pywrc_language_identifiers );
}

/* The language identifiers len() function
 */
Py_ssize_t pywrc_language_identifiers_len(
            pywrc_language_identifiers_t *pywrc_language_identifiers )
{
	static char *function = "pywrc_language_identifiers_len";

	if( pywrc_language_identifiers == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid language identifiers.",
		 function );

		return( -1 );
	}
	return( (Py_ssize_t) pywrc_language_identifiers->number_of_languages );
}

/* The language identifiers getitem() function
 */
PyObject *pywrc_language_identifiers_getitem(
           pywrc_language_identifiers_t *pywrc_language_identifiers,
           Py_ssize_t item_index )
{
	PyObject *language_identifier_object = NULL;
	static char *function                = "pywrc_language_identifiers_getitem";

	if( pywrc_language_identifiers == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid language identifiers.",
		 function );

		return( NULL );
	}
	if( pywrc_language_identifiers->get_language_identifier_by_index == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid language identifiers - missing get language identifier by index function.",
		 function );

		return( NULL );
	}
	if( pywrc_language_identifiers->number_of_languages < 0 )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid language identifiers - invalid number of languages.",
		 function );

		return( NULL );
	}
	if( ( item_index < 0 )
	 || ( item_index >= (Py_ssize_t) pywrc_language_identifiers->number_of_languages ) )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid invalid item index value out of bounds.",
		 function );

		return( NULL );
	}
	language_identifier_object = pywrc_language_identifiers->get_language_identifier_by_index(
	                              pywrc_language_identifiers->resource_object,
	                              (int) item_index );

	return( language_identifier_object );
}

/* The language identifiers iter() function
 */
PyObject *pywrc_language_identifiers_iter(
           pywrc_language_identifiers_t *pywrc_language_identifiers )
{
	static char *function = "pywrc_language_identifiers_iter";

	if( pywrc_language_identifiers == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid language identifiers.",
		 function );

		return( NULL );
	}
	Py_IncRef(
	 (PyObject *) pywrc_language_identifiers );

	return( (PyObject *) pywrc_language_identifiers );
}

/* The language identifiers iternext() function
 */
PyObject *pywrc_language_identifiers_iternext(
           pywrc_language_identifiers_t *pywrc_language_identifiers )
{
	PyObject *language_identifier_object = NULL;
	static char *function                = "pywrc_language_identifiers_iternext";

	if( pywrc_language_identifiers == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid language identifiers.",
		 function );

		return( NULL );
	}
	if( pywrc_language_identifiers->get_language_identifier_by_index == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid language identifiers - missing get language identifier by index function.",
		 function );

		return( NULL );
	}
	if( pywrc_language_identifiers->language_identifier_index < 0 )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid language identifiers - invalid language identifier index.",
		 function );

		return( NULL );
	}
	if( pywrc_language_identifiers->number_of_languages < 0 )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid language identifiers - invalid number of languages.",
		 function );

		return( NULL );
	}
	if( pywrc_language_identifiers->language_identifier_index >= pywrc_language_identifiers->number_of_languages )
	{
		PyErr_SetNone(
		 PyExc_StopIteration );

		return( NULL );
	}
	language_identifier_object = pywrc_language_identifiers->get_language_identifier_by_index(
	                              pywrc_language_identifiers->resource_object,
	                              pywrc_language_identifiers->language_identifier_index );

	if( language_identifier_object != NULL )
	{
		pywrc_language_identifiers->language_identifier_index++;
	}
	return( language_identifier_object );
}

