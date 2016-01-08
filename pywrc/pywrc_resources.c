/*
 * Python object definition of the resources sequence and iterator
 *
 * Copyright (C) 2011-2016, Joachim Metz <joachim.metz@gmail.com>
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

#include "pywrc_libcerror.h"
#include "pywrc_libwrc.h"
#include "pywrc_python.h"
#include "pywrc_resource.h"
#include "pywrc_resources.h"
#include "pywrc_stream.h"

PySequenceMethods pywrc_resources_sequence_methods = {
	/* sq_length */
	(lenfunc) pywrc_resources_len,
	/* sq_concat */
	0,
	/* sq_repeat */
	0,
	/* sq_item */
	(ssizeargfunc) pywrc_resources_getitem,
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

PyTypeObject pywrc_resources_type_object = {
	PyVarObject_HEAD_INIT( NULL, 0 )

	/* tp_name */
	"pywrc._resources",
	/* tp_basicsize */
	sizeof( pywrc_resources_t ),
	/* tp_itemsize */
	0,
	/* tp_dealloc */
	(destructor) pywrc_resources_free,
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
	&pywrc_resources_sequence_methods,
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
	"internal pywrc resources sequence and iterator object",
	/* tp_traverse */
	0,
	/* tp_clear */
	0,
	/* tp_richcompare */
	0,
	/* tp_weaklistoffset */
	0,
	/* tp_iter */
	(getiterfunc) pywrc_resources_iter,
	/* tp_iternext */
	(iternextfunc) pywrc_resources_iternext,
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
	(initproc) pywrc_resources_init,
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

/* Creates a new resources object
 * Returns a Python object if successful or NULL on error
 */
PyObject *pywrc_resources_new(
           pywrc_stream_t *stream_object,
           PyObject* (*get_resource_by_index)(
                        pywrc_stream_t *stream_object,
                        int resource_index ),
           int number_of_resources )
{
	pywrc_resources_t *pywrc_resources = NULL;
	static char *function              = "pywrc_resources_new";

	if( stream_object == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid stream object.",
		 function );

		return( NULL );
	}
	if( get_resource_by_index == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid get resource by index function.",
		 function );

		return( NULL );
	}
	/* Make sure the resources values are initialized
	 */
	pywrc_resources = PyObject_New(
	                 struct pywrc_resources,
	                 &pywrc_resources_type_object );

	if( pywrc_resources == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize resources.",
		 function );

		goto on_error;
	}
	if( pywrc_resources_init(
	     pywrc_resources ) != 0 )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize resources.",
		 function );

		goto on_error;
	}
	pywrc_resources->stream_object         = stream_object;
	pywrc_resources->get_resource_by_index = get_resource_by_index;
	pywrc_resources->number_of_resources   = number_of_resources;

	Py_IncRef(
	 (PyObject *) pywrc_resources->stream_object );

	return( (PyObject *) pywrc_resources );

on_error:
	if( pywrc_resources != NULL )
	{
		Py_DecRef(
		 (PyObject *) pywrc_resources );
	}
	return( NULL );
}

/* Intializes a resources object
 * Returns 0 if successful or -1 on error
 */
int pywrc_resources_init(
     pywrc_resources_t *pywrc_resources )
{
	static char *function = "pywrc_resources_init";

	if( pywrc_resources == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid resources.",
		 function );

		return( -1 );
	}
	/* Make sure the resources values are initialized
	 */
	pywrc_resources->stream_object         = NULL;
	pywrc_resources->get_resource_by_index = NULL;
	pywrc_resources->resource_index        = 0;
	pywrc_resources->number_of_resources   = 0;

	return( 0 );
}

/* Frees a resources object
 */
void pywrc_resources_free(
      pywrc_resources_t *pywrc_resources )
{
	struct _typeobject *ob_type = NULL;
	static char *function       = "pywrc_resources_free";

	if( pywrc_resources == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid resources.",
		 function );

		return;
	}
	ob_type = Py_TYPE(
	           pywrc_resources );

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
	if( pywrc_resources->stream_object != NULL )
	{
		Py_DecRef(
		 (PyObject *) pywrc_resources->stream_object );
	}
	ob_type->tp_free(
	 (PyObject*) pywrc_resources );
}

/* The resources len() function
 */
Py_ssize_t pywrc_resources_len(
            pywrc_resources_t *pywrc_resources )
{
	static char *function = "pywrc_resources_len";

	if( pywrc_resources == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid resources.",
		 function );

		return( -1 );
	}
	return( (Py_ssize_t) pywrc_resources->number_of_resources );
}

/* The resources getitem() function
 */
PyObject *pywrc_resources_getitem(
           pywrc_resources_t *pywrc_resources,
           Py_ssize_t item_index )
{
	PyObject *resource_object = NULL;
	static char *function     = "pywrc_resources_getitem";

	if( pywrc_resources == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid resources.",
		 function );

		return( NULL );
	}
	if( pywrc_resources->get_resource_by_index == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid resources - missing get resource by index function.",
		 function );

		return( NULL );
	}
	if( pywrc_resources->number_of_resources < 0 )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid resources - invalid number of resources.",
		 function );

		return( NULL );
	}
	if( ( item_index < 0 )
	 || ( item_index >= (Py_ssize_t) pywrc_resources->number_of_resources ) )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid invalid item index value out of bounds.",
		 function );

		return( NULL );
	}
	resource_object = pywrc_resources->get_resource_by_index(
	                   pywrc_resources->stream_object,
	                   (int) item_index );

	return( resource_object );
}

/* The resources iter() function
 */
PyObject *pywrc_resources_iter(
           pywrc_resources_t *pywrc_resources )
{
	static char *function = "pywrc_resources_iter";

	if( pywrc_resources == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid resources.",
		 function );

		return( NULL );
	}
	Py_IncRef(
	 (PyObject *) pywrc_resources );

	return( (PyObject *) pywrc_resources );
}

/* The resources iternext() function
 */
PyObject *pywrc_resources_iternext(
           pywrc_resources_t *pywrc_resources )
{
	PyObject *resource_object = NULL;
	static char *function     = "pywrc_resources_iternext";

	if( pywrc_resources == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid resources.",
		 function );

		return( NULL );
	}
	if( pywrc_resources->get_resource_by_index == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid resources - missing get resource by index function.",
		 function );

		return( NULL );
	}
	if( pywrc_resources->resource_index < 0 )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid resources - invalid resource index.",
		 function );

		return( NULL );
	}
	if( pywrc_resources->number_of_resources < 0 )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid resources - invalid number of resources.",
		 function );

		return( NULL );
	}
	if( pywrc_resources->resource_index >= pywrc_resources->number_of_resources )
	{
		PyErr_SetNone(
		 PyExc_StopIteration );

		return( NULL );
	}
	resource_object = pywrc_resources->get_resource_by_index(
	                   pywrc_resources->stream_object,
	                   pywrc_resources->resource_index );

	if( resource_object != NULL )
	{
		pywrc_resources->resource_index++;
	}
	return( resource_object );
}

