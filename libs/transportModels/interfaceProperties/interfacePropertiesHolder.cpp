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
#include "interfacePropertiesHolder.hpp"


//---------------------------------------------------------------------------
namespace Foam
{
  
  interfacePropertiesHolder::interfacePropertiesHolder( const volScalarFieldHolder& alpha1,
                                                        const volVectorFieldHolder& U,
                                                        const IOdictionaryHolder& dict)
    : DependentHolder( Deps( &alpha1, &U, &dict ) )
    , boost::shared_ptr< interfaceProperties >( new interfaceProperties( alpha1(), U(), *dict ) )
  {}
    
  interfacePropertiesHolder::interfacePropertiesHolder() 
    : DependentHolder()
    , boost::shared_ptr< interfaceProperties >()
  {}

  void interfacePropertiesHolder::operator=( const boost::shared_ptr< interfaceProperties >& bt ) 
  {
    boost::shared_ptr< interfaceProperties >::operator=( bt );
  }

  SimpleHolder* interfacePropertiesHolder::clone() const
  {
    return new interfacePropertiesHolder( *this );
  }
  
  void interfacePropertiesHolder::operator()( const interfacePropertiesHolder& the_Arg )
  {
    this->operator=( the_Arg );
  }
  
  interfacePropertiesHolder::~interfacePropertiesHolder()
  {}
}


//---------------------------------------------------------------------------
