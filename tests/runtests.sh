#!/bin/sh
# Script to run tests
#
# Version: 20260714

if [ -f "${PWD}/libwrc/.libs/libwrc.1.dylib" ] && [ -f ./pywrc/.libs/pywrc.so ]
then
    install_name_tool -change /usr/local/lib/libwrc.1.dylib "${PWD}/libwrc/.libs/libwrc.1.dylib" ./pywrc/.libs/pywrc.so
fi

make check-build > /dev/null

# shellcheck disable=SC2068
make check $@
RESULT=$?

if [ ${RESULT} -ne 0 ]
then
    find . -name \*.log -path \*.dir/\*/\*.log -print -exec cat {} \;
fi
exit ${RESULT}

