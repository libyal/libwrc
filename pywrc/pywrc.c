/*
 * Python bindings module for libwrc (pywrc)
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

#include "pywrc.h"
#include "pywrc_file_object_io_handle.h"
#include "pywrc_libcerror.h"
#include "pywrc_libwrc.h"
#include "pywrc_manifest_resource.h"
#include "pywrc_message_table_resource.h"
#include "pywrc_mui_resource.h"
#include "pywrc_python.h"
#include "pywrc_resource.h"
#include "pywrc_resource_item.h"
#include "pywrc_resource_items.h"
#include "pywrc_resources.h"
#include "pywrc_stream.h"
#include "pywrc_string_table_resource.h"
#include "pywrc_unused.h"
#include "pywrc_version_information_resource.h"

/* The pywrc module methods
 */
PyMethodDef pywrc_module_methods[] = {
	{ "get_version",
	  (PyCFunction) pywrc_get_version,
	  METH_NOARGS,
	  "get_version() -> String\n"
	  "\n"
	  "Retrieves the version." },

	{ "open",
	  (PyCFunction) pywrc_open_new_stream,
	  METH_VARARGS | METH_KEYWORDS,
	  "open(filename, mode='r') -> Object\n"
	  "\n"
	  "Opens a stream." },

	{ "open_file_object",
	  (PyCFunction) pywrc_open_new_stream_with_file_object,
	  METH_VARARGS | METH_KEYWORDS,
	  "open_file_object(file_object, mode='r') -> Object\n"
	  "\n"
	  "Opens a stream using a file-like object." },

	/* Sentinel */
	{ NULL, NULL, 0, NULL }
};

/* Retrieves the pywrc/libwrc version
 * Returns a Python object if successful or NULL on error
 */
PyObject *pywrc_get_version(
           PyObject *self PYWRC_ATTRIBUTE_UNUSED,
           PyObject *arguments PYWRC_ATTRIBUTE_UNUSED )
{
	const char *version_string   = NULL;
	size_t version_string_length = 0;

	PYWRC_UNREFERENCED_PARAMETER( self )
	PYWRC_UNREFERENCED_PARAMETER( arguments )

	Py_BEGIN_ALLOW_THREADS

	version_string = libwrc_get_version();

	Py_END_ALLOW_THREADS

	version_string_length = narrow_string_length(
	                         version_string );

	/* Pass the string length to PyUnicode_DecodeUTF8
	 * otherwise it makes the end of string character is part
	 * of the string
	 */
	return( PyUnicode_DecodeUTF8(
	         version_string,
	         (Py_ssize_t) version_string_length,
	         NULL ) );
}

/* Creates a new stream object and opens it
 * Returns a Python object if successful or NULL on error
 */
PyObject *pywrc_open_new_stream(
           PyObject *self PYWRC_ATTRIBUTE_UNUSED,
           PyObject *arguments,
           PyObject *keywords )
{
	pywrc_stream_t *pywrc_stream = NULL;
	static char *function    = "pywrc_open_new_stream";

	PYWRC_UNREFERENCED_PARAMETER( self )

	/* PyObject_New does not invoke tp_init
	 */
	pywrc_stream = PyObject_New(
	                struct pywrc_stream,
	                &pywrc_stream_type_object );

	if( pywrc_stream == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create stream.",
		 function );

		goto on_error;
	}
	if( pywrc_stream_init(
	     pywrc_stream ) != 0 )
	{
		goto on_error;
	}
	if( pywrc_stream_open(
	     pywrc_stream,
	     arguments,
	     keywords ) == NULL )
	{
		goto on_error;
	}
	return( (PyObject *) pywrc_stream );

on_error:
	if( pywrc_stream != NULL )
	{
		Py_DecRef(
		 (PyObject *) pywrc_stream );
	}
	return( NULL );
}

/* Creates a new stream object and opens it using a file-like object
 * Returns a Python object if successful or NULL on error
 */
PyObject *pywrc_open_new_stream_with_file_object(
           PyObject *self PYWRC_ATTRIBUTE_UNUSED,
           PyObject *arguments,
           PyObject *keywords )
{
	pywrc_stream_t *pywrc_stream = NULL;
	static char *function        = "pywrc_open_new_stream_with_file_object";

	PYWRC_UNREFERENCED_PARAMETER( self )

	/* PyObject_New does not invoke tp_init
	 */
	pywrc_stream = PyObject_New(
	                struct pywrc_stream,
	                &pywrc_stream_type_object );

	if( pywrc_stream == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create stream.",
		 function );

		goto on_error;
	}
	if( pywrc_stream_init(
	     pywrc_stream ) != 0 )
	{
		goto on_error;
	}
	if( pywrc_stream_open_file_object(
	     pywrc_stream,
	     arguments,
	     keywords ) == NULL )
	{
		goto on_error;
	}
	return( (PyObject *) pywrc_stream );

on_error:
	if( pywrc_stream != NULL )
	{
		Py_DecRef(
		 (PyObject *) pywrc_stream );
	}
	return( NULL );
}

#if PY_MAJOR_VERSION >= 3

/* The pywrc module definition
 */
PyModuleDef pywrc_module_definition = {
	PyModuleDef_HEAD_INIT,

	/* m_name */
	"pywrc",
	/* m_doc */
	"Python libwrc module (pywrc).",
	/* m_size */
	-1,
	/* m_methods */
	pywrc_module_methods,
	/* m_reload */
	NULL,
	/* m_traverse */
	NULL,
	/* m_clear */
	NULL,
	/* m_free */
	NULL,
};

#endif /* PY_MAJOR_VERSION >= 3 */

/* Initializes the pywrc module
 */
