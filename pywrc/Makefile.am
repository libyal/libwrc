if HAVE_PYTHON
AM_CFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCDATA_CPPFLAGS@ \
	@LIBCLOCALE_CPPFLAGS@ \
	@LIBCSPLIT_CPPFLAGS@ \
	@LIBUNA_CPPFLAGS@ \
	@LIBCFILE_CPPFLAGS@ \
	@LIBCPATH_CPPFLAGS@ \
	@LIBBFIO_CPPFLAGS@ \
	@LIBWRC_DLL_IMPORT@

pyexec_LTLIBRARIES = pywrc.la

pywrc_la_SOURCES = \
	pywrc.c pywrc.h \
	pywrc_codepage.c pywrc_codepage.h \
	pywrc_error.c pywrc_error.h \
	pywrc_file_object_io_handle.c pywrc_file_object_io_handle.h \
	pywrc_integer.c pywrc_integer.h \
	pywrc_libbfio.h \
	pywrc_libcerror.h \
	pywrc_libclocale.h \
	pywrc_libwrc.h \
	pywrc_manifest_resource.c pywrc_manifest_resource.h \
	pywrc_message_table_resource.c pywrc_message_table_resource.h \
	pywrc_mui_resource.c pywrc_mui_resource.h \
	pywrc_python.h \
	pywrc_resource.c pywrc_resource.h \
	pywrc_resource_item.c pywrc_resource_item.h \
	pywrc_resource_items.c pywrc_resource_items.h \
	pywrc_resources.c pywrc_resources.h \
	pywrc_stream.c pywrc_stream.h \
	pywrc_string_table_resource.c pywrc_string_table_resource.h \
	pywrc_unused.h \
	pywrc_version_information_resource.c pywrc_version_information_resource.h

pywrc_la_LIBADD = \
	@LIBCERROR_LIBADD@ \
	../libwrc/libwrc.la \
	@LIBCDATA_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBBFIO_LIBADD@

pywrc_la_CPPFLAGS = $(PYTHON_CPPFLAGS)
pywrc_la_LDFLAGS  = -module -avoid-version $(PYTHON_LDFLAGS)

endif

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	-rm -f Makefile

