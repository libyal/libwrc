AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCSTRING_CPPFLAGS@ \
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
	@LIBWRC_DLL_IMPORT@

if HAVE_PYTHON
TESTS_PYWRC = \
	test_pywrc_set_ascii_codepage.sh
endif

TESTS = \
	test_set_ascii_codepage.sh \
	$(TESTS_PYWRC)

check_SCRIPTS = \
	pywrc_test_set_ascii_codepage.py \
	test_pywrc_set_ascii_codepage.sh \
	test_runner.sh \
	test_set_ascii_codepage.sh

EXTRA_DIST = \
	$(check_SCRIPTS)

check_PROGRAMS =  \
	wrc_test_set_ascii_codepage

wrc_test_set_ascii_codepage_SOURCES = \
	wrc_test_libcerror.h \
	wrc_test_libclocale.h \
	wrc_test_libwrc.h \
	wrc_test_libcstring.h \
	wrc_test_set_ascii_codepage.c

wrc_test_set_ascii_codepage_LDADD = \
	../libwrc/libwrc.la \
	@LIBCLOCALE_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	@LIBCSTRING_LIBADD@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

