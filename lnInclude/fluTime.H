#ifndef fluTime_H
#define fluTime_H


//---------------------------------------------------------------------------
#include <Time.H>
#include "TimeArgs.H"


//---------------------------------------------------------------------------
namespace Foam
{
  class fluTime :  protected TimeArgs, public Time
  {
  private:
    fluTime( const word &name,
             const argList &args, 
             const word &systemName="system", 
             const word &constantName="constant" );
    fluTime( const fluTime& ); // not implemented
    fluTime(); // not implemented
    friend class TimeHolder;
  public:
    ~fluTime();
  };
} // Foam


//---------------------------------------------------------------------------
#endif
