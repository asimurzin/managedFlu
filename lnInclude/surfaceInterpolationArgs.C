#ifndef surfaceInterpolationArgs_C
#define surfaceInterpolationArgs_C


//---------------------------------------------------------------------------
#include "surfaceInterpolationArgs.H"


//---------------------------------------------------------------------------
Foam::surfaceInterpolationArgs::surfaceInterpolationArgs( const fvMeshHolder& fvm ):fvMeshHolder( fvm )
{}

Foam::surfaceInterpolationArgs::surfaceInterpolationArgs():fvMeshHolder()
{}


//---------------------------------------------------------------------------
#endif
