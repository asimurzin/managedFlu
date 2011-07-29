#ifndef fvMeshArgs_C
#define fvMeshArgs_C


//---------------------------------------------------------------------------
#include "fvMeshArgs.H"


//---------------------------------------------------------------------------
Foam::fvMeshArgs::fvMeshArgs( const IOobjectHolder& orh ) : IOobjectHolder( orh ), 
                                                            surfaceInterpolationArgs(),
                                                            polyMeshArgs()
{}

Foam::fvMeshArgs::fvMeshArgs():IOobjectHolder(),
                               surfaceInterpolationArgs(),
                               polyMeshArgs()
{}


//---------------------------------------------------------------------------
#endif
