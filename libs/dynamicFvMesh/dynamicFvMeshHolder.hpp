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
#ifndef dynamicFvMeshHolder_hpp
#define dynamicFvMeshHolder_hpp


//---------------------------------------------------------------------------
#include "DependentHolder.hpp"
#include "Deps.hpp"
#include "fvMeshHolder.hpp"

#include <dynamicFvMesh.H>
#include <boost/shared_ptr.hpp>


//---------------------------------------------------------------------------
namespace Foam
{
  
  class dynamicFvMeshHolder 
    : public fvMeshHolder
    , public boost::shared_ptr< dynamicFvMesh >
  {
  public:
    dynamicFvMeshHolder( const boost::shared_ptr< dynamicFvMesh >&, const Deps& );
    
    dynamicFvMeshHolder();
    
    static dynamicFvMeshHolder New( const IOobjectHolder& );
    
    virtual SimpleHolder* clone() const;
    
    ~dynamicFvMeshHolder();
    
    void operator()( const dynamicFvMeshHolder& );

    using boost::shared_ptr< dynamicFvMesh >::operator*;
    using boost::shared_ptr< dynamicFvMesh >::operator->;
    using boost::shared_ptr< dynamicFvMesh >::get;
    
  protected:
    dynamicFvMeshHolder( const boost::shared_ptr< dynamicFvMesh >&, const IOobjectHolder& ); 

  };
} // Foam


//---------------------------------------------------------------------------
#endif
