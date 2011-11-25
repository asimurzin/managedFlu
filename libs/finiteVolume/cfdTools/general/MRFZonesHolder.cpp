//  managedFlu - OpenFOAM C++ interactive functionality API
//  Copyright (C) 2010- Alexey Petrov
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
#include "MRFZonesHolder.hpp"

//---------------------------------------------------------------------------
namespace Foam
{

  MRFZonesHolder::MRFZonesHolder( fvMeshHolder& mesh ) 
    : DependentHolder( &mesh )
    , boost::shared_ptr< MRFZones >( new MRFZones( *mesh ) )
  {
#ifdef OUR_DEBUG
    cout << "MRFZonesHolder = " << this << nl;
#endif
  }

  MRFZonesHolder::MRFZonesHolder() 
    : DependentHolder()
    , boost::shared_ptr< MRFZones >()
  {
#ifdef OUR_DEBUG
    cout << "MRFZonesHolder = " << this << nl;
#endif
  }
  
  SimpleHolder* MRFZonesHolder::clone() const 
  {
    return new MRFZonesHolder( *this );
  }
  
  MRFZonesHolder::~MRFZonesHolder()
  {
#ifdef OUR_DEBUG
    cout << "~MRFZonesHolder = " << this << nl;
#endif
  }
}


//---------------------------------------------------------------------------
