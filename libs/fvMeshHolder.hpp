#ifndef fvMeshHolder_hpp
#define fvMeshHolder_hpp


//---------------------------------------------------------------------------
#include "DependentHolder.hpp"
#include "Deps.hpp"
#include "objectRegistryHolder.hpp"
#include "volFieldsFwd.hpp"
#include "surfaceFieldsFwd.hpp"

#include <fvMesh.H>
#include <boost/shared_ptr.hpp>


//---------------------------------------------------------------------------
namespace Foam
{
  class IOobjectHolder;
  
  class fvMeshHolder 
    : virtual public DependentHolder
    , public boost::shared_ptr< fvMesh >
    , public objectRegistryHolder
  {
  public:
    fvMeshHolder( const IOobjectHolder& io );
    
    virtual universalHolder* clone() const;
    
    fvMeshHolder();
    ~fvMeshHolder();

    using boost::shared_ptr< fvMesh >::operator*;
    using boost::shared_ptr< fvMesh >::operator->;
    using boost::shared_ptr< fvMesh >::get;

  };
} // Foam


//---------------------------------------------------------------------------
#endif
