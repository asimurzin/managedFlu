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
    shallowWaterFoam

Description
    Transient solver for inviscid shallow-water equations with rotation.

    If the geometry is 3D then it is assumed to be one layers of cells and the
    component of the velocity normal to gravity is removed.

\*---------------------------------------------------------------------------*/

#include "fvCFD.H"
#include "core.hpp"
#include "OpenFOAM/functions.hpp"
#include "finiteVolume/functions.hpp"
#include "pimpleControlHolder.hpp"


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
//---------------------------------------------------------------------------
struct result_readGravitationalAcceleration
{
  dimensionedVector m_g;
  dimensionedVector m_Omega;
  dimensionedScalar m_magg;
  dimensionedVector m_gHat;
  result_readGravitationalAcceleration( dimensionedVector the_g, dimensionedVector the_Omega, 
                                        dimensionedScalar the_magg, dimensionedVector the_gHat )
    : m_g( the_g )
    , m_Omega( the_Omega )
    , m_magg( the_magg )
    , m_gHat( the_gHat )
  {}
};

result_readGravitationalAcceleration readGravitationalAcceleration( const TimeHolder& runTime,
                                                                    const fvMeshHolder& mesh,
                                                                    IOdictionaryHolder& gravitationalProperties,
                                                                    Switch& rotating )
{
  Info<< "\nReading gravitationalProperties" << endl;

  gravitationalProperties( IOdictionaryHolder( IOobjectHolder( "gravitationalProperties",
                                                               runTime->constant(),
                                                               mesh,
                                                               IOobject::MUST_READ_IF_MODIFIED,
                                                               IOobject::NO_WRITE ) ) );

  dimensionedVector g(gravitationalProperties->lookup("g"));
  rotating = Switch(gravitationalProperties->lookup("rotating"));
  dimensionedVector Omega =rotating ? gravitationalProperties->lookup("Omega") : dimensionedVector("Omega", -dimTime, vector(0,0,0));
  dimensionedScalar magg = mag(g);
  dimensionedVector gHat = g/magg;
  
  return result_readGravitationalAcceleration( g, Omega, magg, gHat );
}


//---------------------------------------------------------------------------
surfaceScalarFieldHolder createPhi( const TimeHolder& runTime,
                                    const fvMeshHolder& mesh, 
                                    volVectorFieldHolder& hU )
{
  Info<< "Reading/calculating face flux field phi\n" << endl;

  return surfaceScalarFieldHolder( IOobjectHolder( "phi",
                                                   runTime->timeName(),
                                                   mesh,
                                                   IOobject::READ_IF_PRESENT,
                                                   IOobject::AUTO_WRITE ),
                                   linearInterpolate( hU ) & surfaceVectorFieldHolder( mesh->Sf(), Deps( &mesh ) ) );
}

                                
//---------------------------------------------------------------------------
dimensionedVector createFields( const TimeHolder& runTime,
                                const fvMeshHolder& mesh, 
                                volScalarFieldHolder& h,
                                volScalarFieldHolder& h0,
                                volVectorFieldHolder& U,
                                volVectorFieldHolder& hU,
                                volScalarFieldHolder& hTotal,
                                surfaceScalarFieldHolder& phi,
                                dimensionedVector Omega,
                                dimensionedVector gHat )
{
  Info<< "Reading field h\n" << endl;
  h( volScalarFieldHolder( IOobjectHolder( "h",
                                           runTime->timeName(),
                                           mesh,
                                           IOobject::MUST_READ,
                                           IOobject::AUTO_WRITE ),
                           mesh ) );

  Info<< "Reading field h0 if present\n" << endl;
  h0( volScalarFieldHolder( IOobjectHolder( "h0",
                                            runTime->findInstance("polyMesh", "points"),
                                            mesh,
                                            IOobject::READ_IF_PRESENT ),
                            mesh,
                            dimensionedScalar( "h0", dimLength, 0.0 ) ) );

  Info<< "Reading field U\n" << endl;
  U( volVectorFieldHolder( IOobjectHolder( "U",
                                           runTime->timeName(),
                                           mesh,
                                           IOobject::MUST_READ,
                                           IOobject::AUTO_WRITE ),
                           mesh ) );

  Info<< "Creating field hU\n" << endl;
  hU( volVectorFieldHolder( IOobjectHolder( "hU",
                                            runTime->timeName(),
                                            mesh ),
                            h * U,
                            U->boundaryField().types() ) );

  Info<< "Creating field hTotal for post processing\n" << endl;
  hTotal( volScalarFieldHolder( IOobjectHolder( "hTotal",
                                                runTime->timeName(),
                                                mesh,
                                                IOobject::READ_IF_PRESENT,
                                                IOobject::AUTO_WRITE ),
                                h + h0 ) );
  hTotal->write();

  phi( createPhi( runTime, mesh, hU ) );

  Info<< "Creating Coriolis Force" << endl;

  return dimensionedVector( "F", ( ( 2.0 * Omega ) & gHat ) * gHat );
}


