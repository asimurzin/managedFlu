#ifndef DependentHolder_hpp
#define DependentHolder_hpp


//---------------------------------------------------------------------------
#include "universalArgs.hpp"
#include "universalHolder.hpp"
#include "Deps.hpp"

namespace Foam
{
  class DependentHolder
    : public universalArgs
    , virtual public universalHolder
  {
    public:
      
      DependentHolder( const Deps& dp );
      
      DependentHolder();
      
      virtual universalHolder* clone() const;
      
      virtual ~DependentHolder();
  };
} // Foam


//---------------------------------------------------------------------------
#endif
