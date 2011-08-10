//---------------------------------------------------------------------------
namespace Foam
{
  template<class Type>
  fvMatrixHolder< Type >::fvMatrixHolder( const tmp< fvMatrix< Type > >& tmp_mt, 
					  const GeometricFieldHolder< Type, fvPatchField, volMesh >& field ) 
    : fvMatrixArgs< Type >( field )
    , tmp< fvMatrix< Type > >( tmp_mt )
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
} //Foam


//---------------------------------------------------------------------------
