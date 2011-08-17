#ifndef GeometricFieldHolder_hpp
#define GeometricFieldHolder_hpp


//---------------------------------------------------------------------------
#include "GeometricFieldArgs.hpp"

#include <GeometricField.H>
#include <ext_tmp/ext_tmp.hpp>


//---------------------------------------------------------------------------
namespace Foam
{

  class IOobjectHolder;
  
  template<class Type, template<class> class PatchField, class GeoMesh>
  class GeometricFieldHolder 
    : public GeometricFieldArgs
    , public ext_tmp< GeometricField< Type, PatchField, GeoMesh > >
  {
  public:
    GeometricFieldHolder( const IOobjectHolder&, const fvMeshHolder& );
    GeometricFieldHolder( const tmp< GeometricField< Type, PatchField, GeoMesh > >& , const fvMeshHolder& );
    GeometricFieldHolder( const IOobjectHolder&, const GeometricFieldHolder< Type, PatchField, GeoMesh >& );
    GeometricFieldHolder( const GeometricField< Type, PatchField, GeoMesh >& );
    GeometricFieldHolder( const tmp< GeometricField< Type, PatchField, GeoMesh > >& );
    GeometricFieldHolder( const ext_tmp< GeometricField< Type, PatchField, GeoMesh > >& );
    GeometricFieldHolder();
    
    ~GeometricFieldHolder();
    
    GeometricField< Type, PatchField, GeoMesh >& ref();
    
    void operator = ( const GeometricFieldHolder< Type, PatchField, GeoMesh >& );
    void operator -= ( const GeometricFieldHolder< Type, PatchField, GeoMesh >& );
    void operator()( const GeometricFieldHolder< Type, PatchField, GeoMesh >& );
    
    using ext_tmp< GeometricField< Type, PatchField, GeoMesh > >::operator();
  };
} // Foam


//---------------------------------------------------------------------------
#include "GeometricFieldHolder.cpp"


//---------------------------------------------------------------------------
#endif