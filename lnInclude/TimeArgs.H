#ifndef TimeArgs_H
#define TimeArgs_H


//---------------------------------------------------------------------------
#include "objectRegistryArgs.H"


//---------------------------------------------------------------------------
namespace Foam
{
  class TimeArgs : private objectRegistryArgs
  {
  protected:
    TimeArgs();
  };
} // Foam


//---------------------------------------------------------------------------
#endif
