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
#include "IObasicSourceListHolder.hpp"


//---------------------------------------------------------------------------
namespace Foam
{

  IObasicSourceListHolder::IObasicSourceListHolder( const fvMeshHolder& mesh ) 
    : DependentHolder( Deps( &mesh ) )
    , boost::shared_ptr< IObasicSourceList >( new IObasicSourceList( *mesh ) )
  {
    boost::shared_ptr< basicSourceList >::operator=( boost::shared_ptr< IObasicSourceList >( *this ) );
    boost::shared_ptr< IOdictionary >::operator=( boost::shared_ptr< IObasicSourceList >( *this ) );
  }

  IObasicSourceListHolder::IObasicSourceListHolder() 
    : DependentHolder()
    , boost::shared_ptr< IObasicSourceList >()
  {}
  
  SimpleHolder* IObasicSourceListHolder::clone() const 
  {
    return new IObasicSourceListHolder( *this );
  }
  
  IObasicSourceListHolder::~IObasicSourceListHolder()
  {}

  void IObasicSourceListHolder::operator()( const IObasicSourceListHolder& listHolder )
  {
    this->operator=( listHolder );
  }

}


//---------------------------------------------------------------------------
