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
    
    GeometricFieldHolder( const GeometricField< Type, PatchField, GeoMesh >& , const GeometricFieldArgs& );
    GeometricFieldHolder( const tmp< GeometricField< Type, PatchField, GeoMesh > >& , const GeometricFieldArgs& );

    GeometricFieldHolder( const IOobjectHolder&, const GeometricFieldHolder< Type, PatchField, GeoMesh >& );
    //GeometricFieldHolder( const IOobjectHolder&, const GeometricField< Type, PatchField, GeoMesh >&, const GeometricFieldArgs& );
    
    GeometricFieldHolder( const word&, const GeometricFieldHolder< Type, PatchField, GeoMesh >& );
    //GeometricFieldHolder( const word&, const GeometricField< Type, PatchField, GeoMesh >&, const GeometricFieldArgs& );


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

  template<class Type, template<class> class PatchField, class GeoMesh>
  GeometricFieldArgs createArgs( const GeometricFieldHolder< Type, PatchField, GeoMesh >& );
  
  template<class Type, template<class> class PatchField, class GeoMesh, 
           class Type1, template<class> class PatchField1, class GeoMesh1>
  GeometricFieldArgs createArgs( const GeometricFieldHolder< Type, PatchField, GeoMesh >&, 
                                 const GeometricFieldHolder< Type1, PatchField1, GeoMesh1 >& );

  template<class Type, template<class> class PatchField, class GeoMesh, 
           class Type1, template<class> class PatchField1, class GeoMesh1,
           class Type2, template<class> class PatchField2, class GeoMesh2>
  GeometricFieldArgs createArgs( const GeometricFieldHolder< Type, PatchField, GeoMesh >&, 
                                 const GeometricFieldHolder< Type1, PatchField1, GeoMesh1 >&,
                                 const GeometricFieldHolder< Type2, PatchField2, GeoMesh2 >& );
  

} // Foam


//---------------------------------------------------------------------------
#include "GeometricFieldHolder.cpp"


//---------------------------------------------------------------------------
#endif
