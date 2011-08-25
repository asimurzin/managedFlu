//---------------------------------------------------------------------------
namespace Foam
{
  template< class Type >
  fvMatrixArgs< Type >::fvMatrixArgs( const GeometricFieldHolder< Type, fvPatchField, volMesh >& field ) 
    : universalArgs( new GeometricFieldHolder< Type, fvPatchField, volMesh >( field) )
    , psi_( new GeometricFieldHolder< Type, fvPatchField, volMesh >( field) )
  {}

  template< class Type >
  fvMatrixArgs< Type >::fvMatrixArgs() 
    : universalArgs()
    , psi_()
  {}
  
  
  template< class Type >
  GeometricFieldHolder< Type, fvPatchField, volMesh >& fvMatrixArgs< Type >::psi() const
  {
    return *psi_;
  }
}


//---------------------------------------------------------------------------
