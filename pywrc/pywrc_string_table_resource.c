/*
 * Python object definition of the libwrc string table resource
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
#include "pywrc_string_table_resource.h"
#include "pywrc_unused.h"

PyMethodDef pywrc_string_table_resource_object_methods[] = {

	/* Functions to access the string table resource values */

	{ "copy_from_byte_stream",
	  (PyCFunction) pywrc_string_table_resource_copy_from_byte_stream,
	  METH_VARARGS | METH_KEYWORDS,
	  "copy_from_byte_stream(byte_stream, base_identifier)\n"
	  "\n"
	  "Copies the string table resource from the byte stream." },

	{ "get_number_of_strings",
	  (PyCFunction) pywrc_string_table_resource_get_number_of_strings,
	  METH_NOARGS,
	  "get_number_of_strings() -> Integer\n"
	  "\n"
	  "Retrieves the number of strings." },

	{ "get_string_identifier",
	  (PyCFunction) pywrc_string_table_resource_get_string_identifier,
	  METH_VARARGS | METH_KEYWORDS,
	  "get_string_identifier(string_index) -> Unicode string or None\n"
	  "\n"
	  "Retrieves a specific string identifier." },

	{ "get_string",
	  (PyCFunction) pywrc_string_table_resource_get_string,
	  METH_VARARGS | METH_KEYWORDS,
	  "get_string(string_index) -> Unicode string or None\n"
	  "\n"
	  "Retrieves a specific string." },

	{ "get_string_by_string_identifier",
	  (PyCFunction) pywrc_string_table_resource_get_string_by_string_identifier,
	  METH_VARARGS | METH_KEYWORDS,
	  "get_string_by_string_identifier(string_identifier) -> Unicode string or None\n"
	  "\n"
	  "Retrieves a specific string by identifier." },

	/* Sentinel */
	{ NULL, NULL, 0, NULL }
};

PyGetSetDef pywrc_string_table_resource_object_get_set_definitions[] = {

	{ "number_of_strings",
	  (getter) pywrc_string_table_resource_get_number_of_strings,
	  (setter) 0,
	  "The number of strings.",
	  NULL },

	/* Sentinel */
	{ NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pywrc_string_table_resource_type_object = {
	PyVarObject_HEAD_INIT( NULL, 0 )

	/* tp_name */
	"pywrc.string_table_resource",
	/* tp_basicsize */
	sizeof( pywrc_string_table_resource_t ),
	/* tp_itemsize */
	0,
	/* tp_dealloc */
	(destructor) pywrc_string_table_resource_free,
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
	"pywrc string table resource object (wraps libwrc_string_table_resource_t)",
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
	pywrc_string_table_resource_object_methods,
	/* tp_members */
	0,
	/* tp_getset */
	pywrc_string_table_resource_object_get_set_definitions,
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
	(initproc) pywrc_string_table_resource_init,
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

/* Initializes a string table resource object
 * Returns 0 if successful or -1 on error
 */
int pywrc_string_table_resource_init(
     pywrc_string_table_resource_t *pywrc_string_table_resource )
{
	libcerror_error_t *error = NULL;
	static char *function    = "pywrc_string_table_resource_init";

	if( pywrc_string_table_resource == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid string table resource.",
		 function );

		return( -1 );
	}
	/* Make sure libwrc string_table_resource is set to NULL
	 */
	pywrc_string_table_resource->string_table_resource = NULL;

	if( libwrc_string_table_resource_initialize(
	     &( pywrc_string_table_resource->string_table_resource ),
	     &error ) != 1 )
	{
		pywrc_error_raise(
		 error,
		 PyExc_MemoryError,
		 "%s: unable to initialize string table resource.",
		 function );

		libcerror_error_free(
		 &error );

		return( -1 );
	}
	return( 0 );
}

/* Frees a string table resource object
 */
void pywrc_string_table_resource_free(
      pywrc_string_table_resource_t *pywrc_string_table_resource )
{
	struct _typeobject *ob_type = NULL;
	libcerror_error_t *error    = NULL;
	static char *function       = "pywrc_string_table_resource_free";
	int result                  = 0;

	if( pywrc_string_table_resource == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid string table resource.",
		 function );

		return;
	}
	ob_type = Py_TYPE(
	           pywrc_string_table_resource );

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
	if( pywrc_string_table_resource->string_table_resource != NULL )
	{
		Py_BEGIN_ALLOW_THREADS

		result = libwrc_string_table_resource_free(
		          &( pywrc_string_table_resource->string_table_resource ),
		          &error );

		Py_END_ALLOW_THREADS

		if( result != 1 )
		{
			pywrc_error_raise(
			 error,
			 PyExc_MemoryError,
			 "%s: unable to free libwrc string table resource.",
			 function );

			libcerror_error_free(
			 &error );
		}
	}
	ob_type->tp_free(
	 (PyObject*) pywrc_string_table_resource );
}

/* Copies the string table resource from a byte stream
 * Returns a Python object if successful or NULL on error
 */
PyObject *pywrc_string_table_resource_copy_from_byte_stream(
           pywrc_string_table_resource_t *pywrc_string_table_resource,
           PyObject *arguments,
           PyObject *keywords )
{
	PyObject *bytes_object        = NULL;
	libcerror_error_t *error      = NULL;
	const char *byte_stream       = NULL;
	static char *function         = "pywrc_string_table_resource_copy_from_byte_stream";
	static char *keyword_list[]   = { "byte_stream", "base_identifier", NULL };
	unsigned long base_identifier = 0;
	Py_ssize_t byte_stream_size   = 0;
	int result                    = 0;

	if( pywrc_string_table_resource == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid string table resource.",
		 function );

		return( NULL );
	}
	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "Ok",
	     keyword_list,
	     &bytes_object,
	     &base_identifier ) == 0 )
	{
		return( NULL );
	}
	PyErr_Clear();

