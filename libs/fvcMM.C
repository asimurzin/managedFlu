#ifndef fvcMM_C
#define fvcMM_C


//---------------------------------------------------------------------------
#include "fvcMM.H"


//---------------------------------------------------------------------------
namespace Foam
{
  namespace fvc
  {
    volScalarFieldHolder surfaceSum( const surfaceScalarFieldHolder& field )
    {
     return volScalarFieldHolder( surfaceSum( field() ), field.get_fvMeshArg() );
    }
  }
} //Foam


//---------------------------------------------------------------------------
#endif
