#ifndef adjustPhiMM_H
#define adjustPhiMM_H


//---------------------------------------------------------------------------
#include <adjustPhi.H>
#include "volScalarFieldHolder.H"
#include "volVectorFieldHolder.H"
#include "surfaceScalarFieldHolder.H"


//---------------------------------------------------------------------------
namespace Foam
{

  inline bool adjustPhi( surfaceScalarFieldHolder& phi,
                         const volVectorFieldHolder& U,
                         volScalarFieldHolder& p )
  {
    return adjustPhi( phi(), U(), p() );
  }

} // Foam


//---------------------------------------------------------------------------
#endif
