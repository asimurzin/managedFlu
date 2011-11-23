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
    boundaryFoam

Description
    Steady-state solver for incompressible, 1D turbulent flow, typically to
    generate boundary layer conditions at an inlet, for use in a simulation.

    Boundary layer code to calculate the U, k and epsilon distributions.
    Used to create inlet boundary conditions for experimental comparisons
    for which U and k have not been measured.
    Turbulence model is runtime selectable.

\*---------------------------------------------------------------------------*/

#include "fvCFD.H"
#include "wallFvPatch.H"
#include "makeGraph.H"

#include "core.hpp"
#include "OpenFOAM/functions.hpp"
#include "finiteVolume/functions.hpp"

#include "singlePhaseTransportModelHolder.hpp"
#include "turbulenceModels/incompressible/RAS/RASModelHolder.hpp"
#include "simpleControlHolder.hpp"


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
//---------------------------------------------------------------------------
struct result_createFields
{
  dimensionedVector m_Ubar;
  dimensionedVector m_gradP;
  result_createFields( dimensionedVector the_Ubar, dimensionedVector the_gradP )
    : m_Ubar( the_Ubar )
    , m_gradP( the_gradP )
  {}
};


//---------------------------------------------------------------------------
result_createFields createFields( const TimeHolder& runTime, 
                                  const fvMeshHolder& mesh,
                                  volVectorFieldHolder& U,
                                  surfaceScalarFieldHolder& phi,
                                  singlePhaseTransportModelHolder& laminarTransport,
                                  incompressible::RASModelHolder& turbulence,
                                  IOdictionaryHolder& transportProperties,
                                  vector& flowDirection, tensor& flowMask )
{
  Info<< "Reading field U\n" << endl;
  U( volVectorFieldHolder( IOobjectHolder( "U",
                                           runTime->timeName(),
                                           mesh,
                                           IOobject::MUST_READ,
                                           IOobject::AUTO_WRITE ),
                           mesh ) );


  Info<< "Creating face flux\n" << endl;
  phi( surfaceScalarFieldHolder( IOobjectHolder( "phi",
                                                 runTime->timeName(),
                                                 mesh,
                                                 IOobject::NO_READ,
                                                 IOobject::NO_WRITE ),
                                  mesh,
                                  dimensionedScalar( "zero", mesh->Sf().dimensions() * U->dimensions(), 0.0 ) ) );

  laminarTransport = singlePhaseTransportModelHolder( U, phi );

  turbulence = incompressible::RASModelHolder::New(U, phi, laminarTransport);

  transportProperties = IOdictionaryHolder( IOobjectHolder( "transportProperties",
                                                            runTime->constant(),
                                                            mesh,
                                                            IOobject::MUST_READ_IF_MODIFIED,
                                                            IOobject::NO_WRITE ) );

  dimensionedVector Ubar( transportProperties->lookup( "Ubar" ) );

  flowDirection = ( Ubar / mag( Ubar ) ).value();
  flowMask = sqr( flowDirection );

  dimensionedVector gradP( "gradP", dimensionSet(0, 1, -2, 0, 0), vector::zero );
  
  return result_createFields( Ubar, gradP );
}


//---------------------------------------------------------------------------
void interrogateWallPatches( const fvMeshHolder& mesh,
                             label& faceId, label& patchId, 
                             label& nWallFaces, vector& wallNormal,
                             label& cellId,
                             scalarField& y, 
                             const argList& args )
{
  // Search for wall patches faces and store normals

  faceId = -1;
  patchId = -1;
  nWallFaces = 0;
  wallNormal = vector::zero;

  const fvPatchList& patches = mesh->boundary();

  forAll(patches, patchi)
  {
    const fvPatch& currPatch = patches[ patchi ];

    if ( isA<wallFvPatch>( currPatch ) )
    {
      const vectorField nf( currPatch.nf() );
      forAll(nf, facei)
      {
        nWallFaces++;
        if (nWallFaces == 1)
        {
          wallNormal = -nf[ facei ];
          faceId = facei;
          patchId = patchi;
        }
        else if (nWallFaces == 2)
        {
          const vector wallNormal2 = -nf[ facei ];
          //- Check that wall faces are parallel
          if ( mag( wallNormal & wallNormal2 ) > 1.01 || mag( wallNormal & wallNormal2 ) < 0.99 )
          {
            FatalErrorIn(args.executable()) << "wall faces are not parallel for patches "
                                            << patches[ patchId ].name() << " and "
                                            << currPatch.name() << nl  << exit(FatalError);
          }
        }
        else
        {
          FatalErrorIn(args.executable()) << "number of wall faces > 2"
                                          << nl << exit(FatalError);
        }
      }
    }
  }

  if (nWallFaces == 0)
  {
    FatalErrorIn(args.executable()) << "No wall patches identified"
        << exit(FatalError);
  }
  else
  {
    Info<< "Generating wall data for patch: " << patches[ patchId ].name()
        << endl;
  }

  // store local id of near-walll cell to process
  cellId = patches[patchId].faceCells()[ faceId ];

  // create position array for graph generation
  y = wallNormal & ( mesh->C().internalField() - mesh->C().boundaryField()[ patchId ][ faceId ] );

  Info<< "    Height to first cell centre y0 = " << y[ cellId ] << endl;
}


//---------------------------------------------------------------------------
void evaluateNearWall( incompressible::RASModelHolder& turbulence,
                       volVectorFieldHolder& U,
                       scalarField& y,
                       label& faceId, label& patchId, 
                       label& nWallFaces, vector& wallNormal,
                       label& cellId, vector& flowDirection )
                       
