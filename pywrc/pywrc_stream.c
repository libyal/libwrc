/*
 * Python object wrapper of libwrc_stream_t
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
#include <narrow_string.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( HAVE_WINAPI )
#include <stdlib.h>
#endif

#include "pywrc_codepage.h"
#include "pywrc_error.h"
#include "pywrc_file_object_io_handle.h"
#include "pywrc_integer.h"
#include "pywrc_libbfio.h"
#include "pywrc_libcerror.h"
#include "pywrc_libclocale.h"
#include "pywrc_libwrc.h"
#include "pywrc_python.h"
#include "pywrc_resource.h"
#include "pywrc_resources.h"
#include "pywrc_stream.h"
#include "pywrc_unused.h"

#if !defined( LIBWRC_HAVE_BFIO )

LIBWRC_EXTERN \
int libwrc_stream_open_file_io_handle(
     libwrc_stream_t *stream,
     libbfio_handle_t *file_io_handle,
     int access_flags,
     libwrc_error_t **error );

#endif /* !defined( LIBWRC_HAVE_BFIO ) */

PyMethodDef pywrc_stream_object_methods[] = {

	{ "signal_abort",
	  (PyCFunction) pywrc_stream_signal_abort,
	  METH_NOARGS,
	  "signal_abort() -> None\n"
	  "\n"
	  "Signals the stream to abort the current activity." },

	/* Functions to access the stream */

	{ "open",
	  (PyCFunction) pywrc_stream_open,
	  METH_VARARGS | METH_KEYWORDS,
	  "open(filename, mode='r') -> None\n"
	  "\n"
	  "Opens a stream." },

	{ "open_file_object",
	  (PyCFunction) pywrc_stream_open_file_object,
	  METH_VARARGS | METH_KEYWORDS,
	  "open_file_object(file_object, mode='r') -> None\n"
	  "\n"
	  "Opens a stream using a file-like object." },

	{ "close",
	  (PyCFunction) pywrc_stream_close,
	  METH_NOARGS,
	  "close() -> None\n"
	  "\n"
	  "Closes a stream." },

	{ "get_ascii_codepage",
	  (PyCFunction) pywrc_stream_get_ascii_codepage,
	  METH_NOARGS,
	  "get_ascii_codepage() -> String\n"
	  "\n"
	  "Returns the codepage used for ASCII strings in the stream." },

	{ "set_ascii_codepage",
	  (PyCFunction) pywrc_stream_set_ascii_codepage,
	  METH_VARARGS | METH_KEYWORDS,
	  "set_ascii_codepage(codepage) -> None\n"
	  "\n"
	  "Set the codepage used for ASCII strings in the stream.\n"
	  "Expects the codepage to be a String containing a Python codec definition." },

	{ "get_virtual_address",
	  (PyCFunction) pywrc_stream_get_virtual_address,
	  METH_NOARGS,
	  "get_virtual_address() -> Integer\n"
	  "\n"
	  "Returns the virtual address of the stream." },

	{ "set_virtual_address",
	  (PyCFunction) pywrc_stream_set_virtual_address,
	  METH_VARARGS | METH_KEYWORDS,
	  "set_virtual_address(virtual_address) -> None\n"
	  "\n"
	  "Set the virtual address of the stream." },

	/* Functions to access the resources */

	{ "get_number_of_resources",
	  (PyCFunction) pywrc_stream_get_number_of_resources,
	  METH_NOARGS,
	  "get_number_of_resources() -> Integer\n"
	  "\n"
	  "Retrieves the number of resources." },

	{ "get_resource",
	  (PyCFunction) pywrc_stream_get_resource,
	  METH_VARARGS | METH_KEYWORDS,
	  "get_resource(resource_index) -> Object or None\n"
	  "\n"
	  "Retrieves a specific resource." },

	{ "get_resource_by_identifier",
	  (PyCFunction) pywrc_stream_get_resource_by_identifier,
	  METH_VARARGS | METH_KEYWORDS,
	  "get_resource_by_identifier(resource_identifier) -> Object or None\n"
	  "\n"
	  "Retrieves a specific resource by identifier." },

	{ "get_resource_by_name",
	  (PyCFunction) pywrc_stream_get_resource_by_name,
	  METH_VARARGS | METH_KEYWORDS,
	  "get_resource_by_name(resource_name) -> Object or None\n"
	  "\n"
	  "Retrieves a specific resource by name." },

	/* Sentinel */
	{ NULL, NULL, 0, NULL }
};

