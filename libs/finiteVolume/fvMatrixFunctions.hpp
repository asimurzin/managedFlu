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
  // fvVectorMatrix operators
  inline fvVectorMatrixHolder operator + ( const fvVectorMatrixHolder& mt1, 
					   const fvVectorMatrixHolder& mt2 )
  {
    return fvVectorMatrixHolder( mt1() + mt2(), Deps( mt1.deps(), mt2.deps() ) );
  }

  inline fvVectorMatrixHolder operator - ( const fvVectorMatrixHolder& mt1, 
					   const fvVectorMatrixHolder& mt2 )
  {
    tmp< fvVectorMatrix > result = mt1() - mt2();

    return fvVectorMatrixHolder( mt1() - mt2(), Deps( mt1.deps(), mt2.deps() ) );
  }

  inline fvVectorMatrixHolder operator == ( const fvVectorMatrixHolder& mt1, 
					    const fvVectorMatrixHolder& mt2 )
  {
    return fvVectorMatrixHolder( mt1() == mt2(), Deps( mt1.deps(), mt2.deps() ) );
  }
  
  inline fvVectorMatrixHolder operator == ( const fvVectorMatrixHolder& mt1, 
					    const volVectorFieldHolder& field )
  {
    return fvVectorMatrixHolder( mt1() == field() , Deps( mt1.deps(), &field ) );
  }
  
  
  //---------------------------------------------------------------------------
  // fvScalarMatrix operators
  inline fvScalarMatrixHolder operator + ( const fvScalarMatrixHolder& mt1, 
					   const fvScalarMatrixHolder& mt2 )
  {
    return fvScalarMatrixHolder( mt1() + mt2(),  Deps( mt1.deps(), mt2.deps() ) );
  }
  
  inline fvScalarMatrixHolder operator == ( const fvScalarMatrixHolder& mt1, 
					    const volScalarFieldHolder& field )
  {
    return fvScalarMatrixHolder( mt1() == field() , Deps( mt1.deps(), &field ) );
  }


  //---------------------------------------------------------------------------
} // Foam


//---------------------------------------------------------------------------
#endif
