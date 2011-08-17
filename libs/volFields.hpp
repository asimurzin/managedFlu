#ifndef volFields_hpp
#define volFields_hpp


//---------------------------------------------------------------------------
#include "GeometricFieldHolder.H"

#include <volFields.H>


//---------------------------------------------------------------------------
namespace Foam
{
  typedef GeometricFieldHolder< scalar, fvPatchField, volMesh > volScalarFieldHolder;
  typedef GeometricFieldHolder< vector, fvPatchField, volMesh > volVectorFieldHolder;
}

//---------------------------------------------------------------------------
#endif
