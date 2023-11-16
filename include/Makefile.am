include_HEADERS = \
	libwrc.h

pkginclude_HEADERS = \
	libwrc/codepage.h \
	libwrc/definitions.h \
	libwrc/error.h \
	libwrc/extern.h \
	libwrc/features.h \
	libwrc/types.h

EXTRA_DIST = \
	libwrc.h.in \
	libwrc/definitions.h.in \
	libwrc/features.h.in \
	libwrc/types.h.in

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	-rm -f libwrc.h
	-rm -f libwrc/definitions.h
	-rm -f libwrc/features.h
	-rm -f libwrc/types.h
	-rm -f Makefile

