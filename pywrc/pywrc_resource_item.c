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
#include "pywrc_resource_item.h"
#include "pywrc_resource_items.h"
#include "pywrc_unused.h"

PyMethodDef pywrc_resource_item_object_methods[] = {

	{ "get_identifier",
	  (PyCFunction) pywrc_resource_item_get_identifier,
	  METH_NOARGS,
	  "get_identifier() -> Integer\n"
	  "\n"
	  "Retrieves the resource item identifier." },

	{ "get_name",
	  (PyCFunction) pywrc_resource_item_get_name,
	  METH_NOARGS,
	  "get_name() -> Unicode string or None\n"
	  "\n"
	  "Retrieves the name." },

	/* Functions to access the resource item data */

	{ "read_buffer",
	  (PyCFunction) pywrc_resource_item_read_buffer,
	  METH_VARARGS | METH_KEYWORDS,
	  "read_buffer(size) -> String\n"
	  "\n"
	  "Reads a buffer of resource item data." },

	{ "read_buffer_at_offset",
	  (PyCFunction) pywrc_resource_item_read_buffer_at_offset,
	  METH_VARARGS | METH_KEYWORDS,
	  "read_buffer_at_offset(size, offset) -> String\n"
	  "\n"
	  "Reads a buffer of resource item data at a specific offset." },

	{ "seek_offset",
	  (PyCFunction) pywrc_resource_item_seek_offset,
	  METH_VARARGS | METH_KEYWORDS,
	  "seek_offset(offset, whence) -> None\n"
	  "\n"
	  "Seeks an offset within the resource item data." },

	{ "get_offset",
	  (PyCFunction) pywrc_resource_item_get_offset,
	  METH_NOARGS,
	  "get_offset() -> Integer\n"
	  "\n"
	  "Retrieves the current offset within the resource item data." },

	/* Some Pythonesque aliases */

	{ "read",
	  (PyCFunction) pywrc_resource_item_read_buffer,
	  METH_VARARGS | METH_KEYWORDS,
	  "read(size) -> String\n"
	  "\n"
	  "Reads a buffer of resource item data." },

	{ "seek",
	  (PyCFunction) pywrc_resource_item_seek_offset,
	  METH_VARARGS | METH_KEYWORDS,
	  "seek(offset, whence) -> None\n"
	  "\n"
	  "Seeks an offset within the resource item data." },

	{ "tell",
	  (PyCFunction) pywrc_resource_item_get_offset,
	  METH_NOARGS,
	  "tell() -> Integer\n"
	  "\n"
	  "Retrieves the current offset within the resource item data." },

	/* Functions to access sub items */

	{ "get_number_of_sub_items",
	  (PyCFunction) pywrc_resource_item_get_number_of_sub_items,
	  METH_NOARGS,
	  "get_number_of_sub_items() -> Integer\n"
	  "\n"
	  "Retrieves the number of sub items." },

	{ "get_sub_item",
	  (PyCFunction) pywrc_resource_item_get_sub_item,
	  METH_VARARGS | METH_KEYWORDS,
	  "get_sub_item(item_index) -> Object\n"
	  "\n"
	  "Retrieves the sub item specified by the index." },

	/* Sentinel */
	{ NULL, NULL, 0, NULL }
};

