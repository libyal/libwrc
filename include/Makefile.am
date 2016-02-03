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
	/bin/rm -f libwrc.h
	/bin/rm -f libwrc/definitions.h
	/bin/rm -f libwrc/features.h
	/bin/rm -f libwrc/types.h
	/bin/rm -f Makefile

