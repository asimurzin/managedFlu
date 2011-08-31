#ifndef Args_hpp
#define Args_hpp


//---------------------------------------------------------------------------
#include <set>
#include <boost/shared_ptr.hpp>

namespace Foam
{
  class universalHolder;
  
  typedef boost::shared_ptr< universalHolder > holderPtr;
  
  class Args 
  {
   
    public:
      Args( const universalHolder* uh );
/*      Args( const universalHolder*, const universalHolder* );
      Args( const universalHolder*, const universalHolder*, const universalHolder* );
      Args( const universalHolder*, const universalHolder*, const universalHolder*, const universalHolder* );*/
      
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