PyGetSetDef pywrc_stream_object_get_set_definitions[] = {

	{ "ascii_codepage",
	  (getter) pywrc_stream_get_ascii_codepage,
	  (setter) pywrc_stream_set_ascii_codepage_setter,
	  "The codepage used for ASCII strings in the stream.",
	  NULL },

	{ "number_of_resources",
	  (getter) pywrc_stream_get_number_of_resources,
	  (setter) 0,
	  "The number of resources.",
	  NULL },

	{ "resources",
	  (getter) pywrc_stream_get_resources,
	  (setter) 0,
	  "The resources",
	  NULL },

	/* Sentinel */
	{ NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pywrc_stream_type_object = {
	PyVarObject_HEAD_INIT( NULL, 0 )

	/* tp_name */
	"pywrc.stream",
	/* tp_basicsize */
	sizeof( pywrc_stream_t ),
	/* tp_itemsize */
	0,
	/* tp_dealloc */
	(destructor) pywrc_stream_free,
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
	"pywrc stream object (wraps libwrc_stream_t)",
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
	pywrc_stream_object_methods,
	/* tp_members */
	0,
	/* tp_getset */
	pywrc_stream_object_get_set_definitions,
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
	(initproc) pywrc_stream_init,
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

/* Initializes a stream object
 * Returns 0 if successful or -1 on error
 */
int pywrc_stream_init(
     pywrc_stream_t *pywrc_stream )
{
	libcerror_error_t *error = NULL;
	static char *function    = "pywrc_stream_init";

	if( pywrc_stream == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid stream.",
		 function );

		return( -1 );
	}
	/* Make sure libwrc stream is set to NULL
	 */
	pywrc_stream->stream         = NULL;
	pywrc_stream->file_io_handle = NULL;

	if( libwrc_stream_initialize(
	     &( pywrc_stream->stream ),
	     &error ) != 1 )
	{
		pywrc_error_raise(
		 error,
		 PyExc_MemoryError,
		 "%s: unable to initialize stream.",
		 function );

		libcerror_error_free(
		 &error );

		return( -1 );
	}
	return( 0 );
}

/* Frees a stream object
 */
void pywrc_stream_free(
      pywrc_stream_t *pywrc_stream )
{
	struct _typeobject *ob_type = NULL;
	libcerror_error_t *error    = NULL;
	static char *function       = "pywrc_stream_free";
	int result                  = 0;

	if( pywrc_stream == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid stream.",
		 function );

		return;
	}
	ob_type = Py_TYPE(
	           pywrc_stream );

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
	if( pywrc_stream->file_io_handle != NULL )
	{
		if( pywrc_stream_close(
		     pywrc_stream,
		     NULL ) == NULL )
		{
			return;
		}
	}
	if( pywrc_stream->stream != NULL )
	{
		Py_BEGIN_ALLOW_THREADS

		result = libwrc_stream_free(
		          &( pywrc_stream->stream ),
		          &error );

		Py_END_ALLOW_THREADS

		if( result != 1 )
		{
			pywrc_error_raise(
			 error,
			 PyExc_MemoryError,
			 "%s: unable to free libwrc stream.",
			 function );

			libcerror_error_free(
			 &error );
		}
	}
	ob_type->tp_free(
	 (PyObject*) pywrc_stream );
}

/* Signals the stream to abort the current activity
 * Returns a Python object if successful or NULL on error
 */
PyObject *pywrc_stream_signal_abort(
           pywrc_stream_t *pywrc_stream,
           PyObject *arguments PYWRC_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error = NULL;
	static char *function    = "pywrc_stream_signal_abort";
	int result               = 0;

	PYWRC_UNREFERENCED_PARAMETER( arguments )

	if( pywrc_stream == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid stream.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libwrc_stream_signal_abort(
	          pywrc_stream->stream,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pywrc_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to signal abort.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	Py_IncRef(
	 Py_None );

	return( Py_None );
}

/* Opens a stream
 * Returns a Python object if successful or NULL on error
 */
PyObject *pywrc_stream_open(
           pywrc_stream_t *pywrc_stream,
           PyObject *arguments,
           PyObject *keywords )
{
	PyObject *string_object      = NULL;
	libcerror_error_t *error     = NULL;
	const char *filename_narrow  = NULL;
	static char *function        = "pywrc_stream_open";
	static char *keyword_list[]  = { "filename", "mode", NULL };
	char *mode                   = NULL;
	int result                   = 0;

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	const wchar_t *filename_wide = NULL;
#else
	PyObject *utf8_string_object = NULL;
#endif

	if( pywrc_stream == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid stream.",
		 function );

		return( NULL );
	}
	/* Note that PyArg_ParseTupleAndKeywords with "s" will force Unicode strings to be converted to narrow character string.
	 * On Windows the narrow character strings contains an extended ASCII string with a codepage. Hence we get a conversion
	 * exception. This will also fail if the default encoding is not set correctly. We cannot use "u" here either since that
	 * does not allow us to pass non Unicode string objects and Python (at least 2.7) does not seems to automatically upcast them.
	 */
	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "O|s",
	     keyword_list,
	     &string_object,
	     &mode ) == 0 )
	{
		return( NULL );
	}
	if( ( mode != NULL )
	 && ( mode[ 0 ] != 'r' ) )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: unsupported mode: %s.",
		 function,
		 mode );

		return( NULL );
	}
	PyErr_Clear();

	result = PyObject_IsInstance(
	          string_object,
	          (PyObject *) &PyUnicode_Type );

	if( result == -1 )
	{
		pywrc_error_fetch_and_raise(
		 PyExc_RuntimeError,
		 "%s: unable to determine if string object is of type Unicode.",
		 function );

		return( NULL );
	}
	else if( result != 0 )
	{
		PyErr_Clear();

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
#if PY_MAJOR_VERSION >= 3 && PY_MINOR_VERSION >= 3
		filename_wide = (wchar_t *) PyUnicode_AsWideCharString(
		                             string_object,
		                             NULL );
#else
		filename_wide = (wchar_t *) PyUnicode_AsUnicode(
		                             string_object );
#endif
		Py_BEGIN_ALLOW_THREADS

		result = libwrc_stream_open_wide(
		          pywrc_stream->stream,
		          filename_wide,
		          LIBWRC_OPEN_READ,
		          &error );

		Py_END_ALLOW_THREADS

#if PY_MAJOR_VERSION >= 3 && PY_MINOR_VERSION >= 3
		PyMem_Free(
		 filename_wide );
#endif
#else
		utf8_string_object = PyUnicode_AsUTF8String(
		                      string_object );

		if( utf8_string_object == NULL )
		{
			pywrc_error_fetch_and_raise(
			 PyExc_RuntimeError,
			 "%s: unable to convert Unicode string to UTF-8.",
			 function );

			return( NULL );
		}
#if PY_MAJOR_VERSION >= 3
		filename_narrow = PyBytes_AsString(
		                   utf8_string_object );
#else
		filename_narrow = PyString_AsString(
		                   utf8_string_object );
#endif
		Py_BEGIN_ALLOW_THREADS

		result = libwrc_stream_open(
		          pywrc_stream->stream,
		          filename_narrow,
		          LIBWRC_OPEN_READ,
		          &error );

		Py_END_ALLOW_THREADS

		Py_DecRef(
		 utf8_string_object );
#endif
		if( result != 1 )
		{
			pywrc_error_raise(
			 error,
			 PyExc_IOError,
			 "%s: unable to open stream.",
			 function );

			libcerror_error_free(
			 &error );

			return( NULL );
		}
		Py_IncRef(
		 Py_None );

		return( Py_None );
	}
	PyErr_Clear();

