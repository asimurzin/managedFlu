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
#ifndef radiationModelHolder_hpp
#define radiationModelHolder_hpp


//---------------------------------------------------------------------------
#include "fvMeshHolder.hpp"
#include "DependentHolder.hpp"
#include "Deps.hpp"
#include "volFields.hpp"

#include <radiationModel.H>
#include <boost/shared_ptr.hpp>


//---------------------------------------------------------------------------
namespace Foam
{
  namespace radiation
  {
    class radiationModelHolder 
      : virtual public DependentHolder
      , public boost::shared_ptr< radiationModel >
    {
    public:
      radiationModelHolder();
    
      ~radiationModelHolder();
    
      static radiationModelHolder New( const volScalarFieldHolder& T );
    
      virtual SimpleHolder* clone() const;
      
      void operator()( const radiationModelHolder& );
    
      using  boost::shared_ptr< radiationModel >::operator*;
      using  boost::shared_ptr< radiationModel >::operator->;
    protected:
      radiationModelHolder( const boost::shared_ptr< radiationModel >&, const volScalarFieldHolder& );
    };
  }
} // Foam


//---------------------------------------------------------------------------
#endif
