/*
 * Python object wrapper of libwrc_resource_t
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

#include <common.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( HAVE_WINAPI )
#include <stdlib.h>
#endif

#include "pywrc_error.h"
#include "pywrc_integer.h"
#include "pywrc_libcerror.h"
#include "pywrc_libwrc.h"
#include "pywrc_python.h"
#include "pywrc_resource.h"
#include "pywrc_resource_item.h"
#include "pywrc_resource_items.h"
#include "pywrc_unused.h"

PyMethodDef pywrc_resource_object_methods[] = {

	/* Functions to access the resource values */

	{ "get_identifier",
	  (PyCFunction) pywrc_resource_get_identifier,
	  METH_NOARGS,
	  "get_identifier() -> Integer\n"
	  "\n"
	  "Retrieves the identifier (number)." },

	{ "get_name",
	  (PyCFunction) pywrc_resource_get_name,
	  METH_NOARGS,
	  "get_name() -> Unicode string or None\n"
	  "\n"
	  "Retrieves the name." },

	/* Functions to access the resource items */

	{ "get_number_of_items",
	  (PyCFunction) pywrc_resource_get_number_of_items,
	  METH_NOARGS,
	  "get_number_of_items() -> Integer\n"
	  "\n"
	  "Retrieves the number of items." },

	{ "get_item",
	  (PyCFunction) pywrc_resource_get_item,
	  METH_VARARGS | METH_KEYWORDS,
	  "get_item(item_index) -> Object\n"
	  "\n"
	  "Retrieves the item specified by the index." },

	/* Sentinel */
	{ NULL, NULL, 0, NULL }
};

PyGetSetDef pywrc_resource_object_get_set_definitions[] = {

	{ "identifier",
	  (getter) pywrc_resource_get_identifier,
	  (setter) 0,
	  "The identifier (number).",
	  NULL },

	{ "name",
	  (getter) pywrc_resource_get_name,
	  (setter) 0,
	  "The name.",
	  NULL },

	{ "number_of_items",
	  (getter) pywrc_resource_get_number_of_items,
	  (setter) 0,
	  "The number of items.",
	  NULL },

	{ "items",
	  (getter) pywrc_resource_get_items,
	  (setter) 0,
	  "The items.",
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
           libwrc_resource_t *resource,
           PyObject *parent_object )
{
	pywrc_resource_t *pywrc_resource = NULL;
	static char *function            = "pywrc_resource_new";

	if( resource == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid resource.",
		 function );

		return( NULL );
	}
	/* PyObject_New does not invoke tp_init
	 */
	pywrc_resource = PyObject_New(
	                  struct pywrc_resource,
	                  &pywrc_resource_type_object );

	if( pywrc_resource == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize resource.",
		 function );

		goto on_error;
	}
	pywrc_resource->resource      = resource;
	pywrc_resource->parent_object = parent_object;

	Py_IncRef(
	 (PyObject *) pywrc_resource->parent_object );

	return( (PyObject *) pywrc_resource );

on_error:
	if( pywrc_resource != NULL )
	{
		Py_DecRef(
		 (PyObject *) pywrc_resource );
	}
	return( NULL );
}

/* Initializes a resource object
 * Returns 0 if successful or -1 on error
 */
int pywrc_resource_init(
     pywrc_resource_t *pywrc_resource )
{
	static char *function = "pywrc_resource_init";

	if( pywrc_resource == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid resource.",
		 function );

		return( -1 );
	}
	/* Make sure libwrc resource is set to NULL
	 */
	pywrc_resource->resource = NULL;

	PyErr_Format(
	 PyExc_NotImplementedError,
	 "%s: initialize of resource not supported.",
	 function );

	return( -1 );
}

/* Frees a resource object
 */
