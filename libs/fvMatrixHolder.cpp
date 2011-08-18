//---------------------------------------------------------------------------
namespace Foam
{
  template<class Type>
  fvMatrixHolder< Type >::fvMatrixHolder( const tmp< fvMatrix< Type > >& tmp_mt, 
					  const GeometricFieldHolder< Type, fvPatchField, volMesh >& field ) 
    : fvMatrixArgs< Type >( field )
    , smart_tmp< fvMatrix< Type > >( tmp_mt )
  {
#ifdef OUR_DEBUG
    cout << "flufvMatrix = " << this << nl;
#endif
  }
  
template<class Type>
  fvMatrixHolder< Type >::fvMatrixHolder() 
    : fvMatrixArgs< Type >()
    , smart_tmp< fvMatrix< Type > >()
  {
#ifdef OUR_DEBUG
    cout << "flufvMatrix = " << this << nl;
#endif
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
