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
#include "Args.hpp"
#include "SimpleHolder.hpp"


//---------------------------------------------------------------------------
namespace Foam
{

  Args::Args( const SimpleHolder* uh )
  {
    this->args_.insert(  holderPtr( uh->clone() ) );
  }

  Args::Args( const std::set< holderPtr >& the_deps )
    : args_( the_deps )
  {}

  Args::Args()
  {}
  
  const std::set< holderPtr >& Args::args() const
  {
    return args_;
  }
  
  std::set< holderPtr > operator&&( const std::set< holderPtr >& deps1, const std::set< holderPtr >& deps2)
  {
    std::set< holderPtr > result;
  
    set_union( deps1.begin(), deps1.end(), deps2.begin(), deps2.end(),
              std::insert_iterator<std::set< holderPtr > >(result,result.begin()) );

    return result;
  }
  
}//Foam


//---------------------------------------------------------------------------

