#ifndef polyMeshArgs_H
#define polyMeshArgs_H


//---------------------------------------------------------------------------
#include "objectRegistryArgs.H"


//---------------------------------------------------------------------------
namespace Foam
{
  class polyMeshArgs 
       : protected objectRegistryArgs
  {
  protected:
    polyMeshArgs();
  private:
    // polyMeshArgs(); // not implemented
    polyMeshArgs( const polyMeshArgs& ); // not implemented 
    void operator = ( const polyMeshArgs& ); // not implemented 
  };
} // Foam


//---------------------------------------------------------------------------
#endif
