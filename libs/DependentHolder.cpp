//---------------------------------------------------------------------------
#include "DependentHolder.hpp"

namespace Foam
{
  DependentHolder::DependentHolder( const Deps& dp )
    : universalHolder()
    , Args( dp )
  {}
      
  DependentHolder::DependentHolder()
    : universalHolder()
    , Args()
  {}
  
  universalHolder* DependentHolder::clone() const
  {
    return new DependentHolder( *this );
  }
      
  DependentHolder::~DependentHolder()
  {}
  
} // Foam


//---------------------------------------------------------------------------

