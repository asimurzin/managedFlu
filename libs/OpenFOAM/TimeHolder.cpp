#ifndef TimeHolder_cpp
#define TimeHolder_cpp


//---------------------------------------------------------------------------
#include "TimeHolder.hpp"


//---------------------------------------------------------------------------
#if FOAM_VERSION( >=, 020000 )
#include "TimeHolder_020000.cpp"
#endif


#if FOAM_VERSION( <, 020000 )
#include "TimeHolder_010701.cpp"
#endif


//---------------------------------------------------------------------------
#endif