PyGetSetDef pywrc_resource_item_object_get_set_definitions[] = {

	{ "identifier",
	  (getter) pywrc_resource_item_get_identifier,
	  (setter) 0,
	  "The resource item identifier.",
	  NULL },

	{ "name",
	  (getter) pywrc_resource_item_get_name,
	  (setter) 0,
	  "The name.",
	  NULL },

	{ "number_of_sub_items",
	  (getter) pywrc_resource_item_get_number_of_sub_items,
	  (setter) 0,
	  "The number of sub items.",
	  NULL },

	{ "sub_items",
	  (getter) pywrc_resource_item_get_sub_items,
	  (setter) 0,
	  "The sub items.",
	  NULL },

	/* Sentinel */
	{ NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pywrc_resource_item_type_object = {
	PyVarObject_HEAD_INIT( NULL, 0 )

	/* tp_name */
	"pywrc.resource_item",
	/* tp_basicsize */
	sizeof( pywrc_resource_item_t ),
	/* tp_itemsize */
	0,
	/* tp_dealloc */
	(destructor) pywrc_resource_item_free,
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
	"pywrc resource item object (wraps libwrc_resource_item_t)",
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
	pywrc_resource_item_object_methods,
	/* tp_members */
	0,
	/* tp_getset */
	pywrc_resource_item_object_get_set_definitions,
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
	(initproc) pywrc_resource_item_init,
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

/* Creates a new resource item object
 * Returns a Python object if successful or NULL on error
 */
PyObject *pywrc_resource_item_new(
           libwrc_resource_item_t *resource_item,
           PyObject *parent_object )
{
	pywrc_resource_item_t *pywrc_resource_item = NULL;
	static char *function                      = "pywrc_resource_item_new";

	if( resource_item == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid resource item.",
		 function );

		return( NULL );
	}
	/* PyObject_New does not invoke tp_init
	 */
	pywrc_resource_item = PyObject_New(
	                       struct pywrc_resource_item,
	                       &pywrc_resource_item_type_object );

	if( pywrc_resource_item == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize resource item.",
		 function );

		goto on_error;
	}
	pywrc_resource_item->resource_item = resource_item;
	pywrc_resource_item->parent_object = parent_object;

	if( pywrc_resource_item->parent_object != NULL )
	{
		Py_IncRef(
		 pywrc_resource_item->parent_object );
	}
	return( (PyObject *) pywrc_resource_item );

on_error:
	if( pywrc_resource_item != NULL )
	{
		Py_DecRef(
		 (PyObject *) pywrc_resource_item );
	}
	return( NULL );
}

/* Initializes a resource item object
 * Returns 0 if successful or -1 on error
 */
int pywrc_resource_item_init(
     pywrc_resource_item_t *pywrc_resource_item )
{
	static char *function = "pywrc_resource_item_init";

	if( pywrc_resource_item == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid resource item.",
		 function );

		return( -1 );
	}
	/* Make sure libwrc resource item is set to NULL
	 */
	pywrc_resource_item->resource_item = NULL;

	PyErr_Format(
	 PyExc_NotImplementedError,
	 "%s: initialize of resource item not supported.",
	 function );

	return( -1 );
}

/* Frees a resource item object
 */
void pywrc_resource_item_free(
      pywrc_resource_item_t *pywrc_resource_item )
{
	struct _typeobject *ob_type = NULL;
	libcerror_error_t *error    = NULL;
	static char *function       = "pywrc_resource_item_free";
	int result                  = 0;

	if( pywrc_resource_item == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid resource item.",
		 function );

		return;
	}
	ob_type = Py_TYPE(
	           pywrc_resource_item );

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
	if( pywrc_resource_item->resource_item != NULL )
	{
		Py_BEGIN_ALLOW_THREADS

		result = libwrc_resource_item_free(
		          &( pywrc_resource_item->resource_item ),
		          &error );

		Py_END_ALLOW_THREADS

		if( result != 1 )
		{
			pywrc_error_raise(
			 error,
			 PyExc_MemoryError,
			 "%s: unable to free libwrc resource item.",
			 function );

			libcerror_error_free(
			 &error );
		}
	}
	if( pywrc_resource_item->parent_object != NULL )
	{
		Py_DecRef(
		 pywrc_resource_item->parent_object );
	}
	ob_type->tp_free(
	 (PyObject*) pywrc_resource_item );
}

/* Retrieves the resource item identifier
 * Returns a Python object if successful or NULL on error
 */
