#ifndef simpleControlArgs_hpp
#define simpleControlArgs_hpp


//---------------------------------------------------------------------------
#include "universalArgs.hpp"
#include "universalHolder.hpp"

#include <boost/shared_ptr.hpp>


//---------------------------------------------------------------------------
namespace Foam
{
  class simpleControlArgs
    : public universalArgs
  {
  protected:
    simpleControlArgs( const universalHolder* );

  private:
    simpleControlArgs(); // not implemented
    //simpleControlArgs( const simpleControlArgs& ); // not implemented 
    void operator=( const simpleControlArgs& ); // not implemented 
  };
} // Foam


//---------------------------------------------------------------------------
#endif
