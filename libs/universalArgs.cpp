#include "universalArgs.hpp"
#include "universalHolder.hpp"


//---------------------------------------------------------------------------
namespace Foam
{
  universalArgs::universalArgs( universalHolder* uh )
  {
    this->listArgs.push_back( boost::shared_ptr< universalHolder >( uh ) );
  }
  
  universalArgs::universalArgs( universalHolder* uh1, universalHolder* uh2 )
  {
    this->listArgs.push_back( boost::shared_ptr< universalHolder >( uh1 ) );
    this->listArgs.push_back( boost::shared_ptr< universalHolder >( uh2 ) );
  }

  universalArgs::universalArgs()
  {}
}//Foam


//---------------------------------------------------------------------------

