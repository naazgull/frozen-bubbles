
AC_PREREQ(2.59)
AC_INIT(frozen-bubbles, 0.0.1-1, developer-email)

AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_AUX_DIR([.])

dnl Check for libraries
AC_HAVE_LIBRARY(dl)
AC_HAVE_LIBRARY(pthread)
AC_HAVE_LIBRARY(magic)
AC_HAVE_LIBRARY(z)
AC_HAVE_LIBRARY(ssl)
AC_HAVE_LIBRARY(crypto)
# AC_HAVE_LIBRARY(mongoclient)
# AC_HAVE_LIBRARY(boost_system)
# AC_HAVE_LIBRARY(boost_program_options)
# AC_HAVE_LIBRARY(boost_thread)
# AC_HAVE_LIBRARY(boost_filesystem)
# AC_HAVE_LIBRARY(hiredis)
# AC_HAVE_LIBRARY(zmq)
# AC_HAVE_LIBRARY(ossp-uuid++)
# AC_HAVE_LIBRARY(zapata-base)
# AC_HAVE_LIBRARY(zapata-json)
# AC_HAVE_LIBRARY(zapata-events)
# AC_HAVE_LIBRARY(zapata-zmq)
# AC_HAVE_LIBRARY(zapata-http)
# AC_HAVE_LIBRARY(zapata-rest)

AC_CANONICAL_SYSTEM

dnl Create config.h header file
AH_TOP([#include <frbb/unconfig.h>])
AC_CONFIG_HEADERS([include/frbb/config.h])

dnl Initialize automake
AM_INIT_AUTOMAKE([subdir-objects tar-pax])

dnl this allows us specify individual liking flags for each target
AC_PROG_CXX
AM_PROG_CC_C_O 

dnl Initialize Libtool
LT_INIT

dnl Check if Libtool is present
dnl Libtool is used for building share libraries 
AC_PROG_LIBTOOL

AC_CONFIG_FILES(Makefile
		debian/Makefile
		etc/Makefile
                include/Makefile
		src/Makefile)
AC_OUTPUT
