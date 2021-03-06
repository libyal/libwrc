# Note that we cannot use: AUTOMAKE_OPTIONS = subdir-objects
# subdir-objects will compile the source files to a single version of Python.
# Since subdir-objects is being deprecated we copy the source files instead.
am__installdirs = "$(DESTDIR)$(pyexecdir2)"
pyexecdir = $(pyexecdir2)

if HAVE_PYTHON2
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

am_pywrc_la_rpath = -rpath $(pyexecdir2)

BUILT_SOURCES = \
	pywrc.c pywrc.h \
	pywrc_codepage.c pywrc_codepage.h \
	pywrc_error.c pywrc_error.h \
	pywrc_file_object_io_handle.c pywrc_file_object_io_handle.h \
	pywrc_integer.c pywrc_integer.h \
	pywrc_language_identifiers.c pywrc_language_identifiers.h \
	pywrc_libbfio.h \
	pywrc_libcerror.h \
	pywrc_libclocale.h \
	pywrc_libwrc.h \
	pywrc_manifest.c pywrc_manifest.h \
	pywrc_message_table.c pywrc_message_table.h \
	pywrc_mui.c pywrc_mui.h \
	pywrc_python.h \
	pywrc_resource.c pywrc_resource.h \
	pywrc_resources.c pywrc_resources.h \
	pywrc_stream.c pywrc_stream.h \
	pywrc_string.c pywrc_string.h \
	pywrc_unused.h \
	pywrc_version.c pywrc_version.h

pyexec_LTLIBRARIES = pywrc.la

nodist_pywrc_la_SOURCES = $(BUILT_SOURCES)

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

pywrc_la_CPPFLAGS = $(PYTHON2_CPPFLAGS)
pywrc_la_LDFLAGS  = -module -avoid-version $(PYTHON2_LDFLAGS)

$(BUILT_SOURCES):
	/bin/cp -f $(top_srcdir)/pywrc/$@ $@

endif

MAINTAINERCLEANFILES = \
	Makefile.in

clean-local:
	/bin/rm -f pywrc*.[ch]

distclean: clean
	/bin/rm -f Makefile

