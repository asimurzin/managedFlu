//---------------------------------------------------------------------------
#include "simpleControlHolder.hpp"


//---------------------------------------------------------------------------
namespace Foam
{

  simpleControlHolder::simpleControlHolder( fvMeshHolder& mesh ) 
    : DependentHolder( Foam::deps( &mesh ) )
    , boost::shared_ptr< simpleControl >( new simpleControl( *mesh ) )
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
