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
	@LIBFCACHE_CPPFLAGS@ \
	@LIBFDATA_CPPFLAGS@ \
	@LIBFDATETIME_CPPFLAGS@ \
	@LIBFGUID_CPPFLAGS@ \
	@LIBFVALUE_CPPFLAGS@ \
	@LIBFWNT_CPPFLAGS@ \
	@PTHREAD_CPPFLAGS@ \
	@LIBWRC_DLL_EXPORT@

lib_LTLIBRARIES = libwrc.la

libwrc_la_SOURCES = \
	libwrc.c \
	libwrc_codepage.h \
	libwrc_data_descriptor.c libwrc_data_descriptor.h \
	libwrc_debug.c libwrc_debug.h \
	libwrc_definitions.h \
	libwrc_error.c libwrc_error.h \
	libwrc_extern.h \
	libwrc_io_handle.c libwrc_io_handle.h \
	libwrc_language_entry.c libwrc_language_entry.h \
	libwrc_language_table.c libwrc_language_table.h \
	libwrc_libbfio.h \
	libwrc_libcdata.h \
	libwrc_libcerror.h \
	libwrc_libclocale.h \
	libwrc_libcnotify.h \
	libwrc_libfcache.h \
	libwrc_libfdata.h \
	libwrc_libfguid.h \
	libwrc_libfvalue.h \
	libwrc_libfwnt.h \
	libwrc_libuna.h \
	libwrc_manifest_resource.c libwrc_manifest_resource.h \
	libwrc_manifest_values.c libwrc_manifest_values.h \
	libwrc_message_table_resource.c libwrc_message_table_resource.h \
	libwrc_message_table_values.c libwrc_message_table_values.h \
	libwrc_mui_resource.c libwrc_mui_resource.h \
	libwrc_mui_values.c libwrc_mui_values.h \
	libwrc_notify.c libwrc_notify.h \
	libwrc_resource.c libwrc_resource.h \
	libwrc_resource_item.c libwrc_resource_item.h \
	libwrc_resource_node_entry.c libwrc_resource_node_entry.h \
	libwrc_resource_node_header.c libwrc_resource_node_header.h \
	libwrc_resource_node_tree.c libwrc_resource_node_tree.h \
	libwrc_stream.c libwrc_stream.h \
	libwrc_support.c libwrc_support.h \
	libwrc_string_table_resource.c libwrc_string_table_resource.h \
	libwrc_string_values.c libwrc_string_values.h \
	libwrc_table_entry.c libwrc_table_entry.h \
	libwrc_types.h \
	libwrc_unused.h \
	libwrc_version_information_resource.c libwrc_version_information_resource.h \
	libwrc_version_values.c libwrc_version_values.h \
	wrc_data_descriptor.h \
	wrc_message_table_resource.h \
	wrc_mui_resource.h \
	wrc_resource_node.h \
	wrc_version_information_resource.h

libwrc_la_LIBADD = \
	@LIBCERROR_LIBADD@ \
	@LIBCTHREADS_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBBFIO_LIBADD@ \
	@LIBFCACHE_LIBADD@ \
	@LIBFDATA_LIBADD@ \
	@LIBFDATETIME_LIBADD@ \
	@LIBFGUID_LIBADD@ \
	@LIBFVALUE_LIBADD@ \
	@LIBFWNT_LIBADD@ \
	@PTHREAD_LIBADD@

libwrc_la_LDFLAGS = -no-undefined -version-info 1:0:0

EXTRA_DIST = \
	libwrc_definitions.h.in \
	libwrc.rc \
	libwrc.rc.in

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	-rm -f libwrc_definitions.h
	-rm -f libwrc.rc
	-rm -f Makefile

sources-local: $(BUILT_SOURCES)

splint-local:
	@echo "Running splint on libwrc ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(libwrc_la_SOURCES)

