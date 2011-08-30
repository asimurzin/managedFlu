#ifndef GeometricFieldHolder_hpp
#define GeometricFieldHolder_hpp


//---------------------------------------------------------------------------
#include "universalHolder.hpp"
#include "Deps.hpp"
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
    //reference constructor
    GeometricFieldHolder( const IOobjectHolder&, const fvMeshHolder& );
    GeometricFieldHolder( const IOobjectHolder&, const GeometricFieldHolder< Type, PatchField, GeoMesh >& );
    GeometricFieldHolder( const word&, const GeometricFieldHolder< Type, PatchField, GeoMesh >& );
    
    // constructors with deps
    GeometricFieldHolder( const GeometricField< Type, PatchField, GeoMesh >& , const Deps& );
    GeometricFieldHolder( const tmp< GeometricField< Type, PatchField, GeoMesh > >& , const Deps& );

    GeometricFieldHolder();
    
    ~GeometricFieldHolder();
    
    virtual universalHolder* clone() const;
    
    GeometricField< Type, PatchField, GeoMesh >& ref();
    
    void operator = ( const GeometricFieldHolder< Type, PatchField, GeoMesh >& );
    void operator = ( const GeometricField< Type, PatchField, GeoMesh >& );
    
    void operator -= ( const GeometricFieldHolder< Type, PatchField, GeoMesh >& );
    void operator -= ( const GeometricField< Type, PatchField, GeoMesh >& );
    
    void operator += ( const GeometricFieldHolder< Type, PatchField, GeoMesh >& );
    void operator += ( const GeometricField< Type, PatchField, GeoMesh >& );
    void operator += ( const dimensioned< Type >& );

    //void operator()( const GeometricFieldHolder< Type, PatchField, GeoMesh >& );
    
    using smart_tmp< GeometricField< Type, PatchField, GeoMesh > >::operator();
  };

} // Foam


//---------------------------------------------------------------------------
#include "GeometricFieldHolder.cpp"


//---------------------------------------------------------------------------
#endif
