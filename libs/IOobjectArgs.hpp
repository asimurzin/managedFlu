#ifndef IOobjectArgs_hpp
#define IOobjectArgs_hpp


//---------------------------------------------------------------------------
#include "universalArgs.hpp"

#include <IOobject.H>
#include <objectRegistry.H>
#include <boost/shared_ptr.hpp>


//---------------------------------------------------------------------------
namespace Foam
{
  class objectRegistryHolder;
   
  class IOobjectArgs
    : universalArgs
  {
  public:
    const objectRegistryHolder&  get_objectRegistryArg() const ;

  protected:
    IOobjectArgs( const objectRegistryHolder & registry );
    IOobjectArgs();

  private:
    boost::shared_ptr< objectRegistryHolder > objectRegistryArg;

  };
} // Foam


//---------------------------------------------------------------------------
#endif
