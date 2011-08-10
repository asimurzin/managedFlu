#ifndef fvMatrixFunctionsMM_H
#define fvMatrixFunctionsMM_H


//---------------------------------------------------------------------------
#include <fvm.H>
#include <dimensionedScalar.H>
#include "surfaceFieldsMM.H"
#include "volFieldsMM.H"
#include "fvMatricesMM.H"


//---------------------------------------------------------------------------
namespace Foam
{
  //---------------------------------------------------------------------------
  // fvVectorMatrix operators
  inline fvVectorMatrixHolder operator + ( const fvVectorMatrixHolder& mt1, 
					   const fvVectorMatrixHolder& mt2 )
  {
    tmp< fvVectorMatrix > result = mt1() + mt2();
    
    if ( &( result().psi() ) == &( mt1.psi()() ) )
      return fvVectorMatrixHolder( result, mt1.psi() );
    else if ( &( result().psi() ) == &(  mt2.psi()() ) )
      return fvVectorMatrixHolder( result, mt2.psi() );
    
    FatalErrorIn( "fvVectorMatrixHolder operator+ ( const fvVectorMatrixHolder& mt1, const fvVectorMatrixHolder& mt2 )")
      << exit(FatalError);
    return fvVectorMatrixHolder( result, mt2.psi() ); //dummy return
  }

  inline fvVectorMatrixHolder operator - ( const fvVectorMatrixHolder& mt1, 
					   const fvVectorMatrixHolder& mt2 )
  {
    tmp< fvVectorMatrix > result = mt1() - mt2();
    
    if ( &( result().psi() ) == &( mt1.psi()() ) )
      return fvVectorMatrixHolder( result, mt1.psi() );
    else if ( &( result().psi() ) == &(  mt2.psi()() ) )
      return fvVectorMatrixHolder( result, mt2.psi() );
    
    FatalErrorIn( "fvVectorMatrixHolder operator- ( const fvVectorMatrixHolder& mt1, const fvVectorMatrixHolder& mt2 )")
      << exit(FatalError);
    return fvVectorMatrixHolder( result, mt2.psi() ); //dummy return
  }

  inline fvVectorMatrixHolder operator == ( const fvVectorMatrixHolder& mt1, 
					    const fvVectorMatrixHolder& mt2 )
  {
    tmp< fvVectorMatrix > result = ( mt1() == mt2() );
    
    if ( &( result().psi() ) == &( mt1.psi()() ) )
      return fvVectorMatrixHolder( result, mt1.psi() );
    else if ( &( result().psi() ) == &(  mt2.psi()() ) )
      return fvVectorMatrixHolder( result, mt2.psi() );
    
    FatalErrorIn( "fvVectorMatrixHolder operator==( const fvVectorMatrixHolder& mt1, const fvVectorMatrixHolder& mt2 )")
      << exit(FatalError);
    return fvVectorMatrixHolder( result, mt2.psi() ); //dummy return  
  }
  
  inline fvVectorMatrixHolder operator == ( const fvVectorMatrixHolder& mt1, 
					    const volVectorFieldHolder& field )
  {
    return fvVectorMatrixHolder( mt1() == field() , mt1.psi() );
  }
  
  
  //---------------------------------------------------------------------------
  // fvScalarMatrix operators
  inline fvScalarMatrixHolder operator + ( const fvScalarMatrixHolder& mt1, 
					   const fvScalarMatrixHolder& mt2 )
  {
    tmp< fvScalarMatrix > result = mt1() + mt2();
    
    if ( &( result().psi() ) == &( mt1.psi()() ) )
      return fvScalarMatrixHolder( result, mt1.psi() );
    else if ( &( result().psi() ) == &(  mt2.psi()() ) )
      return fvScalarMatrixHolder( result, mt2.psi() );
    
    FatalErrorIn( "fvScalarMatrixHolder operator+ ( const fvScalarMatrixHolder& mt1, const fvScalarMatrixHolder& mt2 )")
      << exit(FatalError);
    return fvScalarMatrixHolder( result, mt2.psi() ); //dummy return
  }
  
  inline fvScalarMatrixHolder operator == ( const fvScalarMatrixHolder& mt1, 
					    const volScalarFieldHolder& field )
  {
    return fvScalarMatrixHolder( mt1() == field() , mt1.psi() );
  }


  //---------------------------------------------------------------------------
} // Foam


//---------------------------------------------------------------------------
#endif
