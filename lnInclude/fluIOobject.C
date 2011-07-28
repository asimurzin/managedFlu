#ifndef fluIOobject_C
#define fluIOobject_C


//---------------------------------------------------------------------------
#include "fluIOobject.H"


//---------------------------------------------------------------------------
Foam::fluIOobject::fluIOobject( const Foam::word &name, 
                                const Foam::fileName &instance, 
                                const Foam::objectRegistryHolder& registry, 
                                Foam::IOobject::readOption r , 
                                Foam::IOobject::writeOption w, 
                                bool registerObject ) 
                        : Foam::IOobjectArgs( registry )
                        , Foam::IOobject( name, instance, *registry, r, w, registerObject )
{
  cout << "fluIOobject = " << this << nl;
}
Foam::fluIOobject::~fluIOobject()
{
  cout << "~fluIOobject = " << this << nl;
}


//---------------------------------------------------------------------------
#endif
