dnl Function to detect if libwrc dependencies are available
AC_DEFUN([AX_LIBWRC_CHECK_LOCAL],
 [dnl Check for internationalization functions in libwrc/libwrc_i18n.c 
 AC_CHECK_FUNCS([bindtextdomain])
 ])

