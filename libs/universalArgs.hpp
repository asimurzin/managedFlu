#ifndef universalArgs_hpp
#define universalArgs_hpp


//---------------------------------------------------------------------------
#include <list>
#include <boost/shared_ptr.hpp>

namespace Foam
{
  class universalHolder;
  
  class universalArgs 
  {
    public:
      universalArgs( universalHolder* uh );
      universalArgs( universalHolder*, universalHolder* );
    protected:
      universalArgs();

    private:
      std::list< boost::shared_ptr< universalHolder > > listArgs;

  };
} // Foam


//---------------------------------------------------------------------------
#endif
