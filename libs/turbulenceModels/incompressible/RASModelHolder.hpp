#ifndef incompressibleRASModelHolder_hpp
#define incompressibleRASModelHolder_hpp


//---------------------------------------------------------------------------
#include "common.hpp"


//---------------------------------------------------------------------------
#if FOAM_VERSION( >=, 020000 )
#include "turbulenceModels/incompressible/RASModel_impl/RASModelHolder_020000.hpp"
#endif


#if FOAM_VERSION( <, 020000 )
#include "turbulenceModels/incompressible/RASModel_impl/RASModelHolder_010701.hpp"
#endif



//---------------------------------------------------------------------------
#endif
