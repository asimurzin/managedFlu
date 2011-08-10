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
  class GeometricFieldHolder : 
    public GeometricFieldArgs, 
    public tmp< GeometricField< Type, PatchField, GeoMesh > >
  {
  public:
    GeometricFieldHolder( const IOobjectHolder&, const fvMeshHolder& );
    GeometricFieldHolder( const tmp< GeometricField< Type, PatchField, GeoMesh > >& , const fvMeshHolder& );
    GeometricFieldHolder( const IOobjectHolder&, const GeometricFieldHolder< Type, PatchField, GeoMesh >& );
    
    ~GeometricFieldHolder();
    
    GeometricField< Type, PatchField, GeoMesh >& ref();
    
    void operator = ( const GeometricFieldHolder< Type, PatchField, GeoMesh >& );
    void operator-= ( const GeometricFieldHolder< Type, PatchField, GeoMesh >& );

  private:
     GeometricFieldHolder(); // not implemented
    // GeometricFieldHolder( const GeometricFieldHolder& ); // not implemented 
    // void operator = ( const GeometricFieldHolder& ); // not implemented 
  };
  
} // Foam


//---------------------------------------------------------------------------
#include "GeometricFieldHolder.C"


//---------------------------------------------------------------------------
#endif
