/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2004-2010 OpenCFD Ltd.
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
    channelFoam

Description
    Incompressible LES solver for flow in a channel.

\*---------------------------------------------------------------------------*/

#include "fvCFD.H"
#include "singlePhaseTransportModel.H"
#include "IFstream.H"
#include "OFstream.H"
#include "Random.H"

#include "core.hpp"
#include "OpenFOAM/functions.hpp"
#include "finiteVolume/functions.hpp"

#include "singlePhaseTransportModelHolder.hpp"
#include "turbulenceModels/incompressible/LES/LESModelHolder.hpp"
#include "simpleControlHolder.hpp"


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
//---------------------------------------------------------------------------
struct result_readTransportProperties
{
  dimensionedVector m_Ubar;
  dimensionedScalar m_nu;
  dimensionedScalar m_magUbar;
  vector m_flowDirection;
  result_readTransportProperties( dimensionedVector the_Ubar, dimensionedScalar the_nu, dimensionedScalar the_magUbar, vector the_flowDirection )
    : m_Ubar( the_Ubar )
    , m_nu( the_nu )
    , m_magUbar( the_magUbar )
    , m_flowDirection( the_flowDirection )
  {}
};


//---------------------------------------------------------------------------
result_readTransportProperties readTransportProperties( const TimeHolder& runTime, const fvMeshHolder& mesh,
                                                        IOdictionaryHolder& transportProperties )
{
  Info<< "\nReading transportProperties\n" << endl;
  transportProperties = IOdictionaryHolder( IOobjectHolder( "transportProperties",
                                                            runTime->constant(),
                                                            mesh,
                                                            IOobject::MUST_READ_IF_MODIFIED,
                                                            IOobject::NO_WRITE,
                                                            false ) );


    dimensionedScalar nu( transportProperties->lookup("nu") );

    //  Read centerline velocity for channel simulations
    dimensionedVector Ubar( transportProperties->lookup("Ubar") );

    dimensionedScalar magUbar = mag(Ubar);
    vector flowDirection = (Ubar/magUbar).value();
    
    return result_readTransportProperties( Ubar, nu, magUbar, flowDirection );
}


//---------------------------------------------------------------------------
void  createFields( const TimeHolder& runTime, 
                    const fvMeshHolder& mesh,
                    volScalarFieldHolder& p,
                    volVectorFieldHolder& U,
                    surfaceScalarFieldHolder& phi,
                    incompressible::LESModelHolder& sgsModel,
                    singlePhaseTransportModelHolder& laminarTransport,
                    label& pRefCell, scalar& pRefValue )
{
  Info<< "Reading field p\n" << endl;
  p( volScalarFieldHolder( IOobjectHolder( "p",
                                           runTime->timeName(),
                                           mesh,
                                           IOobject::MUST_READ,
                                           IOobject::AUTO_WRITE ),
                           mesh ) );


  Info<< "Reading field U\n" << endl;
  U( volVectorFieldHolder( IOobjectHolder( "U",
                                             runTime->timeName(),
                                             mesh,
                                             IOobject::MUST_READ,
                                             IOobject::AUTO_WRITE ),
                             mesh ) );

  phi( createPhi( runTime, mesh, U ) );

  pRefCell = 0;
  pRefValue = 0.0;
  setRefCell(p, mesh->solutionDict().subDict("PISO"), pRefCell, pRefValue);

  laminarTransport( singlePhaseTransportModelHolder( U, phi ) );

  sgsModel( incompressible::LESModelHolder::New( U, phi, laminarTransport ) );
}


//---------------------------------------------------------------------------
dimensionedScalar createGradP( const TimeHolder& runTime )
{
  dimensionedScalar gradP( "gradP", dimensionSet(0, 1, -2, 0, 0), 0.0 );

  IFstream gradPFile( runTime->path()/runTime->timeName()/"uniform"/"gradP.raw" );
  
  if (gradPFile.good())
  {
    gradPFile >> gradP;
    Info<< "Reading average pressure gradient" << endl << endl;
  }
  else
  {
    Info<< "Initializing with 0 pressure gradient" << endl << endl;
  };
  
  return gradP;
}


//---------------------------------------------------------------------------
void writeGradP( const TimeHolder& runTime, const dimensionedScalar& gradP, const argList& args )
{
  if (runTime->outputTime())
  {
    OFstream gradPFile( runTime->path()/runTime->timeName()/"uniform"/"gradP.raw" );

    if (gradPFile.good())
    {
      gradPFile << gradP << endl;
    }
    else
    {
      FatalErrorIn(args.executable()) << "Cannot open file " << runTime->path()/runTime->timeName()/"uniform"/"gradP.raw" << exit(FatalError);
    };
  };
}


