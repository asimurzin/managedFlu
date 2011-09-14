//---------------------------------------------------------------------------
#include "simpleControlHolder.hpp"

//---------------------------------------------------------------------------
#if FOAM_VERSION( <, 020000 )
#define simpleControlHolder_cpp
#endif


//---------------------------------------------------------------------------
#ifndef simpleControlHolder_cpp
#define simpleControlHolder_cpp


//---------------------------------------------------------------------------
namespace Foam
{

  simpleControlHolder::simpleControlHolder( fvMeshHolder& mesh ) 
    : DependentHolder( &mesh )
    , boost::shared_ptr< simpleControl >( new simpleControl( *mesh ) )
  {
#ifdef OUR_DEBUG
    cout << "simpleControlHolder = " << this << nl;
#endif
  }
  
  SimpleHolder* simpleControlHolder::clone() const 
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
#endif
