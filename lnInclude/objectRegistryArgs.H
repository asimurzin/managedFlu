#ifndef objectRegistryArgs_H
#define objectRegistryArgs_H


//---------------------------------------------------------------------------
#include "TimeHolder.H"
#include "IOobjectArgs.H"


//---------------------------------------------------------------------------
namespace Foam
{
  class objectRegistryArgs:
      private TimeHolder,
      private IOobjectArgs
  {
  public:
    objectRegistryArgs();
    objectRegistryArgs( const objectRegistryHolder& orh,  const TimeHolder& th );
  };
} // Foam


//---------------------------------------------------------------------------
#endif
