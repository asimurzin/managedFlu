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
#ifndef GeometricFieldHolder_hpp
#define GeometricFieldHolder_hpp


//---------------------------------------------------------------------------
#include "SimpleHolder.hpp"
#include "Deps.hpp"
#include "DependentHolder.hpp"
#include "smart_tmp/smart_tmp.hpp"

#include <GeometricField.H>


//---------------------------------------------------------------------------
namespace Foam
{

  class IOobjectHolder;
  class fvMeshHolder;
  
  template<class Type, template<class> class PatchField, class GeoMesh>
  class GeometricFieldHolder 
    : virtual public DependentHolder
    , public smart_tmp< GeometricField< Type, PatchField, GeoMesh > >
  {
  public:
    //reference constructor
    GeometricFieldHolder( const IOobjectHolder&, const fvMeshHolder& );
    GeometricFieldHolder( const IOobjectHolder&, const GeometricFieldHolder< Type, PatchField, GeoMesh >& );
    GeometricFieldHolder( const IOobjectHolder&, const GeometricFieldHolder< Type, PatchField, GeoMesh >&, 
                          const wordList&, const wordList& actualPatchTypes = wordList() );
    GeometricFieldHolder( const IOobjectHolder&, const fvMeshHolder&, 
                          const dimensioned<Type>&, const word& patchFieldType=PatchField<Type>::calculatedType() );
    GeometricFieldHolder( const word&, const GeometricFieldHolder< Type, PatchField, GeoMesh >& );
    
    // constructors with deps
    GeometricFieldHolder( const smart_tmp< GeometricField< Type, PatchField, GeoMesh > >& , const Deps& );

    GeometricFieldHolder();
    
    ~GeometricFieldHolder();
    
    virtual SimpleHolder* clone() const;
    
    GeometricField< Type, PatchField, GeoMesh >& ref();

    void operator = ( const GeometricFieldHolder< Type, PatchField, GeoMesh >& );
    void operator = ( const dimensioned< Type >& );
    
    void operator = ( const smart_tmp< GeometricField< Type, PatchField, GeoMesh > >& );
    void operator -= ( const smart_tmp< GeometricField< Type, PatchField, GeoMesh > >& );
    void operator += ( const smart_tmp< GeometricField< Type, PatchField, GeoMesh > >& );

    void operator *= ( const smart_tmp< GeometricField< scalar, PatchField, GeoMesh > >& );
    void operator /= ( const smart_tmp< GeometricField< scalar, PatchField, GeoMesh > >& );

    void operator += ( const dimensioned< Type >& );
    void operator -= ( const dimensioned< Type >& );
    void operator *= ( const dimensioned< scalar >& );
    void operator /= ( const dimensioned< scalar >& );
    
    void operator == ( const smart_tmp< GeometricField< Type, PatchField, GeoMesh > >& );

    void operator()( const GeometricFieldHolder< Type, PatchField, GeoMesh >& );
#ifndef SWIG
    using Foam::smart_tmp< GeometricField< Type, PatchField, GeoMesh > >::operator();
#endif
    //using Foam::smart_tmp< GeometricField< Type, PatchField, GeoMesh > >::operator*;

  };

} // Foam


//---------------------------------------------------------------------------
#include "GeometricFieldHolder.cpp"


//---------------------------------------------------------------------------
#endif
