#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([Game], [0.0.1], [wytau@sdf.org])
AC_CONFIG_SRCDIR([src/main.cpp])
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AC_CONFIG_MACRO_DIR([m4])

# Checks for programs.
AC_PROG_CXX

# Checks for libraries.
PKG_CHECK_MODULES([sdl2], sdl2, [], AC_MSG_ERROR([Failed to find sdl2]))
PKG_CHECK_MODULES([glm], glm, [], AC_MSG_ERROR([Failed to find glm - OpenGL Mathmatics]))
PKG_CHECK_MODULES([glew], glew, [], AC_MSG_ERROR([Failed to find glew - OpenGL Extention Wrangler]))
PKG_CHECK_MODULES([opengl], gl, [], AC_MSG_ERROR([Failed to find OpenGL]))

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL

# Checks for library functions.

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
