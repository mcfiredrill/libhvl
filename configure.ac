#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.65])
AC_INIT([libhvl], [0.1], [mcfiredrill@gmail.com])
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE([1.10 -Wall no-define foreign])
AC_CONFIG_MACRO_DIR([m4])

AC_LANG([C])

# Remove the check for c++ and fortran compiler
m4_defun([_LT_AC_LANG_CXX_CONFIG], [:])
m4_defun([_LT_AC_LANG_F77_CONFIG], [:])

# Checks for programs.
AC_PROG_CC
LT_INIT([disable-static])

AC_SUBST([HVL_SO_VERSION], [0:0:0])
AC_SUBST([HVL_API_VERSION], [1.0])

# Checks for libraries.
AC_CHECK_LIB([SDL], [SDL_Init])

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h string.h strings.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_INLINE
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([memset])

AC_CONFIG_FILES([Makefile hvl.pc:hvl.pc.in])

AC_OUTPUT
