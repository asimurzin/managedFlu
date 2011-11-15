//---------------------------------------------------------------------------
void createSolidMeshes( const TimeHolder& runTime, const regionProperties& rp, TList<fvMeshHolder>::list& solidRegions )
{
  for ( label i=0; i<rp.solidRegionNames().size(); i++)
  {
    Info<< "Create solid mesh for region " << rp.solidRegionNames()[i]
        << " for time = " << runTime->timeName() << nl << endl;

    solidRegions.push_back( fvMeshHolder( IOobjectHolder( rp.solidRegionNames()[i],
                                                          runTime->timeName(),
                                                          runTime,
                                                          IOobject::MUST_READ ) ) );
  }
}


//---------------------------------------------------------------------------
void createSolidFields( const TimeHolder& runTime, 
                        const TList<fvMeshHolder>::list& solidRegions, 
                        TList<basicSolidThermoHolder>::list& thermos )
{
  // Populate solid field pointer lists
  forAll(solidRegions, i)
  {
    Info<< "*** Reading solid mesh thermophysical properties for region "
        << solidRegions[ i ]->name() << nl << endl;

    Info<< "    Adding to thermos\n" << endl;
    thermos.push_back( basicSolidThermoHolder::New(solidRegions[ i ] ) );
  }
}


//---------------------------------------------------------------------------
scalar readSolidTimeControls( const TimeHolder& runTime )
{
  return runTime->controlDict().lookupOrDefault<scalar>("maxDi", 10.0);
}


//---------------------------------------------------------------------------
scalar solidRegionDiffNo( const fvMeshHolder& mesh, 
                          const TimeHolder& runTime,
                          const volScalarFieldHolder& Cprho,
                          const volScalarFieldHolder& K )
{
    scalar DiNum = 0.0;
    scalar meanDiNum = 0.0;

    //- Take care: can have fluid domains with 0 cells so do not test for
    //  zero internal faces.
    smart_tmp< surfaceScalarField > KrhoCpbyDelta( mesh->surfaceInterpolation::deltaCoeffs() * fvc::interpolate( K() ) / fvc::interpolate( Cprho() ) );

    DiNum = gMax( KrhoCpbyDelta().internalField() ) * runTime->deltaT().value();

    meanDiNum = ( average( KrhoCpbyDelta() ) ).value() * runTime->deltaT().value();

    Info<< "Region: " << mesh->name() << " Diffusion Number mean: " << meanDiNum
        << " max: " << DiNum << endl;

    return DiNum;
}

//---------------------------------------------------------------------------
void setRegionSolidFields( size_t& i, TList<fvMeshHolder>::list& solidRegions, fvMeshHolder& mesh,
                           TList<basicSolidThermoHolder>::list& thermos, basicSolidThermoHolder& thermo,
                           volScalarFieldHolder& rho,
                           volScalarFieldHolder& cp,
                           volScalarFieldHolder& K,
                           volScalarFieldHolder& T )
{
  mesh( solidRegions[i] );
  thermo( thermos[i] );

  rho( volScalarFieldHolder( thermo->rho(), Deps( & thermo ) ) );

  cp( volScalarFieldHolder( thermo->Cp(), Deps( & thermo ) ) );

  K( volScalarFieldHolder( thermo->K(), Deps( & thermo ) ) );
  // tmp<volSymmTensorField> tK = thermo.directionalK();
    
  // const volSymmTensorField& K = tK();
  T( volScalarFieldHolder( thermo->T(), Deps( & thermo ) ) );
}
                           
                                        

//---------------------------------------------------------------------------
scalar solidRegionDiffusionNo( TimeHolder& runTime, 
                               TList<fvMeshHolder>::list& solidRegions, 
                               TList<basicSolidThermoHolder>::list& thermos )
{
  scalar DiNum = -GREAT;
  
  forAll( solidRegions, i )
  {
    fvMeshHolder mesh; basicSolidThermoHolder thermo;
    volScalarFieldHolder rho; volScalarFieldHolder cp;
    volScalarFieldHolder K; volScalarFieldHolder T;
    setRegionSolidFields( i, solidRegions, mesh, thermos, thermo, rho, cp, K,T );
    
    DiNum = max( solidRegionDiffNo( solidRegions[ i ], runTime, rho * cp, K ),
                 DiNum );
  }
  
  return DiNum;
}


//---------------------------------------------------------------------------
int readSolidMultiRegionPIMPLEControls( fvMeshHolder& mesh )
{
  const dictionary& pimple = mesh->solutionDict().subDict("PIMPLE");

  int nNonOrthCorr = pimple.lookupOrDefault<int>("nNonOrthogonalCorrectors", 0);
  
  return nNonOrthCorr;
}


//---------------------------------------------------------------------------
void solveSolid( fvMeshHolder& mesh, basicSolidThermoHolder& thermo,
                 volScalarFieldHolder& rho,
                 volScalarFieldHolder& cp,
                 volScalarFieldHolder& K,
                 volScalarFieldHolder& T, 
                 int& nNonOrthCorr,
                 bool& finalIter )
{
  if (finalIter)
  {
    mesh->data::add("finalIteration", true);
  }

  {
    for (int nonOrth=0; nonOrth<=nNonOrthCorr; nonOrth++)
    {
      smart_tmp<fvScalarMatrix> TEqn( fvm::ddt( rho * cp, T) - fvm::laplacian( K, T ) );
      TEqn->relax();
      TEqn->solve( mesh->solver( T->select( finalIter ) ) );
    }

    Info<< "Min/max T:" << min( T() ) << ' ' << max( T() ) << endl;
  }

  thermo->correct();

  if (finalIter)
  {
    mesh->data::remove("finalIteration");
  }
}


//---------------------------------------------------------------------------
