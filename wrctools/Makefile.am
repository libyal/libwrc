AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCSTRING_CPPFLAGS@ \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCDATA_CPPFLAGS@ \
	@LIBCLOCALE_CPPFLAGS@ \
	@LIBCNOTIFY_CPPFLAGS@ \
	@LIBCSPLIT_CPPFLAGS@ \
	@LIBUNA_CPPFLAGS@ \
	@LIBCFILE_CPPFLAGS@ \
	@LIBCPATH_CPPFLAGS@ \
	@LIBBFIO_CPPFLAGS@ \
	@LIBFCACHE_CPPFLAGS@ \
	@LIBFDATA_CPPFLAGS@ \
	@LIBFDATETIME_CPPFLAGS@ \
	@LIBFVALUE_CPPFLAGS@ \
	@LIBFWNT_CPPFLAGS@ \
	@LIBEXE_CPPFLAGS@ \
	@LIBCSYSTEM_CPPFLAGS@ \
	@LIBWRC_DLL_IMPORT@

AM_LDFLAGS = @STATIC_LDFLAGS@

bin_PROGRAMS = \
	wrcinfo

wrcinfo_SOURCES = \
	wrcinfo.c \
	wrcoutput.c wrcoutput.h \
	wrctools_libbfio.h \
	wrctools_libcerror.h \
	wrctools_libclocale.h \
	wrctools_libcnotify.h \
	wrctools_libcstring.h \
	wrctools_libcsystem.h \
	wrctools_libexe.h \
	wrctools_libfdatetime.h \
	wrctools_libfwnt.h \
	wrctools_libuna.h \
	wrctools_libwrc.h \
	info_handle.c info_handle.h

wrcinfo_LDADD = \
	@LIBCSYSTEM_LIBADD@ \
	@LIBEXE_LIBADD@ \
	@LIBFWNT_LIBADD@ \
	@LIBUNA_LIBADD@ \
	../libwrc/libwrc.la \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	@LIBCSTRING_LIBADD@ \
	@LIBINTL@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

splint:
	@echo "Running splint on wrcinfo ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(wrcinfo_SOURCES)

