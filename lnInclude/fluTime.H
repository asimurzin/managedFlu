#ifndef fluTime_H
#define fluTime_H


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
    {
      cout << "fluTime = " << this << nl;
    }
    fluTime( const fluTime& ); // not implemented
    fluTime(); // not implemented
    friend class TimeHolder;
  public:
    ~fluTime()
    {
      cout << "~fluTime = " << this << nl;
    }
  };
} // Foam

#endif
