#include "Deps.hpp"


//---------------------------------------------------------------------------
namespace Foam
{
  Deps::Deps( const SimpleHolder* uh )
    : Args( uh )
  {}
  
  Deps::Deps( const std::set< holderPtr >& the_deps )
    : Args( the_deps )
  {}

  Deps deps( const Deps& deps1 )
  {
    return deps1.deps();
  }
 
  Deps deps( const Deps& deps1, const Deps& deps2)
  {
    return deps1.deps() && deps2.deps();
  }
  
}//Foam


//---------------------------------------------------------------------------

