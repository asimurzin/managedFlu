/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2004-2011 OpenCFD Ltd.
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Application
    chtMultiRegionFoam

Description
    Combination of heatConductionFoam and buoyantFoam for conjugate heat
    transfer between a solid region and fluid region

\*---------------------------------------------------------------------------*/

#include "fvCFD.H"
#include "basicRhoThermo.H"
#include "turbulenceModel.H"
#include "fixedGradientFvPatchFields.H"
#include "regionProperties.H"
#include "compressibleCourantNo.H"
#include "solidRegionDiffNo.H"
#include "basicSolidThermo.H"
#include "radiationModel.H"


#include "core.hpp"
#include "basicRhoThermoHolder.hpp"
#include "basicSolidThermoHolder.hpp"
#include "turbulenceModels/compressible/turbulenceModel/turbulenceModelHolder.hpp"
#include "radiationModelHolder.hpp"

#include "OpenFOAM/functions.hpp"
#include "finiteVolume/functions.hpp"
#include "thermophysicalModels/radiationModel/functions.hpp"
#include "rhoEqn.hpp"

//---------------------------------------------------------------------------
#include <vector>
template<typename T>
class TList
{
public:
    typedef std::vector< T > list;
private:
    TList() {};
};

#undef forAll
#define forAll(list, i) \
    for ( size_t i=0; i<list.size(); i++)


//---------------------------------------------------------------------------
#include "fluid.hpp"
#include "solid.hpp"


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
//---------------------------------------------------------------------------
void setInitialMultiRegionDeltaT( TimeHolder& runTime,
                                  scalar& CoNum, scalar& DiNum,
                                  const bool& adjustTimeStep, const scalar& maxCo,
                                  const scalar& maxDeltaT, const scalar& maxDi )
{
  if (adjustTimeStep)
  {
    if ((runTime->timeIndex() == 0) && ((CoNum > SMALL) || (DiNum > SMALL)))
    {
      if (CoNum < SMALL)
      {
        CoNum = SMALL;
      }

      if (DiNum < SMALL)
      {
        DiNum = SMALL;
      }

      runTime->setDeltaT( min( min( maxCo / CoNum, maxDi / DiNum ) * runTime->deltaT().value(),
                               maxDeltaT ) );
        Info<< "deltaT = " <<  runTime->deltaT().value() << endl;
    }
  }
}


//---------------------------------------------------------------------------
void readPIMPLEControls( const TimeHolder& runTime, dictionary& pimple, int& nOuterCorr)
{
  // We do not have a top-level mesh. Construct the fvSolution for
  // the runTime instead.
  fvSolution solutionDict( *runTime );

  pimple = solutionDict.subDict("PIMPLE");

  nOuterCorr = pimple.lookupOrDefault<int>("nOuterCorrectors", 1);
}

