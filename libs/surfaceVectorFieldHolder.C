#ifndef surfaceVectorFieldHolder_C
#define surfaceVectorFieldHolder_C


//---------------------------------------------------------------------------
#include "surfaceVectorFieldHolder.H"
#include "IOobjectHolder.H"
#include "fvMeshHolder.H"
#include "surfaceScalarFieldHolder.H"

//---------------------------------------------------------------------------
namespace Foam
{

  surfaceVectorFieldHolder::surfaceVectorFieldHolder( const IOobjectHolder& io, const fvMeshHolder& mesh ) :
    surfaceVectorFieldArgs( mesh ),
    tmp< surfaceVectorField >( new surfaceVectorField( *io, *mesh ) )
  {
#ifdef OUR_DEBUG
    cout << "flusurfaceVectorField = " << this << nl;
#endif
  }

  surfaceVectorFieldHolder::surfaceVectorFieldHolder( const tmp< surfaceVectorField>& tmp_gf, const fvMeshHolder& mesh ) : 
    surfaceVectorFieldArgs( mesh ), 
    tmp< surfaceVectorField >( tmp_gf )
  {
#ifdef OUR_DEBUG
    cout << "flusurfaceVectorField = " << this << nl;
#endif
  }


  surfaceVectorFieldHolder::~surfaceVectorFieldHolder()
  {
#ifdef OUR_DEBUG
    cout << "~flusurfaceVectorField = " << this << nl;
#endif
  }


} //Foam


//---------------------------------------------------------------------------
#endif
