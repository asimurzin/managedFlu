#ifndef fvm_hpp
#define fvm_hpp


//---------------------------------------------------------------------------
#include "common.hpp"

#include <fvm.H>
#include <dimensionedScalar.H>
#include "surfaceFields.hpp"
#include "volFields.hpp"
#include "fvMatrices.hpp"


//---------------------------------------------------------------------------
namespace Foam
{
  namespace fvm
  {
    //-----------------------------------------------------------------------
#if FOAM_VERSION( >=, 020000 )    
    inline fvVectorMatrixHolder ddt( const volVectorFieldHolder& field )
    {
      return fvVectorMatrixHolder( ddt( field() ), &field );
    }

    //-----------------------------------------------------------------------
    inline fvVectorMatrixHolder div( const surfaceScalarFieldHolder& field1, 
				     const volVectorFieldHolder& field2 )
    {
      return fvVectorMatrixHolder( div( field1(), field2() ), Deps( &field1, &field2 ) );
    }
    

    //-----------------------------------------------------------------------
    inline fvVectorMatrixHolder laplacian( const dimensionedScalar& ds, 
                                           const volVectorFieldHolder& field )
    {
      return fvVectorMatrixHolder( laplacian( ds, field() ), &field );
    }

    inline fvScalarMatrixHolder laplacian( const volScalarFieldHolder& field1, 
					   const volScalarFieldHolder& field2 )
    {
      return fvScalarMatrixHolder( laplacian( field1(), field2() ), Deps( &field1, &field2 )  );
    }
#endif

#if FOAM_VERSION( <, 020000 )
    inline fvVectorMatrixHolder ddt( volVectorFieldHolder& field )
    {
      return fvVectorMatrixHolder( ddt( field() ), &field );
    }

    //-----------------------------------------------------------------------
    inline fvVectorMatrixHolder div( const surfaceScalarFieldHolder& field1, 
				     volVectorFieldHolder& field2 )
    {
      return fvVectorMatrixHolder( div( field1(), field2() ), Deps( &field1, &field2 ) );
    }
    

    //-----------------------------------------------------------------------
    inline fvVectorMatrixHolder laplacian( const dimensionedScalar& ds, 
                                           volVectorFieldHolder& field )
    {
      return fvVectorMatrixHolder( laplacian( ds, field() ), &field );
    }

    inline fvScalarMatrixHolder laplacian( const volScalarFieldHolder& field1, 
					   volScalarFieldHolder& field2 )
    {
      return fvScalarMatrixHolder( laplacian( field1(), field2() ), Deps( &field1, &field2 )  );
    }
#endif
  } // fvm
} // Foam


//---------------------------------------------------------------------------
#endif
