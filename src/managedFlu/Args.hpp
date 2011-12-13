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
#ifndef Args_hpp
#define Args_hpp


//---------------------------------------------------------------------------
#include <set>
#include <boost/shared_ptr.hpp>

#include "common.hpp"


//---------------------------------------------------------------------------
namespace Foam
{
  class SimpleHolder;
  
  typedef boost::shared_ptr< SimpleHolder > holderPtr;
  
  class Args 
  {
   
    protected:
      Args();
      Args( const SimpleHolder* uh );
      Args( const std::set< holderPtr >& the_deps );

      const std::set< holderPtr >& args() const;
      
    private:
      std::set< holderPtr > args_;
      
  };

#ifndef SWIG
  std::set< holderPtr > operator&&( const std::set< holderPtr >&, const std::set< holderPtr >& );
#endif
    
} // Foam


//---------------------------------------------------------------------------
#endif

