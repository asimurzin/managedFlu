#include "universalArgs.hpp"
#include "universalHolder.hpp"


//---------------------------------------------------------------------------
namespace Foam
{
  universalArgs::universalArgs( const universalHolder* uh )
  {
    this->args_.insert(  boost::shared_ptr< universalHolder >( uh->clone() ) );
  }
  
  universalArgs::universalArgs( const universalHolder* uh1, const universalHolder* uh2 )
  {
    this->args_.insert( boost::shared_ptr< universalHolder >( uh1->clone() ) );
    this->args_.insert( boost::shared_ptr< universalHolder >( uh2->clone() ) );
  }

  universalArgs::universalArgs( const universalHolder* uh1, const universalHolder* uh2, const universalHolder* uh3 )
  {
    this->args_.insert( boost::shared_ptr< universalHolder >( uh1->clone() ) );
    this->args_.insert( boost::shared_ptr< universalHolder >( uh2->clone() ) );
    this->args_.insert( boost::shared_ptr< universalHolder >( uh3->clone() ) );
  }

  universalArgs::universalArgs()
  {}
}//Foam


//---------------------------------------------------------------------------

