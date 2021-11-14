#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([rhasher], [1.0], [maximelianos.m@gmail.com])
AC_CONFIG_SRCDIR([rhasher.c])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC
AM_INIT_AUTOMAKE

AC_ARG_WITH([readline],
    [AS_HELP_STRING([--with-readline],
        [support readline])],
    [],
    [with_readline=yes])
    

AS_IF(
    [test "x$with_readline" != xno],
    [
        AC_CHECK_LIB(
            [readline], 
            [main],
            [],
            [if test "x$with_readline" != xcheck; then
                AC_MSG_FAILURE(
                [--with-readline was given, but test for readline failed])
            fi]
        )
    ]
)

# Checks for libraries.
AC_CHECK_LIB([rhash], [rhash_library_init], [], [
	AC_MSG_ERROR([Unable to find librhash])
])

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h string.h unistd.h])
AC_CHECK_HEADER([rhash.h], [], [], [
	AC_MSG_ERROR([Unable to find rhash.h])
])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([strcasecmp])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
