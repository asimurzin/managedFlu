#ifndef IOobjectArgs_H
#define IOobjectArgs_H


//---------------------------------------------------------------------------
#include "objectRegistryHolder.H"


//---------------------------------------------------------------------------
namespace Foam
{
  class IOobjectArgs 
       : protected objectRegistryHolder
  {
  public:
    IOobjectArgs( const objectRegistryHolder& orh );
    IOobjectArgs();
  private:
    // IOobjectArgs(); // not implemented
    IOobjectArgs( const IOobjectArgs& ); // not implemented 
    void operator = ( const IOobjectArgs& ); // not implemented 
  };
} // Foam


//---------------------------------------------------------------------------
#endif
