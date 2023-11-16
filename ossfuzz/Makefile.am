if HAVE_LIB_FUZZING_ENGINE
AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCDATA_CPPFLAGS@ \
	@LIBCLOCALE_CPPFLAGS@ \
	@LIBCNOTIFY_CPPFLAGS@ \
	@LIBUNA_CPPFLAGS@ \
	@LIBCFILE_CPPFLAGS@ \
	@LIBCPATH_CPPFLAGS@ \
	@LIBBFIO_CPPFLAGS@

bin_PROGRAMS = \
	manifest_resource_fuzzer \
	message_table_resource_fuzzer \
	mui_resource_fuzzer \
	stream_fuzzer \
	string_table_resource_fuzzer \
	version_information_resource_fuzzer

manifest_resource_fuzzer_SOURCES = \
	manifest_resource_fuzzer.cc \
	ossfuzz_libwrc.h

manifest_resource_fuzzer_LDADD = \
	@LIB_FUZZING_ENGINE@ \
	../libwrc/libwrc.la

message_table_resource_fuzzer_SOURCES = \
	message_table_resource_fuzzer.cc \
	ossfuzz_libwrc.h

message_table_resource_fuzzer_LDADD = \
	@LIB_FUZZING_ENGINE@ \
	../libwrc/libwrc.la

mui_resource_fuzzer_SOURCES = \
	mui_resource_fuzzer.cc \
	ossfuzz_libwrc.h

mui_resource_fuzzer_LDADD = \
	@LIB_FUZZING_ENGINE@ \
	../libwrc/libwrc.la

stream_fuzzer_SOURCES = \
	ossfuzz_libbfio.h \
	ossfuzz_libwrc.h \
	stream_fuzzer.cc

stream_fuzzer_LDADD = \
	@LIB_FUZZING_ENGINE@ \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libwrc/libwrc.la \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	@LIBINTL@

string_table_resource_fuzzer_SOURCES = \
	ossfuzz_libwrc.h \
	string_table_resource_fuzzer.cc

string_table_resource_fuzzer_LDADD = \
	@LIB_FUZZING_ENGINE@ \
	../libwrc/libwrc.la

version_information_resource_fuzzer_SOURCES = \
	ossfuzz_libwrc.h \
	version_information_resource_fuzzer.cc

version_information_resource_fuzzer_LDADD = \
	@LIB_FUZZING_ENGINE@ \
	../libwrc/libwrc.la
endif

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	-rm -f Makefile

splint-local:
	@echo "Running splint on file_fuzzer ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(file_fuzzer_SOURCES)

