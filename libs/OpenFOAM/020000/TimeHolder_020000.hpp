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
#ifndef TimeHolder_020000_hpp
#define TimeHolder_020000_hpp


//---------------------------------------------------------------------------
#include "objectRegistryHolder.hpp"

#include <Time.H>
#include <boost/shared_ptr.hpp>


//---------------------------------------------------------------------------
namespace Foam
{
  class TimeHolder 
    : public objectRegistryHolder
    , public boost::shared_ptr< Time >
  {
  public:
    TimeHolder( const word &name, 
                const argList &args, 
                const word &systemName="system", 
                const word &constantName="constant" );
    
    TimeHolder( const boost::shared_ptr< Time >&, const Deps& );
    //TimeHolder( const Time*, const Deps& ); will be implemented after change shared_ptr with smart_ptr
    
    virtual SimpleHolder* clone() const;
    
    ~TimeHolder();

    using boost::shared_ptr< Time >::operator->;
    using boost::shared_ptr< Time >::operator*;

  private:
    TimeHolder(); // not implemented
    // TimeHolder( const TimeHolder& ); // not implemented 
    void operator = ( const TimeHolder& ); // not implemented 
  };
} // Foam


//---------------------------------------------------------------------------
#endif
