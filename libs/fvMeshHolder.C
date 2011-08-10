#ifndef fvMeshHolder_C
#define fvMeshHolder_C


//---------------------------------------------------------------------------
#include "fvMeshHolder.H"
#include "IOobjectHolder.H"
#include "volFieldsMM.H"
#include "surfaceFieldsMM.H"


//---------------------------------------------------------------------------
namespace Foam
{

  fvMeshHolder::fvMeshHolder( const IOobjectHolder& io ) : 
    fvMeshArgs( io ),
    boost::shared_ptr< fvMesh >( new fvMesh( *io ) ),
    objectRegistryHolder( io ),
    IOobjectHolder( io )
  {
#ifdef OUR_DEBUG  
    cout << "fvMeshHolder=" << this << nl;
#endif
  }

  fvMeshHolder::~fvMeshHolder()
  {
#ifdef OUR_DEBUG
    cout << "~fvMeshHolder=" << this << nl;
#endif
  }

  //-------------------------------------------------------------------------
  surfaceVectorFieldHolder fvMeshHolder::Sf() const
  {
    return surfaceVectorFieldHolder( tmp< surfaceVectorField >( operator->()->Sf() ), *this );
  }
  surfaceScalarFieldHolder fvMeshHolder::magSf() const
  {
    return surfaceScalarFieldHolder( tmp< surfaceScalarField >( operator->()->magSf() ), *this );
  }
  surfaceScalarFieldHolder fvMeshHolder::phi() const
  {
    return surfaceScalarFieldHolder( tmp< surfaceScalarField >( operator->()->phi() ), *this );
  }
  volVectorFieldHolder fvMeshHolder::C() const
  {
    return volVectorFieldHolder( tmp< volVectorField >( operator->()->C() ), *this );
  }
  surfaceVectorFieldHolder fvMeshHolder::Cf() const
  {
    return surfaceVectorFieldHolder( tmp< surfaceVectorField >( operator->()->Cf() ), *this );
  }

} //Foam


//---------------------------------------------------------------------------
#endif
