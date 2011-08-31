//---------------------------------------------------------------------------
namespace Foam
{
  
  template<class Type>
  fvMatrixHolder< Type >::fvMatrixHolder( const fvMatrix< Type >& mt, 
					  const Deps& args ) 
    : DependentHolder( args )
    , smart_tmp< fvMatrix< Type > >( mt )
  {
#ifdef OUR_DEBUG
    cout << "flufvMatrix = " << this << nl;
#endif
  }

  template<class Type>
  fvMatrixHolder< Type >::fvMatrixHolder( const tmp< fvMatrix< Type > >& mt, 
					  const Deps& args ) 
    : DependentHolder( args )
    , smart_tmp< fvMatrix< Type > >( mt )
  {
#ifdef OUR_DEBUG
    cout << "flufvMatrix = " << this << nl;
#endif
  }


template<class Type>
  fvMatrixHolder< Type >::fvMatrixHolder() 
    : DependentHolder()
    , smart_tmp< fvMatrix< Type > >()
  {
#ifdef OUR_DEBUG
    cout << "flufvMatrix = " << this << nl;
#endif
  }

  template<class Type>
  SimpleHolder* fvMatrixHolder< Type >::clone() const
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
      Args::operator=( mt );
      smart_tmp< fvMatrix< Type > >::operator=( mt );
    }
    else
    {
      this->operator()() = mt();
    }
  }
} //Foam


//---------------------------------------------------------------------------