#if PY_MAJOR_VERSION >= 3
	result = PyObject_IsInstance(
	          string_object,
	          (PyObject *) &PyBytes_Type );
#else
	result = PyObject_IsInstance(
	          string_object,
	          (PyObject *) &PyString_Type );
#endif
	if( result == -1 )
	{
		pywrc_error_fetch_and_raise(
		 PyExc_RuntimeError,
		 "%s: unable to determine if string object is of type string.",
		 function );

		return( NULL );
	}
	else if( result != 0 )
	{
		PyErr_Clear();

#if PY_MAJOR_VERSION >= 3
		filename_narrow = PyBytes_AsString(
		                   string_object );
#else
		filename_narrow = PyString_AsString(
		                   string_object );
#endif
		Py_BEGIN_ALLOW_THREADS

		result = libwrc_stream_open(
		          pywrc_stream->stream,
		          filename_narrow,
		          LIBWRC_OPEN_READ,
		          &error );

		Py_END_ALLOW_THREADS

		if( result != 1 )
		{
			pywrc_error_raise(
			 error,
			 PyExc_IOError,
			 "%s: unable to open stream.",
			 function );

			libcerror_error_free(
			 &error );

			return( NULL );
		}
		Py_IncRef(
		 Py_None );

		return( Py_None );
	}
	PyErr_Format(
	 PyExc_TypeError,
	 "%s: unsupported string object type.",
	 function );

	return( NULL );
}

