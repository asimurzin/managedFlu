//---------------------------------------------------------------------------
#include "pimpleControlHolder.hpp"

//---------------------------------------------------------------------------
#if FOAM_VERSION( <, 020000 )
#define pimpleControlHolder_cpp
#endif


//---------------------------------------------------------------------------
#ifndef pimpleControlHolder_cpp
#define pimpleControlHolder_cpp


//---------------------------------------------------------------------------
namespace Foam
{

  pimpleControlHolder::pimpleControlHolder( fvMeshHolder& mesh ) 
    : DependentHolder( &mesh )
    , boost::shared_ptr< pimpleControl >( new pimpleControl( *mesh ) )
  {
#ifdef OUR_DEBUG
    cout << "pimpleControlHolder = " << this << nl;
#endif
  }
  
  SimpleHolder* pimpleControlHolder::clone() const 
  {
    return new pimpleControlHolder( *this );
  }
  
  pimpleControlHolder::~pimpleControlHolder()
  {
#ifdef OUR_DEBUG
    cout << "~pimpleControlHolder = " << this << nl;
#endif
  }
}


//---------------------------------------------------------------------------
#endif
