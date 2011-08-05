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


//---------------------------------------------------------------------------
   surfaceVectorFieldHolder operator+ ( const surfaceVectorFieldHolder& field1, const surfaceVectorFieldHolder& field2 )
   {
     return surfaceVectorFieldHolder( field1() + field2(), field1.get_fvMeshArg() );
   }

   surfaceScalarFieldHolder operator& ( const surfaceVectorFieldHolder& field1, const surfaceVectorField& field2 )
   {
     return surfaceScalarFieldHolder( field1() & field2, field1.get_fvMeshArg() );
   }

} //Foam


//---------------------------------------------------------------------------
#endif
