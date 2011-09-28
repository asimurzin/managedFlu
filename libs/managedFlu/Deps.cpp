#include "Deps.hpp"


//---------------------------------------------------------------------------
namespace Foam
{
  Deps::Deps( const SimpleHolder* uh )
    : Args( uh )
  {}

  Deps::Deps( const std::set< holderPtr >& the_deps  )
    : Args( the_deps )
  {}
  
  Deps::Deps()
    : Args()
  {}

  Deps::Deps( const Deps& deps1, const Deps& deps2)
    : Args( deps1.args() && deps2.args() )
  {}

  Deps::Deps( const Deps& deps1, const Deps& deps2, const Deps& deps3 )
    : Args( deps1.args() && deps2.args() && deps3.args() )
  {}

  Deps::Deps( const Deps& deps1, const Deps& deps2, const Deps& deps3, const Deps& deps4 )
    : Args( deps1.args() && deps2.args() && deps3.args()  && deps4.args() )
  {}
  
}//Foam


//---------------------------------------------------------------------------

