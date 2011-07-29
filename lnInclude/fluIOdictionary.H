#ifndef fluIOdictionary_H
#define fluIOdictionary_H


//---------------------------------------------------------------------------
#include <IOdictionary.H>
#include "IOdictionaryArgs.H"


//---------------------------------------------------------------------------
namespace Foam
{
  class fluIOdictionary : protected IOdictionaryArgs, public IOdictionary
  {
  private:
    fluIOdictionary( const IOobjectHolder& io );
    fluIOdictionary( const fluIOdictionary& ); // not implemented
    fluIOdictionary(); // not implemented
    friend class IOdictionaryHolder;
  public:
    ~fluIOdictionary();
  };
} // Foam


//---------------------------------------------------------------------------
#endif
