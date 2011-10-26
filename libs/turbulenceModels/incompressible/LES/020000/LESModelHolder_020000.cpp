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
    transportModelHolder& transport,
    const word& turbulenceModelName )
  {
    autoPtr< LESModel > result = LESModel::New( U(), phi(), *transport, turbulenceModelName );
    
    return LESModelHolder( boost::shared_ptr< LESModel >( result.ptr() ), U, phi, transport );
  }

  SimpleHolder* LESModelHolder::clone() const
  {
    return new LESModelHolder( *this );
  }

  LESModelHolder::~LESModelHolder()
  {}
  
  void LESModelHolder::operator()( const LESModelHolder& model )
  {
    this->operator=( model );
  }
  
}//incompressible
}//Foam

//---------------------------------------------------------------------------
