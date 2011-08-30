#ifndef turbulenceModelArgs_hpp
#define turbulenceModelArgs_hpp


//---------------------------------------------------------------------------
#include "Deps.hpp"
#include "volFields.hpp"
#include "surfaceFields.hpp"
#include "basicThermoHolder.hpp"


#include <boost/shared_ptr.hpp>


//---------------------------------------------------------------------------
namespace Foam
{

namespace compressible
{
  class turbulenceModelArgs
     : public universalArgs
  {
  protected:
    turbulenceModelArgs();

    turbulenceModelArgs( const Deps& );
    
  };

} //compressible
} // Foam


//---------------------------------------------------------------------------
#endif
