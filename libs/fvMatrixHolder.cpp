//---------------------------------------------------------------------------
namespace Foam
{
  
  template<class Type>
  fvMatrixHolder< Type >::fvMatrixHolder( const fvMatrix< Type >& mt, 
					  const Deps& args ) 
    : fvMatrixArgs( args )
    , smart_tmp< fvMatrix< Type > >( mt )
    , universalHolder()
  {
#ifdef OUR_DEBUG
    cout << "flufvMatrix = " << this << nl;
#endif
  }

  template<class Type>
  fvMatrixHolder< Type >::fvMatrixHolder( const tmp< fvMatrix< Type > >& mt, 
					  const Deps& args ) 
    : fvMatrixArgs( args )
    , smart_tmp< fvMatrix< Type > >( mt )
    , universalHolder()
  {
#ifdef OUR_DEBUG
    cout << "flufvMatrix = " << this << nl;
#endif
  }


template<class Type>
  fvMatrixHolder< Type >::fvMatrixHolder() 
    : fvMatrixArgs()
    , smart_tmp< fvMatrix< Type > >()
    , universalHolder()
  {
#ifdef OUR_DEBUG
    cout << "flufvMatrix = " << this << nl;
#endif
  }

  template<class Type>
  universalHolder* fvMatrixHolder< Type >::clone() const
  {
    return new fvMatrixHolder< Type >( *this );
  }
  
  template<class Type>
  fvMatrixHolder< Type >::~fvMatrixHolder()
  {
#ifdef OUR_DEBUG
    cout << "~flufvMatrix = " << this << nl;
#endif
  }

  template<class Type>
  void fvMatrixHolder< Type >::operator = ( const fvMatrixHolder& mt)
  {
    if ( this->empty() )
    {
      fvMatrixArgs::operator=( mt );
      smart_tmp< fvMatrix< Type > >::operator=( mt );
    }
    else
    {
      this->operator()() = mt();
    }
  }
} //Foam


//---------------------------------------------------------------------------