/* Opens a stream using a file-like object
 * Returns a Python object if successful or NULL on error
 */
PyObject *pywrc_stream_open_file_object(
           pywrc_stream_t *pywrc_stream,
           PyObject *arguments,
           PyObject *keywords )
{
	PyObject *file_object       = NULL;
	libcerror_error_t *error    = NULL;
	char *mode                  = NULL;
	static char *keyword_list[] = { "file_object", "mode", NULL };
	static char *function       = "pywrc_stream_open_file_object";
	int result                  = 0;

	if( pywrc_stream == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid stream.",
		 function );

		return( NULL );
	}
	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "O|s",
	     keyword_list,
	     &file_object,
	     &mode ) == 0 )
	{
		return( NULL );
	}
	if( ( mode != NULL )
	 && ( mode[ 0 ] != 'r' ) )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: unsupported mode: %s.",
		 function,
		 mode );

		return( NULL );
	}
	PyErr_Clear();

	result = PyObject_HasAttrString(
	          file_object,
	          "read" );

	if( result != 1 )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: unsupported file object - missing read attribute.",
		 function );

		return( NULL );
	}
	PyErr_Clear();

	result = PyObject_HasAttrString(
	          file_object,
	          "seek" );

	if( result != 1 )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: unsupported file object - missing seek attribute.",
		 function );

		return( NULL );
	}
	if( pywrc_stream->file_io_handle != NULL )
	{
		pywrc_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: invalid stream - file IO handle already set.",
		 function );

		goto on_error;
	}
	if( pywrc_file_object_initialize(
	     &( pywrc_stream->file_io_handle ),
	     file_object,
	     &error ) != 1 )
	{
		pywrc_error_raise(
		 error,
		 PyExc_MemoryError,
		 "%s: unable to initialize file IO handle.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	Py_BEGIN_ALLOW_THREADS

	result = libwrc_stream_open_file_io_handle(
	          pywrc_stream->stream,
	          pywrc_stream->file_io_handle,
	          LIBWRC_OPEN_READ,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pywrc_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to open stream.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	Py_IncRef(
	 Py_None );

	return( Py_None );

on_error:
	if( pywrc_stream->file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &( pywrc_stream->file_io_handle ),
		 NULL );
	}
	return( NULL );
}

/* Closes a stream
 * Returns a Python object if successful or NULL on error
 */
PyObject *pywrc_stream_close(
           pywrc_stream_t *pywrc_stream,
           PyObject *arguments PYWRC_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error = NULL;
	static char *function    = "pywrc_stream_close";
	int result               = 0;

	PYWRC_UNREFERENCED_PARAMETER( arguments )

	if( pywrc_stream == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid stream.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libwrc_stream_close(
	          pywrc_stream->stream,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 0 )
	{
		pywrc_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to close stream.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	if( pywrc_stream->file_io_handle != NULL )
	{
		Py_BEGIN_ALLOW_THREADS

		result = libbfio_handle_free(
		          &( pywrc_stream->file_io_handle ),
		          &error );

		Py_END_ALLOW_THREADS

		if( result != 1 )
		{
			pywrc_error_raise(
			 error,
			 PyExc_MemoryError,
			 "%s: unable to free libbfio file IO handle.",
			 function );

			libcerror_error_free(
			 &error );

			return( NULL );
		}
	}
	Py_IncRef(
	 Py_None );

	return( Py_None );
}

/* Retrieves the codepage used for ASCII strings in the stream
 * Returns a Python object if successful or NULL on error
 */
PyObject *pywrc_stream_get_ascii_codepage(
           pywrc_stream_t *pywrc_stream,
           PyObject *arguments PYWRC_ATTRIBUTE_UNUSED )
{
	PyObject *string_object     = NULL;
	libcerror_error_t *error    = NULL;
	const char *codepage_string = NULL;
	static char *function       = "pywrc_stream_get_ascii_codepage";
	int ascii_codepage          = 0;
	int result                  = 0;

	PYWRC_UNREFERENCED_PARAMETER( arguments )

	if( pywrc_stream == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid stream.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libwrc_stream_get_ascii_codepage(
	          pywrc_stream->stream,
	          &ascii_codepage,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pywrc_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve ASCII codepage.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	codepage_string = pywrc_codepage_to_string(
	                   ascii_codepage );

	if( codepage_string == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: unsupported ASCII codepage: %d.",
		 function,
		 ascii_codepage );

		return( NULL );
	}
#if PY_MAJOR_VERSION >= 3
	string_object = PyBytes_FromString(
	                 codepage_string );
#else
	string_object = PyString_FromString(
	                 codepage_string );
#endif
	if( string_object == NULL )
	{
		PyErr_Format(
		 PyExc_IOError,
		 "%s: unable to convert codepage string into string object.",
		 function );

		return( NULL );
	}
	return( string_object );
}

/* Sets the codepage used for ASCII strings in the stream
 * Returns 1 if successful or -1 on error
 */
int pywrc_stream_set_ascii_codepage_from_string(
     pywrc_stream_t *pywrc_stream,
     const char *codepage_string )
{
	libcerror_error_t *error      = NULL;
	static char *function         = "pywrc_stream_set_ascii_codepage_from_string";
	size_t codepage_string_length = 0;
	uint32_t feature_flags        = 0;
	int ascii_codepage            = 0;
	int result                    = 0;

	if( pywrc_stream == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid stream.",
		 function );

		return( -1 );
	}
	if( codepage_string == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid codepage string.",
		 function );

		return( -1 );
	}
	codepage_string_length = narrow_string_length(
	                          codepage_string );

	feature_flags = LIBCLOCALE_CODEPAGE_FEATURE_FLAG_HAVE_WINDOWS;

	if( libclocale_codepage_copy_from_string(
	     &ascii_codepage,
	     codepage_string,
	     codepage_string_length,
	     feature_flags,
	     &error ) != 1 )
	{
		pywrc_error_raise(
		 error,
		 PyExc_RuntimeError,
		 "%s: unable to determine ASCII codepage.",
		 function );

		libcerror_error_free(
		 &error );

		return( -1 );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libwrc_stream_set_ascii_codepage(
	          pywrc_stream->stream,
	          ascii_codepage,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pywrc_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to set ASCII codepage.",
		 function );

		libcerror_error_free(
		 &error );

		return( -1 );
	}
	return( 1 );
}

/* Sets the codepage used for ASCII strings in the stream
 * Returns a Python object if successful or NULL on error
 */
PyObject *pywrc_stream_set_ascii_codepage(
           pywrc_stream_t *pywrc_stream,
           PyObject *arguments,
           PyObject *keywords )
{
	static char *keyword_list[] = { "codepage", NULL };
	char *codepage_string       = NULL;
	int result                  = 0;

	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "s",
	     keyword_list,
	     &codepage_string ) == 0 )
	{
		return( NULL );
	}
	result = pywrc_stream_set_ascii_codepage_from_string(
	          pywrc_stream,
	          codepage_string );

	if( result != 1 )
	{
		return( NULL );
	}
	Py_IncRef(
	 Py_None );

	return( Py_None );
}

