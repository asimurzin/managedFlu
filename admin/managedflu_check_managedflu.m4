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

MANAGEDFLU_OPENFOAM_CPPFLAGS=""
AC_SUBST(MANAGEDFLU_OPENFOAM_CPPFLAGS)

MANAGEDFLU_FINITEVOLUME_CPPFLAGS=""
AC_SUBST(MANAGEDFLU_FINITEVOLUME_CPPFLAGS)

MANAGEDFLU_DYNAMICFVMESH_CPPFLAGS=""
AC_SUBST(MANAGEDFLU_DYNAMICFVMESH_CPPFLAGS)

MANAGEDFLU_RANDOMPROCESSES_CPPFLAGS=""
AC_SUBST(MANAGEDFLU_RANDOMPROCESSES_CPPFLAGS)

MANAGEDFLU_INCOMPRESSIBLETRANSPORTMODELS_CPPFLAGS=""
AC_SUBST(MANAGEDFLU_INCOMPRESSIBLETRANSPORTMODELS_CPPFLAGS)

MANAGEDFLU_INTERFACEPROPERTIES_CPPFLAGS=""
AC_SUBST(MANAGEDFLU_INTERFACEPROPERTIES_CPPFLAGS)

MANAGEDFLU_BASICTHERMOPHYSICALMODELS_CPPFLAGS=""
AC_SUBST(MANAGEDFLU_BASICTHERMOPHYSICALMODELS_CPPFLAGS)

MANAGEDFLU_BASICSOLIDTHERMO_CPPFLAGS=""
AC_SUBST(MANAGEDFLU_BASICSOLIDTHERMO_CPPFLAGS)

MANAGEDFLU_RADIATIONMODELS_CPPFLAGS=""
AC_SUBST(MANAGEDFLU_RADIATIONMODELS_CPPFLAGS)

MANAGEDFLU_COMPRESSIBLETURBULENSEMODELS_CPPFLAGS=""
AC_SUBST(MANAGEDFLU_COMPRESSIBLETURBULENSEMODELS_CPPFLAGS)

MANAGEDFLU_INCOMPRESSIBLETURBULENSEMODELS_CPPFLAGS=""
AC_SUBST(MANAGEDFLU_INCOMPRESSIBLETURBULENSEMODELS_CPPFLAGS)


MANAGEDFLU_CXXFLAGS=""
AC_SUBST(MANAGEDFLU_CXXFLAGS)

MANAGEDFLU_LDFLAGS=""
AC_SUBST(MANAGEDFLU_LDFLAGS)

MANAGEDFLU_LIB=""
AC_SUBST(MANAGEDFLU_LIB)

MANAGEDFLU_OPENFOAM_LIB=""
AC_SUBST(MANAGEDFLU_OPENFOAM_LIB)

MANAGEDFLU_FINITEVOLUME_LIB=""
AC_SUBST(MANAGEDFLU_FINITEVOLUME_LIB)

MANAGEDFLU_DYNAMICFVMESH_LIB=""
AC_SUBST(MANAGEDFLU_DYNAMICFVMESH_LIB)

MANAGEDFLU_RANDOMPROCESSES_LIB=""
AC_SUBST(MANAGEDFLU_RANDOMPROCESSES_LIB)

MANAGEDFLU_INCOMPRESSIBLETRANSPORTMODELS_LIB=""
AC_SUBST(MANAGEDFLU_INCOMPRESSIBLETRANSPORTMODELS_LIB)

MANAGEDFLU_INTERFACEPROPERTIES_LIB=""
AC_SUBST(MANAGEDFLU_INTERFACEPROPERTIES_LIB)

MANAGEDFLU_BASICTHERMOPHYSICALMODELS_LIB=""
AC_SUBST(MANAGEDFLU_BASICTHERMOPHYSICALMODELS_LIB)

MANAGEDFLU_BASICSOLIDTHERMO_LIB=""
AC_SUBST(MANAGEDFLU_BASICSOLIDTHERMO_LIB)

MANAGEDFLU_RADIATIONMODELS_LIB=""
AC_SUBST(MANAGEDFLU_RADIATIONMODELS_LIB)

MANAGEDFLU_COMPRESSIBLETURBULENSEMODELS_LIBS=""
AC_SUBST(MANAGEDFLU_COMPRESSIBLETURBULENSEMODELS_LIBS)

