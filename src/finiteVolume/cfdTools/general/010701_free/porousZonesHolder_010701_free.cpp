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
#include "porousZonesHolder.hpp"


//---------------------------------------------------------------------------
namespace Foam
{
  porousZonesHolder::porousZonesHolder( fvMeshHolder& mesh ) 
    : DependentHolder( &mesh )
    , boost::shared_ptr< porousZones >( new porousZones( *mesh ) )
  {
#ifdef OUR_DEBUG
    cout << "porousZonesHolder = " << this << nl;
#endif
  }

  porousZonesHolder::porousZonesHolder() 
    : DependentHolder()
    , boost::shared_ptr< porousZones >()
  {
#ifdef OUR_DEBUG
    cout << "porousZonesHolder = " << this << nl;
#endif
  }
  
  SimpleHolder* porousZonesHolder::clone() const 
  {
    return new porousZonesHolder( *this );
  }
  
  porousZonesHolder::~porousZonesHolder()
  {
#ifdef OUR_DEBUG
    cout << "~porousZonesHolder = " << this << nl;
#endif
  }
}


//---------------------------------------------------------------------------