/* Sets the codepage used for ASCII strings in the stream
 * Returns a Python object if successful or NULL on error
 */
int pywrc_stream_set_ascii_codepage_setter(
     pywrc_stream_t *pywrc_stream,
     PyObject *string_object,
     void *closure PYWRC_ATTRIBUTE_UNUSED )
{
	PyObject *utf8_string_object = NULL;
	static char *function        = "pywrc_stream_set_ascii_codepage_setter";
	char *codepage_string        = NULL;
	int result                   = 0;

	PYWRC_UNREFERENCED_PARAMETER( closure )

	PyErr_Clear();

	result = PyObject_IsInstance(
	          string_object,
	          (PyObject *) &PyUnicode_Type );

	if( result == -1 )
	{
		pywrc_error_fetch_and_raise(
		 PyExc_RuntimeError,
		 "%s: unable to determine if string object is of type Unicode.",
		 function );

		return( -1 );
	}
	else if( result != 0 )
	{
		/* The codepage string should only contain ASCII characters.
		 */
		utf8_string_object = PyUnicode_AsUTF8String(
		                      string_object );

		if( utf8_string_object == NULL )
		{
			pywrc_error_fetch_and_raise(
			 PyExc_RuntimeError,
			 "%s: unable to convert Unicode string to UTF-8.",
			 function );

			return( -1 );
		}
#if PY_MAJOR_VERSION >= 3
		codepage_string = PyBytes_AsString(
		                   utf8_string_object );
#else
		codepage_string = PyString_AsString(
		                   utf8_string_object );
#endif
		if( codepage_string == NULL )
		{
			return( -1 );
		}
		result = pywrc_stream_set_ascii_codepage_from_string(
		          pywrc_stream,
		          codepage_string );

		if( result != 1 )
		{
			return( -1 );
		}
		return( 0 );
	}
	PyErr_Clear();

#if PY_MAJOR_VERSION >= 3
	result = PyObject_IsInstance(
	          string_object,
	          (PyObject *) &PyBytes_Type );
#else
	result = PyObject_IsInstance(
	          string_object,
	          (PyObject *) &PyString_Type );
#endif
	if( result == -1 )
	{
		pywrc_error_fetch_and_raise(
		 PyExc_RuntimeError,
		 "%s: unable to determine if string object is of type string.",
		 function );

		return( -1 );
	}
	else if( result != 0 )
	{
#if PY_MAJOR_VERSION >= 3
		codepage_string = PyBytes_AsString(
		                   string_object );
#else
		codepage_string = PyString_AsString(
		                   string_object );
#endif
		if( codepage_string == NULL )
		{
			return( -1 );
		}
		result = pywrc_stream_set_ascii_codepage_from_string(
			  pywrc_stream,
			  codepage_string );

		if( result != 1 )
		{
			return( -1 );
		}
		return( 0 );
	}
	PyErr_Format(
	 PyExc_TypeError,
	 "%s: unsupported string object type.",
	 function );

	return( -1 );
}

