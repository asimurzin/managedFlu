#ifndef RASModelArgs_hpp
#define RASModelArgs_hpp


//---------------------------------------------------------------------------
#include "universalArgs.hpp"
#include "Deps.hpp"


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

    RASModelArgs( const Deps& );
  };

} //compressible
} // Foam


//---------------------------------------------------------------------------
#endif
