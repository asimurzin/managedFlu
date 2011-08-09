#ifndef volVectorFieldHolder_C
#define volVectorFieldHolder_C


//---------------------------------------------------------------------------
#include "volVectorFieldHolder.H"
#include "IOobjectHolder.H"
#include "fvMeshHolder.H"

//---------------------------------------------------------------------------
namespace Foam
{
 //--------------------------------------------------------------------------
  volVectorFieldHolder::volVectorFieldHolder( const IOobjectHolder& io, const fvMeshHolder& mesh ) :
    volVectorFieldArgs( mesh ),
    tmp< volVectorField >( new volVectorField( *io, *mesh ) )
  {
#ifdef OUR_DEBUG
    cout << "fluvolVectorField = " << this << nl;
#endif
  }

  volVectorFieldHolder::volVectorFieldHolder( const tmp< volVectorField>& tmp_gf, const fvMeshHolder& mesh ) : 
    volVectorFieldArgs( mesh ), 
    tmp< volVectorField >( tmp_gf )
  {
#ifdef OUR_DEBUG
    cout << "fluvolVectorField = " << this << nl;
#endif
  }


  volVectorFieldHolder::~volVectorFieldHolder()
  {
#ifdef OUR_DEBUG
    cout << "~fluvolVectorField = " << this << nl;
#endif
  }
  //-------------------------------------------------------------------------
  void volVectorFieldHolder::operator=( const volVectorFieldHolder& field)
  {
    operator()()= field();
  }

  void volVectorFieldHolder::operator-=( const volVectorFieldHolder& field)
  {
    operator()()-= field();
  }

} //Foam


//---------------------------------------------------------------------------
#endif