/* Retrieves the virtual address
 * Returns a Python object if successful or NULL on error
 */
PyObject *pywrc_stream_get_virtual_address(
           pywrc_stream_t *pywrc_stream,
           PyObject *arguments PYWRC_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error = NULL;
	PyObject *integer_object = NULL;
	static char *function    = "pywrc_stream_get_virtual_address";
	uint32_t virtual_address = 0;
	int result               = 0;

	PYWRC_UNREFERENCED_PARAMETER( arguments )

	if( pywrc_stream == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid stream.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libwrc_stream_get_virtual_address(
	          pywrc_stream->stream,
	          &virtual_address,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pywrc_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve virtual address.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	integer_object = pywrc_integer_unsigned_new_from_64bit(
	                  (uint64_t) virtual_address );

	return( integer_object );
}

/* Sets the virtual address of the stream
 * Returns a Python object if successful or NULL on error
 */
PyObject *pywrc_stream_set_virtual_address(
           pywrc_stream_t *pywrc_stream,
           PyObject *arguments,
           PyObject *keywords )
{
	libcerror_error_t *error      = NULL;
	static char *function         = "pywrc_stream_set_virtual_address";
	static char *keyword_list[]   = { "virtual_address", NULL };
	unsigned long virtual_address = 0;
	int result                    = 0;

	if( pywrc_stream == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid stream.",
		 function );

		return( NULL );
	}
	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "k",
	     keyword_list,
	     &virtual_address ) == 0 )
	{
		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libwrc_stream_set_virtual_address(
	          pywrc_stream->stream,
	          (uint32_t) virtual_address,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pywrc_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to set virtual address.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	Py_IncRef(
	 Py_None );

	return( Py_None );
}

/* Retrieves the number of resources
 * Returns a Python object if successful or NULL on error
 */
PyObject *pywrc_stream_get_number_of_resources(
           pywrc_stream_t *pywrc_stream,
           PyObject *arguments PYWRC_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error = NULL;
	PyObject *integer_object = NULL;
	static char *function    = "pywrc_stream_get_number_of_resources";
	int number_of_resources  = 0;
	int result               = 0;

	PYWRC_UNREFERENCED_PARAMETER( arguments )

	if( pywrc_stream == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid stream.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libwrc_stream_get_number_of_resources(
	          pywrc_stream->stream,
	          &number_of_resources,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pywrc_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve number of resources.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
#if PY_MAJOR_VERSION >= 3
	integer_object = PyLong_FromLong(
	                  (long) number_of_resources );
#else
	integer_object = PyInt_FromLong(
	                  (long) number_of_resources );
#endif
	return( integer_object );
}

/* Retrieves a specific resource by index
 * Returns a Python object if successful or NULL on error
 */
PyObject *pywrc_stream_get_resource_by_index(
           PyObject *pywrc_stream,
           int resource_index )
{
	libcerror_error_t *error    = NULL;
	libwrc_resource_t *resource = NULL;
	PyObject *resource_object   = NULL;
	static char *function       = "pywrc_stream_get_resource_by_index";
	int result                  = 0;

	if( pywrc_stream == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid stream.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libwrc_stream_get_resource_by_index(
	          ( (pywrc_stream_t *) pywrc_stream )->stream,
	          resource_index,
	          &resource,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pywrc_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve resource: %d.",
		 function,
		 resource_index );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	resource_object = pywrc_resource_new(
	                   resource,
	                   pywrc_stream );

	if( resource_object == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create resource object.",
		 function );

		goto on_error;
	}
	return( resource_object );

on_error:
	if( resource != NULL )
	{
		libwrc_resource_free(
		 &resource,
		 NULL );
	}
	return( NULL );
}

/* Retrieves a specific resource
 * Returns a Python object if successful or NULL on error
 */
PyObject *pywrc_stream_get_resource(
           pywrc_stream_t *pywrc_stream,
           PyObject *arguments,
           PyObject *keywords )
{
	PyObject *resource_object   = NULL;
	static char *keyword_list[] = { "resource_index", NULL };
	int resource_index          = 0;

	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "i",
	     keyword_list,
	     &resource_index ) == 0 )
	{
		return( NULL );
	}
	resource_object = pywrc_stream_get_resource_by_index(
	                   (PyObject *) pywrc_stream,
	                   resource_index );

	return( resource_object );
}

/* Retrieves a resources sequence and iterator object for the resources
 * Returns a Python object if successful or NULL on error
 */
PyObject *pywrc_stream_get_resources(
           pywrc_stream_t *pywrc_stream,
           PyObject *arguments PYWRC_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error   = NULL;
	PyObject *resources_object = NULL;
	static char *function      = "pywrc_stream_get_resources";
	int number_of_resources    = 0;
	int result                 = 0;

	PYWRC_UNREFERENCED_PARAMETER( arguments )

	if( pywrc_stream == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid stream.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libwrc_stream_get_number_of_resources(
	          pywrc_stream->stream,
	          &number_of_resources,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pywrc_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve number of resources.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	resources_object = pywrc_resources_new(
	                    (PyObject *) pywrc_stream,
	                    &pywrc_stream_get_resource_by_index,
	                    number_of_resources );

	if( resources_object == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create resources object.",
		 function );

		return( NULL );
	}
	return( resources_object );
}

/* Retrieves a specific resource by identifier
 * Returns a Python object if successful or NULL on error
 */
PyObject *pywrc_stream_get_resource_by_identifier(
           pywrc_stream_t *pywrc_stream,
           PyObject *arguments,
           PyObject *keywords )
{
	libcerror_error_t *error          = NULL;
	libwrc_resource_t *resource       = NULL;
	PyObject *resource_object         = NULL;
	static char *keyword_list[]       = { "resource_identifier", NULL };
	static char *function             = "pywrc_stream_get_resource_by_identifier";
	unsigned long resource_identifier = 0;
	int result                        = 0;

	if( pywrc_stream == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid stream.",
		 function );

		return( NULL );
	}
	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "k",
	     keyword_list,
	     &resource_identifier ) == 0 )
	{
		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libwrc_stream_get_resource_by_identifier(
	          pywrc_stream->stream,
	          (uint32_t) resource_identifier,
	          &resource,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		pywrc_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve resource: %" PRIu32 ".",
		 function,
		 (uint32_t) resource_identifier );

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
	resource_object = pywrc_resource_new(
	                   resource,
	                   (PyObject *) pywrc_stream );

	if( resource_object == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create resource object.",
		 function );

		goto on_error;
	}
	return( resource_object );

