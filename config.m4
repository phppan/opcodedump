dnl $Id$
dnl config.m4 for extension opcodedump

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(opcodedump, for opcodedump support,
dnl Make sure that the comment is aligned:
dnl [  --with-opcodedump             Include opcodedump support])

dnl Otherwise use enable:

dnl PHP_ARG_ENABLE(opcodedump, whether to enable opcodedump support,
dnl Make sure that the comment is aligned:
dnl [  --enable-opcodedump           Enable opcodedump support])

if test "$PHP_OPCODEDUMP" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-opcodedump -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/opcodedump.h"  # you most likely want to change this
  dnl if test -r $PHP_OPCODEDUMP/$SEARCH_FOR; then # path given as parameter
  dnl   OPCODEDUMP_DIR=$PHP_OPCODEDUMP
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for opcodedump files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       OPCODEDUMP_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$OPCODEDUMP_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the opcodedump distribution])
  dnl fi

  dnl # --with-opcodedump -> add include path
  dnl PHP_ADD_INCLUDE($OPCODEDUMP_DIR/include)

  dnl # --with-opcodedump -> check for lib and symbol presence
  dnl LIBNAME=opcodedump # you may want to change this
  dnl LIBSYMBOL=opcodedump # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $OPCODEDUMP_DIR/$PHP_LIBDIR, OPCODEDUMP_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_OPCODEDUMPLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong opcodedump lib version or lib not found])
  dnl ],[
  dnl   -L$OPCODEDUMP_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(OPCODEDUMP_SHARED_LIBADD)

  PHP_NEW_EXTENSION(opcodedump, opcodedump.c, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
fi
