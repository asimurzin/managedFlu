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
#include "GeometricFieldHolder.hpp"

#include "IOobjectHolder.hpp"
#include "fvMeshHolder.hpp"


//---------------------------------------------------------------------------
namespace Foam
{

  template<class Type, template<class> class PatchField, class GeoMesh>
  GeometricFieldHolder< Type, PatchField, GeoMesh >::GeometricFieldHolder( const IOobjectHolder& io, 
									   const fvMeshHolder& mesh ) 
    : DependentHolder( &mesh )
    , smart_tmp< GeometricField< Type, PatchField, GeoMesh > >( new GeometricField< Type, PatchField, GeoMesh >( *io, *mesh ) )
  {
#ifdef OUR_DEBUG
    cout << "GeometricFieldHolder=" << this << nl;
#endif
  }

  template<class Type, template<class> class PatchField, class GeoMesh>
  GeometricFieldHolder< Type, PatchField, GeoMesh >::GeometricFieldHolder( const smart_tmp< GeometricField< Type, PatchField, GeoMesh > >& tmp_gf, 
									   const Deps& args ) 
    : DependentHolder( args )
    , smart_tmp< GeometricField< Type, PatchField, GeoMesh > >( tmp_gf )
  {
#ifdef OUR_DEBUG
    cout << "GeometricFieldHolder=" << this << nl;
#endif
  }

  template<class Type, template<class> class PatchField, class GeoMesh>
  GeometricFieldHolder< Type, PatchField, GeoMesh >::GeometricFieldHolder( const IOobjectHolder& io, 
									   const GeometricFieldHolder< Type, PatchField, GeoMesh >& field )
    : DependentHolder( &field )
    , smart_tmp< GeometricField< Type, PatchField, GeoMesh > >( new GeometricField< Type, PatchField, GeoMesh >( *io, field() ) )
  {
#ifdef OUR_DEBUG
    cout << "GeometricFieldHolder=" << this << nl;
#endif
  }

  template<class Type, template<class> class PatchField, class GeoMesh>
  GeometricFieldHolder< Type, PatchField, GeoMesh >::GeometricFieldHolder( const IOobjectHolder& io, 
									   const GeometricFieldHolder< Type, PatchField, GeoMesh >& field,
									   const wordList& patchFieldTypes, 
									   const wordList& actualPatchTypes )
    : DependentHolder( &field )
    , smart_tmp< GeometricField< Type, PatchField, GeoMesh > >( new GeometricField< Type, PatchField, GeoMesh >( *io, field(), patchFieldTypes, actualPatchTypes ) )
  {
#ifdef OUR_DEBUG
    cout << "GeometricFieldHolder=" << this << nl;
#endif
  }

  template<class Type, template<class> class PatchField, class GeoMesh>
  GeometricFieldHolder< Type, PatchField, GeoMesh >::GeometricFieldHolder( const IOobjectHolder& io, 
									   const fvMeshHolder& mesh,
									   const dimensioned<Type>& dm, 
									   const word& patchFieldType ) 
    : DependentHolder( &mesh )
    , smart_tmp< GeometricField< Type, PatchField, GeoMesh > >( new GeometricField< Type, PatchField, GeoMesh >( *io, *mesh, dm, patchFieldType ) )
  {
#ifdef OUR_DEBUG
    cout << "GeometricFieldHolder=" << this << nl;
#endif
  }

  template<class Type, template<class> class PatchField, class GeoMesh>
  GeometricFieldHolder< Type, PatchField, GeoMesh >::GeometricFieldHolder( const word& wd, 
									   const GeometricFieldHolder< Type, PatchField, GeoMesh >& field )
    : DependentHolder( &field )
    , smart_tmp< GeometricField< Type, PatchField, GeoMesh > >( new GeometricField< Type, PatchField, GeoMesh >( wd, field() ) )
  {
#ifdef OUR_DEBUG
    cout << "GeometricFieldHolder=" << this << nl;
#endif
  }

