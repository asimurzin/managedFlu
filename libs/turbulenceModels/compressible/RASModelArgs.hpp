#ifndef RASModelArgs_hpp
#define RASModelArgs_hpp


//---------------------------------------------------------------------------
#include "universalArgs.hpp"


//---------------------------------------------------------------------------
namespace Foam
{

namespace compressible
{
  class RASModelArgs
    : public universalArgs
  {
  protected:
    RASModelArgs();

    RASModelArgs( 
      const universalHolder*, 
      const universalHolder*, 
      const universalHolder*, 
      const universalHolder* );
  };

} //compressible
} // Foam


//---------------------------------------------------------------------------
#endif
