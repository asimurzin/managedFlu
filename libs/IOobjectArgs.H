#ifndef IOobjectArgs_H
#define IOobjectArgs_H


//---------------------------------------------------------------------------
#include <IOobject.H>
#include <objectRegistry.H>
#include <boost/shared_ptr.hpp>


//---------------------------------------------------------------------------
namespace Foam
{
  class objectRegistryHolder;
   
  class IOobjectArgs
  {
  public:
    const objectRegistryHolder&  get_objectRegistryArg() const ;

  protected:
    IOobjectArgs( const objectRegistryHolder & registry );
    IOobjectArgs();

  private:
    boost::shared_ptr< objectRegistryHolder > objectRegistryArg;

  private:
    // IOobjectArgs( const IOobjectArgs& ); // not implemented 
    //void operator = ( const IOobjectArgs& ); // not implemented 
    // IOobjectArgs(); //not implemented
  };
} // Foam


//---------------------------------------------------------------------------
#endif
