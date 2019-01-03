/*
 * Python object definition of the libwrc version resource
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
#include "pywrc_unused.h"
#include "pywrc_version.h"

PyMethodDef pywrc_version_object_methods[] = {

	/* Functions to access the version resource values */

	{ "get_file_version",
	  (PyCFunction) pywrc_version_get_file_version,
	  METH_VARARGS | METH_KEYWORDS,
	  "get_file_version(language_identifier) -> Integer\n"
	  "\n"
	  "Retrieves the file version." },

	{ "get_product_version",
	  (PyCFunction) pywrc_version_get_product_version,
	  METH_VARARGS | METH_KEYWORDS,
	  "get_product_version(language_identifier) -> Integer\n"
	  "\n"
	  "Retrieves the product version." },

	/* Sentinel */
	{ NULL, NULL, 0, NULL }
};

PyGetSetDef pywrc_version_object_get_set_definitions[] = {

	/* Sentinel */
	{ NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pywrc_version_type_object = {
	PyVarObject_HEAD_INIT( NULL, 0 )

	/* tp_name */
	"pywrc.version",
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
	"pywrc version object (wraps libwrc_resource_t type: LIBWRC_RESOURCE_TYPE_VERSION)",
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
	pywrc_version_object_methods,
	/* tp_members */
	0,
	/* tp_getset */
	pywrc_version_object_get_set_definitions,
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

/* Retrieves the file version for a specific language identifier
 * Returns a Python object if successful or NULL on error
 */
PyObject *pywrc_version_get_file_version(
           pywrc_resource_t *pywrc_resource,
           PyObject *arguments,
           PyObject *keywords )
{
	libcerror_error_t *error     = NULL;
	PyObject *integer_object     = NULL;
	static char *keyword_list[]  = { "language_identifier", NULL };
	static char *function        = "pywrc_version_get_file_version";
	uint64_t file_version        = 0;
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

	result = libwrc_version_get_file_version(
	          pywrc_resource->resource,
	          language_identifier,
	          &file_version,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pywrc_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve file version.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	integer_object = pywrc_integer_unsigned_new_from_64bit(
	                  file_version );

	return( integer_object );
}

/* Retrieves the product version for a specific language identifier
 * Returns a Python object if successful or NULL on error
 */
PyObject *pywrc_version_get_product_version(
           pywrc_resource_t *pywrc_resource,
           PyObject *arguments,
           PyObject *keywords )
{
	libcerror_error_t *error     = NULL;
	PyObject *integer_object     = NULL;
	static char *keyword_list[]  = { "language_identifier", NULL };
	static char *function        = "pywrc_version_get_product_version";
	uint64_t product_version     = 0;
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

	result = libwrc_version_get_product_version(
	          pywrc_resource->resource,
	          language_identifier,
	          &product_version,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pywrc_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve product version.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	integer_object = pywrc_integer_unsigned_new_from_64bit(
	                  product_version );

	return( integer_object );
}

