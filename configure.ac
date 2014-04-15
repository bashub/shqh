#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT(shqh, 0.90)
AM_INIT_AUTOMAKE()

AC_CONFIG_SRCDIR([shqh.c])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC
PKG_CHECK_MODULES([CHECK],[check >= 0.9.4])
# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h string.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_CHECK_FUNCS([strstr])
AC_CHECK_LIB([leveldb],[leveldb_open])


AC_CONFIG_FILES([Makefile])
AC_OUTPUT
