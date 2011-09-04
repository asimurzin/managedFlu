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
#ifndef objectRegistryHolder_cxx
#define objectRegistryHolder_cxx


//---------------------------------------------------------------------------
%module "wrappers.src.OpenFOAM.objectRegistryHolder"

%{
  #include "wrappers/src/OpenFOAM/objectRegistryHolder.hh"
%}


//---------------------------------------------------------------------------
%import "Foam/ext/common/OpenFOAM/shared_ptr/shared_ptr_objectRegistry.cxx"

%import "wrappers/src/OpenFOAM/IOobjectHolder.cxx"

%include "objectRegistryHolder.hpp"


//---------------------------------------------------------------------------
%feature( "pythonappend" ) Foam::objectRegistryHolder::SMARTPTR_PYAPPEND_GETATTR( objectRegistryHolder );

%extend Foam::objectRegistryHolder
{
  SMARTPTR_EXTEND_ATTR( objectRegistryHolder );
}



//--------------------------------------------------------------------------------------
#endif
