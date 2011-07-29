#ifndef objectRegistryArgs_H
#define objectRegistryArgs_H


//---------------------------------------------------------------------------
#include "TimeHolder.H"
#include "IOobjectArgs.H"


//---------------------------------------------------------------------------
namespace Foam
{
  class objectRegistryArgs:
      private objectRegistryHolder,
      private TimeHolder,
      private IOobjectArgs
  {
  protected:
    objectRegistryArgs();
    objectRegistryArgs( const objectRegistryHolder& orh,  const TimeHolder& th );
  };
} // Foam


//---------------------------------------------------------------------------
#endif