  template<class Type, template<class> class PatchField, class GeoMesh>
  GeometricFieldHolder< Type, PatchField, GeoMesh >::GeometricFieldHolder()
    : DependentHolder()
    , smart_tmp< GeometricField< Type, PatchField, GeoMesh > >()
  {
#ifdef OUR_DEBUG
    cout << "GeometricFieldHolder=" << this << nl;
#endif
  }

  
  template<class Type, template<class> class PatchField, class GeoMesh>
  SimpleHolder* GeometricFieldHolder< Type, PatchField, GeoMesh >::clone() const
  {
    return new GeometricFieldHolder< Type, PatchField, GeoMesh >( *this );
  }
  
  template<class Type, template<class> class PatchField, class GeoMesh>
  GeometricFieldHolder< Type, PatchField, GeoMesh >::~GeometricFieldHolder()
  {
#ifdef OUR_DEBUG
    cout << "~GeometricFieldHolder=" << this << nl;
#endif
  }
  
  
  //-------------------------------------------------------------------------
  template<class Type, template<class> class PatchField, class GeoMesh>
  GeometricField< Type, PatchField, GeoMesh >& 
  GeometricFieldHolder< Type, PatchField, GeoMesh >::ref()
  {
    return this->operator()();
  }

  template<class Type, template<class> class PatchField, class GeoMesh>
  void GeometricFieldHolder< Type, PatchField, GeoMesh >::operator = ( const GeometricFieldHolder< Type, PatchField, GeoMesh >& field )
  {
    if ( this->empty() )
    {
      Args::operator=( field );
      smart_tmp< GeometricField< Type, PatchField, GeoMesh > >::operator=( field );
    }
    else
    {
      this->ref() = field();
    }
  }

  template<class Type, template<class> class PatchField, class GeoMesh>
  void GeometricFieldHolder< Type, PatchField, GeoMesh >::operator = ( const dimensioned< Type >& dmT )
  {
    if ( this->empty() )
    {
      FatalErrorIn("GeometricFieldHolder< Type, PatchField, GeoMesh >::operator = ( const dimensioned< Type >& )")
                << "attempt to assign to uninitialized holder"
                << abort(FatalError);      
    }
      this->ref() = dmT;
  }
  
  template<class Type, template<class> class PatchField, class GeoMesh>
  void GeometricFieldHolder< Type, PatchField, GeoMesh >::operator = ( const smart_tmp< GeometricField< Type, PatchField, GeoMesh > >& field )
  {
    if ( this->empty() )
    {
      FatalErrorIn("GeometricFieldHolder< Type, PatchField, GeoMesh >::operator = ( const smart_tmp< GeometricField< Type, PatchField, GeoMesh > >& )")
                << "attempt to assign to uninitialized holder"
                << abort(FatalError);      
    }

    this->ref() = field();

  }
  
  template<class Type, template<class> class PatchField, class GeoMesh>
  void GeometricFieldHolder< Type, PatchField, GeoMesh >::operator -= ( const smart_tmp< GeometricField< Type, PatchField, GeoMesh > >& field)
  {
    if ( this->empty() )
    {
      FatalErrorIn("GeometricFieldHolder< Type, PatchField, GeoMesh >::operator -= ( const smart_tmp< GeometricField< Type, PatchField, GeoMesh > >& )")
                << "attempt to assign to uninitialized holder"
                << abort(FatalError);      
    }
    this->ref() -= field();
  }

  template<class Type, template<class> class PatchField, class GeoMesh>
  void GeometricFieldHolder< Type, PatchField, GeoMesh >::operator += ( const smart_tmp< GeometricField< Type, PatchField, GeoMesh > >& field)
  {
    if ( this->empty() )
    {
      FatalErrorIn("GeometricFieldHolder< Type, PatchField, GeoMesh >::operator += ( const smart_tmp< GeometricField< Type, PatchField, GeoMesh > >&  )")
                << "attempt to assign to uninitialized holder"
                << abort(FatalError);      
    }
    this->ref() += field();
  }