{
  // Evaluate near-wall behaviour

  scalar nu = turbulence->nu()().boundaryField()[ patchId ][ faceId ];
  scalar nut = turbulence->nut()().boundaryField()[ patchId ][ faceId ];
  symmTensor R = turbulence->devReff()().boundaryField()[ patchId ][ faceId ];
  scalar epsilon = turbulence->epsilon()()[ cellId ];
  // scalar omega = turbulence->omega()()[cellId];
  scalar k = turbulence->k()()[ cellId] ;
  scalar magUp = mag( U()[ cellId ] - U->boundaryField()[ patchId ][ faceId ]);

  scalar tauw = flowDirection & R & wallNormal;

  scalar uTau = ::sqrt( mag( tauw ) );

  scalar yPlus = uTau * y[ cellId ] / ( nu + ROOTVSMALL );

  scalar uPlus = magUp / ( uTau + ROOTVSMALL );

  scalar nutPlus = nut / nu;

  scalar kPlus = k / ( sqr( uTau ) + ROOTVSMALL );

  scalar epsilonPlus = epsilon * nu / ( pow4( uTau ) + ROOTVSMALL );

  //    scalar omegaPlus = omega*nu/(sqr(uTau) + ROOTVSMALL);

  scalar Rey = magUp * y[ cellId ] / nu;

  Info<< "Rey = " << Rey << ", uTau = " << uTau << ", nut+ = " << nutPlus
      << ", y+ = " << yPlus << ", u+ = " << uPlus
      << ", k+ = " << kPlus << ", epsilon+ = " << epsilonPlus
      << endl;
}


//---------------------------------------------------------------------------
void makeGraphs( TimeHolder& runTime, 
                  fvMeshHolder& mesh,
                  volVectorFieldHolder& U,
                  incompressible::RASModelHolder& turbulence,
                  label& faceId, label& patchId, label& nWallFaces, vector& wallNormal,
                  label& cellId, vector& flowDirection, scalarField& y  )
{
  volSymmTensorField R( IOobject( "R",
                                  runTime->timeName(),
                                  *mesh,
                                  IOobject::NO_READ,
                                  IOobject::AUTO_WRITE ),
                        turbulence->R() );

  runTime->write();

  const word& gFormat = runTime->graphFormat();

  makeGraph( y, flowDirection & U(), "Uf", gFormat );

  makeGraph( y, turbulence->nu(), gFormat );
  makeGraph( y, turbulence->k(), gFormat );
  makeGraph( y, turbulence->epsilon(), gFormat );

  makeGraph( y, flowDirection & R & flowDirection, "Rff", gFormat );
  makeGraph( y, wallNormal & R & wallNormal, "Rww", gFormat );
  makeGraph( y, flowDirection & R & wallNormal, "Rfw", gFormat );

  makeGraph( y, sqrt( mag( R.component( symmTensor::XX ) ) ), "u", gFormat );
  makeGraph( y, sqrt( mag( R.component( symmTensor::YY ) ) ), "v", gFormat );
  makeGraph( y, sqrt( mag( R.component( symmTensor::ZZ ) ) ), "w", gFormat );
  makeGraph( y, R.component( symmTensor::XY ), "uv", gFormat );

  makeGraph( y, mag( fvc::grad( U() ) ), "gammaDot", gFormat );
}


//---------------------------------------------------------------------------
int main(int argc, char *argv[])
{
  argList args = setRootCase( argc, argv );
    
  TimeHolder runTime=createTime( Time::controlDictName, args );
    
  fvMeshHolder mesh = createMesh( runTime );
    
  volVectorFieldHolder U; surfaceScalarFieldHolder phi;
  incompressible::RASModelHolder turbulence;
  singlePhaseTransportModelHolder laminarTransport;
  IOdictionaryHolder transportProperties;
  vector flowDirection; tensor flowMask;
  
  result_createFields result = createFields( runTime, mesh, U, phi, laminarTransport, turbulence, transportProperties, flowDirection, flowMask );
  
  dimensionedVector Ubar = result.m_Ubar;
  dimensionedVector gradP = result.m_gradP;
  
  label faceId; label patchId;
  label nWallFaces; vector wallNormal;
  label cellId; scalarField y;
  interrogateWallPatches( mesh, faceId, patchId, nWallFaces, wallNormal, cellId, y, args );

  // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

  Info<< "\nStarting time loop\n" << endl;

  while (runTime->loop())
  {
    Info<< "Time = " << runTime->timeName() << nl << endl;

    smart_tmp< fvVectorMatrix > divR(turbulence->divDevReff( U() ) );
    divR->source() = flowMask & divR->source();

    smart_tmp< fvVectorMatrix > UEqn( divR() == gradP );

    UEqn->relax();
    UEqn->solve();

    // Correct driving force for a constant volume flow rate
    dimensionedVector UbarStar = flowMask & U->weightedAverage( mesh->V() );

    U += ( Ubar - UbarStar );
    gradP += ( Ubar - UbarStar ) / ( 1.0 / UEqn->A() )().weightedAverage( mesh->V() );
    
    turbulence->correct();

    Info<< "Uncorrected Ubar = " << ( flowDirection & UbarStar.value() )
        << ", pressure gradient = " << ( flowDirection & gradP.value() )
        << endl;

    evaluateNearWall( turbulence, U, y, faceId, patchId, nWallFaces, wallNormal, cellId, flowDirection );
   
    if (runTime->outputTime())
    {
      makeGraphs( runTime, mesh, U, turbulence, faceId, patchId, nWallFaces, wallNormal, cellId, flowDirection, y  );
    }

    Info<< "ExecutionTime = " << runTime->elapsedCpuTime() << " s"
        << "  ClockTime = " << runTime->elapsedClockTime() << " s"
        << nl << endl;
  }

  Info<< "End\n" << endl;

  return 0;
}


// ************************************************************************* //