//---------------------------------------------------------------------------
int main(int argc, char *argv[])
{
  argList args = setRootCase( argc, argv );
    
  TimeHolder runTime=createTime( Time::controlDictName, args );
    
  fvMeshHolder mesh = createMesh( runTime );
  
  IOdictionaryHolder transportProperties;
  
  result_readTransportProperties result = readTransportProperties( runTime, mesh, transportProperties );
  
  dimensionedVector Ubar = result.m_Ubar;
  dimensionedScalar nu = result.m_nu;
  dimensionedScalar magUbar = result.m_magUbar;
  vector flowDirection = result.m_flowDirection;

  volScalarFieldHolder p; volVectorFieldHolder U; surfaceScalarFieldHolder phi;
  incompressible::LESModelHolder sgsModel; singlePhaseTransportModelHolder laminarTransport;
  label pRefCell; scalar pRefValue;
  
  createFields( runTime, mesh, p, U, phi, sgsModel, laminarTransport, pRefCell, pRefValue );
  
  scalar cumulativeContErr = initContinuityErrs();
  
  dimensionedScalar gradP = createGradP( runTime );
  

  Info<< "\nStarting time loop\n" << endl;

  while (runTime->loop())
  {
    Info<< "Time = " << runTime->timeName() << nl << endl;

    dictionary pisoDict; int nOuterCorr; int nCorr; int nNonOrthCorr;
    bool momentumPredictor; bool transonic;
    readPISOControls( mesh, pisoDict, nOuterCorr, nCorr, nNonOrthCorr, momentumPredictor, transonic);
        
    scalar CoNum; scalar meanCoNum;
    CourantNo( runTime, mesh, phi, CoNum, meanCoNum );

    sgsModel->correct();

    smart_tmp< fvVectorMatrix > UEqn( fvm::ddt( U() ) + fvm::div( phi(), U() ) + sgsModel->divDevBeff( U() ) == flowDirection*gradP );

    if (momentumPredictor)
    {
      solve( UEqn() == -fvc::grad( p() ) );
    }

    // --- PISO loop

    smart_tmp< volScalarField > rAU( 1.0 / UEqn->A() );

    for (int corr=0; corr<nCorr; corr++)
    {
      U = rAU() * UEqn->H();
      phi = ( fvc::interpolate( U() ) & mesh->Sf() ) + fvc::ddtPhiCorr( rAU(), U(), phi() );

      adjustPhi(phi, U, p);

      for (int nonOrth=0; nonOrth<=nNonOrthCorr; nonOrth++)
      {
        smart_tmp< fvScalarMatrix > pEqn( fvm::laplacian( rAU(), p() ) == fvc::div( phi() ) );
        
        pEqn->setReference( pRefCell, pRefValue );
        
        if (corr == nCorr-1 && nonOrth == nNonOrthCorr)
        {
          pEqn->solve( mesh->solver( p->name() + "Final" ) );
        }
        else
        {
          pEqn->solve( mesh->solver( p->name() ) );
        }

        if (nonOrth == nNonOrthCorr)
        {
          phi -= pEqn->flux();
        }
      }
      continuityErrors( runTime, mesh, phi, cumulativeContErr );
      U -= rAU() * fvc::grad( p() );
      U->correctBoundaryConditions();
    }

    // Correct driving force for a constant mass flow rate

    // Extract the velocity in the flow direction
    dimensionedScalar magUbarStar = ( flowDirection & U() )().weightedAverage( mesh->V() );
    
    // Calculate the pressure gradient increment needed to
    // adjust the average flow-rate to the correct value
    dimensionedScalar gragPplus = ( magUbar - magUbarStar ) / rAU->weightedAverage( mesh->V() );

    U += flowDirection * rAU() * gragPplus;

    gradP += gragPplus;

    Info<< "Uncorrected Ubar = " << magUbarStar.value() << tab
        << "pressure gradient = " << gradP.value() << endl;

    runTime->write();
    writeGradP( runTime, gradP, args );

    Info<< "ExecutionTime = " << runTime->elapsedCpuTime() << " s"
        << "  ClockTime = " << runTime->elapsedClockTime() << " s"
        << nl << endl;
  }

  Info<< "End\n" << endl;

  return 0;
}


// ************************************************************************* //
