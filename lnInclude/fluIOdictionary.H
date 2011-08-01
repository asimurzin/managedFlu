#ifndef fluIOdictionary_H
#define fluIOdictionary_H


//---------------------------------------------------------------------------
#include <IOdictionary.H>
#include "IOobjectHolder.H"
#include "dictionaryHolder.H"


//---------------------------------------------------------------------------
namespace Foam
{
  class fluIOdictionary : 
    protected IOobjectHolder
    , protected dictionaryHolder
    , public IOdictionary
  {
  private:
    fluIOdictionary( const IOobjectHolder& io );
    fluIOdictionary( const IOobjectHolder&, const dictionaryHolder& );
    fluIOdictionary( const fluIOdictionary& ); // not implemented
    fluIOdictionary(); // not implemented
    friend class IOdictionaryHolder;
  public:
    ~fluIOdictionary();
  };
} // Foam


//---------------------------------------------------------------------------
#endif
