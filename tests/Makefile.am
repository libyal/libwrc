AUTOMAKE_OPTIONS = subdir-objects

AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCDATA_CPPFLAGS@ \
	@LIBCTHREADS_CPPFLAGS@ \
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
	@LIBFGUID_CPPFLAGS@ \
	@LIBFVALUE_CPPFLAGS@ \
	@LIBFWNT_CPPFLAGS@ \
	@PTHREAD_CPPFLAGS@ \
	@LIBWRC_DLL_IMPORT@

if HAVE_PYTHON_TESTS
TESTS_PYWRC = \
	test_python_module.sh
endif

TESTS = \
	test_library.sh \
	test_wrcinfo.sh \
	$(TESTS_PYWRC)

check_SCRIPTS = \
	pywrc_test_manifest_resource.py \
	pywrc_test_message_table_resource.py \
	pywrc_test_mui_resource.py \
	pywrc_test_stream.py \
	pywrc_test_string_table_resource.py \
	pywrc_test_support.py \
	pywrc_test_version_information_resource.py \
	test_library.sh \
	test_manpage.sh \
	test_python_module.sh \
	test_runner.sh \
	test_wrcinfo.sh

EXTRA_DIST = \
	$(check_SCRIPTS)

check_PROGRAMS = \
	wrc_test_data_descriptor \
	wrc_test_error \
	wrc_test_io_handle \
	wrc_test_language_entry \
	wrc_test_language_table \
	wrc_test_manifest_resource \
	wrc_test_message_table_resource \
	wrc_test_mui_resource \
	wrc_test_mui_values \
	wrc_test_notify \
	wrc_test_resource \
	wrc_test_resource_item \
	wrc_test_resource_node_entry \
	wrc_test_resource_node_header \
	wrc_test_stream \
	wrc_test_string_table_resource \
	wrc_test_support \
	wrc_test_table_entry \
	wrc_test_version_information_resource \
	wrc_test_version_values

wrc_test_data_descriptor_SOURCES = \
	wrc_test_data_descriptor.c \
	wrc_test_functions.c wrc_test_functions.h \
	wrc_test_libbfio.h \
	wrc_test_libcerror.h \
	wrc_test_libwrc.h \
	wrc_test_macros.h \
	wrc_test_memory.c wrc_test_memory.h \
	wrc_test_unused.h

wrc_test_data_descriptor_LDADD = \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libwrc/libwrc.la \
	@LIBCERROR_LIBADD@

wrc_test_error_SOURCES = \
	wrc_test_error.c \
	wrc_test_libwrc.h \
	wrc_test_macros.h \
	wrc_test_unused.h

wrc_test_error_LDADD = \
	../libwrc/libwrc.la

wrc_test_io_handle_SOURCES = \
	wrc_test_io_handle.c \
	wrc_test_libcerror.h \
	wrc_test_libwrc.h \
	wrc_test_macros.h \
	wrc_test_memory.c wrc_test_memory.h \
	wrc_test_unused.h

wrc_test_io_handle_LDADD = \
	../libwrc/libwrc.la \
	@LIBCERROR_LIBADD@

wrc_test_language_entry_SOURCES = \
	wrc_test_language_entry.c \
	wrc_test_libcerror.h \
	wrc_test_libwrc.h \
	wrc_test_macros.h \
	wrc_test_memory.c wrc_test_memory.h \
	wrc_test_unused.h

wrc_test_language_entry_LDADD = \
	../libwrc/libwrc.la \
	@LIBCERROR_LIBADD@

wrc_test_language_table_SOURCES = \
	wrc_test_language_table.c \
	wrc_test_libcerror.h \
	wrc_test_libwrc.h \
	wrc_test_macros.h \
	wrc_test_memory.c wrc_test_memory.h \
	wrc_test_unused.h

wrc_test_language_table_LDADD = \
	../libwrc/libwrc.la \
	@LIBCERROR_LIBADD@

wrc_test_manifest_resource_SOURCES = \
	wrc_test_libcerror.h \
	wrc_test_libwrc.h \
	wrc_test_macros.h \
	wrc_test_manifest_resource.c \
	wrc_test_memory.c wrc_test_memory.h \
	wrc_test_unused.h

wrc_test_manifest_resource_LDADD = \
	../libwrc/libwrc.la \
	@LIBCERROR_LIBADD@

wrc_test_message_table_resource_SOURCES = \
	wrc_test_libcerror.h \
	wrc_test_libwrc.h \
	wrc_test_macros.h \
	wrc_test_memory.c wrc_test_memory.h \
	wrc_test_message_table_resource.c \
	wrc_test_unused.h

wrc_test_message_table_resource_LDADD = \
	../libwrc/libwrc.la \
	@LIBCERROR_LIBADD@

wrc_test_mui_resource_SOURCES = \
	wrc_test_libcerror.h \
	wrc_test_libwrc.h \
	wrc_test_macros.h \
	wrc_test_memory.c wrc_test_memory.h \
	wrc_test_mui_resource.c \
	wrc_test_unused.h

wrc_test_mui_resource_LDADD = \
	../libwrc/libwrc.la \
	@LIBCERROR_LIBADD@