PyObject *pywrc_resource_item_get_identifier(
           pywrc_resource_item_t *pywrc_resource_item,
           PyObject *arguments PYWRC_ATTRIBUTE_UNUSED )
{
	PyObject *integer_object = NULL;
	libcerror_error_t *error = NULL;
	static char *function    = "pywrc_resource_item_get_identifier";
	uint32_t value_32bit     = 0;
	int result               = 0;

	PYWRC_UNREFERENCED_PARAMETER( arguments )

	if( pywrc_resource_item == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid resource item.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libwrc_resource_item_get_identifier(
	          pywrc_resource_item->resource_item,
	          &value_32bit,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pywrc_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve resource item identifier.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	integer_object = PyLong_FromUnsignedLong(
	                  (unsigned long) value_32bit );

	return( integer_object );
}

/* Retrieves the name
 * Returns a Python object if successful or NULL on error
 */
PyObject *pywrc_resource_item_get_name(
           pywrc_resource_item_t *pywrc_resource_item,
           PyObject *arguments PYWRC_ATTRIBUTE_UNUSED )
{
	PyObject *string_object  = NULL;
	libcerror_error_t *error = NULL;
	static char *function    = "pywrc_resource_item_get_name";
	char *utf8_string        = NULL;
	size_t utf8_string_size  = 0;
	int result               = 0;

	PYWRC_UNREFERENCED_PARAMETER( arguments )

	if( pywrc_resource_item == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid resource item.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libwrc_resource_item_get_utf8_name_size(
	          pywrc_resource_item->resource_item,
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

	result = libwrc_resource_item_get_utf8_name(
	          pywrc_resource_item->resource_item,
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

/* Reads (resource item) data at the current offset into a buffer
 * Returns a Python object if successful or NULL on error
 */
PyObject *pywrc_resource_item_read_buffer(
           pywrc_resource_item_t *pywrc_resource_item,
           PyObject *arguments,
           PyObject *keywords )
{
	PyObject *integer_object    = NULL;
	PyObject *string_object     = NULL;
	libcerror_error_t *error    = NULL;
	char *buffer                = NULL;
	static char *function       = "pywrc_resource_item_read_buffer";
	static char *keyword_list[] = { "size", NULL };
	size64_t read_size          = 0;
	ssize_t read_count          = 0;
	int result                  = 0;

	if( pywrc_resource_item == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid pywrc resource item.",
		 function );

		return( NULL );
	}
	if( pywrc_resource_item->resource_item == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid pywrc resource item - missing libwrc resource item.",
		 function );

		return( NULL );
	}
	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "|O",
	     keyword_list,
	     &integer_object ) == 0 )
	{
		return( NULL );
	}
	if( integer_object == NULL )
	{
		result = 0;
	}
	else
	{
		result = PyObject_IsInstance(
		          integer_object,
		          (PyObject *) &PyLong_Type );

		if( result == -1 )
		{
			pywrc_error_fetch_and_raise(
			 PyExc_RuntimeError,
			 "%s: unable to determine if integer object is of type long.",
			 function );

			return( NULL );
		}
#if PY_MAJOR_VERSION < 3
		else if( result == 0 )
		{
			PyErr_Clear();

			result = PyObject_IsInstance(
				  integer_object,
				  (PyObject *) &PyInt_Type );

			if( result == -1 )
			{
				pywrc_error_fetch_and_raise(
				 PyExc_RuntimeError,
				 "%s: unable to determine if integer object is of type int.",
				 function );

				return( NULL );
			}
		}
#endif
	}
	if( result != 0 )
	{
		if( pywrc_integer_unsigned_copy_to_64bit(
		     integer_object,
		     (uint64_t *) &read_size,
		     &error ) != 1 )
		{
			pywrc_error_raise(
			 error,
			 PyExc_IOError,
			 "%s: unable to convert integer object into read size.",
			 function );

			libcerror_error_free(
			 &error );

			return( NULL );
		}
	}
	else if( ( integer_object == NULL )
	      || ( integer_object == Py_None ) )
	{
		Py_BEGIN_ALLOW_THREADS

		result = libwrc_resource_item_get_size(
			  pywrc_resource_item->resource_item,
			  (uint32_t *) &read_size,
			  &error );

		Py_END_ALLOW_THREADS

		if( result != 1 )
		{
			pywrc_error_raise(
			 error,
			 PyExc_IOError,
			 "%s: unable to retrieve size.",
			 function );

			libcerror_error_free(
			 &error );

			return( NULL );
		}
	}
	else
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: unsupported integer object type.",
		 function );

		return( NULL );
	}
	if( read_size == 0 )
	{
#if PY_MAJOR_VERSION >= 3
		string_object = PyBytes_FromString(
		                 "" );
#else
		string_object = PyString_FromString(
		                 "" );
#endif
		return( string_object );
	}
	/* Make sure the data fits into a memory buffer
	 */
	if( ( read_size > (size64_t) INT_MAX )
	 || ( read_size > (size64_t) SSIZE_MAX ) )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid argument read size value exceeds maximum.",
		 function );

		return( NULL );
	}
