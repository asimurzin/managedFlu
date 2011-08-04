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
    cout << "fluvolScalarField = " << this << nl;
  }

  volScalarFieldHolder::volScalarFieldHolder( const tmp< volScalarField>& tmp_gf, const fvMeshHolder& mesh ) : 
    volScalarFieldArgs( mesh ), 
    tmp< volScalarField >( tmp_gf )
  {
    cout << "fluvolScalarField = " << this << nl;
  }


  volScalarFieldHolder::~volScalarFieldHolder()
  {
    cout << "~fluvolScalarField = " << this << nl;
  }


//---------------------------------------------------------------------------
   volScalarFieldHolder operator+ ( const volScalarFieldHolder& field1, const volScalarFieldHolder& field2 )
   {
     return volScalarFieldHolder( field1() + field2(), field1.get_fvMeshArg() );
   }

} //Foam


//---------------------------------------------------------------------------
#endif
