/*
 * Python object wrapper of libwrc_resource_t
 *
 * Copyright (C) 2011-2017, Joachim Metz <joachim.metz@gmail.com>
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

#include "pywrc_error.h"
#include "pywrc_integer.h"
#include "pywrc_language_identifiers.h"
#include "pywrc_libcerror.h"
#include "pywrc_libwrc.h"
#include "pywrc_python.h"
#include "pywrc_resource.h"
#include "pywrc_unused.h"

PyMethodDef pywrc_resource_object_methods[] = {

	/* Functions to access the resource values */

	{ "get_identifier",
	  (PyCFunction) pywrc_resource_get_identifier,
	  METH_NOARGS,
	  "get_identifier() -> Integer\n"
	  "\n"
	  "Retrieves the identifier (number)." },

	/* Functions to access the language identifiers */

	{ "get_number_of_languages",
	  (PyCFunction) pywrc_resource_get_number_of_languages,
	  METH_NOARGS,
	  "get_number_of_languages() -> Integer\n"
	  "\n"
	  "Retrieves the number of languages." },

	{ "get_language_identifier",
	  (PyCFunction) pywrc_resource_get_language_identifier,
	  METH_VARARGS | METH_KEYWORDS,
	  "get_language_identifier(language_identifier_index) -> Integer or None\n"
	  "\n"
	  "Retrieves a specific language identifier." },

	/* Sentinel */
	{ NULL, NULL, 0, NULL }
};

PyGetSetDef pywrc_resource_object_get_set_definitions[] = {

	{ "identifier",
	  (getter) pywrc_resource_get_identifier,
	  (setter) 0,
	  "The identifier (number).",
	  NULL },

	{ "number_of_languages",
	  (getter) pywrc_resource_get_number_of_languages,
	  (setter) 0,
	  "The number of languages.",
	  NULL },

	{ "language_identifiers",
	  (getter) pywrc_resource_get_language_identifiers,
	  (setter) 0,
	  "The language identifiers",
	  NULL },

	/* Sentinel */
	{ NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pywrc_resource_type_object = {
	PyVarObject_HEAD_INIT( NULL, 0 )

	/* tp_name */
	"pywrc.resource",
	/* tp_basicsize */
	sizeof( pywrc_resource_t ),
	/* tp_itemsize */
	0,
	/* tp_dealloc */
	(destructor) pywrc_resource_free,
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
	0,
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
	Py_TPFLAGS_DEFAULT,
	/* tp_doc */
	"pywrc resource object (wraps libwrc_resource_t)",
	/* tp_traverse */
	0,
	/* tp_clear */
	0,
	/* tp_richcompare */
	0,
	/* tp_weaklistoffset */
	0,
	/* tp_iter */
	0,
	/* tp_iternext */
	0,
	/* tp_methods */
	pywrc_resource_object_methods,
	/* tp_members */
	0,
	/* tp_getset */
	pywrc_resource_object_get_set_definitions,
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
	(initproc) pywrc_resource_init,
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

/* Creates a new resource object
 * Returns a Python object if successful or NULL on error
 */
PyObject *pywrc_resource_new(
           PyTypeObject *type_object,
           libwrc_resource_t *resource,
           pywrc_stream_t *stream_object )
{
	pywrc_resource_t *pywrc_resource = NULL;
	static char *function            = "pywrc_resource_new";

	if( resource == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid resource.",
		 function );

		return( NULL );
	}
	pywrc_resource = PyObject_New(
	                  struct pywrc_resource,
	                  type_object );

	if( pywrc_resource == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize resource.",
		 function );

		goto on_error;
	}
	if( pywrc_resource_init(
	     pywrc_resource ) != 0 )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize resource.",
		 function );

		goto on_error;
	}
	pywrc_resource->resource      = resource;
	pywrc_resource->stream_object = stream_object;

	Py_IncRef(
	 (PyObject *) pywrc_resource->stream_object );

	return( (PyObject *) pywrc_resource );

on_error:
	if( pywrc_resource != NULL )
	{
		Py_DecRef(
		 (PyObject *) pywrc_resource );
	}
	return( NULL );
}

/* Intializes an resource object
 * Returns 0 if successful or -1 on error
 */
int pywrc_resource_init(
     pywrc_resource_t *pywrc_resource )
{
	static char *function = "pywrc_resource_init";

	if( pywrc_resource == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid resource.",
		 function );

		return( -1 );
	}
	/* Make sure libwrc resource is set to NULL
	 */
	pywrc_resource->resource = NULL;

	return( 0 );
}

/* Frees an resource object
 */
