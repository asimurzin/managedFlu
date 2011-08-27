#ifndef radiationModelArgs_hpp
#define radiationModelArgs_hpp


//---------------------------------------------------------------------------
#include "universalArgs.hpp"
#include "universalHolder.hpp"

#include <boost/shared_ptr.hpp>


//---------------------------------------------------------------------------
namespace Foam
{
  class radiationModelArgs
    : universalArgs
  {
  protected:  
    radiationModelArgs();   

    radiationModelArgs( const universalHolder* );

  };
} // Foam


//---------------------------------------------------------------------------
#endif
