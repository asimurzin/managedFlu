//---------------------------------------------------------------------------
#include "core.hpp"


//---------------------------------------------------------------------------
void compressibleCourantNo( 
  const TimeHolder& runTime, 
  const fvMeshHolder& mesh, 
  const surfaceScalarFieldHolder& phi,
  const volScalarFieldHolder& rho,
  scalar& CoNum,
  scalar& meanCoNum )
{
  CoNum = 0.0;
  meanCoNum = 0.0;

  if ( mesh->nInternalFaces() )
  {
    scalarField sumPhi( fvc::surfaceSum( mag( phi ) )().internalField() / rho->internalField() );

    CoNum = 0.5 * gMax( sumPhi / mesh->V().field() ) * runTime->deltaTValue();

    meanCoNum = 0.5 * ( gSum( sumPhi ) / gSum( mesh->V().field() ) )*runTime->deltaTValue();
  }

  Info<< "Courant Number mean: " << meanCoNum
      << " max: " << CoNum << endl;
}


//---------------------------------------------------------------------------

