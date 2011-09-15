dnl managedFlu - OpenFOAM C++ interactive functionality API
dnl Copyright (C) 2011- Alexey Petrov
dnl 
dnl This program is free software: you can redistribute it and/or modify
dnl it under the terms of the GNU General Public License as published by
dnl the Free Software Foundation, either version 3 of the License, or
dnl (at your option) any later version.
dnl
dnl This program is distributed in the hope that it will be useful,
dnl but WITHOUT ANY WARRANTY; without even the implied warranty of
dnl MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
dnl GNU General Public License for more details.
dnl 
dnl You should have received a copy of the GNU General Public License
dnl along with this program.  If not, see <http://www.gnu.org/licenses/>.
dnl 
dnl See http://sourceforge.net/projects/managedflu
dnl
dnl Author : Alexey PETROV, Andrey SIMURZIN
dnl


dnl --------------------------------------------------------------------------------
AC_DEFUN([MANAGEDFLU_CHECK_MANAGEDFLU],
[
AC_CHECKING(for managedFlu package)

AC_REQUIRE([CONFFLU_CHECK_OPENFOAM])

MANAGEDFLU_CPPFLAGS=""
AC_SUBST(MANAGEDFLU_CPPFLAGS)

MANAGEDFLU_CXXFLAGS=""
AC_SUBST(MANAGEDFLU_CXXFLAGS)

MANAGEDFLU_LDFLAGS=""
AC_SUBST(MANAGEDFLU_LDFLAGS)

MANAGEDFLU_LIBS=""
AC_SUBST(MANAGEDFLU_LIBS)

AC_SUBST(ENABLE_MANAGEDFLU)

managedflu_ok=no

dnl --------------------------------------------------------------------------------
AC_ARG_WITH( [managedflu-includes],
             AC_HELP_STRING( [--with-managedflu-includes=<path>],
                             [use <path> to look for managedflu headers] ),
             [],
             [with_managedflu_includes=""])
   
managedflu_header_dir=${with_managedflu_includes}

if test "x${with_managedflu_includes}" = "x" ; then
   if test ! "x${TEST_MM_ROOT_DIR}" = "x" && test -d ${TEST_MM_ROOT_DIR} ; then
      managedflu_header_dir=${TEST_MM_ROOT_DIR}/libs
   fi
fi

AC_CHECK_FILE( [${managedflu_header_dir}/DependentHolder.hpp], [ managedflu_includes=yes ], [ managedflu_includes=no ] )

dnl if test "x${managedflu_includes}" = "xno" ; then
dnl    managedflu_header_dir=/usr/local/include/managedflu/libs
dnl   AC_CHECK_FILE( [${managedflu_header_dir}/DependentHolder.hpp], [ managedflu_includes=yes ], [ managedflu_includes=no ] )
dnl fi

if test "x${managedflu_includes}" = "xyes" ; then
   MANAGEDFLU_CPPFLAGS="-I${managedflu_header_dir} -I${managedflu_header_dir}/lnInclude"
   CPPFLAGS=${MANAGEDFLU_CPPFLAGS}
fi

if test "x${managedflu_includes}" = "xno" ; then
   AC_MSG_WARN( [use --with-managedflu-includes=<path> to define path to managedflu libraries] )
fi


dnl --------------------------------------------------------------------------------
AC_ARG_WITH( [managedflu-libraries],
             AC_HELP_STRING( [--with-managedflu-libraries=<path>],
                             [use <path> to look for managedflu libraries] ),
             [],
             [with_managedflu_libraries=""])

managedflu_libraries_dir=${with_managedflu_libraries}

if test "x${with_managedflu_libraries}" = "x" ; then
   if test ! "x${TEST_MM_ROOT_DIR}" = "x" && test -d ${TEST_MM_ROOT_DIR} ; then
      managedflu_libraries_dir="${TEST_MM_ROOT_DIR}/libs"
   fi
fi

AC_CHECK_FILE( [${managedflu_libraries_dir}/libtestFixingBug.so], [ managedflu_libraries=yes ], [ managedflu_libraries=no ] )

dnl if test "x${managedflu_libraries}" = "xno" ; then
dnl   managedflu_libraries_dir=/usr/local/lib
dnl   AC_CHECK_FILE( [${managedflu_libraries_dir}/libtestFixingBug.so], [ managedflu_libraries=yes ], [ managedflu_libraries=no ] )
dnl fi

if test "x${managedflu_libraries}" = "xno" ; then
  managedflu_libraries_dir=${FOAM_USER_LIBBIN}
  AC_CHECK_FILE( [${managedflu_libraries_dir}/libtestFixingBug.so], [ managedflu_libraries=yes ], [ managedflu_libraries=no ] )
fi

if test "x${managedflu_libraries}" = "xyes" ; then
   MANAGEDFLU_LDFLAGS="-L${managedflu_libraries_dir}"
   MANAGEDFLU_LIBS="-ltestFixingBug -lcompressibleTurbulenceHolders -lincompressibleTurbulenceHolders"
fi

if test "x${managedflu_libraries}" = "xno" ; then
   AC_MSG_WARN( [use --with-managedflu-libraries=<path> to define path to managedflu libraries] )
fi
dnl --------------------------------------------------------------------------------
if test "${managedflu_libraries}" = "yes" && test "${managedflu_includes}" = "yes"; then 
   managedflu_ok=yes
fi

ENABLE_MANAGEDFLU=${managedflu_ok}

AC_MSG_NOTICE( @ENABLE_MANAGEDFLU@ == "${ENABLE_MANAGEDFLU}" )

AC_MSG_NOTICE( @MANAGEDFLU_CXXFLAGS@ == "${MANAGEDFLU_CXXFLAGS}" )

AC_MSG_NOTICE( @MANAGEDFLU_CPPFLAGS@ == "${MANAGEDFLU_CPPFLAGS}" )

AC_MSG_NOTICE( @MANAGEDFLU_LDFLAGS@ == "${MANAGEDFLU_LDFLAGS}" )

AC_MSG_NOTICE( @MANAGEDFLU_LIBS@ == "${MANAGEDFLU_LIBS}" )

])


dnl --------------------------------------------------------------------------------
