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
      
  DependentHolder::~DependentHolder()
  {}
  
} // Foam


//---------------------------------------------------------------------------

