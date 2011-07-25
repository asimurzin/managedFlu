#ifndef fluTimeHolder_H
#define fluTimeHolder_H


//---------------------------------------------------------------------------
#include <Time.H>

namespace Foam
{
  class fluTime : public Time
  {
  private:
    fluTime( const word &name,
             const argList &args, 
             const word &systemName="system", 
             const word &constantName="constant" ) : Time( name, args, systemName, constantName )
    {}
    fluTime( const fluTime& ); // not implemented
    fluTime(); // not implemented
    friend class TimeHolder;
  };
} // Foam

#endif
