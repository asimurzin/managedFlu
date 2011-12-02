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
#include "LESModelHolder.hpp"


//---------------------------------------------------------------------------
namespace Foam
{
namespace incompressible
{
  LESModelHolder::LESModelHolder( 
    const boost::shared_ptr< LESModel >& tm, 
    const volVectorFieldHolder& U,
    const surfaceScalarFieldHolder& phi,
    transportModelHolder& transport )
    : DependentHolder( Deps( &U, &phi, &transport ) )
    , boost::shared_ptr< LESModel >( tm )
  {
    turbulenceModelHolder::operator=( boost::shared_ptr< LESModel >( *this ) );
  }

  LESModelHolder::LESModelHolder()
    : DependentHolder()
    , boost::shared_ptr< LESModel >()
  {}

  LESModelHolder LESModelHolder::New( 
    const volVectorFieldHolder& U,
    const surfaceScalarFieldHolder& phi,
    transportModelHolder& transport )
  {
    autoPtr< LESModel > result = LESModel::New( U(), phi(), *transport );
    
    return LESModelHolder( boost::shared_ptr< LESModel >( result.ptr() ), U, phi, transport );
  }

  SimpleHolder* LESModelHolder::clone() const
  {
    return new LESModelHolder( *this );
  }

  LESModelHolder::~LESModelHolder()
  {}
  
}//incompressible
}//Foam

//---------------------------------------------------------------------------
