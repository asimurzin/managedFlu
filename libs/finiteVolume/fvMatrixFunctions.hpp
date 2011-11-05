#ifndef fvMatrixFunctions_hpp
#define fvMatrixFunctions_hpp


//---------------------------------------------------------------------------
#include <fvm.H>
#include <dimensionedScalar.H>
#include "surfaceFields.hpp"
#include "volFields.hpp"
#include "fvMatrices.hpp"


//---------------------------------------------------------------------------
namespace Foam
{
  //---------------------------------------------------------------------------
  template< class Type >
  inline fvMatrixHolder< Type > operator + ( const fvMatrixHolder< Type >& mt1, 
                                             const fvMatrixHolder< Type >& mt2 )
  {
    return fvMatrixHolder< Type >( mt1() + mt2(), Deps( mt1.deps(), mt2.deps() ) );
  }

  template< class Type >
  inline fvMatrixHolder< Type > operator - ( const fvMatrixHolder< Type >& mt1, 
                                             const fvMatrixHolder< Type >& mt2 )
  {
    return fvMatrixHolder< Type >( mt1() - mt2(), Deps( mt1.deps(), mt2.deps() ) );
  }

  template< class Type >
  inline fvMatrixHolder< Type > operator + ( const fvMatrixHolder< Type >& mt1, 
                                             const GeometricFieldHolder< Type, fvPatchField, volMesh >& field )
  {
    return fvMatrixHolder< Type >( mt1() + field() , Deps( mt1.deps(), &field ) );
  }
  
  template< class Type >
  inline fvMatrixHolder< Type > operator - ( const fvMatrixHolder< Type >& mt1, 
                                             const GeometricFieldHolder< Type, fvPatchField, volMesh >& field )
  {
    return fvMatrixHolder< Type >( mt1() - field() , Deps( mt1.deps(), &field ) );
  }

  template< class Type >
  inline fvMatrixHolder< Type > operator == ( const fvMatrixHolder< Type >& mt1, 
                                              const fvMatrixHolder< Type >& mt2 )
  {
    return fvMatrixHolder< Type >( mt1() == mt2(), Deps( mt1.deps(), mt2.deps() ) );
  }

  template< class Type >
  inline fvMatrixHolder< Type > operator == ( const fvMatrixHolder< Type >& mt1, 
                                              const GeometricFieldHolder< Type, fvPatchField, volMesh >& field )
  {
    return fvMatrixHolder< Type >( mt1() == field() , Deps( mt1.deps(), &field ) );
  }
  
  
  //---------------------------------------------------------------------------
} // Foam


//---------------------------------------------------------------------------
#endif
