#ifndef fluIOobject_H
#define fluIOobject_H


//---------------------------------------------------------------------------
#include <IOobject.H>
#include "IOobjectArgs.H"


//---------------------------------------------------------------------------
namespace Foam
{
  class objectRegistryHolder;
  
  class fluIOobject : protected IOobjectArgs, public IOobject
  {
  private:
    fluIOobject( const word &name, 
                 const fileName &instance, 
                 const objectRegistryHolder& registry, 
                 IOobject::readOption r = IOobject::NO_READ, 
                 IOobject::writeOption w = IOobject::NO_WRITE, 
                 bool registerObject = true );
    fluIOobject(); // not implemented
    // fluIOobject( const fluIOobject& ); // not implemented
    void operator = ( const fluIOobject& ); // not implemented 
    friend class IOobjectHolder;
  public:
    ~fluIOobject();
  };
} // Foam


//---------------------------------------------------------------------------
#endif
