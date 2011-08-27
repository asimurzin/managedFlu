#ifndef IOdictionaryArgs_hpp
#define IOdictionaryArgs_hpp


//---------------------------------------------------------------------------
#include "universalArgs.hpp"
#include "universalHolder.hpp"

#include <boost/shared_ptr.hpp>


//---------------------------------------------------------------------------
namespace Foam
{
  class IOdictionaryArgs
    : public universalArgs
  {
  protected:
    IOdictionaryArgs( const universalHolder*, const universalHolder* );
    IOdictionaryArgs( const universalHolder* );
    IOdictionaryArgs();

  };
} // Foam


//---------------------------------------------------------------------------
#endif
