#ifndef adjustPhi_hpp
#define adjustPhi_hpp


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