#if PY_MAJOR_VERSION >= 3
	string_object = PyBytes_FromStringAndSize(
	                 NULL,
	                 read_size );

	buffer = PyBytes_AsString(
	          string_object );
#else
	/* Note that a size of 0 is not supported
	 */
	string_object = PyString_FromStringAndSize(
	                 NULL,
	                 read_size );

	buffer = PyString_AsString(
	          string_object );
#endif
	Py_BEGIN_ALLOW_THREADS

	read_count = libwrc_resource_item_read_buffer(
	              pywrc_resource_item->resource_item,
	              (uint8_t *) buffer,
	              (size_t) read_size,
	              &error );

	Py_END_ALLOW_THREADS

	if( read_count <= -1 )
	{
		pywrc_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to read data.",
		 function );

		libcerror_error_free(
		 &error );

		Py_DecRef(
		 (PyObject *) string_object );

		return( NULL );
	}
	/* Need to resize the string here in case read_size was not fully read.
	 */
#if PY_MAJOR_VERSION >= 3
	if( _PyBytes_Resize(
	     &string_object,
	     (Py_ssize_t) read_count ) != 0 )
#else
	if( _PyString_Resize(
	     &string_object,
	     (Py_ssize_t) read_count ) != 0 )
#endif
	{
		Py_DecRef(
		 (PyObject *) string_object );

		return( NULL );
	}
	return( string_object );
}

/* Reads (resource item) data at a specific offset
 * Returns a Python object if successful or NULL on error
 */
PyObject *pywrc_resource_item_read_buffer_at_offset(
           pywrc_resource_item_t *pywrc_resource_item,
           PyObject *arguments,
           PyObject *keywords )
{
	PyObject *integer_object    = NULL;
	PyObject *string_object     = NULL;
	libcerror_error_t *error    = NULL;
	char *buffer                = NULL;
	static char *function       = "pywrc_resource_item_read_buffer_at_offset";
	static char *keyword_list[] = { "size", "offset", NULL };
	size64_t read_size          = 0;
	ssize_t read_count          = 0;
	off64_t read_offset         = 0;
	int result                  = 0;

	if( pywrc_resource_item == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid pywrc resource item.",
		 function );

		return( NULL );
	}
	if( pywrc_resource_item->resource_item == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid pywrc resource item - missing libwrc resource item.",
		 function );

		return( NULL );
	}
	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "OL",
	     keyword_list,
	     &integer_object,
	     &read_offset ) == 0 )
	{
		return( NULL );
	}
	result = PyObject_IsInstance(
	          integer_object,
	          (PyObject *) &PyLong_Type );

	if( result == -1 )
	{
		pywrc_error_fetch_and_raise(
	         PyExc_RuntimeError,
		 "%s: unable to determine if integer object is of type long.",
		 function );

		return( NULL );
	}
#if PY_MAJOR_VERSION < 3
	else if( result == 0 )
	{
		PyErr_Clear();

		result = PyObject_IsInstance(
		          integer_object,
		          (PyObject *) &PyInt_Type );

		if( result == -1 )
		{
			pywrc_error_fetch_and_raise(
		         PyExc_RuntimeError,
			 "%s: unable to determine if integer object is of type int.",
			 function );

			return( NULL );
		}
	}
