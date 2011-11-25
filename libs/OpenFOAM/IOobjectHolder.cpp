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
#include "IOobjectHolder.hpp"

#include "objectRegistryHolder.hpp"


//---------------------------------------------------------------------------
namespace Foam
{

  IOobjectHolder::IOobjectHolder( const word &name, 
                                  const fileName &instance, 
                                  const objectRegistryHolder & registry, 
                                  IOobject::readOption r, 
                                  IOobject::writeOption w, 
                                  bool registerObject ) 
    : DependentHolder( &registry )
    , boost::shared_ptr< IOobject >( new IOobject( name, instance, *registry, r, w, registerObject ) )
  {}
  
  void IOobjectHolder::operator=( const boost::shared_ptr< IOobject >& ioPtr )
  {
   boost::shared_ptr< IOobject >::operator=( ioPtr );
  }
  
  IOobjectHolder::IOobjectHolder() 
    : DependentHolder()
    , boost::shared_ptr< IOobject >()
  {}

  SimpleHolder* IOobjectHolder::clone() const
  {
    return new IOobjectHolder( *this );
  }

  IOobjectHolder::~IOobjectHolder()
  {}
}


//---------------------------------------------------------------------------