  template<class Type, template<class> class PatchField, class GeoMesh>
  void GeometricFieldHolder< Type, PatchField, GeoMesh >::operator /= ( const smart_tmp< GeometricField< scalar, PatchField, GeoMesh > >& field)
  {
    if ( this->empty() )
    {
      FatalErrorIn("GeometricFieldHolder< Type, PatchField, GeoMesh >::operator /= ( const smart_tmp< GeometricField< Type, PatchField, GeoMesh > >& )")
                << "attempt to assign to uninitialized holder"
                << abort(FatalError);      
    }
    this->ref() /= field();
  }

  template<class Type, template<class> class PatchField, class GeoMesh>
  void GeometricFieldHolder< Type, PatchField, GeoMesh >::operator *= ( const smart_tmp< GeometricField< scalar, PatchField, GeoMesh > >& field)
  {
    if ( this->empty() )
    {
      FatalErrorIn("GeometricFieldHolder< Type, PatchField, GeoMesh >::operator *= ( const smart_tmp< GeometricField< Type, PatchField, GeoMesh > >& )")
                << "attempt to assign to uninitialized holder"
                << abort(FatalError);      
    }
    this->ref() *= field();
  }

  template<class Type, template<class> class PatchField, class GeoMesh>
  void GeometricFieldHolder< Type, PatchField, GeoMesh >::operator += ( const dimensioned< Type >& dmT )
  {
    if ( this->empty() )
    {
      FatalErrorIn("GeometricFieldHolder< Type, PatchField, GeoMesh >::operator += ( const dimensioned< Type >& )")
                << "attempt to assign to uninitialized holder"
                << abort(FatalError);      
    }
      this->ref() += dmT;
  }

  template<class Type, template<class> class PatchField, class GeoMesh>
  void GeometricFieldHolder< Type, PatchField, GeoMesh >::operator -= ( const dimensioned< Type >& dmT )
  {
    if ( this->empty() )
    {
      FatalErrorIn("GeometricFieldHolder< Type, PatchField, GeoMesh >::operator -= ( const dimensioned< Type >& )")
                << "attempt to assign to uninitialized holder"
                << abort(FatalError);      
    }
      this->ref() -= dmT;
  }

  template<class Type, template<class> class PatchField, class GeoMesh>
  void GeometricFieldHolder< Type, PatchField, GeoMesh >::operator *= ( const dimensioned< scalar >& dmT )
  {
    if ( this->empty() )
    {
      FatalErrorIn("GeometricFieldHolder< Type, PatchField, GeoMesh >::operator *= ( const dimensioned< scalar >& )")
                << "attempt to assign to uninitialized holder"
                << abort(FatalError);      
    }
      this->ref() *= dmT;
  }

  template<class Type, template<class> class PatchField, class GeoMesh>
  void GeometricFieldHolder< Type, PatchField, GeoMesh >::operator /= ( const dimensioned< scalar >& dmT )
  {
    if ( this->empty() )
    {
      FatalErrorIn("GeometricFieldHolder< Type, PatchField, GeoMesh >::operator /= ( const dimensioned< scalar >& )")
                << "attempt to assign to uninitialized holder"
                << abort(FatalError);      
    }
      this->ref() /= dmT;
  }
  
  template<class Type, template<class> class PatchField, class GeoMesh>
  void GeometricFieldHolder< Type, PatchField, GeoMesh >::operator == ( const smart_tmp< GeometricField< Type, PatchField, GeoMesh > >& field )
  {
    if ( this->empty() )
    {
      FatalErrorIn("GeometricFieldHolder< Type, PatchField, GeoMesh >::operator == ( const smart_tmp< GeometricField< Type, PatchField, GeoMesh > >& )")
                << "attempt run operator== on uninitialized holder"
                << abort(FatalError);      
    }

    this->ref() == field();

  }


  template<class Type, template<class> class PatchField, class GeoMesh>
  void GeometricFieldHolder< Type, PatchField, GeoMesh >::operator () ( const GeometricFieldHolder< Type, PatchField, GeoMesh >& field )
  {
    Args::operator=( field );
    smart_tmp< GeometricField< Type, PatchField, GeoMesh > >::operator=( field );
  }
 
  
} //Foam


//---------------------------------------------------------------------------

