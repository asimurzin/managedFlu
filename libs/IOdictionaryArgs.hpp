#ifndef IOdictionaryArgs_hpp
#define IOdictionaryArgs_hpp


//---------------------------------------------------------------------------
#include "universalArgs.hpp"
#include <boost/shared_ptr.hpp>


//---------------------------------------------------------------------------
namespace Foam
{
  class IOobjectHolder;
  class dictionaryHolder;
  
  class IOdictionaryArgs
    : universalArgs
  {
  protected:
    IOdictionaryArgs( const IOobjectHolder&, const dictionaryHolder& );
    IOdictionaryArgs( const IOobjectHolder& );
    IOdictionaryArgs();

  private:
    boost::shared_ptr< IOobjectHolder > IOobjectArg;
    boost::shared_ptr< dictionaryHolder > dictionaryArg;

  };
} // Foam


//---------------------------------------------------------------------------
#endif
