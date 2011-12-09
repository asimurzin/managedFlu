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
#include "TimeHolder.hpp"


//---------------------------------------------------------------------------
namespace Foam
{
  TimeHolder::TimeHolder( const word &name, 
			  const fileName& rootPath,
			  const fileName& caseName,
			  const word &systemName, 
			  const word &constantName ) 
    : DependentHolder()
    , boost::shared_ptr< Time >( new Time( name, rootPath, caseName, systemName, constantName ) )
  {
    objectRegistryHolder::operator=( boost::shared_ptr< Time >( *this ) );
  }

  TimeHolder::TimeHolder(  const dictionary& dict,
                           const fileName& rootPath,
                           const fileName& caseName,
                           const word& systemName,
                           const word& constantName ) 
    : DependentHolder()
    , boost::shared_ptr< Time >( new Time( dict, rootPath, caseName, systemName, constantName  ) )
  {
    objectRegistryHolder::operator=( boost::shared_ptr< Time >( *this ) );
  }

  TimeHolder::TimeHolder( const boost::shared_ptr< Time >& the_time, const Deps& the_deps)
    : DependentHolder( the_deps )
    , boost::shared_ptr< Time >( the_time )
  {
    objectRegistryHolder::operator=( boost::shared_ptr< Time >( *this ) );
  }
  
  SimpleHolder* TimeHolder::clone() const
  {
    return new TimeHolder( *this );
  }

  TimeHolder::~TimeHolder()
  {}

} //Foam


//---------------------------------------------------------------------------
