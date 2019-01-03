/*
 * Python object definition of the libwrc MUI resource
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
#include "pywrc_mui.h"
#include "pywrc_python.h"
#include "pywrc_resource.h"
#include "pywrc_unused.h"

PyMethodDef pywrc_mui_object_methods[] = {

	/* Functions to access the mui resource values */

	{ "get_file_type",
	  (PyCFunction) pywrc_mui_get_file_type,
	  METH_VARARGS | METH_KEYWORDS,
	  "get_file_type(language_identifier) -> Integer or None\n"
	  "\n"
	  "Retrieves the file type." },

	{ "get_main_name",
	  (PyCFunction) pywrc_mui_get_main_name,
	  METH_VARARGS | METH_KEYWORDS,
	  "get_main_name(language_identifier) -> Unicode string or None\n"
	  "\n"
	  "Retrieves the main name." },

	{ "get_mui_name",
	  (PyCFunction) pywrc_mui_get_mui_name,
	  METH_VARARGS | METH_KEYWORDS,
	  "get_mui_name(language_identifier) -> Unicode string or None\n"
	  "\n"
	  "Retrieves the MUI name." },

	{ "get_language",
	  (PyCFunction) pywrc_mui_get_language,
	  METH_VARARGS | METH_KEYWORDS,
	  "get_language(language_identifier) -> Unicode string or None\n"
	  "\n"
	  "Retrieves the language." },

	{ "get_fallback_language",
	  (PyCFunction) pywrc_mui_get_fallback_language,
	  METH_VARARGS | METH_KEYWORDS,
	  "get_fallback_language(language_identifier) -> Unicode string or None\n"
	  "\n"
	  "Retrieves the fallback language." },

	/* Sentinel */
	{ NULL, NULL, 0, NULL }
};

