#ifndef GeometricFieldHolder_hpp
#define GeometricFieldHolder_hpp


//---------------------------------------------------------------------------
#include "universalHolder.hpp"
#include "GeometricFieldArgs.hpp"
#include "smart_tmp/smart_tmp.hpp"

#include <GeometricField.H>


//---------------------------------------------------------------------------
namespace Foam
{

  class IOobjectHolder;
  
  template<class Type, template<class> class PatchField, class GeoMesh>
  class GeometricFieldHolder 
    : public GeometricFieldArgs
    , public smart_tmp< GeometricField< Type, PatchField, GeoMesh > >
    , public universalHolder
  {
  public:
    GeometricFieldHolder( const IOobjectHolder&, const fvMeshHolder& );
    GeometricFieldHolder( const tmp< GeometricField< Type, PatchField, GeoMesh > >& , const fvMeshHolder& );
    GeometricFieldHolder( const IOobjectHolder&, const GeometricFieldHolder< Type, PatchField, GeoMesh >& );
    GeometricFieldHolder( const GeometricField< Type, PatchField, GeoMesh >&, const universalArgs& );
    GeometricFieldHolder( const tmp< GeometricField< Type, PatchField, GeoMesh > >&, const universalArgs& );
    GeometricFieldHolder( const smart_tmp< GeometricField< Type, PatchField, GeoMesh > >&, const universalArgs& );
    GeometricFieldHolder();
    
    ~GeometricFieldHolder();
    
    GeometricField< Type, PatchField, GeoMesh >& ref();
    
    void operator = ( const GeometricFieldHolder< Type, PatchField, GeoMesh >& );
    void operator -= ( const GeometricFieldHolder< Type, PatchField, GeoMesh >& );
    void operator()( const GeometricFieldHolder< Type, PatchField, GeoMesh >& );
    
    using smart_tmp< GeometricField< Type, PatchField, GeoMesh > >::operator();
  };
} // Foam


//---------------------------------------------------------------------------
#include "GeometricFieldHolder.cpp"


//---------------------------------------------------------------------------
#endif