void pywrc_resource_free(
      pywrc_resource_t *pywrc_resource )
{
	libcerror_error_t *error    = NULL;
	struct _typeobject *ob_type = NULL;
	static char *function       = "pywrc_resource_free";
	int result                  = 0;

	if( pywrc_resource == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid resource.",
		 function );

		return;
	}
	if( pywrc_resource->resource == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid resource - missing libwrc resource.",
		 function );

		return;
	}
	ob_type = Py_TYPE(
	           pywrc_resource );

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
	Py_BEGIN_ALLOW_THREADS

	result = libwrc_resource_free(
	          &( pywrc_resource->resource ),
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pywrc_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to free libwrc resource.",
		 function );

		libcerror_error_free(
		 &error );
	}
	if( pywrc_resource->stream_object != NULL )
	{
		Py_DecRef(
		 (PyObject *) pywrc_resource->stream_object );
	}
	ob_type->tp_free(
	 (PyObject*) pywrc_resource );
}

/* Retrieves the identifier
 * Returns a Python object if successful or NULL on error
 */
PyObject *pywrc_resource_get_identifier(
           pywrc_resource_t *pywrc_resource,
           PyObject *arguments PYWRC_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error = NULL;
	PyObject *integer_object = NULL;
	static char *function    = "pywrc_resource_get_identifier";
	uint32_t identifier      = 0;
	int result               = 0;

	PYWRC_UNREFERENCED_PARAMETER( arguments )

	if( pywrc_resource == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid resource.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libwrc_resource_get_identifier(
	          pywrc_resource->resource,
	          &identifier,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pywrc_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve identifier.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	integer_object = pywrc_integer_unsigned_new_from_64bit(
	                  (uint64_t) identifier );

	return( integer_object );
}

/* Retrieves the number of languages
 * Returns a Python object if successful or NULL on error
 */
PyObject *pywrc_resource_get_number_of_languages(
           pywrc_resource_t *pywrc_resource,
           PyObject *arguments PYWRC_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error = NULL;
	PyObject *integer_object = NULL;
	static char *function    = "pywrc_resource_get_number_of_languages";
	int number_of_languages  = 0;
	int result               = 0;

	PYWRC_UNREFERENCED_PARAMETER( arguments )

	if( pywrc_resource == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid resource.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libwrc_resource_get_number_of_languages(
	          pywrc_resource->resource,
	          &number_of_languages,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pywrc_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve number of languages.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
#if PY_MAJOR_VERSION >= 3
	integer_object = PyLong_FromLong(
	                  (long) number_of_languages );
#else
	integer_object = PyInt_FromLong(
	                  (long) number_of_languages );
#endif
	return( integer_object );
}

/* Retrieves a specific language identifier by index
 * Returns a Python object if successful or NULL on error
 */
PyObject *pywrc_resource_get_language_identifier_by_index(
           pywrc_resource_t *pywrc_resource,
           int language_identifier_index )
{
	libcerror_error_t *error     = NULL;
	PyObject *integer_object     = NULL;
	static char *function        = "pywrc_resource_get_language_identifier_by_index";
	uint32_t language_identifier = 0;
	int result                   = 0;

	if( pywrc_resource == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid resource.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libwrc_resource_get_language_identifier(
	          pywrc_resource->resource,
	          language_identifier_index,
	          &language_identifier,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pywrc_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve language identifier: %d.",
		 function,
		 language_identifier_index );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	integer_object = pywrc_integer_unsigned_new_from_64bit(
	                  (uint64_t) language_identifier );

	return( integer_object );
}

/* Retrieves a specific language identifier
 * Returns a Python object if successful or NULL on error
 */
PyObject *pywrc_resource_get_language_identifier(
           pywrc_resource_t *pywrc_resource,
           PyObject *arguments,
           PyObject *keywords )
{
	static char *keyword_list[]   = { "language_identifier_index", NULL };
	int language_identifier_index = 0;

	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "i",
	     keyword_list,
	     &language_identifier_index ) == 0 )
	{
		return( NULL );
	}
	return( pywrc_resource_get_language_identifier_by_index(
	         pywrc_resource,
	         language_identifier_index ) );
}

/* Retrieves a language identifiers sequence and iterator object for the language identifiers
 * Returns a Python object if successful or NULL on error
 */
PyObject *pywrc_resource_get_language_identifiers(
           pywrc_resource_t *pywrc_resource,
           PyObject *arguments PYWRC_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error              = NULL;
	PyObject *language_identifiers_object = NULL;
	static char *function                 = "pywrc_resource_get_language_identifiers";
	int number_of_languages               = 0;
	int result                            = 0;

	PYWRC_UNREFERENCED_PARAMETER( arguments )

	if( pywrc_resource == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid resource.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libwrc_resource_get_number_of_languages(
	          pywrc_resource->resource,
	          &number_of_languages,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pywrc_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve number of languages.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	language_identifiers_object = pywrc_language_identifiers_new(
	                               pywrc_resource,
	                               &pywrc_resource_get_language_identifier_by_index,
	                               number_of_languages );

	if( language_identifiers_object == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create language identifiers object.",
		 function );

		return( NULL );
	}
	return( language_identifiers_object );
}

