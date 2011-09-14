//---------------------------------------------------------------------------
#include "RASModelHolder.hpp"



//---------------------------------------------------------------------------
#if FOAM_VERSION( >=, 020000 )
#include "turbulenceModels/compressible/RASModel_impl/RASModelHolder_020000.cpp"
#endif


#if FOAM_VERSION( <, 020000 )
#include "turbulenceModels/compressible/RASModel_impl/RASModelHolder_010701.cpp"
#endif


//---------------------------------------------------------------------------
