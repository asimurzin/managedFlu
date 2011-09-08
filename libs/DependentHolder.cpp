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
  
  const Deps DependentHolder::deps() const
  { 
    return this->args();
  }
  
} // Foam


//---------------------------------------------------------------------------

