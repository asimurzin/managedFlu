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
#ifndef Deps_hpp
#define Deps_hpp


//---------------------------------------------------------------------------
#include "SimpleHolder.hpp"
#include "Args.hpp"


namespace Foam
{
  
  class Deps 
    : public Args
  {
    public:
      Deps( const SimpleHolder* );
      Deps( const std::set< holderPtr >& the_deps );
      Deps( const Deps&, const Deps& );
      Deps( const Deps&, const Deps&, const Deps& );
      Deps( const Deps&, const Deps&, const Deps&, const Deps& );
      Deps();
      
    private:
      //Deps(); //not implemented
      //Deps( const Deps&); //not implemented
      //void operator=( const Deps&); //not implemented

  };

   
} // Foam


//---------------------------------------------------------------------------
#endif