void pywrc_resource_free(
      pywrc_resource_t *pywrc_resource )
{
	struct _typeobject *ob_type = NULL;
	libcerror_error_t *error    = NULL;
	static char *function       = "pywrc_resource_free";
	int result                  = 0;

	if( pywrc_resource == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid resource.",
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
	if( pywrc_resource->resource != NULL )
	{
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
	}
	if( pywrc_resource->parent_object != NULL )
	{
		Py_DecRef(
		 (PyObject *) pywrc_resource->parent_object );
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
	PyObject *integer_object = NULL;
	libcerror_error_t *error = NULL;
	static char *function    = "pywrc_resource_get_identifier";
	uint32_t identifier      = 0;
	int result               = 0;

	PYWRC_UNREFERENCED_PARAMETER( arguments )

	if( pywrc_resource == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
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

/* Retrieves the name
 * Returns a Python object if successful or NULL on error
 */
PyObject *pywrc_resource_get_name(
           pywrc_resource_t *pywrc_resource,
           PyObject *arguments PYWRC_ATTRIBUTE_UNUSED )
{
	PyObject *string_object  = NULL;
	libcerror_error_t *error = NULL;
	static char *function    = "pywrc_resource_get_name";
	char *utf8_string        = NULL;
	size_t utf8_string_size  = 0;
	int result               = 0;

	PYWRC_UNREFERENCED_PARAMETER( arguments )

	if( pywrc_resource == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid resource.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libwrc_resource_get_utf8_name_size(
	          pywrc_resource->resource,
	          &utf8_string_size,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		pywrc_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to determine size of name as UTF-8 string.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	else if( ( result == 0 )
	      || ( utf8_string_size == 0 ) )
	{
		Py_IncRef(
		 Py_None );

		return( Py_None );
	}
	utf8_string = (char *) PyMem_Malloc(
	                        sizeof( char ) * utf8_string_size );

	if( utf8_string == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create UTF-8 string.",
		 function );

		goto on_error;
	}
	Py_BEGIN_ALLOW_THREADS

	result = libwrc_resource_get_utf8_name(
	          pywrc_resource->resource,
	          (uint8_t *) utf8_string,
	          utf8_string_size,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pywrc_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve name as UTF-8 string.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	/* Pass the string length to PyUnicode_DecodeUTF8 otherwise it makes
	 * the end of string character is part of the string
	 */
	string_object = PyUnicode_DecodeUTF8(
	                 utf8_string,
	                 (Py_ssize_t) utf8_string_size - 1,
	                 NULL );

	if( string_object == NULL )
	{
		PyErr_Format(
		 PyExc_IOError,
		 "%s: unable to convert UTF-8 string into Unicode object.",
		 function );

		goto on_error;
	}
	PyMem_Free(
	 utf8_string );

	return( string_object );

on_error:
	if( utf8_string != NULL )
	{
		PyMem_Free(
		 utf8_string );
	}
	return( NULL );
}

/* Retrieves the number of resource items
 * Returns a Python object if successful or NULL on error
 */
PyObject *pywrc_resource_get_number_of_items(
           pywrc_resource_t *pywrc_resource,
           PyObject *arguments PYWRC_ATTRIBUTE_UNUSED )
{
	PyObject *integer_object = NULL;
	libcerror_error_t *error = NULL;
	static char *function    = "pywrc_resource_get_number_of_items";
	int number_of_items      = 0;
	int result               = 0;

	PYWRC_UNREFERENCED_PARAMETER( arguments )

	if( pywrc_resource == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid resource.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libwrc_resource_get_number_of_items(
	          pywrc_resource->resource,
	          &number_of_items,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pywrc_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve .",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
#if PY_MAJOR_VERSION >= 3
	integer_object = PyLong_FromLong(
	                  (long) number_of_items );
#else
	integer_object = PyInt_FromLong(
	                  (long) number_of_items );
#endif
	return( integer_object );
}

/* Retrieves a specific resource item by index
 * Returns a Python object if successful or NULL on error
 */
PyObject *pywrc_resource_get_item_by_index(
           PyObject *pywrc_resource,
           int item_index )
{
	PyObject *item_object        = NULL;
	libcerror_error_t *error     = NULL;
	libwrc_resource_item_t *item = NULL;
	static char *function        = "pywrc_resource_get_item_by_index";
	int result                   = 0;

	if( pywrc_resource == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid resource.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libwrc_resource_get_item_by_index(
	          ( (pywrc_resource_t *) pywrc_resource )->resource,
	          item_index,
	          &item,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pywrc_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve : %d.",
		 function,
		 item_index );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	item_object = pywrc_resource_item_new(
	               item,
	               pywrc_resource );

	if( item_object == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create resource item object.",
		 function );

		goto on_error;
	}
	return( item_object );

on_error:
	if( item != NULL )
	{
		libwrc_resource_item_free(
		 &item,
		 NULL );
	}
	return( NULL );
}

/* Retrieves a specific resource item
 * Returns a Python object if successful or NULL on error
 */
PyObject *pywrc_resource_get_item(
           pywrc_resource_t *pywrc_resource,
           PyObject *arguments,
           PyObject *keywords )
{
	PyObject *item_object       = NULL;
	static char *keyword_list[] = { "item_index", NULL };
	int item_index              = 0;

	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "i",
	     keyword_list,
	     &item_index ) == 0 )
	{
		return( NULL );
	}
	item_object = pywrc_resource_get_item_by_index(
	               (PyObject *) pywrc_resource,
	               item_index );

	return( item_object );
}

/* Retrieves a sequence and iterator object for the resource items
 * Returns a Python object if successful or NULL on error
 */
PyObject *pywrc_resource_get_items(
           pywrc_resource_t *pywrc_resource,
           PyObject *arguments PYWRC_ATTRIBUTE_UNUSED )
{
	PyObject *sequence_object = NULL;
	libcerror_error_t *error  = NULL;
	static char *function     = "pywrc_resource_get_items";
	int number_of_items       = 0;
	int result                = 0;

	PYWRC_UNREFERENCED_PARAMETER( arguments )

	if( pywrc_resource == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid resource.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libwrc_resource_get_number_of_items(
	          pywrc_resource->resource,
	          &number_of_items,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pywrc_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve number of items.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	sequence_object = pywrc_resource_items_new(
	                   (PyObject *) pywrc_resource,
	                   &pywrc_resource_get_item_by_index,
	                   number_of_items );

	if( sequence_object == NULL )
	{
		pywrc_error_raise(
		 error,
		 PyExc_MemoryError,
		 "%s: unable to create sequence object.",
		 function );

		return( NULL );
	}
	return( sequence_object );
}


