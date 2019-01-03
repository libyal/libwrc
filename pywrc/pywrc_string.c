/*
 * Python object definition of the libwrc string resource
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

#include "pywrc_error.h"
#include "pywrc_integer.h"
#include "pywrc_libcerror.h"
#include "pywrc_libwrc.h"
#include "pywrc_python.h"
#include "pywrc_resource.h"
#include "pywrc_string.h"
#include "pywrc_unused.h"

PyMethodDef pywrc_string_object_methods[] = {

	/* Functions to access the string resource values */

	{ "get_number_of_strings",
	  (PyCFunction) pywrc_string_get_number_of_strings,
	  METH_VARARGS | METH_KEYWORDS,
	  "get_number_of_strings(language_identifier) -> Integer\n"
	  "\n"
	  "Retrieves the number of strings." },

	{ "get_string_identifier",
	  (PyCFunction) pywrc_string_get_string_identifier,
	  METH_VARARGS | METH_KEYWORDS,
	  "get_string_identifier(language_identifier, string_index) -> Unicode string or None\n"
	  "\n"
	  "Retrieves a specific string identifier." },

	{ "get_string",
	  (PyCFunction) pywrc_string_get_string,
	  METH_VARARGS | METH_KEYWORDS,
	  "get_string(language_identifier, string_index) -> Unicode string or None\n"
	  "\n"
	  "Retrieves a specific string." },

	{ "get_string_by_string_identifier",
	  (PyCFunction) pywrc_string_get_string_by_string_identifier,
	  METH_VARARGS | METH_KEYWORDS,
	  "get_string_by_string_identifier(language_identifier, string_identifier) -> Unicode string or None\n"
	  "\n"
	  "Retrieves a specific string by identifier." },

	/* Sentinel */
	{ NULL, NULL, 0, NULL }
};

PyGetSetDef pywrc_string_object_get_set_definitions[] = {

	/* Sentinel */
	{ NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pywrc_string_type_object = {
	PyVarObject_HEAD_INIT( NULL, 0 )

	/* tp_name */
	"pywrc.string",
	/* tp_basicsize */
	sizeof( pywrc_resource_t ),
	/* tp_itemsize */
	0,
	/* tp_dealloc */
	0,
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
	"pywrc string object (wraps libwrc_resource_t type: LIBWRC_RESOURCE_TYPE_STRING)",
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
	pywrc_string_object_methods,
	/* tp_members */
	0,
	/* tp_getset */
	pywrc_string_object_get_set_definitions,
	/* tp_base */
	&pywrc_resource_type_object,
	/* tp_dict */
	0,
	/* tp_descr_get */
	0,
	/* tp_descr_set */
	0,
	/* tp_dictoffset */
	0,
	/* tp_init */
	0,
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

/* Retrieves the number of strings
 * Returns a Python object if successful or NULL on error
 */
PyObject *pywrc_string_get_number_of_strings(
           pywrc_resource_t *pywrc_resource,
           PyObject *arguments,
           PyObject *keywords )
{
	libcerror_error_t *error     = NULL;
	PyObject *integer_object     = NULL;
	static char *keyword_list[]  = { "language_identifier", NULL };
	static char *function        = "pywrc_string_get_number_of_strings";
	uint32_t language_identifier = 0;
	int number_of_strings        = 0;
	int result                   = 0;

	if( pywrc_resource == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid resource.",
		 function );

		return( NULL );
	}
	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "k",
	     keyword_list,
	     &language_identifier ) == 0 )
	{
		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libwrc_string_get_number_of_strings(
	          pywrc_resource->resource,
	          language_identifier,
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

/* Retrieves the string identifier for a specific language identifier and string index
 * Returns a Python object if successful or NULL on error
 */
PyObject *pywrc_string_get_string_identifier(
           pywrc_resource_t *pywrc_resource,
           PyObject *arguments,
           PyObject *keywords )
{
	libcerror_error_t *error     = NULL;
	PyObject *integer_object     = NULL;
	static char *keyword_list[]  = { "language_identifier", "string_index", NULL };
	static char *function        = "pywrc_string_get_string_identifier";
	uint32_t language_identifier = 0;
	uint32_t string_identifier   = 0;
	int result                   = 0;
	int string_index             = 0;

	if( pywrc_resource == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid resource.",
		 function );

		return( NULL );
	}
	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "ki",
	     keyword_list,
	     &language_identifier,
	     &string_index ) == 0 )
	{
		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libwrc_string_get_identifier(
	          pywrc_resource->resource,
	          language_identifier,
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

/* Retrieves the string for a specific language identifier and string index
 * Returns a Python object if successful or NULL on error
 */
PyObject *pywrc_string_get_string(
           pywrc_resource_t *pywrc_resource,
           PyObject *arguments,
           PyObject *keywords )
{
	libcerror_error_t *error     = NULL;
	PyObject *string_object      = NULL;
	uint8_t *string              = NULL;
	static char *keyword_list[]  = { "language_identifier", "string_index", NULL };
	const char *errors           = NULL;
	static char *function        = "pywrc_string_get_string";
	size_t string_size           = 0;
	uint32_t language_identifier = 0;
	int result                   = 0;
	int string_index             = 0;

	if( pywrc_resource == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid resource.",
		 function );

		return( NULL );
	}
	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "ki",
	     keyword_list,
	     &language_identifier,
	     &string_index ) == 0 )
	{
		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libwrc_string_get_utf8_string_size(
	          pywrc_resource->resource,
	          language_identifier,
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
		 PyExc_IOError,
		 "%s: unable to create string.",
		 function );

		goto on_error;
	}
	Py_BEGIN_ALLOW_THREADS

	result = libwrc_string_get_utf8_string(
		  pywrc_resource->resource,
	          language_identifier,
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
			 errors );

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

/* Retrieves the string for a specific language identifier and string identifier
 * Returns a Python object if successful or NULL on error
 */
PyObject *pywrc_string_get_string_by_string_identifier(
           pywrc_resource_t *pywrc_resource,
           PyObject *arguments,
           PyObject *keywords )
{
	libcerror_error_t *error     = NULL;
	PyObject *string_object      = NULL;
	uint8_t *string              = NULL;
	static char *keyword_list[]  = { "language_identifier", "string_identifier", NULL };
	const char *errors           = NULL;
	static char *function        = "pywrc_string_get_string_by_string_identifier";
	size_t string_size           = 0;
	uint32_t language_identifier = 0;
	uint32_t string_identifier   = 0;
	int result                   = 0;
	int string_index             = 0;

	if( pywrc_resource == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid resource.",
		 function );

		return( NULL );
	}
	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "kk",
	     keyword_list,
	     &language_identifier,
	     &string_identifier ) == 0 )
	{
		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libwrc_string_get_index_by_identifier(
	          pywrc_resource->resource,
	          language_identifier,
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

	result = libwrc_string_get_utf8_string_size(
	          pywrc_resource->resource,
	          language_identifier,
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
		 PyExc_IOError,
		 "%s: unable to create string.",
		 function );

		goto on_error;
	}
	Py_BEGIN_ALLOW_THREADS

	result = libwrc_string_get_utf8_string(
		  pywrc_resource->resource,
	          language_identifier,
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
			 errors );

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