on_error:
	if( resource != NULL )
	{
		libwrc_resource_free(
		 &resource,
		 NULL );
	}
	return( NULL );
}

/* Retrieves a specific resource by name
 * Returns a Python object if successful or NULL on error
 */
PyObject *pywrc_stream_get_resource_by_name(
           pywrc_stream_t *pywrc_stream,
           PyObject *arguments,
           PyObject *keywords )
{
	libcerror_error_t *error     = NULL;
	libwrc_resource_t *resource  = NULL;
	PyObject *resource_object    = NULL;
	char *resource_name          = 0;
	static char *keyword_list[]  = { "resource_name", NULL };
	static char *function        = "pywrc_stream_get_resource_by_name";
	size_t resource_name_length  = 0;
	int result                   = 0;

	if( pywrc_stream == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid stream.",
		 function );

		return( NULL );
	}
	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "s",
	     keyword_list,
	     &resource_name ) == 0 )
	{
		return( NULL );
	}
	resource_name_length = narrow_string_length(
	                        resource_name );

	Py_BEGIN_ALLOW_THREADS

	result = libwrc_stream_get_resource_by_utf8_name(
	          pywrc_stream->stream,
	          (uint8_t *) resource_name,
	          resource_name_length,
	          &resource,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		pywrc_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve resource: %s.",
		 function,
		 resource_name );

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
	resource_object = pywrc_resource_new(
	                   resource,
	                   (PyObject *) pywrc_stream );

	if( resource_object == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create resource object.",
		 function );

		goto on_error;
	}
	return( resource_object );

on_error:
	if( resource != NULL )
	{
		libwrc_resource_free(
		 &resource,
		 NULL );
	}
	return( NULL );
}

