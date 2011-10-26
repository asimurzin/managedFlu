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
#include "dynamicFvMeshHolder.hpp"


//---------------------------------------------------------------------------
namespace Foam
{
  dynamicFvMeshHolder::dynamicFvMeshHolder( const boost::shared_ptr< dynamicFvMesh >& dFM, const IOobjectHolder& io ) 
    : DependentHolder( &io )
    , boost::shared_ptr< dynamicFvMesh >( dFM )
  {
    fvMeshHolder::operator=( boost::shared_ptr< dynamicFvMesh >( *this ) );
  }

  dynamicFvMeshHolder::dynamicFvMeshHolder( dynamicFvMesh* mesh, const Deps& the_deps ) 
    : DependentHolder( the_deps )
    , boost::shared_ptr< dynamicFvMesh >( mesh )
  {
    fvMeshHolder::operator=( boost::shared_ptr< dynamicFvMesh >( *this ) );
  }
  
  dynamicFvMeshHolder dynamicFvMeshHolder::New( const IOobjectHolder& io )
  {
    autoPtr< dynamicFvMesh > a_mesh = dynamicFvMesh::New( *io );
    
    return dynamicFvMeshHolder( boost::shared_ptr< dynamicFvMesh >( a_mesh.ptr() ), io );
  }
  
  dynamicFvMeshHolder::dynamicFvMeshHolder()
    : DependentHolder()
    , boost::shared_ptr< dynamicFvMesh >()
  {}

  SimpleHolder* dynamicFvMeshHolder::clone() const
  {
    return new dynamicFvMeshHolder( *this );
  }
  
  dynamicFvMeshHolder::~dynamicFvMeshHolder()
  {}
  
  void dynamicFvMeshHolder::operator()( const dynamicFvMeshHolder& the_Arg )
  {
    this->operator=( the_Arg );
  }

} //Foam


//---------------------------------------------------------------------------
