#ifndef turbulenceModelArgs_hpp
#define turbulenceModelArgs_hpp


//---------------------------------------------------------------------------
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

    turbulenceModelArgs( 
      const universalHolder*, 
      const universalHolder*, 
      const universalHolder*, 
      const universalHolder* );
    
  };

} //compressible
} // Foam


//---------------------------------------------------------------------------
#endif
