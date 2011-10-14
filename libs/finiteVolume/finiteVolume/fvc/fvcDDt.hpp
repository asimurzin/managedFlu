#ifndef fvcDDt_hpp
#define fvcDDt_hpp


//---------------------------------------------------------------------------
#include <fvcDDt.H>
#include "surfaceFields.hpp"
#include "volFields.hpp"


//---------------------------------------------------------------------------
namespace Foam
{
  namespace fvc
  {
   template<class Type>
   inline GeometricFieldHolder< Type, fvPatchField, volMesh> DDt( const surfaceScalarFieldHolder& field1,
                                                                  const GeometricFieldHolder< Type, fvPatchField, volMesh >& field2 )
    
   {
     return GeometricFieldHolder< Type, fvPatchField, volMesh >( DDt( field1(), field2() ), Deps( &field1, &field2 ) );
   }
   
  } // fvc
} //Foam


//---------------------------------------------------------------------------
#endif