#if PY_MAJOR_VERSION >= 3
	result = PyObject_IsInstance(
	          bytes_object,
	          (PyObject *) &PyBytes_Type );
#else
	result = PyObject_IsInstance(
	          bytes_object,
	          (PyObject *) &PyString_Type );
#endif
	if( result == -1 )
	{
		pywrc_error_fetch_and_raise(
		 PyExc_RuntimeError,
		 "%s: unable to determine if object is of type bytes.",
		 function );

		return( NULL );
	}
	else if( result == 0 )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: unsupported bytes object type",
		 function );

		return( NULL );
	}
	PyErr_Clear();

#if PY_MAJOR_VERSION >= 3
	byte_stream = PyBytes_AsString(
	               bytes_object );

	byte_stream_size = PyBytes_Size(
	                    bytes_object );
#else
	byte_stream = PyString_AsString(
	               bytes_object );

	byte_stream_size = PyString_Size(
	                    bytes_object );
#endif
	if( ( byte_stream_size < 0 )
	 || ( byte_stream_size > (Py_ssize_t) SSIZE_MAX ) )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid byte stream size value out of bounds.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libwrc_string_table_resource_read(
	          pywrc_string_table_resource->string_table_resource,
	          (uint8_t *) byte_stream,
	          (size_t) byte_stream_size,
	          (uint32_t) base_identifier,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pywrc_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to copy string table resource from byte stream.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	Py_IncRef(
	 Py_None );

	return( Py_None );
}

/* Retrieves the number of strings
 * Returns a Python object if successful or NULL on error
 */
PyObject *pywrc_string_table_resource_get_number_of_strings(
           pywrc_string_table_resource_t *pywrc_string_table_resource,
           PyObject *arguments )
{
	PyObject *integer_object = NULL;
	libcerror_error_t *error = NULL;
	static char *function    = "pywrc_string_table_resource_get_number_of_strings";
	int number_of_strings    = 0;
	int result               = 0;

	PYWRC_UNREFERENCED_PARAMETER( arguments )

	if( pywrc_string_table_resource == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid string table resource.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libwrc_string_table_resource_get_number_of_strings(
	          pywrc_string_table_resource->string_table_resource,
	          &number_of_strings,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pywrc_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve number of strings.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
#if PY_MAJOR_VERSION >= 3
	integer_object = PyLong_FromLong(
	                  (long) number_of_strings );
#else
	integer_object = PyInt_FromLong(
	                  (long) number_of_strings );
#endif
	return( integer_object );
}

/* Retrieves the string identifier for a specific string index
 * Returns a Python object if successful or NULL on error
 */
PyObject *pywrc_string_table_resource_get_string_identifier(
           pywrc_string_table_resource_t *pywrc_string_table_resource,
           PyObject *arguments,
           PyObject *keywords )
{
	libcerror_error_t *error     = NULL;
	PyObject *integer_object     = NULL;
	static char *keyword_list[]  = { "string_index", NULL };
	static char *function        = "pywrc_string_table_resource_get_string_identifier";
	uint32_t string_identifier   = 0;
	int result                   = 0;
	int string_index             = 0;

	if( pywrc_string_table_resource == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid string table resource.",
		 function );

		return( NULL );
	}
	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "i",
	     keyword_list,
	     &string_index ) == 0 )
	{
		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libwrc_string_table_resource_get_identifier(
	          pywrc_string_table_resource->string_table_resource,
	          string_index,
	          &string_identifier,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pywrc_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve string identifier: %d.",
		 function,
		 string_index );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	integer_object = pywrc_integer_unsigned_new_from_64bit(
	                  (uint64_t) string_identifier );

	return( integer_object );
}

