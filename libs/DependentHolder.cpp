//---------------------------------------------------------------------------
#include "DependentHolder.hpp"

namespace Foam
{
  DependentHolder::DependentHolder( const Deps& dp )
    : SimpleHolder()
    , Args( dp )
  {}
      
  DependentHolder::DependentHolder()
    : SimpleHolder()
    , Args()
  {}
      
  DependentHolder::~DependentHolder()
  {}
  
} // Foam


//---------------------------------------------------------------------------

