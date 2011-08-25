#include "universalArgs.hpp"
#include "universalHolder.hpp"


//---------------------------------------------------------------------------
namespace Foam
{
  universalArgs::universalArgs( const universalHolder* uh )
  {
    this->listArgs.push_back(  boost::shared_ptr< universalHolder >( uh->clone() ) );
  }
  
  universalArgs::universalArgs( const universalHolder* uh1, const universalHolder* uh2 )
  {
    this->listArgs.push_back( boost::shared_ptr< universalHolder >( uh1->clone() ) );
    this->listArgs.push_back( boost::shared_ptr< universalHolder >( uh2->clone() ) );
  }

  universalArgs::universalArgs( const universalHolder* uh1, const universalHolder* uh2, const universalHolder* uh3 )
  {
    this->listArgs.push_back( boost::shared_ptr< universalHolder >( uh1->clone() ) );
    this->listArgs.push_back( boost::shared_ptr< universalHolder >( uh2->clone() ) );
    this->listArgs.push_back( boost::shared_ptr< universalHolder >( uh3->clone() ) );
  }

  universalArgs::universalArgs()
  {}
}//Foam


//---------------------------------------------------------------------------

