#ifndef fvcMM_H
#define fvcMM_H


//---------------------------------------------------------------------------
#include <fvc.H>
#include "surfaceScalarFieldHolder.H"
#include "volScalarFieldHolder.H"


//---------------------------------------------------------------------------
namespace Foam
{
  namespace fvc
  {
    volScalarFieldHolder surfaceSum( const surfaceScalarFieldHolder& );
  }
} // Foam


//---------------------------------------------------------------------------
#endif
