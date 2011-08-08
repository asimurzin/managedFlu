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
    icoFoam

Description
    Transient solver for incompressible, laminar flow of Newtonian fluids.

\*---------------------------------------------------------------------------*/

#include "fvCFD.H"
#include "Allheaders.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char *argv[])
{
    Foam::argList args(argc, argv);
    if (!args.checkRootCase())
    {
        Foam::FatalError.exit();
    }

    Info<< "Create time\n" << endl;
      
    TimeHolder runTime( Foam::Time::controlDictName, args );
    
    Info << "Create mesh for time = "  << runTime->timeName() << Foam::nl << Foam::endl;
    
    fvMeshHolder mesh( Foam::IOobjectHolder( Foam::fvMesh::defaultRegion,
                                                   runTime->timeName(),
                                                   runTime,
                                                   Foam::IOobject::MUST_READ ) );
    
    Info<< "Reading transportProperties\n" << endl;

    IOdictionaryHolder transportProperties( IOobjectHolder( "transportProperties",
                                                            runTime->constant(),
                                                            mesh,
                                                            IOobject::MUST_READ_IF_MODIFIED,
                                                            IOobject::NO_WRITE ) );

    dimensionedScalar nu( transportProperties->lookup("nu") );

    Info << "Reading field p\n" << endl;
  
    volScalarFieldHolder p( IOobjectHolder( "p",
                                             runTime->timeName(),
                                             mesh,
                                             IOobject::MUST_READ,
                                             IOobject::AUTO_WRITE ), mesh );

    Info<< "Reading field U\n" << endl;
    volVectorFieldHolder U( IOobjectHolder( "U",
                                            runTime->timeName(),
                                            mesh,
                                            IOobject::MUST_READ,
                                            IOobject::AUTO_WRITE ), mesh );

    
    Info<< "Reading/calculating face flux field phi\n" << endl;

    surfaceScalarFieldHolder phi( IOobjectHolder( "phi",
                                                  runTime->timeName(),
                                                  mesh,
                                                  IOobject::READ_IF_PRESENT,
                                                  IOobject::AUTO_WRITE ),
                                  linearInterpolate(U) & mesh->Sf() );
    label pRefCell = 0;
    scalar pRefValue = 0.0;
    setRefCell(p, mesh->solutionDict().subDict("PISO"), pRefCell, pRefValue);


    #include "initContinuityErrs.H"

    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    Info<< "\nStarting time loop\n" << endl;

    while (runTime->loop())
    {

        Info<< "Time = " << runTime->timeName() << nl << endl;
        
        const dictionary& pisoDict = mesh->solutionDict().subDict("PISO");
 
        const int nOuterCorr = pisoDict.lookupOrDefault<int>("nOuterCorrectors", 1);
        const int nCorr = pisoDict.lookupOrDefault<int>("nCorrectors", 1);

        const int nNonOrthCorr = pisoDict.lookupOrDefault<int>("nNonOrthogonalCorrectors", 0);

        const bool momentumPredictor = pisoDict.lookupOrDefault("momentumPredictor", true);

        const bool transonic = pisoDict.lookupOrDefault("transonic", false);
        
        // CourantNo
        scalar CoNum = 0.0;
        scalar meanCoNum = 0.0;
        
        if ( mesh->nInternalFaces() )
        { 
          scalarField sumPhi( fvc::surfaceSum(mag(phi))().internalField() );
          
          CoNum = 0.5 * gMax( sumPhi / mesh->V().field() ) * runTime->deltaTValue();
          meanCoNum = 0.5 * ( gSum( sumPhi ) / gSum( mesh->V().field() ) ) * runTime->deltaTValue();

        }
        // end of CourantNo


        fvVectorMatrixHolder UEqn
        (
            fvm::ddt( U )
          + fvm::div( phi, U )
          - fvm::laplacian( nu, U )
        );

        solve( UEqn == -fvc::grad( p ) );
/*
        // --- PISO loop

        for (int corr=0; corr<nCorr; corr++)
        {
            volScalarField rAU(1.0/UEqn.A());

            U = rAU*UEqn.H();
            phi = (fvc::interpolate(U) & mesh.Sf())
                + fvc::ddtPhiCorr(rAU, U, phi);

            adjustPhi(phi, U, p);

            for (int nonOrth=0; nonOrth<=nNonOrthCorr; nonOrth++)
            {
                fvScalarMatrix pEqn
                (
                    fvm::laplacian(rAU, p) == fvc::div(phi)
                );

                pEqn.setReference(pRefCell, pRefValue);
                pEqn.solve();

                if (nonOrth == nNonOrthCorr)
                {
                    phi -= pEqn.flux();
                }
            }

            #include "continuityErrs.H"

            U -= rAU*fvc::grad(p);
            U.correctBoundaryConditions();
        }
*/
        runTime->write();

        Info<< "ExecutionTime = " << runTime->elapsedCpuTime() << " s"
            << "  ClockTime = " << runTime->elapsedClockTime() << " s"
            << nl << endl;
    }

    Info<< "End\n" << endl;

    return 0;
}


// ************************************************************************* //