#endif
	if( result != 0 )
	{
		if( pywrc_integer_unsigned_copy_to_64bit(
		     integer_object,
		     (uint64_t *) &read_size,
		     &error ) != 1 )
		{
			pywrc_error_raise(
			 error,
			 PyExc_IOError,
			 "%s: unable to convert integer object into read size.",
			 function );

			libcerror_error_free(
			 &error );

			return( NULL );
		}
	}
	else
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: unsupported integer object type.",
		 function );

		return( NULL );
	}
	if( read_size == 0 )
	{
#if PY_MAJOR_VERSION >= 3
		string_object = PyBytes_FromString(
		                 "" );
#else
		string_object = PyString_FromString(
		                 "" );
#endif
		return( string_object );
	}
	/* Make sure the data fits into a memory buffer
	 */
	if( ( read_size > (size64_t) INT_MAX )
	 || ( read_size > (size64_t) SSIZE_MAX ) )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid argument read size value exceeds maximum.",
		 function );

		return( NULL );
	}
#if PY_MAJOR_VERSION >= 3
	string_object = PyBytes_FromStringAndSize(
	                 NULL,
	                 read_size );

	buffer = PyBytes_AsString(
	          string_object );
#else
	/* Note that a size of 0 is not supported
	 */
	string_object = PyString_FromStringAndSize(
	                 NULL,
	                 read_size );

	buffer = PyString_AsString(
	          string_object );
#endif
	Py_BEGIN_ALLOW_THREADS

	read_count = libwrc_resource_item_read_buffer_at_offset(
	              pywrc_resource_item->resource_item,
	              (uint8_t *) buffer,
	              (size_t) read_size,
	              (off64_t) read_offset,
	              &error );

	Py_END_ALLOW_THREADS

	if( read_count <= -1 )
	{
		pywrc_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to read data.",
		 function );

		libcerror_error_free(
		 &error );

		Py_DecRef(
		 (PyObject *) string_object );

		return( NULL );
	}
	/* Need to resize the string here in case read_size was not fully read.
	 */
#if PY_MAJOR_VERSION >= 3
	if( _PyBytes_Resize(
	     &string_object,
	     (Py_ssize_t) read_count ) != 0 )
#else
	if( _PyString_Resize(
	     &string_object,
	     (Py_ssize_t) read_count ) != 0 )
#endif
	{
		Py_DecRef(
		 (PyObject *) string_object );

		return( NULL );
	}
	return( string_object );
}

/* Seeks a certain offset in the (resource item) data
 * Returns a Python object if successful or NULL on error
 */
