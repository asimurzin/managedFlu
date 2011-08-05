#ifndef linearInterpolate_C
#define linearInterpolate_C


//---------------------------------------------------------------------------
#include "linearInterpolate.H"


//---------------------------------------------------------------------------
namespace Foam
{

   surfaceVectorFieldHolder linearInterpolate( const volVectorFieldHolder& field )
   {
     return surfaceVectorFieldHolder( linearInterpolate( field() ) , field.get_fvMeshArg() );
   }

} //Foam


//---------------------------------------------------------------------------
#endif
