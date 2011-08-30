#ifndef universalArgs_hpp
#define universalArgs_hpp


//---------------------------------------------------------------------------
#include <set>
#include <boost/shared_ptr.hpp>

namespace Foam
{
  class universalHolder;
  
  typedef boost::shared_ptr< universalHolder > holderPtr;
  
  class universalArgs 
  {
   
    public:
      universalArgs( const universalHolder* uh );
/*      universalArgs( const universalHolder*, const universalHolder* );
      universalArgs( const universalHolder*, const universalHolder*, const universalHolder* );
      universalArgs( const universalHolder*, const universalHolder*, const universalHolder*, const universalHolder* );*/
      
      universalArgs( const std::set< holderPtr >& the_deps );
      
      const std::set< holderPtr >& deps() const;
    protected:
      universalArgs();

    private:
      std::set< holderPtr > deps_;
      
  };

  std::set< holderPtr > operator&&( const std::set< holderPtr >&, const std::set< holderPtr >& );
    
} // Foam


//---------------------------------------------------------------------------
#endif

