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
#include "singlePhaseTransportModelHolder.hpp"


//---------------------------------------------------------------------------
namespace Foam
{
  
  singlePhaseTransportModelHolder::singlePhaseTransportModelHolder( const volVectorFieldHolder& U, const surfaceScalarFieldHolder& phi )
    : DependentHolder( Deps( &U, &phi ) )
    , boost::shared_ptr< singlePhaseTransportModel >( new singlePhaseTransportModel( U(), phi() ) )
  {
    transportModelHolder::operator=( boost::shared_ptr< singlePhaseTransportModel >( *this ) );
  }
    
  singlePhaseTransportModelHolder::singlePhaseTransportModelHolder() 
    : transportModelHolder()
    , boost::shared_ptr< singlePhaseTransportModel >()
  {}

  void singlePhaseTransportModelHolder::operator=( const boost::shared_ptr< singlePhaseTransportModel >& bt ) 
  {
    boost::shared_ptr< singlePhaseTransportModel >::operator=( bt );
    transportModelHolder::operator=( bt );
  }

  SimpleHolder* singlePhaseTransportModelHolder::clone() const
  {
    return new singlePhaseTransportModelHolder( *this );
  }
  
  void singlePhaseTransportModelHolder::operator()( const singlePhaseTransportModelHolder& model )
  {
    this->operator=( model );
  }
  
  singlePhaseTransportModelHolder::~singlePhaseTransportModelHolder()
  {}
}


//---------------------------------------------------------------------------