wrc_test_mui_values_SOURCES = \
	wrc_test_libcerror.h \
	wrc_test_libwrc.h \
	wrc_test_macros.h \
	wrc_test_memory.c wrc_test_memory.h \
	wrc_test_mui_values.c \
	wrc_test_unused.h

wrc_test_mui_values_LDADD = \
	../libwrc/libwrc.la \
	@LIBCERROR_LIBADD@

wrc_test_notify_SOURCES = \
	wrc_test_libcerror.h \
	wrc_test_libwrc.h \
	wrc_test_macros.h \
	wrc_test_notify.c \
	wrc_test_unused.h

wrc_test_notify_LDADD = \
	../libwrc/libwrc.la \
	@LIBCERROR_LIBADD@

wrc_test_resource_SOURCES = \
	wrc_test_libcdata.h \
	wrc_test_libcerror.h \
	wrc_test_libwrc.h \
	wrc_test_macros.h \
	wrc_test_memory.c wrc_test_memory.h \
	wrc_test_resource.c \
	wrc_test_unused.h

wrc_test_resource_LDADD = \
	@LIBCDATA_LIBADD@ \
	../libwrc/libwrc.la \
	@LIBCERROR_LIBADD@

wrc_test_resource_item_SOURCES = \
	wrc_test_libcdata.h \
	wrc_test_libcerror.h \
	wrc_test_libwrc.h \
	wrc_test_macros.h \
	wrc_test_memory.c wrc_test_memory.h \
	wrc_test_resource_item.c \
	wrc_test_unused.h

wrc_test_resource_item_LDADD = \
	@LIBCDATA_LIBADD@ \
	../libwrc/libwrc.la \
	@LIBCERROR_LIBADD@

wrc_test_resource_node_entry_SOURCES = \
	wrc_test_functions.c wrc_test_functions.h \
	wrc_test_libbfio.h \
	wrc_test_libcerror.h \
	wrc_test_libwrc.h \
	wrc_test_macros.h \
	wrc_test_memory.c wrc_test_memory.h \
	wrc_test_resource_node_entry.c \
	wrc_test_unused.h

wrc_test_resource_node_entry_LDADD = \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libwrc/libwrc.la \
	@LIBCERROR_LIBADD@

wrc_test_resource_node_header_SOURCES = \
	wrc_test_functions.c wrc_test_functions.h \
	wrc_test_libbfio.h \
	wrc_test_libcerror.h \
	wrc_test_libwrc.h \
	wrc_test_macros.h \
	wrc_test_memory.c wrc_test_memory.h \
	wrc_test_resource_node_header.c \
	wrc_test_unused.h

wrc_test_resource_node_header_LDADD = \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libwrc/libwrc.la \
	@LIBCERROR_LIBADD@

wrc_test_stream_SOURCES = \
	wrc_test_functions.c wrc_test_functions.h \
	wrc_test_getopt.c wrc_test_getopt.h \
	wrc_test_libbfio.h \
	wrc_test_libcerror.h \
	wrc_test_libclocale.h \
	wrc_test_libcnotify.h \
	wrc_test_libuna.h \
	wrc_test_libwrc.h \
	wrc_test_macros.h \
	wrc_test_memory.c wrc_test_memory.h \
	wrc_test_stream.c \
	wrc_test_unused.h

wrc_test_stream_LDADD = \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libwrc/libwrc.la \
	@LIBCTHREADS_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	@PTHREAD_LIBADD@

wrc_test_string_table_resource_SOURCES = \
	wrc_test_libcerror.h \
	wrc_test_libwrc.h \
	wrc_test_macros.h \
	wrc_test_memory.c wrc_test_memory.h \
	wrc_test_string_table_resource.c \
	wrc_test_unused.h

wrc_test_string_table_resource_LDADD = \
	../libwrc/libwrc.la \
	@LIBCERROR_LIBADD@

wrc_test_support_SOURCES = \
	wrc_test_libcerror.h \
	wrc_test_libwrc.h \
	wrc_test_macros.h \
	wrc_test_support.c \
	wrc_test_unused.h

wrc_test_support_LDADD = \
	../libwrc/libwrc.la \
	@LIBCERROR_LIBADD@

wrc_test_table_entry_SOURCES = \
	wrc_test_libcerror.h \
	wrc_test_libwrc.h \
	wrc_test_macros.h \
	wrc_test_memory.c wrc_test_memory.h \
	wrc_test_table_entry.c \
	wrc_test_unused.h

wrc_test_table_entry_LDADD = \
	../libwrc/libwrc.la \
	@LIBCERROR_LIBADD@

wrc_test_version_information_resource_SOURCES = \
	wrc_test_libcerror.h \
	wrc_test_libwrc.h \
	wrc_test_macros.h \
	wrc_test_memory.c wrc_test_memory.h \
	wrc_test_unused.h \
	wrc_test_version_information_resource.c

wrc_test_version_information_resource_LDADD = \
	../libwrc/libwrc.la \
	@LIBCERROR_LIBADD@

wrc_test_version_values_SOURCES = \
	wrc_test_libcerror.h \
	wrc_test_libwrc.h \
	wrc_test_macros.h \
	wrc_test_memory.c wrc_test_memory.h \
	wrc_test_unused.h \
	wrc_test_version_values.c

wrc_test_version_values_LDADD = \
	../libwrc/libwrc.la \
	@LIBCERROR_LIBADD@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	-rm -f Makefile

