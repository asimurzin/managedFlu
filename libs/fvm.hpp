#ifndef fvm_hpp
#define fvm_hpp


//---------------------------------------------------------------------------
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
    inline fvVectorMatrixHolder ddt( const volVectorFieldHolder& field )
    {
      return fvVectorMatrixHolder( ddt( field() ), &field );
    }


    //-----------------------------------------------------------------------
    inline fvVectorMatrixHolder div( const surfaceScalarFieldHolder& field1, 
				     const volVectorFieldHolder& field2 )
    {
      return fvVectorMatrixHolder( div( field1(), field2() ), universalArgs( &field2 ).deps() && universalArgs( &field1 ).deps()  );
    }
    

    //-----------------------------------------------------------------------
    inline fvVectorMatrixHolder laplacian( const dimensionedScalar& ds, 
                                           const volVectorFieldHolder& field )
    {
      return fvVectorMatrixHolder( laplacian( ds, field() ), universalArgs( &field ).deps() );
    }

    inline fvScalarMatrixHolder laplacian( const volScalarFieldHolder& field1, 
					   const volScalarFieldHolder& field2 )
    {
      return fvScalarMatrixHolder( laplacian( field1(), field2() ), universalArgs( &field2 ).deps() && universalArgs( &field1 ).deps()  );
    }
  } // fvm
} // Foam


//---------------------------------------------------------------------------
#endif
