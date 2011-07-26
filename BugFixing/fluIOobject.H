#ifndef fluIOobject_H
#define fluIOobject_H


//---------------------------------------------------------------------------
#include <IOobject.H>
#include "objectRegistryHolder.H"

namespace Foam
{
  class fluIOobject : protected objectRegistryHolder, public IOobject
  {
  private:
    fluIOobject( const word &name, 
                 const fileName &instance, 
                 const objectRegistryHolder& registry, 
                 IOobject::readOption r = IOobject::NO_READ, 
                 IOobject::writeOption w = IOobject::NO_WRITE, 
                 bool registerObject=true ) : objectRegistryHolder( registry ),
                                              IOobject( name, instance, registry, r, w, registerObject )
                                                
    {}
    fluIOobject( const fluIOobject& ); // not implemented
    fluIOobject(); // not implemented
    friend class IOobjectHolder;
  };
} // Foam

#endif
