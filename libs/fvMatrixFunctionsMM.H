#ifndef fvMatrixFunctionsMM_H
#define fvMatrixFunctionsMM_H


//---------------------------------------------------------------------------
#include <fvm.H>
#include <dimensionedScalar.H>
#include "surfaceFieldsMM.H"
#include "volFieldsMM.H"


//---------------------------------------------------------------------------
namespace Foam
{


//---------------------------------------------------------------------------
// fvVectorMatrix operators
   inline fvVectorMatrixHolder operator+ ( const fvVectorMatrixHolder& mt1, const fvVectorMatrixHolder& mt2 )
   {
     tmp< fvVectorMatrix > result = mt1() + mt2();

     if ( &( result().psi() ) == &( mt1.get_fieldArg()() ) )
       return fvVectorMatrixHolder( result, mt1.get_fieldArg() );
     else if ( &( result().psi() ) == &(  mt2.get_fieldArg()() ) )
       return fvVectorMatrixHolder( result, mt2.get_fieldArg() );

     FatalErrorIn( "fvVectorMatrixHolder operator+ ( const fvVectorMatrixHolder& mt1, const fvVectorMatrixHolder& mt2 )")
                    << exit(FatalError);
   }

   inline fvVectorMatrixHolder operator- ( const fvVectorMatrixHolder& mt1, const fvVectorMatrixHolder& mt2 )
   {
     tmp< fvVectorMatrix > result = mt1() - mt2();

     if ( &( result().psi() ) == &( mt1.get_fieldArg()() ) )
       return fvVectorMatrixHolder( result, mt1.get_fieldArg() );
     else if ( &( result().psi() ) == &(  mt2.get_fieldArg()() ) )
       return fvVectorMatrixHolder( result, mt2.get_fieldArg() );

     FatalErrorIn( "fvVectorMatrixHolder operator- ( const fvVectorMatrixHolder& mt1, const fvVectorMatrixHolder& mt2 )")
                    << exit(FatalError);
   }

   inline fvVectorMatrixHolder operator==( const fvVectorMatrixHolder& mt1, const fvVectorMatrixHolder& mt2 )
   {
     tmp< fvVectorMatrix > result = ( mt1() == mt2() );

     if ( &( result().psi() ) == &( mt1.get_fieldArg()() ) )
       return fvVectorMatrixHolder( result, mt1.get_fieldArg() );
     else if ( &( result().psi() ) == &(  mt2.get_fieldArg()() ) )
       return fvVectorMatrixHolder( result, mt2.get_fieldArg() );

     FatalErrorIn( "fvVectorMatrixHolder operator==( const fvVectorMatrixHolder& mt1, const fvVectorMatrixHolder& mt2 )")
                    << exit(FatalError);

   }

   inline fvVectorMatrixHolder operator==( const fvVectorMatrixHolder& mt1, const volVectorFieldHolder& field )
   {
     return fvVectorMatrixHolder( mt1() == field() , mt1.get_fieldArg() );
   }


//---------------------------------------------------------------------------
// fvScalarMatrix operators

   inline fvScalarMatrixHolder operator+ ( const fvScalarMatrixHolder& mt1, const fvScalarMatrixHolder& mt2 )
   {
     tmp< fvScalarMatrix > result = mt1() + mt2();

     if ( &( result().psi() ) == &( mt1.get_fieldArg()() ) )
     {
       return fvScalarMatrixHolder( result, mt1.get_fieldArg() );
     }
     else if ( &( result().psi() ) == &(  mt2.get_fieldArg()() ) )
     {
       return fvScalarMatrixHolder( result, mt2.get_fieldArg() );
     }

     FatalErrorIn( "fvScalarMatrixHolder operator+ ( const fvScalarMatrixHolder& mt1, const fvScalarMatrixHolder& mt2 )")
                    << exit(FatalError);
   }

   inline fvScalarMatrixHolder operator==( const fvScalarMatrixHolder& mt1, const volScalarFieldHolder& field )
   {
     return fvScalarMatrixHolder( mt1() == field() , mt1.get_fieldArg() );
   }


//---------------------------------------------------------------------------




} // Foam


//---------------------------------------------------------------------------
#endif