MANAGEDFLU_INCOMPRESSIBLETURBULENSEMODELS_LIBS=""
AC_SUBST(MANAGEDFLU_INCOMPRESSIBLETURBULENSEMODELS_LIBS)


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
   if test ! "x${MANAGEDFLU_ROOT_DIR}" = "x" && test -d ${MANAGEDFLU_ROOT_DIR} ; then
      managedflu_header_dir=${MANAGEDFLU_ROOT_DIR}/src
   fi
fi

AC_CHECK_FILE( [${managedflu_header_dir}/managedFlu/DependentHolder.hpp], [ managedflu_includes=yes ], [ managedflu_includes=no ] )

if test "x${managedflu_includes}" = "xyes" ; then
   MANAGEDFLU_CPPFLAGS="-I${managedflu_header_dir} -I${managedflu_header_dir}/managedFlu/lnInclude"
   
   MANAGEDFLU_OPENFOAM_CPPFLAGS="-I${managedflu_header_dir}/OpenFOAM/lnInclude"
   MANAGEDFLU_FINITEVOLUME_CPPFLAGS="-I${managedflu_header_dir}/finiteVolume/lnInclude"
   MANAGEDFLU_DYNAMICFVMESH_CPPFLAGS="-I${managedflu_header_dir}/dynamicFvMesh/lnInclude"
   MANAGEDFLU_RANDOMPROCESSES_CPPFLAGS="-I${managedflu_header_dir}/randomProcesses/lnInclude"
   MANAGEDFLU_INCOMPRESSIBLETRANSPORTMODELS_CPPFLAGS="-I${managedflu_header_dir}/transportModels/incompressible/lnInclude"
   MANAGEDFLU_INTERFACEPROPERTIES_CPPFLAGS="-I${managedflu_header_dir}/transportModels/interfaceProperties/lnInclude"
   MANAGEDFLU_BASICTHERMOPHYSICALMODELS_CPPFLAGS="-I${managedflu_header_dir}/thermophysicalModels/basic/lnInclude"
   MANAGEDFLU_BASICSOLIDTHERMO_CPPFLAGS="-I${managedflu_header_dir}/thermophysicalModels/basicSolidThermo/lnInclude"
   MANAGEDFLU_RADIATIONMODELS_CPPFLAGS="-I${managedflu_header_dir}/thermophysicalModels/radiationModel/lnInclude" 
   MANAGEDFLU_COMPRESSIBLETURBULENSEMODELS_CPPFLAGS="-I${managedflu_header_dir}/turbulenceModels/compressible/turbulenceModel/lnInclude -I${managedflu_header_dir}/turbulenceModels/compressible/RAS/lnInclude"
   MANAGEDFLU_INCOMPRESSIBLETURBULENSEMODELS_CPPFLAGS="-I${managedflu_header_dir}/turbulenceModels/incompressible/turbulenceModel/lnInclude -I${managedflu_header_dir}/turbulenceModels/incompressible/RAS/lnInclude  -I${managedflu_header_dir}/turbulenceModels/incompressible/LES/lnInclude"
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
   if test ! "x${MANAGEDFLU_ROOT_DIR}" = "x" && test -d ${MANAGEDFLU_ROOT_DIR} ; then
      managedflu_libraries_dir="${MANAGEDFLU_ROOT_DIR}/lib"
   fi
fi

AC_CHECK_FILE( [${managedflu_libraries_dir}/libmanagedFlu.so], [ managedflu_libraries=yes ], [ managedflu_libraries=no ] )


