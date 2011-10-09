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
    cout << "GeometricFieldHolder=" << this << nl;
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
  void GeometricFieldHolder< Type, PatchField, GeoMesh >::operator () ( const GeometricFieldHolder< Type, PatchField, GeoMesh >& field )
  {
    Args::operator=( field );
    smart_tmp< GeometricField< Type, PatchField, GeoMesh > >::operator=( field );
  }
 
  
} //Foam


//---------------------------------------------------------------------------