PyObject *pywrc_resource_item_seek_offset(
           pywrc_resource_item_t *pywrc_resource_item,
           PyObject *arguments,
           PyObject *keywords )
{
	libcerror_error_t *error    = NULL;
	static char *function       = "pywrc_resource_item_seek_offset";
	static char *keyword_list[] = { "offset", "whence", NULL };
	off64_t offset              = 0;
	int whence                  = 0;

	if( pywrc_resource_item == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid item.",
		 function );

		return( NULL );
	}
	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "L|i",
	     keyword_list,
	     &offset,
	     &whence ) == 0 )
	{
		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	offset = libwrc_resource_item_seek_offset(
	          pywrc_resource_item->resource_item,
	          offset,
	          whence,
	          &error );

	Py_END_ALLOW_THREADS

 	if( offset == -1 )
	{
		pywrc_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to seek offset.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	Py_IncRef(
	 Py_None );

	return( Py_None );
}

/* Retrieves the current offset in the (resource item) data
 * Returns a Python object if successful or NULL on error
 */
PyObject *pywrc_resource_item_get_offset(
           pywrc_resource_item_t *pywrc_resource_item,
           PyObject *arguments PYWRC_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error = NULL;
	PyObject *integer_object = NULL;
	static char *function    = "pywrc_resource_item_get_offset";
	off64_t current_offset   = 0;
	int result               = 0;

	PYWRC_UNREFERENCED_PARAMETER( arguments )

	if( pywrc_resource_item == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid item.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libwrc_resource_item_get_offset(
	          pywrc_resource_item->resource_item,
	          &current_offset,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pywrc_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve offset.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	integer_object = pywrc_integer_signed_new_from_64bit(
	                  (int64_t) current_offset );

	return( integer_object );
}

/* Retrieves the number of sub items
 * Returns a Python object if successful or NULL on error
 */
PyObject *pywrc_resource_item_get_number_of_sub_items(
           pywrc_resource_item_t *pywrc_resource_item,
           PyObject *arguments PYWRC_ATTRIBUTE_UNUSED )
{
	PyObject *integer_object = NULL;
	libcerror_error_t *error = NULL;
	static char *function    = "pywrc_resource_item_get_number_of_sub_items";
	int number_of_sub_items  = 0;
	int result               = 0;

	PYWRC_UNREFERENCED_PARAMETER( arguments )

	if( pywrc_resource_item == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid resource item.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libwrc_resource_item_get_number_of_sub_items(
	          pywrc_resource_item->resource_item,
	          &number_of_sub_items,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pywrc_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve number of sub items.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
#if PY_MAJOR_VERSION >= 3
	integer_object = PyLong_FromLong(
	                  (long) number_of_sub_items );
#else
	integer_object = PyInt_FromLong(
	                  (long) number_of_sub_items );
#endif
	return( integer_object );
}

/* Retrieves a specific sub sub item by index
 * Returns a Python object if successful or NULL on error
 */
PyObject *pywrc_resource_item_get_sub_item_by_index(
           PyObject *pywrc_resource_item,
           int sub_item_index )
{
	PyObject *item_object            = NULL;
	libcerror_error_t *error         = NULL;
	libwrc_resource_item_t *sub_item = NULL;
	static char *function            = "pywrc_resource_item_get_sub_item_by_index";
	int result                       = 0;

	if( pywrc_resource_item == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid resource item.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libwrc_resource_item_get_sub_item_by_index(
	          ( (pywrc_resource_item_t *) pywrc_resource_item )->resource_item,
	          sub_item_index,
	          &sub_item,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pywrc_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve sub sub item: %d.",
		 function,
		 sub_item_index );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	item_object = pywrc_resource_item_new(
	               sub_item,
	               ( (pywrc_resource_item_t *) pywrc_resource_item )->parent_object );

	if( item_object == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create sub resource item object.",
		 function );

		goto on_error;
	}
	return( item_object );

on_error:
	if( sub_item != NULL )
	{
		libwrc_resource_item_free(
		 &sub_item,
		 NULL );
	}
	return( NULL );
}

/* Retrieves a specific sub sub item
 * Returns a Python object if successful or NULL on error
 */
PyObject *pywrc_resource_item_get_sub_item(
           pywrc_resource_item_t *pywrc_resource_item,
           PyObject *arguments,
           PyObject *keywords )
{
	PyObject *item_object       = NULL;
	static char *keyword_list[] = { "sub_item_index", NULL };
	int sub_item_index          = 0;

	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "i",
	     keyword_list,
	     &sub_item_index ) == 0 )
	{
		return( NULL );
	}
	item_object = pywrc_resource_item_get_sub_item_by_index(
	               (PyObject *) pywrc_resource_item,
	               sub_item_index );

	return( item_object );
}

/* Retrieves a sequence and iterator object for the sub items
 * Returns a Python object if successful or NULL on error
 */
PyObject *pywrc_resource_item_get_sub_items(
           pywrc_resource_item_t *pywrc_resource_item,
           PyObject *arguments PYWRC_ATTRIBUTE_UNUSED )
{
	PyObject *sequence_object = NULL;
	libcerror_error_t *error  = NULL;
	static char *function     = "pywrc_resource_item_get_sub_items";
	int number_of_sub_items   = 0;
	int result                = 0;

	PYWRC_UNREFERENCED_PARAMETER( arguments )

	if( pywrc_resource_item == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid resource item.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libwrc_resource_item_get_number_of_sub_items(
	          pywrc_resource_item->resource_item,
	          &number_of_sub_items,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pywrc_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve number of sub items.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	sequence_object = pywrc_resource_items_new(
	                   (PyObject *) pywrc_resource_item,
	                   &pywrc_resource_item_get_sub_item_by_index,
	                   number_of_sub_items );

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

