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
AC_DEFUN([MANAGEDFLU_CHECK_OPENFOAM],
[
AC_CHECKING(for OpenFOAM package)

AC_REQUIRE([CONFFLU_CHECK_OPENFOAM])

MANAGEDFLU_HEADER_SUFFIX="unknown"

AC_SUBST(MANAGEDFLU_HEADER_SUFFIX)

case "x${FOAM_BRANCH}" in
xfree )
  if test ${FOAM_VERSION} -le 010701; then
      MANAGEDFLU_HEADER_SUFFIX="${FOAM_VERSION}_${FOAM_BRANCH}"
  fi
;;
xdev )
  if test ${FOAM_VERSION} -le 010600; then
      MANAGEDFLU_HEADER_SUFFIX="${FOAM_VERSION}_${FOAM_BRANCH}"
  fi
;;
*)
  if test ${FOAM_VERSION} -le 020000; then
      MANAGEDFLU_HEADER_SUFFIX="${FOAM_VERSION}"
  fi
;;
esac

AC_MSG_NOTICE( @MANAGEDFLU_HEADER_SUFFIX@ == "${MANAGEDFLU_HEADER_SUFFIX}" )

])


dnl --------------------------------------------------------------------------------
