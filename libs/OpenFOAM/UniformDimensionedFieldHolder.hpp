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
#ifndef UniformDimensionedFieldHolder_hpp
#define UniformDimensionedFieldHolder_hpp


//---------------------------------------------------------------------------
#include "SimpleHolder.hpp"
#include "Deps.hpp"
#include "DependentHolder.hpp"
#include "IOobjectHolder.hpp"
#include <boost/shared_ptr.hpp>

#include <UniformDimensionedField.H>


//---------------------------------------------------------------------------
namespace Foam
{

  template<class Type>
  class UniformDimensionedFieldHolder 
    : public IOobjectHolder
    , public boost::shared_ptr< UniformDimensionedField< Type > >
  {
  public:
    //reference constructor
    UniformDimensionedFieldHolder( const IOobjectHolder& );
    UniformDimensionedFieldHolder( const IOobjectHolder&, const dimensioned< Type >& );
    
    UniformDimensionedFieldHolder();
    
    ~UniformDimensionedFieldHolder();
    
    virtual SimpleHolder* clone() const;
    
    void operator()( const UniformDimensionedFieldHolder& );
    
    using boost::shared_ptr< UniformDimensionedField< Type > >::operator*;
  };

} // Foam


//---------------------------------------------------------------------------
#include "UniformDimensionedFieldHolder.cpp"


//---------------------------------------------------------------------------
#endif
