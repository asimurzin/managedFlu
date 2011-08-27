#ifndef basicThermoArgs_hpp
#define basicThermoArgs_hpp


//---------------------------------------------------------------------------
#include "universalArgs.hpp"
#include "universalHolder.hpp"

#include <boost/shared_ptr.hpp>


//---------------------------------------------------------------------------
namespace Foam
{
  class basicThermoArgs
    : universalArgs
  {
  protected:  
    basicThermoArgs();   

    basicThermoArgs( const universalHolder* );

  };
} // Foam


//---------------------------------------------------------------------------
#endif
