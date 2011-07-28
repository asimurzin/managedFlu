#ifndef fluTime_C
#define fluTime_C


//---------------------------------------------------------------------------
#include "fluTime.H"



//---------------------------------------------------------------------------
Foam::fluTime::fluTime( const word &name,
                        const argList &args, 
                        const word &systemName, 
                        const word &constantName ) : TimeArgs(), Time( name, args, systemName, constantName )
{
  cout << "fluTime = " << this << nl;
}
Foam::fluTime::~fluTime()
{
  cout << "~fluTime = " << this << nl;
}


//---------------------------------------------------------------------------
#endif
