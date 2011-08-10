#ifndef adjustPhiMM_H
#define adjustPhiMM_H


//---------------------------------------------------------------------------
#include <adjustPhi.H>
#include "volFieldsMM.H"
#include "surfaceFieldsMM.H"



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
