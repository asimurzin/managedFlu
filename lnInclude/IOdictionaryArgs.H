#ifndef IOdictionaryArgs_H
#define IOdictionaryArgs_H


//---------------------------------------------------------------------------
#include <IOdictionary.H>
#include <boost/shared_ptr.hpp>


//---------------------------------------------------------------------------
namespace Foam
{
  class IOobjectHolder;
  class dictionaryHolder;
  
  class IOdictionaryArgs
  {
  protected:
    IOdictionaryArgs( const IOobjectHolder&, const dictionaryHolder& );
    IOdictionaryArgs( const IOobjectHolder& );
  private:
    boost::shared_ptr< IOobjectHolder > IOobjectArg;
    boost::shared_ptr< dictionaryHolder > dictionaryArg;
    //IOdictionaryArgs( const IOdictionaryArgs& ); // not implemented 
    void operator = ( const IOdictionaryArgs& ); // not implemented 
    IOdictionaryArgs(); //not implemented
  };
} // Foam


//---------------------------------------------------------------------------
#endif
