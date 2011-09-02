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
#ifndef compressible_turbulenceModelHolder_cxx
#define compressible_turbulenceModelHolder_cxx


//---------------------------------------------------------------------------
%module "wrappers.src.turbulenceModels.compressible_turbulenceModelHolder"

%{
  #include "compressible_turbulenceModelHolder.hh"
%}


//---------------------------------------------------------------------------
%import "wrappers/src/shared_ptr/shared_ptr_compressible_turbulenceModel.cxx"

%import "wrappers/src/DependentHolder.cxx"

%import "wrappers/src/OpenFOAM/GeometricFieldHolders.cxx"

%import "wrappers/src/thermophysicalModels/basicThermoHolder.cxx"

%include "turbulenceModels/compressible/turbulenceModelHolder.hpp"


//---------------------------------------------------------------------------
%feature( "pythonappend" ) Foam::compressible::turbulenceModelHolder::SMARTPTR_PYAPPEND_GETATTR( turbulenceModelHolder );

%extend Foam::compressible::turbulenceModelHolder
{
  SMARTPTR_EXTEND_ATTR( turbulenceModelHolder );
  HOLDERS_CALL_SHARED_PTR_EXTENSION( compressible::turbulenceModel );
}


//--------------------------------------------------------------------------------------
#endif
