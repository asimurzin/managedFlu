#ifndef adjustPhi_hpp
#define adjustPhi_hpp


//---------------------------------------------------------------------------
#include <adjustPhi.H>
#include "volFields.hpp"
#include "surfaceFields.hpp"


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
