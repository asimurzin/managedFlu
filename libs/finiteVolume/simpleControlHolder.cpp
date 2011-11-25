//  managedFlu - OpenFOAM C++ interactive functionality API
//  Copyright (C) 2010- Alexey Petrov
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
//  Author : Alexey PETROV, Andrey Simurzin


//---------------------------------------------------------------------------
#include "simpleControlHolder.hpp"

//---------------------------------------------------------------------------
#if FOAM_VERSION( <, 020000 )
#define simpleControlHolder_cpp
#endif


//---------------------------------------------------------------------------
#ifndef simpleControlHolder_cpp
#define simpleControlHolder_cpp


//---------------------------------------------------------------------------
namespace Foam
{

  simpleControlHolder::simpleControlHolder( fvMeshHolder& mesh ) 
    : DependentHolder( &mesh )
    , boost::shared_ptr< simpleControl >( new simpleControl( *mesh ) )
  {
#ifdef OUR_DEBUG
    cout << "simpleControlHolder = " << this << nl;
#endif
  }
  
  SimpleHolder* simpleControlHolder::clone() const 
  {
    return new simpleControlHolder( *this );
  }
  
  simpleControlHolder::~simpleControlHolder()
  {
#ifdef OUR_DEBUG
    cout << "~simpleControlHolder = " << this << nl;
#endif
  }
}


//---------------------------------------------------------------------------
#endif
