//---------------------------------------------------------------------------
#include "simpleControlHolder.hpp"


//---------------------------------------------------------------------------
namespace Foam
{

  simpleControlHolder::simpleControlHolder( fvMeshHolder& mesh ) 
    : simpleControlArgs( &mesh )
    , boost::shared_ptr< simpleControl >( new simpleControl( *mesh ) )
    , universalHolder()
  {
#ifdef OUR_DEBUG
    cout << "simpleControlHolder = " << this << nl;
#endif
  }
  
  universalHolder* simpleControlHolder::clone() const 
  {
    return new simpleControlHolder( *this );
  }
  
  simpleControlHolder::~simpleControlHolder()
  {
#ifdef OUR_DEBUG
    cout << "~simpleControlHolder = " << this << nl;
#endif
  }
}


//---------------------------------------------------------------------------
