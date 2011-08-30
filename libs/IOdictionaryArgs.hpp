#ifndef IOdictionaryArgs_hpp
#define IOdictionaryArgs_hpp


//---------------------------------------------------------------------------
#include "universalArgs.hpp"
#include "universalHolder.hpp"
#include "Deps.hpp"

#include <boost/shared_ptr.hpp>


//---------------------------------------------------------------------------
namespace Foam
{
  class IOdictionaryArgs
    : public universalArgs
  {
  protected:
    IOdictionaryArgs( const Deps& );
    IOdictionaryArgs();

  };
} // Foam


//---------------------------------------------------------------------------
#endif
