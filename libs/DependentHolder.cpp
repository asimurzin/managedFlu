//---------------------------------------------------------------------------
#include "DependentHolder.hpp"

namespace Foam
{
  DependentHolder::DependentHolder( const Deps& dp )
    : universalHolder()
    , universalArgs( dp )
  {}
      
  DependentHolder::DependentHolder()
    : universalHolder()
    , universalArgs()
  {}
  
  universalHolder* DependentHolder::clone() const
  {
    return new DependentHolder( *this );
  }
      
  DependentHolder::~DependentHolder()
  {}
  
} // Foam


//---------------------------------------------------------------------------

