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
    protected:
      universalArgs( universalHolder* uh );
      universalArgs( universalHolder*, universalHolder* );
      universalArgs();

    private:
      std::list< boost::shared_ptr< universalHolder > > listArgs;

      void operator=( const universalArgs& ); // not implemented
      universalArgs( const universalArgs& ); // not implemented
  };
} // Foam


//---------------------------------------------------------------------------
#endif
