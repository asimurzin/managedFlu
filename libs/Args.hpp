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
   
    public:
      Args( const SimpleHolder* uh );
/*      Args( const SimpleHolder*, const SimpleHolder* );
      Args( const SimpleHolder*, const SimpleHolder*, const SimpleHolder* );
      Args( const SimpleHolder*, const SimpleHolder*, const SimpleHolder*, const SimpleHolder* );*/
      
      Args( const std::set< holderPtr >& the_deps );
      
      const std::set< holderPtr >& deps() const;
    protected:
      Args();

    private:
      std::set< holderPtr > deps_;
      
  };

  std::set< holderPtr > operator&&( const std::set< holderPtr >&, const std::set< holderPtr >& );
    
} // Foam


//---------------------------------------------------------------------------
#endif

