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
#ifndef objectRegistryHolder_hpp
#define objectRegistryHolder_hpp


//---------------------------------------------------------------------------
#include "IOobjectHolder.hpp"

#include <objectRegistry.H>
#include <boost/shared_ptr.hpp>


//---------------------------------------------------------------------------
namespace Foam
{
  class objectRegistryHolder 
    : public IOobjectHolder 
    , public boost::shared_ptr<objectRegistry>
    
  {
  public:
    objectRegistryHolder();

    virtual SimpleHolder* clone() const;
    
    using boost::shared_ptr< objectRegistry >::operator*;
    using boost::shared_ptr< objectRegistry >::operator->;
  protected:
    void operator=( const boost::shared_ptr<objectRegistry>& );

  };
} // Foam


//---------------------------------------------------------------------------
#endif
