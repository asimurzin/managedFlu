#ifndef compressibleRASModelHolder_hpp
#define compressibleRASModelHolder_hpp


//---------------------------------------------------------------------------
#include "common.hpp"


//---------------------------------------------------------------------------
#if FOAM_VERSION( >=, 020000 )
#include "turbulenceModels/compressible/RASModel_impl/RASModelHolder_020000.hpp"
#endif


#if FOAM_VERSION( <, 020000 )
#include "turbulenceModels/compressible/RASModel_impl/RASModelHolder_010701.hpp"
#endif



//---------------------------------------------------------------------------
#endif
