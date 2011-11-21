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
namespace compressible
{
  RASModelHolder::RASModelHolder( 
    const boost::shared_ptr< RASModel >& tm, 
    const volScalarFieldHolder& rho, 
    const volVectorFieldHolder& U,  
    const surfaceScalarFieldHolder& phi, 
    const basicThermoHolder& thermo )
    : DependentHolder( Deps( &rho, &U, &phi, &thermo ) )
    , boost::shared_ptr< RASModel >( tm )
  {
    turbulenceModelHolder::operator=( boost::shared_ptr< RASModel >( *this ) );
  }

  RASModelHolder::RASModelHolder()
    : DependentHolder()
    , boost::shared_ptr< RASModel >()
  {}

  RASModelHolder RASModelHolder::New( 
    const volScalarFieldHolder& rho,
    const volVectorFieldHolder& U,
    const surfaceScalarFieldHolder& phi,
    const basicThermoHolder& thermo,
    const word& turbulenceModelName )
  {
    autoPtr< RASModel > result = RASModel::New( rho(), U(), phi(), *thermo, turbulenceModelName );
    
    return RASModelHolder( boost::shared_ptr< RASModel >( result.ptr() ), rho, U, phi, thermo );
  }

  SimpleHolder* RASModelHolder::clone() const
  {
    return new RASModelHolder( *this );
  }

  RASModelHolder::~RASModelHolder()
  {}
  
}//compressible
}//Foam

//---------------------------------------------------------------------------
