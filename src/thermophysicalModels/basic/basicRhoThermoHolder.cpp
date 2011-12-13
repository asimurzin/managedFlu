//  managedFlu - OpenFOAM C++ interactive functionality API
//  Copyright (C) 2011- Alexey Petrov
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
#include "basicRhoThermoHolder.hpp"


//---------------------------------------------------------------------------
namespace Foam
{

  basicRhoThermoHolder::basicRhoThermoHolder( const boost::shared_ptr< basicRhoThermo >& pThermo, const fvMeshHolder& mesh ) 
    : DependentHolder( &mesh )
    , boost::shared_ptr< basicRhoThermo >( pThermo )
  {
    basicThermoHolder::operator=( boost::shared_ptr< basicRhoThermo >( *this ) );
  }

  basicRhoThermoHolder::basicRhoThermoHolder() 
    : basicThermoHolder()
    , boost::shared_ptr< basicRhoThermo >()
  {}

  basicRhoThermoHolder::~basicRhoThermoHolder()
  {}

  SimpleHolder* basicRhoThermoHolder::clone() const
  {
    return new basicRhoThermoHolder( *this );
  }

  basicRhoThermoHolder basicRhoThermoHolder::New( const fvMeshHolder& mesh )
  {
    autoPtr< basicRhoThermo > pThermo = basicRhoThermo::New( *mesh );
    
    return basicRhoThermoHolder( boost::shared_ptr< basicRhoThermo >( pThermo.ptr() ), mesh );
  }
  
  void basicRhoThermoHolder::operator()( const basicRhoThermoHolder& the_Arg )
  {
    this->operator=( the_Arg );
  }


}
//---------------------------------------------------------------------------
