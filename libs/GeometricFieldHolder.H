#ifndef GeometricFieldHolder_H
#define GeometricFieldHolder_H


//---------------------------------------------------------------------------
#include <GeometricField.H>
#include <tmp.H>
#include "GeometricFieldArgs.H"


//---------------------------------------------------------------------------
namespace Foam
{

  class IOobjectHolder;
  
  template<class Type, template<class> class PatchField, class GeoMesh>
  class GeometricFieldHolder 
    : public GeometricFieldArgs
    , public tmp< GeometricField< Type, PatchField, GeoMesh > >
  {
  public:
    GeometricFieldHolder( const IOobjectHolder&, const fvMeshHolder& );
    GeometricFieldHolder( const tmp< GeometricField< Type, PatchField, GeoMesh > >& , const fvMeshHolder& );
    GeometricFieldHolder( const IOobjectHolder&, const GeometricFieldHolder< Type, PatchField, GeoMesh >& );
    GeometricFieldHolder();
    
    ~GeometricFieldHolder();
    
    GeometricField< Type, PatchField, GeoMesh >& ref();
    
    void operator = ( const GeometricFieldHolder< Type, PatchField, GeoMesh >& );
    void operator -= ( const GeometricFieldHolder< Type, PatchField, GeoMesh >& );
    void operator()( const GeometricFieldHolder< Type, PatchField, GeoMesh >& );
    const GeometricField< Type, PatchField, GeoMesh >& operator()() const;
    GeometricField< Type, PatchField, GeoMesh >& operator()();

  };
} // Foam


//---------------------------------------------------------------------------
#include "GeometricFieldHolder.C"


//---------------------------------------------------------------------------
#endif
