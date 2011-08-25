//---------------------------------------------------------------------------
namespace Foam
{
  template<class Type>
  fvMatrixHolder< Type >::fvMatrixHolder( const tmp< fvMatrix< Type > >& tmp_mt, 
					  const GeometricFieldHolder< Type, fvPatchField, volMesh >& field ) 
    : fvMatrixArgs< Type >( field )
    , smart_tmp< fvMatrix< Type > >( tmp_mt )
    , universalHolder()
  {
#ifdef OUR_DEBUG
    cout << "flufvMatrix = " << this << nl;
#endif
  }
  
  template<class Type>
  fvMatrixHolder< Type >::fvMatrixHolder( const fvMatrix< Type >& mt, 
					  const universalArgs& args ) 
    : fvMatrixArgs< Type >( args )
    , smart_tmp< fvMatrix< Type > >( mt )
    , universalHolder()
  {
#ifdef OUR_DEBUG
    cout << "flufvMatrix = " << this << nl;
#endif
  }

  template<class Type>
  fvMatrixHolder< Type >::fvMatrixHolder( const tmp< fvMatrix< Type > >& mt, 
					  const universalArgs& args ) 
    : fvMatrixArgs< Type >( args )
    , smart_tmp< fvMatrix< Type > >( mt )
    , universalHolder()
  {
#ifdef OUR_DEBUG
    cout << "flufvMatrix = " << this << nl;
#endif
  }


template<class Type>
  fvMatrixHolder< Type >::fvMatrixHolder() 
    : fvMatrixArgs< Type >()
    , smart_tmp< fvMatrix< Type > >()
    , universalHolder()
  {
#ifdef OUR_DEBUG
    cout << "flufvMatrix = " << this << nl;
#endif
  }

  template<class Type>
  universalHolder* fvMatrixHolder< Type >::clone()
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
      fvMatrixArgs< Type >::operator=( mt );
      smart_tmp< fvMatrix< Type > >::operator=( mt );
    }
    else
    {
      this->operator()() = mt();
    }
  }
} //Foam


//---------------------------------------------------------------------------
