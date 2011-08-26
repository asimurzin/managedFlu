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
    : GeometricFieldArgs( mesh )
    , smart_tmp< GeometricField< Type, PatchField, GeoMesh > >( new GeometricField< Type, PatchField, GeoMesh >( *io, *mesh ) )
    , universalHolder()
  {
#ifdef OUR_DEBUG
    cout << "GeometricFieldHolder=" << this << nl;
#endif
  }

  template<class Type, template<class> class PatchField, class GeoMesh>
  GeometricFieldHolder< Type, PatchField, GeoMesh >::GeometricFieldHolder( const tmp< GeometricField< Type, PatchField, GeoMesh > >& tmp_gf, 
									   const universalArgs& args ) 
    : GeometricFieldArgs( args )
    , smart_tmp< GeometricField< Type, PatchField, GeoMesh > >( tmp_gf )
    , universalHolder()
  {
#ifdef OUR_DEBUG
    cout << "GeometricFieldHolder=" << this << nl;
#endif
  }

  template<class Type, template<class> class PatchField, class GeoMesh>
  GeometricFieldHolder< Type, PatchField, GeoMesh >::GeometricFieldHolder( const tmp< GeometricField< Type, PatchField, GeoMesh > >& tmp_gf, 
									   const GeometricFieldArgs& args ) 
    : GeometricFieldArgs( args )
    , smart_tmp< GeometricField< Type, PatchField, GeoMesh > >( tmp_gf )
    , universalHolder()
  {
#ifdef OUR_DEBUG
    cout << "GeometricFieldHolder=" << this << nl;
#endif
  }

  template<class Type, template<class> class PatchField, class GeoMesh>
  GeometricFieldHolder< Type, PatchField, GeoMesh >::GeometricFieldHolder( const IOobjectHolder& io, 
									   const GeometricFieldHolder< Type, PatchField, GeoMesh >& field )
    : GeometricFieldArgs( field.mesh() )
    , smart_tmp< GeometricField< Type, PatchField, GeoMesh > >( new GeometricField< Type, PatchField, GeoMesh >( *io, field() ) )
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
  void GeometricFieldHolder< Type, PatchField, GeoMesh >::operator () ( const GeometricFieldHolder< Type, PatchField, GeoMesh >& field )
  {
    GeometricFieldArgs::operator=( field );
    smart_tmp< GeometricField< Type, PatchField, GeoMesh > >::operator=( field );
  }
 
  //-------------------------------------------------------------------------
  template<class Type, template<class> class PatchField, class GeoMesh>
  GeometricFieldArgs createArgs( const GeometricFieldHolder< Type, PatchField, GeoMesh >& field )
  {
    if ( field.mesh().get() != 0 )
      return field.mesh();
    
    return universalArgs( &field );
  }
  
  template<class Type, template<class> class PatchField, class GeoMesh, 
           class Type1, template<class> class PatchField1, class GeoMesh1>
  GeometricFieldArgs createArgs( const GeometricFieldHolder< Type, PatchField, GeoMesh >& field, 
                                 const GeometricFieldHolder< Type1, PatchField1, GeoMesh1 >&  field1)
  {
    if ( field.mesh().get() != 0 )
      return field.mesh();
    else if ( field1.mesh().get() != 0 )
      return field1.mesh();
    
    return universalArgs( &field, &field1 );
  }

  template<class Type, template<class> class PatchField, class GeoMesh, 
           class Type1, template<class> class PatchField1, class GeoMesh1,
           class Type2, template<class> class PatchField2, class GeoMesh2>
  GeometricFieldArgs createArgs( const GeometricFieldHolder< Type, PatchField, GeoMesh >& field, 
                                 const GeometricFieldHolder< Type1, PatchField1, GeoMesh1 >& field1,
                                 const GeometricFieldHolder< Type2, PatchField2, GeoMesh2 >& field2 )
  {
    if ( field.mesh().get() != 0 )
      return field.mesh();
    else if ( field1.mesh().get() != 0 )
      return field1.mesh();
    else if ( field2.mesh().get() != 0 )
      return field2.mesh();
    
    return universalArgs( &field, &field1, &field2 );
  }

  
} //Foam


//---------------------------------------------------------------------------

