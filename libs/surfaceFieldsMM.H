#ifndef surfaceFieldsMM_H
#define surfaceFieldsMM_H


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