PyGetSetDef pywrc_mui_object_get_set_definitions[] = {

	/* Sentinel */
	{ NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pywrc_mui_type_object = {
	PyVarObject_HEAD_INIT( NULL, 0 )

	/* tp_name */
	"pywrc.mui",
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
	"pywrc mui object (wraps libwrc_resource_t type: LIBWRC_RESOURCE_TYPE_MUI)",
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
	pywrc_mui_object_methods,
	/* tp_members */
	0,
	/* tp_getset */
	pywrc_mui_object_get_set_definitions,
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

/* Retrieves the file type for a specific language identifier
 * Returns a Python object if successful or NULL on error
 */
PyObject *pywrc_mui_get_file_type(
           pywrc_resource_t *pywrc_resource,
           PyObject *arguments,
           PyObject *keywords )
{
	libcerror_error_t *error     = NULL;
	PyObject *integer_object     = NULL;
	static char *keyword_list[]  = { "language_identifier", NULL };
	static char *function        = "pywrc_mui_get_file_type";
	uint32_t file_type           = 0;
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

	result = libwrc_mui_get_file_type(
	          pywrc_resource->resource,
	          language_identifier,
	          &file_type,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pywrc_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve file type.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	integer_object = pywrc_integer_unsigned_new_from_64bit(
	                  (uint32_t) file_type );

	return( integer_object );
}

/* Retrieves the main name for a specific language identifier
 * Returns a Python object if successful or NULL on error
 */
PyObject *pywrc_mui_get_main_name(
           pywrc_resource_t *pywrc_resource,
           PyObject *arguments,
           PyObject *keywords )
{
	libcerror_error_t *error     = NULL;
	PyObject *string_object      = NULL;
	static char *keyword_list[]  = { "language_identifier", NULL };
	const char *errors           = NULL;
	uint8_t *main_name           = NULL;
	static char *function        = "pywrc_mui_get_main_name";
	size_t main_name_size        = 0;
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

	result = libwrc_mui_get_utf8_main_name_size(
	          pywrc_resource->resource,
	          language_identifier,
	          &main_name_size,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		pywrc_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve main name size.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	else if( ( result == 0 )
	      || ( main_name_size == 0 ) )
	{
		Py_IncRef(
		 Py_None );

		return( Py_None );
	}
	main_name = (uint8_t *) PyMem_Malloc(
	                         sizeof( uint8_t ) * main_name_size );

	if( main_name == NULL )
	{
		PyErr_Format(
		 PyExc_IOError,
		 "%s: unable to create main name.",
		 function );

		goto on_error;
	}
	Py_BEGIN_ALLOW_THREADS

	result = libwrc_mui_get_utf8_main_name(
		  pywrc_resource->resource,
	          language_identifier,
		  main_name,
		  main_name_size,
		  &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pywrc_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve main name.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	/* Pass the string length to PyUnicode_DecodeUTF8
	 * otherwise it makes the end of string character is part
	 * of the string
	 */
	string_object = PyUnicode_DecodeUTF8(
			 (char *) main_name,
			 (Py_ssize_t) main_name_size - 1,
			 errors );

	PyMem_Free(
	 main_name );

	return( string_object );

on_error:
	if( main_name != NULL )
	{
		PyMem_Free(
		 main_name );
	}
	return( NULL );
}

/* Retrieves the MUI name for a specific language identifier
 * Returns a Python object if successful or NULL on error
 */
PyObject *pywrc_mui_get_mui_name(
           pywrc_resource_t *pywrc_resource,
           PyObject *arguments,
           PyObject *keywords )
{
	libcerror_error_t *error     = NULL;
	PyObject *string_object      = NULL;
	static char *keyword_list[]  = { "language_identifier", NULL };
	const char *errors           = NULL;
	uint8_t *mui_name            = NULL;
	static char *function        = "pywrc_mui_get_mui_name";
	size_t mui_name_size         = 0;
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

	result = libwrc_mui_get_utf8_mui_name_size(
	          pywrc_resource->resource,
	          language_identifier,
	          &mui_name_size,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		pywrc_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve MUI name size.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	else if( ( result == 0 )
	      || ( mui_name_size == 0 ) )
	{
		Py_IncRef(
		 Py_None );

		return( Py_None );
	}
	mui_name = (uint8_t *) PyMem_Malloc(
	                        sizeof( uint8_t ) * mui_name_size );

	if( mui_name == NULL )
	{
		PyErr_Format(
		 PyExc_IOError,
		 "%s: unable to create MUI name.",
		 function );

		goto on_error;
	}
	Py_BEGIN_ALLOW_THREADS

	result = libwrc_mui_get_utf8_mui_name(
		  pywrc_resource->resource,
	          language_identifier,
		  mui_name,
		  mui_name_size,
		  &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pywrc_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve MUI name.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	/* Pass the string length to PyUnicode_DecodeUTF8
	 * otherwise it makes the end of string character is part
	 * of the string
	 */
	string_object = PyUnicode_DecodeUTF8(
			 (char *) mui_name,
			 (Py_ssize_t) mui_name_size - 1,
			 errors );

	PyMem_Free(
	 mui_name );

	return( string_object );

on_error:
	if( mui_name != NULL )
	{
		PyMem_Free(
		 mui_name );
	}
	return( NULL );
}

/* Retrieves the language for a specific language identifier
 * Returns a Python object if successful or NULL on error
 */
PyObject *pywrc_mui_get_language(
           pywrc_resource_t *pywrc_resource,
           PyObject *arguments,
           PyObject *keywords )
{
	libcerror_error_t *error     = NULL;
	PyObject *string_object      = NULL;
	static char *keyword_list[]  = { "language_identifier", NULL };
	const char *errors           = NULL;
	uint8_t *language            = NULL;
	static char *function        = "pywrc_mui_get_language";
	size_t language_size         = 0;
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

	result = libwrc_mui_get_utf8_language_size(
	          pywrc_resource->resource,
	          language_identifier,
	          &language_size,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		pywrc_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve language size.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	else if( ( result == 0 )
	      || ( language_size == 0 ) )
	{
		Py_IncRef(
		 Py_None );

		return( Py_None );
	}
	language = (uint8_t *) PyMem_Malloc(
	                        sizeof( uint8_t ) * language_size );

	if( language == NULL )
	{
		PyErr_Format(
		 PyExc_IOError,
		 "%s: unable to create language.",
		 function );

		goto on_error;
	}
	Py_BEGIN_ALLOW_THREADS

	result = libwrc_mui_get_utf8_language(
		  pywrc_resource->resource,
	          language_identifier,
		  language,
		  language_size,
		  &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pywrc_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve language.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	/* Pass the string length to PyUnicode_DecodeUTF8
	 * otherwise it makes the end of string character is part
	 * of the string
	 */
	string_object = PyUnicode_DecodeUTF8(
			 (char *) language,
			 (Py_ssize_t) language_size - 1,
			 errors );

	PyMem_Free(
	 language );

	return( string_object );

on_error:
	if( language != NULL )
	{
		PyMem_Free(
		 language );
	}
	return( NULL );
}

/* Retrieves the fallback language for a specific language identifier
 * Returns a Python object if successful or NULL on error
 */
PyObject *pywrc_mui_get_fallback_language(
           pywrc_resource_t *pywrc_resource,
           PyObject *arguments,
           PyObject *keywords )
{
	libcerror_error_t *error      = NULL;
	PyObject *string_object       = NULL;
	static char *keyword_list[]   = { "language_identifier", NULL };
	const char *errors            = NULL;
	uint8_t *fallback_language    = NULL;
	static char *function         = "pywrc_mui_get_fallback_language";
	size_t fallback_language_size = 0;
	uint32_t language_identifier  = 0;
	int result                    = 0;

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

	result = libwrc_mui_get_utf8_fallback_language_size(
	          pywrc_resource->resource,
	          language_identifier,
	          &fallback_language_size,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		pywrc_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve fallback language size.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	else if( ( result == 0 )
	      || ( fallback_language_size == 0 ) )
	{
		Py_IncRef(
		 Py_None );

		return( Py_None );
	}
	fallback_language = (uint8_t *) PyMem_Malloc(
	                                 sizeof( uint8_t ) * fallback_language_size );

	if( fallback_language == NULL )
	{
		PyErr_Format(
		 PyExc_IOError,
		 "%s: unable to create fallback language.",
		 function );

		goto on_error;
	}
	Py_BEGIN_ALLOW_THREADS

	result = libwrc_mui_get_utf8_fallback_language(
		  pywrc_resource->resource,
	          language_identifier,
		  fallback_language,
		  fallback_language_size,
		  &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pywrc_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve fallback language.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	/* Pass the string length to PyUnicode_DecodeUTF8
	 * otherwise it makes the end of string character is part
	 * of the string
	 */
	string_object = PyUnicode_DecodeUTF8(
			 (char *) fallback_language,
			 (Py_ssize_t) fallback_language_size - 1,
			 errors );

	PyMem_Free(
	 fallback_language );

	return( string_object );

on_error:
	if( fallback_language != NULL )
	{
		PyMem_Free(
		 fallback_language );
	}
	return( NULL );
}

