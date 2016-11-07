AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCTHREADS_CPPFLAGS@ \
	@LIBCDATA_CPPFLAGS@ \
	@LIBCLOCALE_CPPFLAGS@ \
	@LIBCNOTIFY_CPPFLAGS@ \
	@LIBCSPLIT_CPPFLAGS@ \
	@LIBUNA_CPPFLAGS@ \
	@LIBCFILE_CPPFLAGS@ \
	@LIBCPATH_CPPFLAGS@ \
	@LIBBFIO_CPPFLAGS@ \
	@LIBCSYSTEM_CPPFLAGS@ \
	@PTHREAD_CPPFLAGS@ \
	@LIBWRC_DLL_IMPORT@

if HAVE_PYTHON_TESTS
TESTS_PYWRC = \
	test_python_functions.sh \
	test_pywrc_set_ascii_codepage.sh
endif

TESTS = \
	test_api_functions.sh \
	test_api_types.sh \
	test_wrcinfo.sh \
	$(TESTS_PYWRC)

check_SCRIPTS = \
	pywrc_test_get_version.py \
	pywrc_test_set_ascii_codepage.py \
	test_api_functions.sh \
	test_api_types.sh \
	test_python_functions.sh \
	test_pywrc_set_ascii_codepage.sh \
	test_runner.sh \
	test_wrcinfo.sh

EXTRA_DIST = \
	$(check_SCRIPTS)

check_PROGRAMS = \
	wrc_test_error \
	wrc_test_notify \
	wrc_test_resource \
	wrc_test_stream \
	wrc_test_support

wrc_test_error_SOURCES = \
	wrc_test_error.c
	wrc_test_libwrc.h \
	wrc_test_macros.h \
	wrc_test_unused.h

wrc_test_error_LDADD = \
	../libwrc/libwrc.la

wrc_test_notify_SOURCES = \
	wrc_test_libwrc.h \
	wrc_test_macros.h \
	wrc_test_notify.c
	wrc_test_unused.h

wrc_test_notify_LDADD = \
	../libwrc/libwrc.la

wrc_test_resource_SOURCES = \
	wrc_test_libcerror.h \
	wrc_test_libwrc.h \
	wrc_test_macros.h \
	wrc_test_memory.c wrc_test_memory.h \
	wrc_test_resource.c \
	wrc_test_unused.h

wrc_test_resource_LDADD = \
	../libwrc/libwrc.la \
	@LIBCERROR_LIBADD@

wrc_test_stream_SOURCES = \
	wrc_test_libcerror.h \
	wrc_test_libclocale.h \
	wrc_test_libwrc.h \
	wrc_test_libcsystem.h \
	wrc_test_libuna.h \
	wrc_test_macros.h \
	wrc_test_memory.c wrc_test_memory.h \
	wrc_test_stream.c

wrc_test_stream_LDADD = \
	@LIBCSYSTEM_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libwrc/libwrc.la \
	@LIBCERROR_LIBADD@

wrc_test_support_SOURCES = \
	wrc_test_libwrc.h \
	wrc_test_macros.h \
	wrc_test_support.c
	wrc_test_unused.h

wrc_test_support_LDADD = \
	../libwrc/libwrc.la

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

