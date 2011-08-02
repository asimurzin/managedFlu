#ifndef fvMeshHolder_C
#define fvMeshHolder_C


//---------------------------------------------------------------------------
#include "fvMeshHolder.H"


//---------------------------------------------------------------------------
namespace Foam
{

  fvMeshHolder::fvMeshHolder( const IOobjectHolder& io ) : 
    IOobjectHolder( io ),
    boost::shared_ptr< fvMesh >( new fvMesh( *io ) )
  {
    cout << "fvMeshHolder=" << this << nl;
  }

  fvMeshHolder::fvMeshHolder() : 
    IOobjectHolder(),
    boost::shared_ptr< fvMesh >()
  {
    cout << "fvMeshHolder=" << this << nl;
  } 

  fvMeshHolder::~fvMeshHolder()
  {
    cout << "~fvMeshHolder=" << this << nl;
  }
} //Foam


//---------------------------------------------------------------------------
#endif
