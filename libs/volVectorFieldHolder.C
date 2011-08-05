#ifndef volVectorFieldHolder_C
#define volVectorFieldHolder_C


//---------------------------------------------------------------------------
#include "volVectorFieldHolder.H"
#include "IOobjectHolder.H"
#include "fvMeshHolder.H"

//---------------------------------------------------------------------------
namespace Foam
{

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


//---------------------------------------------------------------------------
   volVectorFieldHolder operator+ ( const volVectorFieldHolder& field1, const volVectorFieldHolder& field2 )
   {
     return volVectorFieldHolder( field1() + field2(), field1.get_fvMeshArg() );
   }

} //Foam


//---------------------------------------------------------------------------
#endif