if test "x${managedflu_libraries}" = "xyes" ; then
   MANAGEDFLU_LDFLAGS="-L${managedflu_libraries_dir}"
   MANAGEDFLU_LIB="-lmanagedFlu"
   
   MANAGEDFLU_OPENFOAM_LIB="-lmanagedFlu-OpenFOAM"
   MANAGEDFLU_FINITEVOLUME_LIB="-lmanagedFlu-finiteVolume"
   MANAGEDFLU_DYNAMICFVMESH_LIB="-lmanagedFlu-dynamicFvMesh"
   MANAGEDFLU_RANDOMPROCESSES_LIB="-lmanagedFlu-randomProcesses"
   MANAGEDFLU_INCOMPRESSIBLETRANSPORTMODELS_LIB="-lmanagedFlu-incompressibleTransportModels"
   MANAGEDFLU_INTERFACEPROPERTIES_LIB="-lmanagedFlu-interfaceProperties"
   MANAGEDFLU_BASICTHERMOPHYSICALMODELS_LIB="-lmanagedFlu-basicThermophysicalModels"
   MANAGEDFLU_BASICSOLIDTHERMO_LIB="-lmanagedFlu-basicSolidThermo"
   MANAGEDFLU_RADIATIONMODELS_LIB="-lmanagedFlu-radiationModels"
   MANAGEDFLU_COMPRESSIBLETURBULENSEMODELS_LIBS="-lmanagedFlu-compressibleTurbulenceModel -lmanagedFlu-compressibleRASModels"
   MANAGEDFLU_INCOMPRESSIBLETURBULENSEMODELS_LIBS="-lmanagedFlu-incompressibleTurbulenceModel -lmanagedFlu-incompressibleRASModels -lmanagedFlu-incompressibleLESModels"
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
  
AC_MSG_NOTICE( @MANAGEDFLU_OPENFOAM_CPPFLAGS@ =="${MANAGEDFLU_OPENFOAM_CPPFLAGS}" )

AC_MSG_NOTICE( @MANAGEDFLU_FINITEVOLUME_CPPFLAGS@ == "${MANAGEDFLU_FINITEVOLUME_CPPFLAGS}" )

AC_MSG_NOTICE( @MANAGEDFLU_INCOMPRESSIBLETRANSPORTMODELS_CPPFLAGS@ == "${MANAGEDFLU_INCOMPRESSIBLETRANSPORTMODELS_CPPFLAGS}" )

AC_MSG_NOTICE( @MANAGEDFLU_BASICTHERMOPHYSICALMODELS_CPPFLAGS@ == "${MANAGEDFLU_BASICTHERMOPHYSICALMODELS_CPPFLAGS}" )

AC_MSG_NOTICE( @MANAGEDFLU_RADIATIONMODELS_CPPFLAGS@ == "${MANAGEDFLU_RADIATIONMODELS_CPPFLAGS}" )

AC_MSG_NOTICE( @MANAGEDFLU_COMPRESSIBLETURBULENSEMODELS_CPPFLAGS@ == "${MANAGEDFLU_COMPRESSIBLETURBULENSEMODELS_CPPFLAGS}" )

AC_MSG_NOTICE( @MANAGEDFLU_INCOMPRESSIBLETURBULENSEMODELS_CPPFLAGS@ == "${MANAGEDFLU_INCOMPRESSIBLETURBULENSEMODELS_CPPFLAGS}" )

AC_MSG_NOTICE( @MANAGEDFLU_LDFLAGS@ == "${MANAGEDFLU_LDFLAGS}" )

AC_MSG_NOTICE( @MANAGEDFLU_LIB@ == "${MANAGEDFLU_LIB}" )

AC_MSG_NOTICE( @MANAGEDFLU_OPENFOAM_LIB@ =="${MANAGEDFLU_OPENFOAM_LIB}" )

AC_MSG_NOTICE( @MANAGEDFLU_FINITEVOLUME_LIB@ == "${MANAGEDFLU_FINITEVOLUME_LIB}" )

AC_MSG_NOTICE( @MANAGEDFLU_INCOMPRESSIBLETRANSPORTMODELS_LIB@ == "${MANAGEDFLU_INCOMPRESSIBLETRANSPORTMODELS_LIB}" )

AC_MSG_NOTICE( @MANAGEDFLU_BASICTHERMOPHYSICALMODELS_LIB@ == "${MANAGEDFLU_BASICTHERMOPHYSICALMODELS_LIB}" )

AC_MSG_NOTICE( @MANAGEDFLU_RADIATIONMODELS_LIB@ == "${MANAGEDFLU_RADIATIONMODELS_LIB}" )

AC_MSG_NOTICE( @MANAGEDFLU_COMPRESSIBLETURBULENSEMODELS_LIBS@ == "${MANAGEDFLU_COMPRESSIBLETURBULENSEMODELS_LIBS}" )

AC_MSG_NOTICE( @MANAGEDFLU_INCOMPRESSIBLETURBULENSEMODELS_LIBS@ == "${MANAGEDFLU_INCOMPRESSIBLETURBULENSEMODELS_LIBS}" )


])


dnl --------------------------------------------------------------------------------
