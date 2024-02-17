/*
 * Python object definition of the libwrc MUI resource
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
#include "pywrc_mui_resource.h"
#include "pywrc_python.h"
#include "pywrc_unused.h"

PyMethodDef pywrc_mui_resource_object_methods[] = {

	/* Functions to access the MUI resource values */

	{ "copy_from_byte_stream",
	  (PyCFunction) pywrc_mui_resource_copy_from_byte_stream,
	  METH_VARARGS | METH_KEYWORDS,
	  "copy_from_byte_stream(byte_stream)\n"
	  "\n"
	  "Copies the MUI resource from the byte stream." },

	{ "get_file_type",
	  (PyCFunction) pywrc_mui_resource_get_file_type,
	  METH_NOARGS,
	  "get_file_type() -> Integer or None\n"
	  "\n"
	  "Retrieves the file type." },

	{ "get_main_name",
	  (PyCFunction) pywrc_mui_resource_get_main_name,
	  METH_NOARGS,
	  "get_main_name() -> Unicode string or None\n"
	  "\n"
	  "Retrieves the main name." },

	{ "get_mui_name",
	  (PyCFunction) pywrc_mui_resource_get_mui_name,
	  METH_NOARGS,
	  "get_mui_name() -> Unicode string or None\n"
	  "\n"
	  "Retrieves the MUI name." },

	{ "get_language",
	  (PyCFunction) pywrc_mui_resource_get_language,
	  METH_NOARGS,
	  "get_language() -> Unicode string or None\n"
	  "\n"
	  "Retrieves the language." },

	{ "get_fallback_language",
	  (PyCFunction) pywrc_mui_resource_get_fallback_language,
	  METH_NOARGS,
	  "get_fallback_language() -> Unicode string or None\n"
	  "\n"
	  "Retrieves the fallback language." },

	/* Sentinel */
	{ NULL, NULL, 0, NULL }
};

PyGetSetDef pywrc_mui_resource_object_get_set_definitions[] = {

	{ "main_name",
	  (getter) pywrc_mui_resource_get_main_name,
	  (setter) 0,
	  "The main name.",
	  NULL },

	{ "mui_name",
	  (getter) pywrc_mui_resource_get_mui_name,
	  (setter) 0,
	  "The MUI name.",
	  NULL },

	{ "language",
	  (getter) pywrc_mui_resource_get_language,
	  (setter) 0,
	  "The language.",
	  NULL },

	{ "fallback_language",
	  (getter) pywrc_mui_resource_get_fallback_language,
	  (setter) 0,
	  "The fallback language.",
	  NULL },

	/* Sentinel */
	{ NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pywrc_mui_resource_type_object = {
	PyVarObject_HEAD_INIT( NULL, 0 )

	/* tp_name */
	"pywrc.mui_resource",
	/* tp_basicsize */
	sizeof( pywrc_mui_resource_t ),
	/* tp_itemsize */
	0,
	/* tp_dealloc */
	(destructor) pywrc_mui_resource_free,
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
	"pywrc mui resource object (wraps libwrc_mui_resource_t)",
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
	pywrc_mui_resource_object_methods,
	/* tp_members */
	0,
	/* tp_getset */
	pywrc_mui_resource_object_get_set_definitions,
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
	(initproc) pywrc_mui_resource_init,
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

/* Initializes a MUI resource object
 * Returns 0 if successful or -1 on error
 */
int pywrc_mui_resource_init(
     pywrc_mui_resource_t *pywrc_mui_resource )
{
	libcerror_error_t *error = NULL;
	static char *function    = "pywrc_mui_resource_init";

	if( pywrc_mui_resource == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid MUI resource.",
		 function );

		return( -1 );
	}
	/* Make sure libwrc mui_resource is set to NULL
	 */
	pywrc_mui_resource->mui_resource = NULL;

	if( libwrc_mui_resource_initialize(
	     &( pywrc_mui_resource->mui_resource ),
	     &error ) != 1 )
	{
		pywrc_error_raise(
		 error,
		 PyExc_MemoryError,
		 "%s: unable to initialize MUI resource.",
		 function );

		libcerror_error_free(
		 &error );

		return( -1 );
	}
	return( 0 );
}

/* Frees a MUI resource object
 */
void pywrc_mui_resource_free(
      pywrc_mui_resource_t *pywrc_mui_resource )
{
	struct _typeobject *ob_type = NULL;
	libcerror_error_t *error    = NULL;
	static char *function       = "pywrc_mui_resource_free";
	int result                  = 0;

	if( pywrc_mui_resource == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid MUI resource.",
		 function );

		return;
	}
	ob_type = Py_TYPE(
	           pywrc_mui_resource );

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
	if( pywrc_mui_resource->mui_resource != NULL )
	{
		Py_BEGIN_ALLOW_THREADS

		result = libwrc_mui_resource_free(
		          &( pywrc_mui_resource->mui_resource ),
		          &error );

		Py_END_ALLOW_THREADS

		if( result != 1 )
		{
			pywrc_error_raise(
			 error,
			 PyExc_MemoryError,
			 "%s: unable to free libwrc MUI resource.",
			 function );

			libcerror_error_free(
			 &error );
		}
	}
	ob_type->tp_free(
	 (PyObject*) pywrc_mui_resource );
}

/* Copies the MUI resource from a byte stream
 * Returns a Python object if successful or NULL on error
 */
PyObject *pywrc_mui_resource_copy_from_byte_stream(
           pywrc_mui_resource_t *pywrc_mui_resource,
           PyObject *arguments,
           PyObject *keywords )
{
	PyObject *bytes_object      = NULL;
	libcerror_error_t *error    = NULL;
	const char *byte_stream     = NULL;
	static char *function       = "pywrc_mui_resource_copy_from_byte_stream";
	static char *keyword_list[] = { "byte_stream", NULL };
	Py_ssize_t byte_stream_size = 0;
	int result                  = 0;

	if( pywrc_mui_resource == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid MUI resource.",
		 function );

		return( NULL );
	}
	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "O",
	     keyword_list,
	     &bytes_object ) == 0 )
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

	result = libwrc_mui_resource_read(
	          pywrc_mui_resource->mui_resource,
	          (uint8_t *) byte_stream,
	          (size_t) byte_stream_size,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pywrc_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to copy MUI resource from byte stream.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	Py_IncRef(
	 Py_None );

	return( Py_None );
}

