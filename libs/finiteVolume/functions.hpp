//  managedFlu - OpenFOAM C++ interactive functionality API
//  Copyright (C) 2010- Alexey Petrov
//  Copyright (C) 2009-2010 Pebble Bed Modular Reactor (Pty) Limited (PBMR)
//  
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//  
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//  
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
//  See http://sourceforge.net/projects/pythonflu
//
//  Author : Alexey PETROV, Andrey Simurzin


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
void CourantNo( const TimeHolder& runTime, 
                const fvMeshHolder& mesh, 
                const surfaceScalarFieldHolder& phi,
                scalar& CoNum,
                scalar& meanCoNum )
{
  CoNum = 0.0;
  meanCoNum = 0.0;
        
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
uniformDimensionedVectorFieldHolder readGravitationalAcceleration( const TimeHolder& runTime, const fvMeshHolder& mesh )
{
  Info<< "\nReading g" << endl;
  return uniformDimensionedVectorFieldHolder( IOobjectHolder( "g",
                                                              runTime->constant(),
                                                              mesh,
                                                              IOobject::MUST_READ,
                                                              IOobject::NO_WRITE ) );
}


//---------------------------------------------------------------------------
surfaceScalarFieldHolder createPhi( 
  const TimeHolder& runTime, 
  const fvMeshHolder& mesh, 
  const volVectorFieldHolder& U )
{
 Info<< "Reading/calculating face flux field phi\n" << endl;

 return surfaceScalarFieldHolder( IOobjectHolder( "phi",
                                                 runTime->timeName(),
                                                 mesh,
                                                 IOobject::READ_IF_PRESENT,
                                                 IOobject::AUTO_WRITE ),
                                 linearInterpolate( U ) & surfaceVectorFieldHolder( mesh->Sf(), &mesh ) );
 }


//---------------------------------------------------------------------------
void readTimeControls( const TimeHolder& runTime, bool& adjustTimeStep, scalar& maxCo, scalar& maxDeltaT)
{
  adjustTimeStep = runTime->controlDict().lookupOrDefault("adjustTimeStep", false);
 
  maxCo = runTime->controlDict().lookupOrDefault<scalar>("maxCo", 1.0);

  maxDeltaT =runTime->controlDict().lookupOrDefault<scalar>("maxDeltaT", GREAT);
}


//---------------------------------------------------------------------------
void setInitialDeltaT( TimeHolder& runTime, const bool& adjustTimeStep, const scalar& maxCo, const scalar& CoNum )
{
  if (adjustTimeStep)
  {
    if ((runTime->timeIndex() == 0) && (CoNum > SMALL))
    {
      runTime->setDeltaT( min( maxCo * runTime->deltaTValue() / CoNum, runTime->deltaTValue() ) );
    }
  }
}


//---------------------------------------------------------------------------
void setDeltaT( TimeHolder& runTime, const bool& adjustTimeStep, const scalar& maxCo, const scalar& CoNum, const scalar& maxDeltaT )
{
  if (adjustTimeStep)
  {
    scalar maxDeltaTFact = maxCo / ( CoNum + SMALL );
    scalar deltaTFact = min( min( maxDeltaTFact, 1.0 + 0.1 * maxDeltaTFact ), 1.2 );

    runTime->setDeltaT( min( deltaTFact * runTime->deltaTValue(), maxDeltaT ) );

    Info<< "deltaT = " <<  runTime->deltaTValue() << endl;
  }
}


//---------------------------------------------------------------------------