#if PY_MAJOR_VERSION >= 3
PyMODINIT_FUNC PyInit_pywrc(
                void )
#else
PyMODINIT_FUNC initpywrc(
                void )
#endif
{
	PyObject *module           = NULL;
	PyGILState_STATE gil_state = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	libwrc_notify_set_stream(
	 stderr,
	 NULL );
	libwrc_notify_set_verbose(
	 1 );
#endif

	/* Create the module
	 * This function must be called before grabbing the GIL
	 * otherwise the module will segfault on a version mismatch
	 */
#if PY_MAJOR_VERSION >= 3
	module = PyModule_Create(
	          &pywrc_module_definition );
#else
	module = Py_InitModule3(
	          "pywrc",
	          pywrc_module_methods,
	          "Python libwrc module (pywrc)." );
#endif
	if( module == NULL )
	{
#if PY_MAJOR_VERSION >= 3
		return( NULL );
#else
		return;
#endif
	}
#if PY_VERSION_HEX < 0x03070000
	PyEval_InitThreads();
#endif
	gil_state = PyGILState_Ensure();

	/* Setup the manifest resource type object
	 */
	pywrc_manifest_resource_type_object.tp_new = PyType_GenericNew;

	if( PyType_Ready(
	     &pywrc_manifest_resource_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pywrc_manifest_resource_type_object );

	PyModule_AddObject(
	 module,
	 "manifest_resource",
	 (PyObject *) &pywrc_manifest_resource_type_object );

	/* Setup the message table resource type object
	 */
	pywrc_message_table_resource_type_object.tp_new = PyType_GenericNew;

	if( PyType_Ready(
	     &pywrc_message_table_resource_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pywrc_message_table_resource_type_object );

	PyModule_AddObject(
	 module,
	 "message_table_resource",
	 (PyObject *) &pywrc_message_table_resource_type_object );

	/* Setup the manifest resource type object
	 */
	pywrc_manifest_resource_type_object.tp_new = PyType_GenericNew;

	if( PyType_Ready(
	     &pywrc_manifest_resource_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pywrc_manifest_resource_type_object );

	PyModule_AddObject(
	 module,
	 "manifest_resource",
	 (PyObject *) &pywrc_manifest_resource_type_object );

	/* Setup the message table resource type object
	 */
	pywrc_message_table_resource_type_object.tp_new = PyType_GenericNew;

	if( PyType_Ready(
	     &pywrc_message_table_resource_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pywrc_message_table_resource_type_object );

	PyModule_AddObject(
	 module,
	 "message_table_resource",
	 (PyObject *) &pywrc_message_table_resource_type_object );

	/* Setup the MUI resource type object
	 */
	pywrc_mui_resource_type_object.tp_new = PyType_GenericNew;

	if( PyType_Ready(
	     &pywrc_mui_resource_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pywrc_mui_resource_type_object );

	PyModule_AddObject(
	 module,
	 "mui_resource",
	 (PyObject *) &pywrc_mui_resource_type_object );

	/* Setup the resource type object
	 */
	pywrc_resource_type_object.tp_new = PyType_GenericNew;

	if( PyType_Ready(
	     &pywrc_resource_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pywrc_resource_type_object );

	PyModule_AddObject(
	 module,
	 "resource",
	 (PyObject *) &pywrc_resource_type_object );

	/* Setup the resource item type object
	 */
	pywrc_resource_item_type_object.tp_new = PyType_GenericNew;

	if( PyType_Ready(
	     &pywrc_resource_item_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pywrc_resource_item_type_object );

	PyModule_AddObject(
	 module,
	 "resource_item",
	 (PyObject *) &pywrc_resource_item_type_object );

	/* Setup the resource items type object
	 */
	pywrc_resource_items_type_object.tp_new = PyType_GenericNew;

	if( PyType_Ready(
	     &pywrc_resource_items_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pywrc_resource_items_type_object );

	PyModule_AddObject(
	 module,
	 "resource_items",
	 (PyObject *) &pywrc_resource_items_type_object );

	/* Setup the resources type object
	 */
	pywrc_resources_type_object.tp_new = PyType_GenericNew;

	if( PyType_Ready(
	     &pywrc_resources_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pywrc_resources_type_object );

	PyModule_AddObject(
	 module,
	 "resources",
	 (PyObject *) &pywrc_resources_type_object );

	/* Setup the stream type object
	 */
	pywrc_stream_type_object.tp_new = PyType_GenericNew;

	if( PyType_Ready(
	     &pywrc_stream_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pywrc_stream_type_object );

	PyModule_AddObject(
	 module,
	 "stream",
	 (PyObject *) &pywrc_stream_type_object );

	/* Setup the string table resource type object
	 */
	pywrc_string_table_resource_type_object.tp_new = PyType_GenericNew;

	if( PyType_Ready(
	     &pywrc_string_table_resource_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pywrc_string_table_resource_type_object );

	PyModule_AddObject(
	 module,
	 "string_table_resource",
	 (PyObject *) &pywrc_string_table_resource_type_object );

	/* Setup the version information resource type object
	 */
	pywrc_version_information_resource_type_object.tp_new = PyType_GenericNew;

	if( PyType_Ready(
	     &pywrc_version_information_resource_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pywrc_version_information_resource_type_object );

	PyModule_AddObject(
	 module,
	 "version_information_resource",
	 (PyObject *) &pywrc_version_information_resource_type_object );

	PyGILState_Release(
	 gil_state );

#if PY_MAJOR_VERSION >= 3
	return( module );
#else
	return;
#endif

on_error:
	PyGILState_Release(
	 gil_state );

#if PY_MAJOR_VERSION >= 3
	return( NULL );
#else
	return;
#endif
}

