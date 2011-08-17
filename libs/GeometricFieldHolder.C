//---------------------------------------------------------------------------
#include "GeometricFieldHolder.H"
#include "IOobjectHolder.H"
#include "fvMeshHolder.H"


//---------------------------------------------------------------------------
namespace Foam
{

  template<class Type, template<class> class PatchField, class GeoMesh>
  GeometricFieldHolder< Type, PatchField, GeoMesh >::GeometricFieldHolder( const IOobjectHolder& io, 
									   const fvMeshHolder& mesh ) 
    : GeometricFieldArgs( mesh )
    , ext_tmp< GeometricField< Type, PatchField, GeoMesh > >( new GeometricField< Type, PatchField, GeoMesh >( *io, *mesh ) )
  {
#ifdef OUR_DEBUG
    cout << "GeometricFieldHolder=" << this << nl;
#endif
  }

  template<class Type, template<class> class PatchField, class GeoMesh>
  GeometricFieldHolder< Type, PatchField, GeoMesh >::GeometricFieldHolder( const tmp< GeometricField< Type, PatchField, GeoMesh > >& tmp_gf, 
									   const fvMeshHolder& mesh ) 
    : GeometricFieldArgs( mesh )
    , ext_tmp< GeometricField< Type, PatchField, GeoMesh > >( tmp_gf )
  {
#ifdef OUR_DEBUG
    cout << "GeometricFieldHolder=" << this << nl;
#endif
  }

  template<class Type, template<class> class PatchField, class GeoMesh>
  GeometricFieldHolder< Type, PatchField, GeoMesh >::GeometricFieldHolder( const IOobjectHolder& io, 
									   const GeometricFieldHolder< Type, PatchField, GeoMesh >& field )
    : GeometricFieldArgs( field.mesh() )
    , ext_tmp< GeometricField< Type, PatchField, GeoMesh > >( new GeometricField< Type, PatchField, GeoMesh >( *io, field() ) )
  {
#ifdef OUR_DEBUG
    cout << "GeometricFieldHolder=" << this << nl;
#endif
  }

  template<class Type, template<class> class PatchField, class GeoMesh>
  GeometricFieldHolder< Type, PatchField, GeoMesh >::GeometricFieldHolder()
    : GeometricFieldArgs()
    , ext_tmp< GeometricField< Type, PatchField, GeoMesh > >()
  {
#ifdef OUR_DEBUG
    cout << "GeometricFieldHolder=" << this << nl;
#endif
  }

  template<class Type, template<class> class PatchField, class GeoMesh>
  GeometricFieldHolder< Type, PatchField, GeoMesh >::GeometricFieldHolder( const GeometricField< Type, PatchField, GeoMesh >& gf )
    : GeometricFieldArgs()
    , ext_tmp< GeometricField< Type, PatchField, GeoMesh > >( gf )
  {
#ifdef OUR_DEBUG
    cout << "GeometricFieldHolder=" << this << nl;
#endif
  }

  template<class Type, template<class> class PatchField, class GeoMesh>
  GeometricFieldHolder< Type, PatchField, GeoMesh >::GeometricFieldHolder( const tmp< GeometricField< Type, PatchField, GeoMesh > >& gf )
    : GeometricFieldArgs()
    , ext_tmp< GeometricField< Type, PatchField, GeoMesh > >( gf )
  {
#ifdef OUR_DEBUG
    cout << "GeometricFieldHolder=" << this << nl;
#endif
  }

  template<class Type, template<class> class PatchField, class GeoMesh>
  GeometricFieldHolder< Type, PatchField, GeoMesh >::GeometricFieldHolder( const ext_tmp< GeometricField< Type, PatchField, GeoMesh > >& gf )
    : GeometricFieldArgs()
    , ext_tmp< GeometricField< Type, PatchField, GeoMesh > >( gf )
  {
#ifdef OUR_DEBUG
    cout << "GeometricFieldHolder=" << this << nl;
#endif
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
      ext_tmp< GeometricField< Type, PatchField, GeoMesh > >::operator=( field );
    }
    else
    {
      this->ref() = field();
    }
  }
  
  template<class Type, template<class> class PatchField, class GeoMesh>
  void GeometricFieldHolder< Type, PatchField, GeoMesh >::operator -= ( const GeometricFieldHolder< Type, PatchField, GeoMesh >& field)
  {
    this->ref() -= field();
  }

  template<class Type, template<class> class PatchField, class GeoMesh>
  void GeometricFieldHolder< Type, PatchField, GeoMesh >::operator () ( const GeometricFieldHolder< Type, PatchField, GeoMesh >& field )
  {
    GeometricFieldArgs::operator=( field );
    ext_tmp< GeometricField< Type, PatchField, GeoMesh > >::operator=( field );
  }
 
} //Foam


//---------------------------------------------------------------------------

