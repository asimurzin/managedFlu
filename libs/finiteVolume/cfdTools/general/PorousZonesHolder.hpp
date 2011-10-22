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
#ifndef PorousZonesHolder_hpp
#define PorousZonesHolder_hpp


//---------------------------------------------------------------------------
#include "DependentHolder.hpp"
#include "Deps.hpp"
#include "fvMeshHolder.hpp"

#include <PorousZones.H>
#include <boost/shared_ptr.hpp>


//---------------------------------------------------------------------------
namespace Foam
{
  template<class ZoneType>
  class PorousZonesHolder 
    : virtual public DependentHolder
    , public boost::shared_ptr< PorousZones< ZoneType > >
  {
  public:
    PorousZonesHolder( fvMeshHolder& mesh );
    PorousZonesHolder();
    
    ~PorousZonesHolder();
    
    virtual SimpleHolder* clone() const;
#ifndef SWIG
    using  boost::shared_ptr< PorousZones< ZoneType > >::operator*;
    using  boost::shared_ptr< PorousZones< ZoneType > >::operator->;
#endif
  };
} // Foam


//---------------------------------------------------------------------------
#include "PorousZonesHolder.cpp"


//---------------------------------------------------------------------------
#endif
