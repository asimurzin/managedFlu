//  Copyright (C) 2010- Alexey Petrov
//  Copyright (C) 2009-2010 Pebble Bed Modular Reactor (Pty) Limited (PBMR)
//  
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//  
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//  
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
//  See http://sourceforge.net/projects/pythonflu
//
//  Author : Alexey PETROV


//---------------------------------------------------------------------------
#ifndef GeometricFieldHolder_hxx
#define GeometricFieldHolder_hxx


//---------------------------------------------------------------------------
%include "GeometricFieldHolder.H"
%import "GeometricFieldFunctions.hxx"


//---------------------------------------------------------------------------
%define GEOMETRIC_FIELDHOLDER_TYPEMAP( Type, TPatchField, TMesh )

%typecheck( SWIG_TYPECHECK_POINTER ) Foam::GeometricFieldHolder< Type, TPatchField, TMesh >& 
{
  void *ptr;
  
  int res_Holder = SWIG_ConvertPtr( $input, (void **) &ptr, $descriptor( Foam::GeometricFieldHolder< Type, TPatchField, TMesh > * ), 0 );
  int res_T = SWIG_ConvertPtr( $input, (void **) &ptr, $descriptor( Foam::GeometricField< Type, TPatchField, TMesh > * ), 0 );
  int res_tmpT = SWIG_ConvertPtr( $input, (void **) &ptr, $descriptor( Foam::tmp< Foam::GeometricField< Type, TPatchField, TMesh > > * ), 0 );
  int res_ext_tmpT = SWIG_ConvertPtr( $input, (void **) &ptr, $descriptor( Foam::ext_tmp< Foam::GeometricField< Type, TPatchField, TMesh > > * ), 0 );
  $1 =  SWIG_CheckState( res_Holder ) || SWIG_CheckState( res_T ) || SWIG_CheckState( res_tmpT ) || SWIG_CheckState( res_ext_tmpT );
}

%typemap( in ) Foam::GeometricFieldHolder< Type, TPatchField, TMesh >& ( void  *argp = 0, int check = 0, Foam::GeometricFieldHolder< Type, TPatchField, TMesh > result ) 
{
  check = SWIG_ConvertPtr( $input, &argp, $descriptor(  Foam::GeometricFieldHolder< Type, TPatchField, TMesh > * ), %convertptr_flags );
  if ( SWIG_IsOK( check )&& argp  ){
    result = *%reinterpret_cast( argp, Foam::GeometricFieldHolder< Type, TPatchField, TMesh >* );
  } else {
    check = SWIG_ConvertPtr( $input, &argp, $descriptor(  Foam::GeometricField< Type, TPatchField, TMesh > * ), SWIG_POINTER_DISOWN | %convertptr_flags );
    if ( SWIG_IsOK( check )&& argp  ){
      Foam::GeometricField< Type, TPatchField, TMesh > * res =  %reinterpret_cast( argp, Foam::GeometricField< Type, TPatchField, TMesh >* );
      result = Foam::GeometricFieldHolder< Type, TPatchField, TMesh >( *res );
    } else {
      check = SWIG_ConvertPtr( $input, &argp, $descriptor( Foam::tmp< Foam::GeometricField< Type, TPatchField, TMesh > >* ), SWIG_POINTER_DISOWN | %convertptr_flags );
      if ( SWIG_IsOK( check ) && argp ) {
        Foam::tmp< Foam::GeometricField< Type, TPatchField, TMesh> >* tmp_res =%reinterpret_cast( argp, Foam::tmp< Foam::GeometricField< Type, TPatchField, TMesh > > * );
        result = Foam::GeometricFieldHolder< Type, TPatchField, TMesh >( *tmp_res );
      } else {
        check = SWIG_ConvertPtr( $input, &argp, $descriptor( Foam::ext_tmp< Foam::GeometricField< Type, TPatchField, TMesh > >* ), SWIG_POINTER_DISOWN | %convertptr_flags );
        if ( SWIG_IsOK( check ) && argp ) {
          Foam::ext_tmp< Foam::GeometricField< Type, TPatchField, TMesh> >* tmp_res =%reinterpret_cast( argp, Foam::ext_tmp< Foam::GeometricField< Type, TPatchField, TMesh > > * );
          result = Foam::GeometricFieldHolder< Type, TPatchField, TMesh >( *tmp_res );
        } else {
          %argument_fail( check, "$type", $symname, $argnum );
        }
      }
    }
  }
$1 = &result;
}
%enddef


//---------------------------------------------------------------------------
%import "Foam/src/finiteVolume/fvMesh/fvMeshes.cxx"


GEOMETRIC_FIELDHOLDER_TYPEMAP( Foam::scalar, Foam::fvPatchField, Foam::volMesh );
GEOMETRIC_FIELDHOLDER_TYPEMAP( Foam::vector, Foam::fvPatchField, Foam::volMesh );

GEOMETRIC_FIELDHOLDER_TYPEMAP( Foam::scalar, Foam::fvsPatchField, Foam::surfaceMesh );
GEOMETRIC_FIELDHOLDER_TYPEMAP( Foam::vector, Foam::fvsPatchField, Foam::surfaceMesh );


//--------------------------------------------------------------------------------------
#endif
