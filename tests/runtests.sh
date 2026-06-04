#!/bin/sh
# Script to run tests
#
# Version: 20260602

if test -f ${PWD}/libwrc/.libs/libwrc.1.dylib && test -f ./pywrc/.libs/pywrc.so
then
	install_name_tool -change /usr/local/lib/libwrc.1.dylib ${PWD}/libwrc/.libs/libwrc.1.dylib ./pywrc/.libs/pywrc.so
fi

make check $@
RESULT=$?

if test ${RESULT} -ne 0 && test -f tests/test-suite.log
then
	cat tests/test-suite.log
fi
exit ${RESULT}

