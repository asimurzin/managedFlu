//---------------------------------------------------------------------------
#include "core.hpp"


//---------------------------------------------------------------------------
surfaceScalarFieldHolder compressibleCreatePhi( 
  const TimeHolder& runTime, 
  const fvMeshHolder& mesh, 
  const volVectorFieldHolder& U,
  const volScalarFieldHolder& rho )
{
  Info<< "Reading/calculating face flux field phi\n" << endl;
  
  return surfaceScalarFieldHolder( IOobjectHolder( "phi",
                                                   runTime->timeName(),
                                                   mesh,
                                                   IOobject::READ_IF_PRESENT,
                                                   IOobject::AUTO_WRITE ),
                                    linearInterpolate( rho * U ) & surfaceVectorFieldHolder( mesh->Sf(), &mesh ) );
}


//---------------------------------------------------------------------------
