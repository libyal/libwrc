/*
 * Python bindings module for libwrc (pywrc)
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
#include <narrow_string.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( HAVE_WINAPI )
#include <stdlib.h>
#endif

#include "pywrc.h"
#include "pywrc_file_object_io_handle.h"
#include "pywrc_language_identifiers.h"
#include "pywrc_libcerror.h"
#include "pywrc_libwrc.h"
#include "pywrc_manifest.h"
#include "pywrc_message_table.h"
#include "pywrc_mui.h"
#include "pywrc_python.h"
#include "pywrc_resource.h"
#include "pywrc_resources.h"
#include "pywrc_stream.h"
#include "pywrc_string.h"
#include "pywrc_unused.h"
#include "pywrc_version.h"

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
	  (PyCFunction) pywrc_stream_new_open,
	  METH_VARARGS | METH_KEYWORDS,
	  "open(filename, mode='r') -> Object\n"
	  "\n"
	  "Opens a stream." },

	{ "open_file_object",
	  (PyCFunction) pywrc_stream_new_open_file_object,
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
	const char *errors           = NULL;
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
	         errors ) );
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
	PyObject *module                               = NULL;
	PyTypeObject *language_identifiers_type_object = NULL;
	PyTypeObject *manifest_type_object             = NULL;
	PyTypeObject *message_table_type_object        = NULL;
	PyTypeObject *mui_type_object                  = NULL;
	PyTypeObject *resource_type_object             = NULL;
	PyTypeObject *resources_type_object            = NULL;
	PyTypeObject *stream_type_object               = NULL;
	PyTypeObject *string_type_object               = NULL;
	PyTypeObject *version_type_object              = NULL;
	PyGILState_STATE gil_state                     = 0;

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
	PyEval_InitThreads();

	gil_state = PyGILState_Ensure();

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

	stream_type_object = &pywrc_stream_type_object;

	PyModule_AddObject(
	 module,
	 "stream",
	 (PyObject *) stream_type_object );

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

	resources_type_object = &pywrc_resources_type_object;

	PyModule_AddObject(
	 module,
	 "_resources",
	 (PyObject *) resources_type_object );

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

	resource_type_object = &pywrc_resource_type_object;

	PyModule_AddObject(
	 module,
	 "resource",
	 (PyObject *) resource_type_object );

	/* Setup the language identifier type object
	 */
	pywrc_language_identifiers_type_object.tp_new = PyType_GenericNew;

	if( PyType_Ready(
	     &pywrc_language_identifiers_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pywrc_language_identifiers_type_object );

	language_identifiers_type_object = &pywrc_language_identifiers_type_object;

	PyModule_AddObject(
	 module,
	 "_language_identifiers",
	 (PyObject *) language_identifiers_type_object );

	/* Setup the manifest type object
	 */
	pywrc_manifest_type_object.tp_new = PyType_GenericNew;

	if( PyType_Ready(
	     &pywrc_manifest_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pywrc_manifest_type_object );

	manifest_type_object = &pywrc_manifest_type_object;

	PyModule_AddObject(
	 module,
	 "manifest",
	 (PyObject *) manifest_type_object );

	/* Setup the message table type object
	 */
	pywrc_message_table_type_object.tp_new = PyType_GenericNew;

	if( PyType_Ready(
	     &pywrc_message_table_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pywrc_message_table_type_object );

	message_table_type_object = &pywrc_message_table_type_object;

	PyModule_AddObject(
	 module,
	 "message_table",
	 (PyObject *) message_table_type_object );

	/* Setup the MUI type object
	 */
	pywrc_mui_type_object.tp_new = PyType_GenericNew;

	if( PyType_Ready(
	     &pywrc_mui_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pywrc_mui_type_object );

	mui_type_object = &pywrc_mui_type_object;

	PyModule_AddObject(
	 module,
	 "mui",
	 (PyObject *) mui_type_object );

	/* Setup the string type object
	 */
	pywrc_string_type_object.tp_new = PyType_GenericNew;

	if( PyType_Ready(
	     &pywrc_string_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pywrc_string_type_object );

	string_type_object = &pywrc_string_type_object;

	PyModule_AddObject(
	 module,
	 "string",
	 (PyObject *) string_type_object );

	/* Setup the version type object
	 */
	pywrc_version_type_object.tp_new = PyType_GenericNew;

	if( PyType_Ready(
	     &pywrc_version_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pywrc_version_type_object );

	version_type_object = &pywrc_version_type_object;

	PyModule_AddObject(
	 module,
	 "version",
	 (PyObject *) version_type_object );

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