//---------------------------------------------------------------------------
void setMultiRegionDeltaT( TimeHolder& runTime,
                                  scalar& CoNum, scalar& DiNum,
                                  const bool& adjustTimeStep, const scalar& maxCo,
                                  const scalar& maxDeltaT, const scalar& maxDi )
{
  if (adjustTimeStep)
  {
    if (CoNum == -GREAT)
    {
      CoNum = SMALL;
    }

    if (DiNum == -GREAT)
    {
      DiNum = SMALL;
    }

    scalar maxDeltaTFluid = maxCo / (CoNum + SMALL);
    scalar maxDeltaTSolid = maxDi / (DiNum + SMALL);

    scalar deltaTFluid =min( min( maxDeltaTFluid, 1.0 + 0.1 * maxDeltaTFluid), 1.2 );

    runTime->setDeltaT( min( min( deltaTFluid, maxDeltaTSolid ) * runTime->deltaT().value(),
                            maxDeltaT ) );

    Info<< "deltaT = " <<  runTime->deltaT().value() << endl;
}

}
//---------------------------------------------------------------------------
int main(int argc, char *argv[])
{
  argList args = setRootCase( argc, argv );
   
  TimeHolder runTime=createTime( Time::controlDictName, args );

  regionProperties rp( *runTime );
  
  TList<fvMeshHolder>::list fluidRegions;
  createFluidMeshes( runTime, rp, fluidRegions );
  
  TList<fvMeshHolder>::list solidRegions;
  createSolidMeshes( runTime, rp, solidRegions );

  TList<basicRhoThermoHolder>::list thermoFluid; TList<volScalarFieldHolder>::list rhoFluid;
  TList<volScalarFieldHolder>::list KFluid; TList<volVectorFieldHolder>::list UFluid;
  TList<surfaceScalarFieldHolder>::list phiFluid; TList<uniformDimensionedVectorFieldHolder>::list gFluid;
  TList<compressible::turbulenceModelHolder>::list turbulence; TList<volScalarFieldHolder>::list p_rghFluid;
  TList<volScalarFieldHolder>::list ghFluid; TList<surfaceScalarFieldHolder>::list ghfFluid;
  TList<radiation::radiationModelHolder>::list radiation; TList<volScalarFieldHolder>::list DpDtFluid;
  TList<scalar>::list initialMassFluid;
  createFluidFields( runTime, fluidRegions, thermoFluid, rhoFluid, KFluid, UFluid, phiFluid, gFluid, turbulence, 
                     p_rghFluid, ghFluid, ghfFluid, radiation, DpDtFluid, initialMassFluid );
  
  TList<basicSolidThermoHolder>::list thermos;
  createSolidFields( runTime, solidRegions, thermos );

  TList<scalar>::list cumulativeContErr = initContinuityErrs( fluidRegions );
  
  bool adjustTimeStep; scalar maxCo; scalar maxDeltaT;
  readTimeControls( runTime, adjustTimeStep, maxCo, maxDeltaT );
  
  scalar maxDi = readSolidTimeControls( runTime );
  
  scalar CoNum = compressibleMultiRegionCourantNo( runTime, fluidRegions, rhoFluid, phiFluid );
  
  scalar DiNum = solidRegionDiffusionNo(runTime,  solidRegions, thermos );
  
  setInitialMultiRegionDeltaT( runTime, CoNum, DiNum, adjustTimeStep, maxCo, maxDeltaT, maxDi );
  
  while ( runTime->run() )
  {
    readTimeControls( runTime, adjustTimeStep, maxCo, maxDeltaT );
    maxDi = readSolidTimeControls( runTime );
    
    dictionary pimple; int nOuterCorr;
    readPIMPLEControls( runTime, pimple, nOuterCorr);

    CoNum = compressibleMultiRegionCourantNo( runTime, fluidRegions, rhoFluid, phiFluid );
  
    DiNum = solidRegionDiffusionNo(runTime,  solidRegions, thermos );
    
    setMultiRegionDeltaT( runTime, CoNum, DiNum, adjustTimeStep, maxCo, maxDeltaT, maxDi );
 
    ( *runTime )++;

    Info<< "Time = " << runTime->timeName() << nl << endl;

    if (nOuterCorr != 1)
    {
      forAll(fluidRegions, i)
      {
        fvMeshHolder mesh; basicRhoThermoHolder thermo; volScalarFieldHolder rho; volScalarFieldHolder K;
        volVectorFieldHolder U; surfaceScalarFieldHolder phi; compressible::turbulenceModelHolder turb;
        volScalarFieldHolder DpDt; volScalarFieldHolder p; volScalarFieldHolder psi;
        volScalarFieldHolder h; volScalarFieldHolder p_rgh; volScalarFieldHolder gh;
        surfaceScalarFieldHolder ghf; radiation::radiationModelHolder rad;
        
        dimensionedScalar initialMass = setRegionFluidFields( i, fluidRegions, mesh, thermoFluid, thermo, rhoFluid, rho, KFluid, K,
                                                              UFluid, U, phiFluid, phi, turbulence, turb, p_rghFluid, p_rgh,
                                                              ghFluid, gh, ghfFluid, ghf, radiation, rad, DpDtFluid, DpDt,
                                                              initialMassFluid, p, psi, h );
        
        storeOldFluidFields( p_rgh, rho );
      }
    }


    // --- PIMPLE loop
    for (int oCorr=0; oCorr<nOuterCorr; oCorr++)
    {
      bool finalIter = oCorr == nOuterCorr-1;
      forAll(fluidRegions, i)
      {
        Info << "\nSolving for fluid region "
             << fluidRegions[i]->name() << endl;
        
        fvMeshHolder mesh; basicRhoThermoHolder thermo; volScalarFieldHolder rho; volScalarFieldHolder K;
        volVectorFieldHolder U; surfaceScalarFieldHolder phi; compressible::turbulenceModelHolder turb;
        volScalarFieldHolder DpDt; volScalarFieldHolder p; volScalarFieldHolder psi;
        volScalarFieldHolder h; volScalarFieldHolder p_rgh; volScalarFieldHolder gh;
        surfaceScalarFieldHolder ghf; radiation::radiationModelHolder rad;

        dimensionedScalar initialMass = setRegionFluidFields( i, fluidRegions, mesh, thermoFluid, thermo, rhoFluid, rho, KFluid, K,
                                                              UFluid, U, phiFluid, phi, turbulence, turb, p_rghFluid, p_rgh,
                                                              ghFluid, gh, ghfFluid, ghf, radiation, rad, DpDtFluid, DpDt,
                                                              initialMassFluid, p, psi, h );
        
        dictionary pimple; int nCorr; int nNonOrthCorr; bool momentumPredictor;
        readFluidMultiRegionPIMPLEControls( mesh, pimple, nCorr, nNonOrthCorr, momentumPredictor );
        

        solveFluid( i, mesh, thermo, thermoFluid, rho, K, U, phi, turb, p_rgh, gh, 
                    ghf, rad, DpDt, p, psi, h, finalIter, oCorr, nCorr, nNonOrthCorr, nOuterCorr, momentumPredictor, cumulativeContErr, initialMass );

      }

      forAll(solidRegions, i)
      {
        Info<< "\nSolving for solid region " << solidRegions[i]->name() << endl;
        fvMeshHolder mesh; basicSolidThermoHolder thermo;
        volScalarFieldHolder rho; volScalarFieldHolder cp;
        volScalarFieldHolder K; volScalarFieldHolder T;
        setRegionSolidFields( i, solidRegions, mesh, thermos, thermo, rho, cp, K,T );
        int nNonOrthCorr = readSolidMultiRegionPIMPLEControls( mesh );
        solveSolid( mesh, thermo, rho, cp, K, T, nNonOrthCorr, finalIter );
      } 
    }
    runTime->write();

    Info<< "ExecutionTime = " << runTime->elapsedCpuTime() << " s"
        << "  ClockTime = " << runTime->elapsedClockTime() << " s"
        << nl << endl;
  }
        
  
  Info<< "End\n" << endl;

  return 0;
}


// ************************************************************************* //
