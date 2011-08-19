//---------------------------------------------------------------------------
#include "simpleControlHolder.hpp"


//---------------------------------------------------------------------------
namespace Foam
{

  simpleControlHolder::simpleControlHolder( fvMeshHolder& mesh ) 
    : simpleControlArgs( mesh )
    , boost::shared_ptr< simpleControl >( new simpleControl( *mesh ) )
  {
#ifdef OUR_DEBUG
    cout << "simpleControlHolder = " << this << nl;
#endif
  }
 
  simpleControlHolder::~simpleControlHolder()
  {
#ifdef OUR_DEBUG
    cout << "~simpleControlHolder = " << this << nl;
#endif
  }
}


//---------------------------------------------------------------------------