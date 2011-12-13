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
#include "radiationModelHolder.hpp"


//---------------------------------------------------------------------------
namespace Foam
{
  namespace radiation
  {

    radiationModelHolder::radiationModelHolder( const boost::shared_ptr< radiationModel >& bt, const volScalarFieldHolder& T ) 
      : DependentHolder( &T )
      , boost::shared_ptr< radiationModel >( bt )
    {}

    radiationModelHolder::radiationModelHolder() 
      : DependentHolder()
      , boost::shared_ptr< radiationModel >()
    {}

    radiationModelHolder radiationModelHolder::New( const volScalarFieldHolder& T )
    {
      autoPtr< radiationModel > a_model = radiationModel::New( T() ) ;
      
      return radiationModelHolder( boost::shared_ptr< radiationModel >( a_model.ptr() ), T );
    }
    
    SimpleHolder* radiationModelHolder::clone() const
    {
      return new radiationModelHolder( *this );
    }
    
    radiationModelHolder::~radiationModelHolder()
    {
#ifdef OUR_DEBUG
      cout << "~radiationModelHolder = " << this << nl;
#endif
    }
    
    void radiationModelHolder::operator()( const radiationModelHolder& the_Arg )
    {
      this->operator=( the_Arg );
    }

  }
}


//---------------------------------------------------------------------------
