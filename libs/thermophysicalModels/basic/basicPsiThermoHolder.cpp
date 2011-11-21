//  managedFlu - OpenFOAM C++ interactive functionality API
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
//  Author : Alexey PETROV, Andrey Simurzin


//---------------------------------------------------------------------------
#include "basicPsiThermoHolder.hpp"


//---------------------------------------------------------------------------
namespace Foam
{

  basicPsiThermoHolder::basicPsiThermoHolder( const boost::shared_ptr< basicPsiThermo >& pThermo, const fvMeshHolder& mesh ) 
    : DependentHolder( &mesh )
    , boost::shared_ptr< basicPsiThermo >( pThermo )
  {
    basicThermoHolder::operator=( boost::shared_ptr< basicPsiThermo >( *this ) );
  }

  basicPsiThermoHolder::basicPsiThermoHolder() 
    : basicThermoHolder()
    , boost::shared_ptr< basicPsiThermo >()
  {}

  basicPsiThermoHolder::~basicPsiThermoHolder()
  {}

  SimpleHolder* basicPsiThermoHolder::clone() const
  {
    return new basicPsiThermoHolder( *this );
  }

  basicPsiThermoHolder basicPsiThermoHolder::New( const fvMeshHolder& mesh )
  {
    autoPtr< basicPsiThermo > pThermo = basicPsiThermo::New( *mesh );
    
    return basicPsiThermoHolder( boost::shared_ptr< basicPsiThermo >( pThermo.ptr() ), mesh );
  }

}
//---------------------------------------------------------------------------