//---------------------------------------------------------------------------
void CourantNo( const TimeHolder& runTime, 
                const fvMeshHolder& mesh, 
                const surfaceScalarFieldHolder& phi,
                volScalarFieldHolder& h,
                dimensionedScalar& magg,
                scalar& CoNum,
                scalar& meanCoNum,
                scalar& waveCoNum )
{
  CoNum = 0.0;
  meanCoNum = 0.0;
  waveCoNum = 0.0;

  if (mesh->nInternalFaces())
  {
    smart_tmp< scalarField > sumPhi( fvc::surfaceSum( mag( phi() ))().internalField() / h->internalField() );

    CoNum = 0.5 * gMax( sumPhi() / mesh->V().field() ) * runTime->deltaTValue();

    meanCoNum = 0.5 * ( gSum( sumPhi() ) / gSum( mesh->V().field() ) ) * runTime->deltaTValue();

    // Gravity wave Courant number
    waveCoNum = 0.25 * gMax( fvc::surfaceSum( fvc::interpolate( sqrt( h() ) ) * mesh->magSf() )().internalField() 
                       / mesh->V().field() ) * sqrt( magg ).value() * runTime->deltaTValue();
  }
  Info << "Courant number mean: " << meanCoNum << " max: " << CoNum << endl;

  Info << "Gravity wave Courant number max: " << waveCoNum << endl;

}


//---------------------------------------------------------------------------
int main(int argc, char *argv[])
{
  argList args = setRootCase( argc, argv );
   
  TimeHolder runTime=createTime( Time::controlDictName, args );

  fvMeshHolder mesh = createMesh( runTime );

  IOdictionaryHolder gravitationalProperties; Switch rotating;
  result_readGravitationalAcceleration res = readGravitationalAcceleration( runTime, mesh, gravitationalProperties, rotating );
  dimensionedVector g = res.m_g;
  dimensionedVector Omega = res.m_Omega;
  dimensionedScalar magg = res.m_magg;
  dimensionedVector gHat = res.m_gHat;
  
  volScalarFieldHolder h; volScalarFieldHolder h0;
  volVectorFieldHolder U; volVectorFieldHolder hU;
  volScalarFieldHolder hTotal; surfaceScalarFieldHolder phi;
  
  dimensionedVector F = createFields( runTime, mesh, h, h0, U, hU, hTotal, phi, Omega, gHat );

  pimpleControlHolder pimple( mesh );

  // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

  Info<< "\nStarting time loop\n" << endl;

  while ( runTime->loop() )
  {
    Info<< "\n Time = " << runTime->timeName() << nl << endl;

    scalar CoNum; scalar meanCoNum; scalar waveCoNum;
    CourantNo( runTime, mesh, phi, h, magg, CoNum, meanCoNum, waveCoNum );
    // --- Pressure-velocity PIMPLE corrector loop
    for ( pimple->start(); pimple->loop(); (*pimple)++ )
    {
      surfaceScalarField phiv( "phiv", phi() / fvc::interpolate( h() ) );

      smart_tmp< fvVectorMatrix > hUEqn( fvm::ddt( hU() ) + fvm::div( phiv, hU() ) );

      hUEqn->relax();

      if ( pimple->momentumPredictor() )
      {
        if (rotating)
        {
          solve( hUEqn() + ( F ^ hU() ) == -magg * h() * fvc::grad( h() + h0() ) );
        }
        else
        {
          solve( hUEqn() == -magg * h() * fvc::grad( h() + h0() ) );
        }

        // Constrain the momentum to be in the geometry if 3D geometry
        if ( mesh->nGeometricD() == 3 )
        {
          hU -= ( gHat & hU() ) * gHat;
          hU->correctBoundaryConditions();
        }
      }

      // --- PISO loop
      for ( int corr=0; corr < pimple->nCorr(); corr++ )
      {
        smart_tmp< volScalarField > rAU( 1.0/ hUEqn->A() );
        smart_tmp< surfaceScalarField > ghrAUf( magg * fvc::interpolate( h() * rAU() ) );

        smart_tmp< surfaceScalarField > phih0( ghrAUf() * mesh->magSf() * fvc::snGrad( h0() ) );

        if (rotating)
        {
          hU = rAU() * ( hUEqn->H() - ( F ^ hU() ) );
        }
        else
        {
          hU = rAU() * hUEqn->H();
        }

        phi = ( fvc::interpolate( hU() ) & mesh->Sf() ) + fvc::ddtPhiCorr( rAU() , h(), hU(), phi() ) - phih0();

        for (int nonOrth=0; nonOrth<=pimple->nNonOrthCorr(); nonOrth++)
        {
          smart_tmp< fvScalarMatrix > hEqn( fvm::ddt( h() ) + fvc::div( phi() ) - fvm::laplacian( ghrAUf(), h() ) );

          hEqn->solve( mesh->solver( h->select( pimple->finalInnerIter( corr, nonOrth ) ) ) );

          if ( nonOrth == pimple->nNonOrthCorr() )
          {
            phi += hEqn->flux();
          }
        }

        hU -= rAU() * h() * magg * fvc::grad( h() + h0() );

        // Constrain the momentum to be in the geometry if 3D geometry
        if ( mesh->nGeometricD() == 3 )
        {
          hU -= ( gHat & hU() ) * gHat;
        }

        hU->correctBoundaryConditions();
      }
    }

    U == hU() / h();
    hTotal == h() + h0();

    runTime->write();

    Info << "ExecutionTime = " << runTime->elapsedCpuTime() << " s"
         << "  ClockTime = " << runTime->elapsedClockTime() << " s"
         << nl << endl;
  }

  Info<< "End\n" << endl;

  return 0;
}


// ************************************************************************* //
