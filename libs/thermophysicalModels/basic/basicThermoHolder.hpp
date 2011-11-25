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
#ifndef basicThermoHolder_hpp
#define basicThermoHolder_hpp


//---------------------------------------------------------------------------
#include "fvMeshHolder.hpp"
#include "DependentHolder.hpp"
#include "Deps.hpp"

#include <basicThermo.H>
#include <boost/shared_ptr.hpp>


//---------------------------------------------------------------------------
namespace Foam
{
  
  class basicThermoHolder 
    : virtual public DependentHolder
    , public boost::shared_ptr< basicThermo >
  {
  public:
    basicThermoHolder();
    
    ~basicThermoHolder();
    
    virtual SimpleHolder* clone() const;
    
    using  boost::shared_ptr< basicThermo >::operator*;
    using  boost::shared_ptr< basicThermo >::operator->;
  protected:
    void operator=( const boost::shared_ptr< basicThermo >& );
  };
} // Foam


//---------------------------------------------------------------------------
#endif
