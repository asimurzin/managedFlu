#ifndef universalArgs_hpp
#define universalArgs_hpp


//---------------------------------------------------------------------------
#include <set>
#include <boost/shared_ptr.hpp>

namespace Foam
{
  class universalHolder;
  
  class universalArgs 
  {
    public:
      universalArgs( const universalHolder* uh );
      universalArgs( const universalHolder*, const universalHolder* );
      universalArgs( const universalHolder*, const universalHolder*, const universalHolder* );
    protected:
      universalArgs();

    private:
      std::set< boost::shared_ptr< universalHolder > > args_;

  };
} // Foam


//---------------------------------------------------------------------------
#endif
