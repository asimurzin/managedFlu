#ifndef Args_hpp
#define Args_hpp


//---------------------------------------------------------------------------
#include <set>
#include <boost/shared_ptr.hpp>

namespace Foam
{
  class SimpleHolder;
  
  typedef boost::shared_ptr< SimpleHolder > holderPtr;
  
  class Args 
  {
   
    protected:
      Args();
      Args( const SimpleHolder* uh );
      Args( const std::set< holderPtr >& the_deps );

      const std::set< holderPtr >& args() const;
      
    private:
      std::set< holderPtr > args_;
      
  };

#ifndef SWIG
  std::set< holderPtr > operator&&( const std::set< holderPtr >&, const std::set< holderPtr >& );
#endif
    
} // Foam


//---------------------------------------------------------------------------
#endif

