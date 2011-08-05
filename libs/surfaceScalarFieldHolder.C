#ifndef surfaceScalarFieldHolder_C
#define surfaceScalarFieldHolder_C


//---------------------------------------------------------------------------
#include "surfaceScalarFieldHolder.H"
#include "IOobjectHolder.H"
#include "fvMeshHolder.H"



//---------------------------------------------------------------------------
namespace Foam
{

  surfaceScalarFieldHolder::surfaceScalarFieldHolder( const IOobjectHolder& io, const fvMeshHolder& mesh ) :
    surfaceScalarFieldArgs( mesh ),
    tmp< surfaceScalarField >( new surfaceScalarField( *io, *mesh ) )
  {
#ifdef OUR_DEBUG
    cout << "flusurfaceScalarField = " << this << nl;
#endif
  }

  surfaceScalarFieldHolder::surfaceScalarFieldHolder( const IOobjectHolder& ioh, const surfaceScalarFieldHolder& ssfh ):
    surfaceScalarFieldArgs( ssfh.get_fvMeshArg() ),
    tmp< surfaceScalarField >( new surfaceScalarField( *ioh, ssfh() ) )
  {
#ifdef OUR_DEBUG
    cout << "flusurfaceScalarField = " << this << nl;
#endif
  }

  surfaceScalarFieldHolder::surfaceScalarFieldHolder( const tmp< surfaceScalarField>& tmp_gf, const fvMeshHolder& mesh ) : 
    surfaceScalarFieldArgs( mesh ), 
    tmp< surfaceScalarField >( tmp_gf )
  {
#ifdef OUR_DEBUG
    cout << "flusurfaceScalarField = " << this << nl;
#endif
  }


  surfaceScalarFieldHolder::~surfaceScalarFieldHolder()
  {
#ifdef OUR_DEBUG
    cout << "~flusurfaceScalarField = " << this << nl;
#endif
  }


//---------------------------------------------------------------------------
   surfaceScalarFieldHolder operator+ ( const surfaceScalarFieldHolder& field1, const surfaceScalarFieldHolder& field2 )
   {
     return surfaceScalarFieldHolder( field1() + field2(), field1.get_fvMeshArg() );
   }

} //Foam


//---------------------------------------------------------------------------
#endif
