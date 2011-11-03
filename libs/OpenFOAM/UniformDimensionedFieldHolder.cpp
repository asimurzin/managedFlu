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
#include "UniformDimensionedFieldHolder.hpp"


//---------------------------------------------------------------------------
namespace Foam
{

  template<class Type >
  UniformDimensionedFieldHolder< Type >::UniformDimensionedFieldHolder( const IOobjectHolder& io ) 
    : DependentHolder( &io )
    , boost::shared_ptr< UniformDimensionedField< Type > >( new UniformDimensionedField< Type >( *io ) )
  {
    IOobjectHolder::operator=( boost::shared_ptr< UniformDimensionedField< Type > >( *this ) );
  }


  template<class Type >
  UniformDimensionedFieldHolder< Type >::UniformDimensionedFieldHolder( const IOobjectHolder& io, 
									const dimensioned< Type >& dim )
    : DependentHolder( &io )
    , boost::shared_ptr< UniformDimensionedField< Type > >( new UniformDimensionedField< Type >( *io, dim ) )
  {
    IOobjectHolder::operator=( boost::shared_ptr< UniformDimensionedField< Type > >( *this ) );
  }
  

  template<class Type >
  UniformDimensionedFieldHolder< Type >::UniformDimensionedFieldHolder()
    : DependentHolder()
    , boost::shared_ptr< UniformDimensionedField< Type > >()
  {}

  
  template<class Type >
  SimpleHolder* UniformDimensionedFieldHolder< Type >::clone() const
  {
    return new UniformDimensionedFieldHolder< Type >( *this );
  }
  
  template<class Type >
  UniformDimensionedFieldHolder< Type >::~UniformDimensionedFieldHolder()
  {}
  
  template<class Type >
  void UniformDimensionedFieldHolder< Type >::operator()( const UniformDimensionedFieldHolder< Type >& the_Arg )
  {
    this->operator=( the_Arg );
  }

} //Foam


//---------------------------------------------------------------------------

