//---------------------------------------------------------------------------
#include "core.hpp"


//---------------------------------------------------------------------------
scalar initContinuityErrs()
{
  scalar cumulativeContErr = 0;
  return cumulativeContErr;
}


//---------------------------------------------------------------------------
void readPISOControls( const fvMeshHolder& mesh, dictionary& pisoDict, 
                       int& nOuterCorr, int& nCorr, int& nNonOrthCorr, bool& momentumPredictor, bool& transonic)
{
  pisoDict = mesh->solutionDict().subDict("PISO");
  
  nOuterCorr = pisoDict.lookupOrDefault<int>("nOuterCorrectors", 1);
  
  nCorr = pisoDict.lookupOrDefault<int>("nCorrectors", 1);

  nNonOrthCorr = pisoDict.lookupOrDefault<int>("nNonOrthogonalCorrectors", 0);

  momentumPredictor = pisoDict.lookupOrDefault("momentumPredictor", true);

  transonic = pisoDict.lookupOrDefault("transonic", false);
}


//---------------------------------------------------------------------------
void CourantNo( const TimeHolder& runTime, const fvMeshHolder& mesh, const surfaceScalarFieldHolder& phi )
{
  scalar CoNum = 0.0;
  scalar meanCoNum = 0.0;
        
  if ( mesh->nInternalFaces() )
  { 
    scalarField sumPhi( fvc::surfaceSum(mag(phi))().internalField() );
          
    CoNum = 0.5 * gMax( sumPhi / mesh->V().field() ) * runTime->deltaTValue();
    meanCoNum = 0.5 * ( gSum( sumPhi ) / gSum( mesh->V().field() ) ) * runTime->deltaTValue();
  }
  Info<< "Courant Number mean: " << meanCoNum << " max: " << CoNum << endl;
}


//---------------------------------------------------------------------------
void continuityErrors( const TimeHolder& runTime, const fvMeshHolder& mesh, 
                       const surfaceScalarFieldHolder& phi, scalar& cumulativeContErr )
{
  volScalarFieldHolder contErr( fvc::div(phi) );

  scalar sumLocalContErr = runTime->deltaTValue() * mag( contErr )().weightedAverage( mesh->V() ).value();
  scalar globalContErr = runTime->deltaTValue() * contErr().weightedAverage( mesh->V() ).value();
  cumulativeContErr += globalContErr;
  Info << "time step continuity errors : sum local = " << sumLocalContErr
       << ", global = " << globalContErr
       << ", cumulative = " << cumulativeContErr << endl;
}


//---------------------------------------------------------------------------
uniformDimensionedVectorField readGravitationalAcceleration( const TimeHolder& runTime, const fvMeshHolder& mesh )
{
  Info<< "\nReading g" << endl;
  return uniformDimensionedVectorField( IOobject( "g",
           runTime->constant(),
           *mesh,
           IOobject::MUST_READ,
           IOobject::NO_WRITE ) );
}


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
                                    linearInterpolate( rho * U ) & mesh->Sf() );
}
