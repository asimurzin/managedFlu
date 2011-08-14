#ifndef surfaceFields_hpp
#define surfaceFields_hpp


//---------------------------------------------------------------------------
#include <surfaceFields.H>
#include "GeometricFieldHolder.H"



//---------------------------------------------------------------------------
namespace Foam
{
  typedef GeometricFieldHolder< scalar, fvsPatchField, surfaceMesh > surfaceScalarFieldHolder;
  typedef GeometricFieldHolder< vector, fvsPatchField, surfaceMesh > surfaceVectorFieldHolder;
}

//---------------------------------------------------------------------------
#endif
