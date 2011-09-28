#include "Args.hpp"
#include "SimpleHolder.hpp"


//---------------------------------------------------------------------------
namespace Foam
{

  Args::Args( const SimpleHolder* uh )
  {
    this->args_.insert(  holderPtr( uh->clone() ) );
  }

  Args::Args( const std::set< holderPtr >& the_deps )
    : args_( the_deps )
  {}

  Args::Args()
  {}
  
  const std::set< holderPtr >& Args::args() const
  {
    return args_;
  }
  
  std::set< holderPtr > operator&&( const std::set< holderPtr >& deps1, const std::set< holderPtr >& deps2)
  {
    std::set< holderPtr > result;
  
    set_union( deps1.begin(), deps1.end(), deps2.begin(), deps2.end(),
              std::insert_iterator<std::set< holderPtr > >(result,result.begin()) );

    return result;
  }
  
}//Foam


//---------------------------------------------------------------------------

