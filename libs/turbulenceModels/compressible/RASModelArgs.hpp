#ifndef RASModelArgs_hpp
#define RASModelArgs_hpp


//---------------------------------------------------------------------------
#include "turbulenceModelArgs.hpp"


//---------------------------------------------------------------------------
namespace Foam
{

namespace compressible
{
  class RASModelArgs
    : turbulenceModelArgs
  {
  protected:
    RASModelArgs( 
      const volScalarFieldHolder&, 
      const volVectorFieldHolder&, 
      const surfaceScalarFieldHolder&, 
      const basicThermoHolder& );
    
  private:
    RASModelArgs(); // not implemented
    //RASModelArgs( const RASModelArgs& ); // not implemented 
    void operator=( const RASModelArgs& ); // not implemented 
  };

} //compressible
} // Foam


//---------------------------------------------------------------------------
#endif
