#ifndef geometricFieldFunctionsMM_C
#define geometricFieldFunctionsMM_C


//---------------------------------------------------------------------------
#include "geometricFieldFunctionsMM.H"


//---------------------------------------------------------------------------
namespace Foam
{

   surfaceScalarFieldHolder mag( const surfaceScalarFieldHolder&  field)
   {
     return surfaceScalarFieldHolder( mag( field() ), field.get_fvMeshArg() );
   }

} //Foam


//---------------------------------------------------------------------------
#endif