/* Retrieves the file type
 * Returns a Python object if successful or NULL on error
 */
PyObject *pywrc_mui_resource_get_file_type(
           pywrc_mui_resource_t *pywrc_mui_resource,
           PyObject *arguments )
{
	PyObject *integer_object = NULL;
	libcerror_error_t *error = NULL;
	static char *function    = "pywrc_mui_resource_get_file_type";
	uint32_t file_type       = 0;
	int result               = 0;

	PYWRC_UNREFERENCED_PARAMETER( arguments )

	if( pywrc_mui_resource == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid MUI resource.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libwrc_mui_resource_get_file_type(
	          pywrc_mui_resource->mui_resource,
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

/* Retrieves the main name
 * Returns a Python object if successful or NULL on error
 */
PyObject *pywrc_mui_resource_get_main_name(
           pywrc_mui_resource_t *pywrc_mui_resource,
           PyObject *arguments )
{
	PyObject *string_object  = NULL;
	libcerror_error_t *error = NULL;
	uint8_t *main_name       = NULL;
	static char *function    = "pywrc_mui_resource_get_main_name";
	size_t main_name_size    = 0;
	int result               = 0;

	PYWRC_UNREFERENCED_PARAMETER( arguments )

	if( pywrc_mui_resource == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid MUI resource.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libwrc_mui_resource_get_utf8_main_name_size(
	          pywrc_mui_resource->mui_resource,
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
		 PyExc_MemoryError,
		 "%s: unable to create main name.",
		 function );

		goto on_error;
	}
	Py_BEGIN_ALLOW_THREADS

	result = libwrc_mui_resource_get_utf8_main_name(
		  pywrc_mui_resource->mui_resource,
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
			 NULL );

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

/* Retrieves the MUI name
 * Returns a Python object if successful or NULL on error
 */
PyObject *pywrc_mui_resource_get_mui_name(
           pywrc_mui_resource_t *pywrc_mui_resource,
           PyObject *arguments )
{
	PyObject *string_object  = NULL;
	libcerror_error_t *error = NULL;
	uint8_t *mui_name        = NULL;
	static char *function    = "pywrc_mui_resource_get_mui_name";
	size_t mui_name_size     = 0;
	int result               = 0;

	PYWRC_UNREFERENCED_PARAMETER( arguments )

	if( pywrc_mui_resource == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid MUI resource.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libwrc_mui_resource_get_utf8_mui_name_size(
	          pywrc_mui_resource->mui_resource,
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
		 PyExc_MemoryError,
		 "%s: unable to create MUI name.",
		 function );

		goto on_error;
	}
	Py_BEGIN_ALLOW_THREADS

	result = libwrc_mui_resource_get_utf8_mui_name(
		  pywrc_mui_resource->mui_resource,
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
			 NULL );

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

/* Retrieves the language
 * Returns a Python object if successful or NULL on error
 */
PyObject *pywrc_mui_resource_get_language(
           pywrc_mui_resource_t *pywrc_mui_resource,
           PyObject *arguments )
{
	PyObject *string_object  = NULL;
	libcerror_error_t *error = NULL;
	uint8_t *language        = NULL;
	static char *function    = "pywrc_mui_resource_get_language";
	size_t language_size     = 0;
	int result               = 0;

	PYWRC_UNREFERENCED_PARAMETER( arguments )

	if( pywrc_mui_resource == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid MUI resource.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libwrc_mui_resource_get_utf8_language_size(
	          pywrc_mui_resource->mui_resource,
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
		 PyExc_MemoryError,
		 "%s: unable to create language.",
		 function );

		goto on_error;
	}
	Py_BEGIN_ALLOW_THREADS

	result = libwrc_mui_resource_get_utf8_language(
		  pywrc_mui_resource->mui_resource,
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
			 NULL );

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

/* Retrieves the fallback language
 * Returns a Python object if successful or NULL on error
 */
PyObject *pywrc_mui_resource_get_fallback_language(
           pywrc_mui_resource_t *pywrc_mui_resource,
           PyObject *arguments )
{
	PyObject *string_object       = NULL;
	libcerror_error_t *error      = NULL;
	uint8_t *fallback_language    = NULL;
	static char *function         = "pywrc_mui_resource_get_fallback_language";
	size_t fallback_language_size = 0;
	int result                    = 0;

	PYWRC_UNREFERENCED_PARAMETER( arguments )

	if( pywrc_mui_resource == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid MUI resource.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libwrc_mui_resource_get_utf8_fallback_language_size(
	          pywrc_mui_resource->mui_resource,
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
		 PyExc_MemoryError,
		 "%s: unable to create fallback language.",
		 function );

		goto on_error;
	}
	Py_BEGIN_ALLOW_THREADS

	result = libwrc_mui_resource_get_utf8_fallback_language(
		  pywrc_mui_resource->mui_resource,
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
			 NULL );

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

