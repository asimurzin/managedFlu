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
    : GeometricFieldArgs( Foam::deps( &mesh ) )
    , smart_tmp< GeometricField< Type, PatchField, GeoMesh > >( new GeometricField< Type, PatchField, GeoMesh >( *io, *mesh ) )
    , universalHolder()
  {
#ifdef OUR_DEBUG
    cout << "GeometricFieldHolder=" << this << nl;
#endif
  }

  template<class Type, template<class> class PatchField, class GeoMesh>
  GeometricFieldHolder< Type, PatchField, GeoMesh >::GeometricFieldHolder( const tmp< GeometricField< Type, PatchField, GeoMesh > >& tmp_gf, 
									   const Deps& args ) 
    : GeometricFieldArgs( args )
    , smart_tmp< GeometricField< Type, PatchField, GeoMesh > >( tmp_gf )
    , universalHolder()
  {
#ifdef OUR_DEBUG
    cout << "GeometricFieldHolder=" << this << nl;
#endif
  }

  template<class Type, template<class> class PatchField, class GeoMesh>
  GeometricFieldHolder< Type, PatchField, GeoMesh >::GeometricFieldHolder( const GeometricField< Type, PatchField, GeoMesh >& gf, 
									   const Deps& args ) 
    : GeometricFieldArgs( args )
    , smart_tmp< GeometricField< Type, PatchField, GeoMesh > >( gf )
    , universalHolder()
  {
#ifdef OUR_DEBUG
    cout << "GeometricFieldHolder=" << this << nl;
#endif
  }

  template<class Type, template<class> class PatchField, class GeoMesh>
  GeometricFieldHolder< Type, PatchField, GeoMesh >::GeometricFieldHolder( const IOobjectHolder& io, 
									   const GeometricFieldHolder< Type, PatchField, GeoMesh >& field )
    : GeometricFieldArgs( Foam::deps( &field ) )
    , smart_tmp< GeometricField< Type, PatchField, GeoMesh > >( new GeometricField< Type, PatchField, GeoMesh >( *io, field() ) )
    , universalHolder()
  {
#ifdef OUR_DEBUG
    cout << "GeometricFieldHolder=" << this << nl;
#endif
  }

  template<class Type, template<class> class PatchField, class GeoMesh>
  GeometricFieldHolder< Type, PatchField, GeoMesh >::GeometricFieldHolder( const word& wd, 
									   const GeometricFieldHolder< Type, PatchField, GeoMesh >& field )
    : GeometricFieldArgs( Foam::deps( &field ) )
    , smart_tmp< GeometricField< Type, PatchField, GeoMesh > >( new GeometricField< Type, PatchField, GeoMesh >( wd, field() ) )
    , universalHolder()
  {
#ifdef OUR_DEBUG
    cout << "GeometricFieldHolder=" << this << nl;
#endif
  }

  template<class Type, template<class> class PatchField, class GeoMesh>
  GeometricFieldHolder< Type, PatchField, GeoMesh >::GeometricFieldHolder()
    : GeometricFieldArgs()
    , smart_tmp< GeometricField< Type, PatchField, GeoMesh > >()
    , universalHolder()
  {
#ifdef OUR_DEBUG
    cout << "GeometricFieldHolder=" << this << nl;
#endif
  }

  
  template<class Type, template<class> class PatchField, class GeoMesh>
  universalHolder* GeometricFieldHolder< Type, PatchField, GeoMesh >::clone() const
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
      GeometricFieldArgs::operator=( field );
      smart_tmp< GeometricField< Type, PatchField, GeoMesh > >::operator=( field );
    }
    else
    {
      this->ref() = field();
    }
  }
  
  template<class Type, template<class> class PatchField, class GeoMesh>
  void GeometricFieldHolder< Type, PatchField, GeoMesh >::operator = ( const GeometricField< Type, PatchField, GeoMesh >& field )
  {
      this->ref() = field;
  }


  template<class Type, template<class> class PatchField, class GeoMesh>
  void GeometricFieldHolder< Type, PatchField, GeoMesh >::operator -= ( const GeometricFieldHolder< Type, PatchField, GeoMesh >& field)
  {
    this->ref() -= field();
  }

  template<class Type, template<class> class PatchField, class GeoMesh>
  void GeometricFieldHolder< Type, PatchField, GeoMesh >::operator -= ( const GeometricField< Type, PatchField, GeoMesh >& field)
  {
    this->ref() -= field;
  }

  template<class Type, template<class> class PatchField, class GeoMesh>
  void GeometricFieldHolder< Type, PatchField, GeoMesh >::operator += ( const GeometricFieldHolder< Type, PatchField, GeoMesh >& field)
  {
    this->ref() += field();
  }

  template<class Type, template<class> class PatchField, class GeoMesh>
  void GeometricFieldHolder< Type, PatchField, GeoMesh >::operator += ( const GeometricField< Type, PatchField, GeoMesh >& field)
  {
    this->ref() += field;
  }

  template<class Type, template<class> class PatchField, class GeoMesh>
  void GeometricFieldHolder< Type, PatchField, GeoMesh >::operator += ( const dimensioned< Type >& value)
  {
    this->ref() += value;
  }


/*
  template<class Type, template<class> class PatchField, class GeoMesh>
  void GeometricFieldHolder< Type, PatchField, GeoMesh >::operator () ( const GeometricFieldHolder< Type, PatchField, GeoMesh >& field )
  {
    GeometricFieldArgs::operator=( field );
    smart_tmp< GeometricField< Type, PatchField, GeoMesh > >::operator=( field );
  }
*/ 
  
} //Foam


//---------------------------------------------------------------------------

