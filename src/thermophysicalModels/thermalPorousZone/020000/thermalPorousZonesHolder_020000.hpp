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
#ifndef thermalPorousZonesHolder_020000_hpp
#define thermalPorousZonesHolder_020000_hpp


//---------------------------------------------------------------------------
#include "PorousZonesHolder.hpp"
#include <thermalPorousZone.H>
#include <thermalPorousZones.H>

namespace Foam
{
  class thermalPorousZonesHolder 
    : public PorousZonesHolder< thermalPorousZone >
    , public boost::shared_ptr< thermalPorousZones >
  {
  public:
    thermalPorousZonesHolder( fvMeshHolder& mesh );
    thermalPorousZonesHolder();
    
    ~thermalPorousZonesHolder();
    
    virtual SimpleHolder* clone() const;
#ifndef SWIG
    using  boost::shared_ptr< thermalPorousZones >::operator*;
    using  boost::shared_ptr< thermalPorousZones >::operator->;
#endif
  };
} // Foam


//---------------------------------------------------------------------------
#endif
