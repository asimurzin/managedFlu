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
#include "RASModelHolder.hpp"


//---------------------------------------------------------------------------
namespace Foam
{
namespace incompressible
{
  RASModelHolder::RASModelHolder( 
    const boost::shared_ptr< RASModel >& tm, 
    const volVectorFieldHolder& U,
    const surfaceScalarFieldHolder& phi,
    transportModelHolder& transport )
    : DependentHolder( Deps( &U, &phi, &transport ) )
    , boost::shared_ptr< RASModel >( tm )
  {
    turbulenceModelHolder::operator=( boost::shared_ptr< RASModel >( *this ) );
  }

  RASModelHolder::RASModelHolder()
    : DependentHolder()
    , boost::shared_ptr< RASModel >()
  {}

  RASModelHolder RASModelHolder::New( 
    const volVectorFieldHolder& U,
    const surfaceScalarFieldHolder& phi,
    transportModelHolder& transport,
    const word& turbulenceModelName )
  {
    autoPtr< RASModel > result = RASModel::New( U(), phi(), *transport, turbulenceModelName );
    
    return RASModelHolder( boost::shared_ptr< RASModel >( result.ptr() ), U, phi, transport );
  }

  SimpleHolder* RASModelHolder::clone() const
  {
    return new RASModelHolder( *this );
  }

  RASModelHolder::~RASModelHolder()
  {}
  
}//incompressible
}//Foam

//---------------------------------------------------------------------------
