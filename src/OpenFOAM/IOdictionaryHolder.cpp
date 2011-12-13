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
#include "IOdictionaryHolder.hpp"


//---------------------------------------------------------------------------
namespace Foam
{
  IOdictionaryHolder::IOdictionaryHolder( const IOobjectHolder&  ioh ) 
    : DependentHolder( &ioh )
    , boost::shared_ptr< IOdictionary >( new IOdictionary( *ioh ) )
  {
    dictionaryHolder::operator=( boost::shared_ptr< IOdictionary >( *this ) );
    IOobjectHolder::operator=( boost::shared_ptr< IOdictionary >( *this ) );
  }

  IOdictionaryHolder::IOdictionaryHolder( const IOobjectHolder& ioh, 
					  const dictionaryHolder& dict ) 
    : DependentHolder( Deps( &ioh, &dict ) )
    , boost::shared_ptr< IOdictionary >( new IOdictionary( *ioh, *dict ) )
  {
    dictionaryHolder::operator=( boost::shared_ptr< IOdictionary >( *this ) );
    IOobjectHolder::operator=( boost::shared_ptr< IOdictionary >( *this ) );
  }

  IOdictionaryHolder::IOdictionaryHolder() 
    : DependentHolder()
    , boost::shared_ptr< IOdictionary >()
  {}

  SimpleHolder* IOdictionaryHolder::clone() const
  {
    return new IOdictionaryHolder( *this );
  }
  
  void IOdictionaryHolder::operator=( const boost::shared_ptr< IOdictionary >&  iodic)
  {
    boost::shared_ptr< IOdictionary >::operator=( iodic );
    dictionaryHolder::operator=( boost::shared_ptr< IOdictionary >( *this ) );
    IOobjectHolder::operator=( boost::shared_ptr< IOdictionary >( *this ) );
  }
  
  IOdictionaryHolder::~IOdictionaryHolder()
  {}
  
  void IOdictionaryHolder::operator()( const IOdictionaryHolder& iodict )
  {
    this->operator=( iodict );
  }

}//Foam


//---------------------------------------------------------------------------
