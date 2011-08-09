#ifndef volScalarFieldHolder_C
#define volScalarFieldHolder_C


//---------------------------------------------------------------------------
#include "volScalarFieldHolder.H"
#include "IOobjectHolder.H"
#include "fvMeshHolder.H"

//---------------------------------------------------------------------------
namespace Foam
{

  volScalarFieldHolder::volScalarFieldHolder( const IOobjectHolder& io, const fvMeshHolder& mesh ) :
    volScalarFieldArgs( mesh ),
    tmp< volScalarField >( new volScalarField( *io, *mesh ) )
  {
#ifdef OUR_DEBUG
    cout << "fluvolScalarField = " << this << nl;
#endif
  }

  volScalarFieldHolder::volScalarFieldHolder( const tmp< volScalarField>& tmp_gf, const fvMeshHolder& mesh ) : 
    volScalarFieldArgs( mesh ), 
    tmp< volScalarField >( tmp_gf )
  {
#ifdef OUR_DEBUG
    cout << "fluvolScalarField = " << this << nl;
#endif
  }


  volScalarFieldHolder::~volScalarFieldHolder()
  {
#ifdef OUR_DEBUG
    cout << "~fluvolScalarField = " << this << nl;
#endif
  }


} //Foam


//---------------------------------------------------------------------------
#endif
