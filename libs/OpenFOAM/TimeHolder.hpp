#ifndef TimeHolder_hpp
#define TimeHolder_hpp


//---------------------------------------------------------------------------
#include "common.hpp"


//---------------------------------------------------------------------------
#if FOAM_VERSION( >=, 020000 )
#include "TimeHolder_020000.hpp"
#endif


#if FOAM_VERSION( <, 020000 )
#include "TimeHolder_010701.hpp"
#endif


//---------------------------------------------------------------------------
#endif