/* Retrieves a specific string
 * Returns a Python object if successful or NULL on error
 */
PyObject *pywrc_string_table_resource_get_string(
           pywrc_string_table_resource_t *pywrc_string_table_resource,
           PyObject *arguments,
           PyObject *keywords )
{
	PyObject *string_object     = NULL;
	libcerror_error_t *error    = NULL;
	uint8_t *string             = NULL;
	static char *function       = "pywrc_string_table_resource_get_string";
	static char *keyword_list[] = { "string_index", NULL };
	size_t string_size          = 0;
	int result                  = 0;
	int string_index            = 0;

	if( pywrc_string_table_resource == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid string table resource.",
		 function );

		return( NULL );
	}
	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "i",
	     keyword_list,
	     &string_index ) == 0 )
	{
		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libwrc_string_table_resource_get_utf8_string_size(
	          pywrc_string_table_resource->string_table_resource,
	          string_index,
	          &string_size,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pywrc_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve string: %d size.",
		 function,
		 string_index );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	string = (uint8_t *) PyMem_Malloc(
	                      sizeof( uint8_t ) * string_size );

	if( string == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create string.",
		 function );

		goto on_error;
	}
	Py_BEGIN_ALLOW_THREADS

	result = libwrc_string_table_resource_get_utf8_string(
		  pywrc_string_table_resource->string_table_resource,
		  string_index,
		  string,
		  string_size,
		  &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pywrc_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve string: %d.",
		 function,
		 string_index );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	/* Pass the string length to PyUnicode_DecodeUTF8
	 * otherwise it makes the end of string character is part
	 * of the string
	 */
	string_object = PyUnicode_DecodeUTF8(
			 (char *) string,
			 (Py_ssize_t) string_size - 1,
			 NULL );

	PyMem_Free(
	 string );

	return( string_object );

on_error:
	if( string != NULL )
	{
		PyMem_Free(
		 string );
	}
	return( NULL );
}

/* Retrieves the string for a specific string identifier
 * Returns a Python object if successful or NULL on error
 */
PyObject *pywrc_string_table_resource_get_string_by_string_identifier(
           pywrc_string_table_resource_t *pywrc_string_table_resource,
           PyObject *arguments,
           PyObject *keywords )
{
	PyObject *string_object     = NULL;
	libcerror_error_t *error    = NULL;
	uint8_t *string             = NULL;
	static char *function       = "pywrc_string_table_resource_get_string_by_string_identifier";
	static char *keyword_list[] = { "string_identifier", NULL };
	size_t string_size          = 0;
	uint32_t string_identifier  = 0;
	int result                  = 0;
	int string_index            = 0;

	if( pywrc_string_table_resource == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid string table resource.",
		 function );

		return( NULL );
	}
	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "k",
	     keyword_list,
	     &string_identifier ) == 0 )
	{
		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libwrc_string_table_resource_get_index_by_identifier(
	          pywrc_string_table_resource->string_table_resource,
	          string_identifier,
	          &string_index,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		pywrc_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve string index.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	else if( result == 0 )
	{
		Py_IncRef(
		 Py_None );

		return( Py_None );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libwrc_string_table_resource_get_utf8_string_size(
	          pywrc_string_table_resource->string_table_resource,
	          string_index,
	          &string_size,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pywrc_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve string: %d size.",
		 function,
		 string_index );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	string = (uint8_t *) PyMem_Malloc(
	                      sizeof( uint8_t ) * string_size );

	if( string == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create string.",
		 function );

		goto on_error;
	}
	Py_BEGIN_ALLOW_THREADS

	result = libwrc_string_table_resource_get_utf8_string(
		  pywrc_string_table_resource->string_table_resource,
		  string_index,
		  string,
		  string_size,
		  &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pywrc_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve string: %d.",
		 function,
		 string_index );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	/* Pass the string length to PyUnicode_DecodeUTF8
	 * otherwise it makes the end of string character is part
	 * of the string
	 */
	string_object = PyUnicode_DecodeUTF8(
			 (char *) string,
			 (Py_ssize_t) string_size - 1,
			 NULL );

	PyMem_Free(
	 string );

	return( string_object );

on_error:
	if( string != NULL )
	{
		PyMem_Free(
		 string );
	}
	return( NULL );
}

