
//---------------------------------------------------------------------------
void createFluidMeshes( const TimeHolder& runTime, const regionProperties& rp, TList<fvMeshHolder>::list& fluidRegions )
{
  for ( label i=0; i<rp.fluidRegionNames().size(); i++)
  {
    Info<< "Create fluid mesh for region " << rp.fluidRegionNames()[i]
        << " for time = " << runTime->timeName() << nl << endl;
    fluidRegions.push_back( fvMeshHolder( IOobjectHolder( rp.fluidRegionNames()[i],
                                                          runTime->timeName(),
                                                          runTime,
                                                          IOobject::MUST_READ ) ) );
  }
}


//---------------------------------------------------------------------------

void createFluidFields( const TimeHolder& runTime,
                        const TList<fvMeshHolder>::list& fluidRegions,
                        TList<basicRhoThermoHolder>::list& thermoFluid,
                        TList<volScalarFieldHolder>::list& rhoFluid,
                        TList<volScalarFieldHolder>::list& KFluid,
                        TList<volVectorFieldHolder>::list& UFluid,
                        TList<surfaceScalarFieldHolder>::list& phiFluid,
                        TList<uniformDimensionedVectorFieldHolder>::list& gFluid,
                        TList<compressible::turbulenceModelHolder>::list& turbulence,
                        TList<volScalarFieldHolder>::list& p_rghFluid,
                        TList<volScalarFieldHolder>::list& ghFluid,
                        TList<surfaceScalarFieldHolder>::list& ghfFluid,
                        TList<radiation::radiationModelHolder>::list& radiation,
                        TList<volScalarFieldHolder>::list& DpDtFluid,
                        TList<scalar>::list& initialMassFluid )
{
  // Populate fluid field pointer lists
  forAll(fluidRegions, i)
  {
    Info<< "*** Reading fluid mesh thermophysical properties for region "
        << fluidRegions[i]->name() << nl << endl;

    Info<< "    Adding to thermoFluid\n" << endl;
    thermoFluid.push_back( basicRhoThermoHolder::New( fluidRegions[ i ] ) );

    Info<< "    Adding to rhoFluid\n" << endl;
    rhoFluid.push_back( volScalarFieldHolder( IOobjectHolder( "rho",
                                                              runTime->timeName(),
                                                              fluidRegions[ i ],
                                                              IOobject::NO_READ,
                                                              IOobject::AUTO_WRITE ),
                                              volScalarFieldHolder( thermoFluid[ i ]->rho(), Deps( &thermoFluid[ i ] ) ) ) );

    Info<< "    Adding to KFluid\n" << endl;
    KFluid.push_back( volScalarFieldHolder( IOobjectHolder( "K",
                                                            runTime->timeName(),
                                                            fluidRegions[ i ],
                                                            IOobject::NO_READ,
                                                            IOobject::NO_WRITE ),
                                            volScalarFieldHolder( thermoFluid[ i ]->Cp() * thermoFluid[ i ]->alpha(), Deps( &thermoFluid[ i ] ) ) ) );

    Info<< "    Adding to UFluid\n" << endl;
    UFluid.push_back( volVectorFieldHolder( IOobjectHolder( "U",
                                                            runTime->timeName(),
                                                            fluidRegions[ i ],
                                                            IOobject::MUST_READ,
                                                            IOobject::AUTO_WRITE ),
                                            fluidRegions[ i ] ) );

    Info<< "    Adding to phiFluid\n" << endl;
    phiFluid.push_back( surfaceScalarFieldHolder( IOobjectHolder( "phi",
                                                                  runTime->timeName(),
                                                                  fluidRegions[ i ],
                                                                  IOobject::READ_IF_PRESENT,
                                                                  IOobject::AUTO_WRITE ),
                                                  linearInterpolate( rhoFluid[ i ] * UFluid[ i ] ) & 
                                                  surfaceVectorFieldHolder( fluidRegions[ i ]->Sf(), Deps( &fluidRegions[ i ] ) ) ) );

    Info<< "    Adding to gFluid\n" << endl;
    gFluid.push_back( uniformDimensionedVectorFieldHolder( IOobjectHolder( "g",
                                                                           runTime->constant(),
                                                                           fluidRegions[ i ],
                                                                           IOobject::MUST_READ,
                                                                           IOobject::NO_WRITE ) ) );
    
 
    Info<< "    Adding to turbulence\n" << endl;
    turbulence.push_back( compressible::turbulenceModelHolder::New( rhoFluid[i], UFluid[i], phiFluid[i], thermoFluid[i] ) );

    Info<< "    Adding to ghFluid\n" << endl;
    ghFluid.push_back( volScalarFieldHolder( "gh",  
                                             gFluid[ i ] & volVectorFieldHolder( fluidRegions[ i ]->C(), Deps( &fluidRegions[ i ] ) ) ) );

    Info<< "    Adding to ghfFluid\n" << endl;
    ghfFluid.push_back( surfaceScalarFieldHolder( "ghf", 
                                                  gFluid[ i ] & surfaceVectorFieldHolder( fluidRegions[ i ]->Cf(), Deps( &fluidRegions[ i ] ) ) ) );

    p_rghFluid.push_back( volScalarFieldHolder( IOobjectHolder( "p_rgh",
                                                                runTime->timeName(),
                                                                fluidRegions[ i ],
                                                                IOobject::MUST_READ,
                                                                IOobject::AUTO_WRITE ),
                                                fluidRegions[ i ] ) );

    // Force p_rgh to be consistent with p
    p_rghFluid[ i ] = volScalarFieldHolder( thermoFluid[ i ]->p(), Deps( &thermoFluid[ i ] ) ) - rhoFluid[ i ]*ghFluid[ i ];
    
    radiation.push_back( radiation::radiationModelHolder::New( volScalarFieldHolder( thermoFluid[ i ]->T(), Deps( &thermoFluid[ i ] ) ) ) );

    initialMassFluid.push_back( fvc::domainIntegrate( rhoFluid[ i ]() ).value() );
    Info << "    Adding to DpDtFluid\n" << endl;
    DpDtFluid.push_back( volScalarFieldHolder( "DpDt",
                                               fvc::DDt( surfaceScalarFieldHolder( "phiU",
                                                                                   phiFluid[ i ] / fvc::interpolate(rhoFluid[ i ]) ),  
                                                         volScalarFieldHolder( thermoFluid[ i ]->p(), Deps( &thermoFluid[ i ] ) ) ) ) );
  }
}


//---------------------------------------------------------------------------
TList<scalar>::list initContinuityErrs( const TList<fvMeshHolder>::list& fluidRegions )
{
  return TList<scalar>::list(fluidRegions.size(), 0.0);
}


//---------------------------------------------------------------------------

scalar compressibleCourantNo( const fvMeshHolder& mesh,
                                          const TimeHolder& runTime,
                                          const volScalarFieldHolder& rho,
                                          const surfaceScalarFieldHolder& phi )
{
    smart_tmp< scalarField > sumPhi( fvc::surfaceSum(mag( phi() ) )().internalField() / rho->internalField() );

    scalar CoNum = 0.5 * gMax( sumPhi() / mesh->V().field() ) * runTime->deltaTValue();

    scalar meanCoNum =
        0.5 * ( gSum( sumPhi() ) / gSum( mesh->V().field() ) ) * runTime->deltaTValue();

    Info<< "Region: " << mesh->name() << " Courant Number mean: " << meanCoNum
        << " max: " << CoNum << endl;

    return CoNum;
}


//---------------------------------------------------------------------------
scalar compressibleMultiRegionCourantNo( const TimeHolder& runTime,
                                         const TList<fvMeshHolder>::list& fluidRegions,
                                         const TList<volScalarFieldHolder>::list& rhoFluid,
                                         const TList<surfaceScalarFieldHolder>::list& phiFluid )
{
  scalar CoNum = -GREAT;
  forAll(fluidRegions, regionI)
  {
    CoNum = max( compressibleCourantNo( fluidRegions[regionI], runTime, rhoFluid[regionI], phiFluid[regionI] ),
                 CoNum );
  }
  return CoNum;
}

    
//---------------------------------------------------------------------------
dimensionedScalar setRegionFluidFields( size_t& i, TList<fvMeshHolder>::list& fluidRegions, fvMeshHolder& mesh,
                                        TList<basicRhoThermoHolder>::list& thermoFluid, basicRhoThermoHolder& thermo,
                                        TList<volScalarFieldHolder>::list& rhoFluid, volScalarFieldHolder& rho, 
                                        TList<volScalarFieldHolder>::list& KFluid, volScalarFieldHolder& K,
                                        TList<volVectorFieldHolder>::list& UFluid, volVectorFieldHolder& U,
                                        TList<surfaceScalarFieldHolder>::list& phiFluid, surfaceScalarFieldHolder& phi,
                                        TList<compressible::turbulenceModelHolder>::list& turbulence, compressible::turbulenceModelHolder& turb,
                                        TList<volScalarFieldHolder>::list& p_rghFluid, volScalarFieldHolder& p_rgh,
                                        TList<volScalarFieldHolder>::list& ghFluid, volScalarFieldHolder& gh,
                                        TList<surfaceScalarFieldHolder>::list& ghfFluid, surfaceScalarFieldHolder& ghf,
                                        TList<radiation::radiationModelHolder>::list& radiation, radiation::radiationModelHolder& rad,
                                        TList<volScalarFieldHolder>::list& DpDtFluid, volScalarFieldHolder& DpDt,
                                        TList<scalar>::list& initialMassFluid,
                                        volScalarFieldHolder& p, volScalarFieldHolder& psi,
                                        volScalarFieldHolder& h )
{
  mesh( fluidRegions[i] );
  thermo( thermoFluid[i] );
  rho( rhoFluid[i] );
  K( KFluid[i] );
  U( UFluid[i] );
  phi( phiFluid[i] );
  turb( turbulence[i] );
  DpDt( DpDtFluid[i] );
  p( volScalarFieldHolder( thermo->p(), Deps( &thermo ) ) );
  psi( volScalarFieldHolder( thermo->psi(), Deps( &thermo ) ) );
  h( volScalarFieldHolder( thermo->h(), Deps( &thermo ) ) );
  p_rgh( p_rghFluid[i] );
  gh( ghFluid[i] );
  ghf( ghfFluid[i] );
  rad( radiation[i] );
  dimensionedScalar initialMass( "initialMass", dimMass, initialMassFluid[i] );
  
  return initialMass;
}


//---------------------------------------------------------------------------
void storeOldFluidFields( volScalarFieldHolder& p_rgh, volScalarFieldHolder& rho )
{ 
  p_rgh->storePrevIter();
  rho->storePrevIter();
}


//---------------------------------------------------------------------------
void readFluidMultiRegionPIMPLEControls( const fvMeshHolder& mesh, dictionary& pimple,
                                         int& nCorr, int& nNonOrthCorr, bool& momentumPredictor )
{
  pimple = mesh->solutionDict().subDict("PIMPLE");

  nCorr = pimple.lookupOrDefault<int>("nCorrectors", 1);
  nNonOrthCorr = pimple.lookupOrDefault<int>("nNonOrthogonalCorrectors", 0);
  momentumPredictor = pimple.lookupOrDefault("momentumPredictor", true);
}


//---------------------------------------------------------------------------
fvVectorMatrixHolder fun_Ueqn( const bool& momentumPredictor,
                              const bool& finalIter,
                              const fvMeshHolder& mesh,
                              const volScalarFieldHolder& rho,
                              volVectorFieldHolder& U, 
                              const surfaceScalarFieldHolder& phi, 
                              const compressible::turbulenceModelHolder& turb,
                              const surfaceScalarFieldHolder& ghf,
                              const volScalarFieldHolder& p_rgh )
{
  // Solve the Momentum equation
  fvVectorMatrixHolder UEqn( fvm::ddt(rho, U) + fvm::div(phi, U) + fvVectorMatrixHolder( turb->divDevRhoReff( U() ), Deps( &turb, &U ) ) );

  UEqn->relax();

  if (momentumPredictor)
  {
    solve( UEqn == fvc::reconstruct( ( - ghf * fvc::snGrad( rho ) - fvc::snGrad( p_rgh ) ) * surfaceScalarFieldHolder( mesh->magSf(), Deps( &mesh ) ) ),
           mesh->solver( U->select( finalIter ) ) );
  }
  
  return UEqn;
}

//---------------------------------------------------------------------------
void fun_hEqn( const bool& finalIter,
               const fvMeshHolder& mesh,
               const basicRhoThermoHolder& thermo,
               const volScalarFieldHolder& rho,
               const volScalarFieldHolder& p,
               const volScalarFieldHolder& h,
               const volScalarFieldHolder& DpDt,
               const surfaceScalarFieldHolder& phi,
               const radiation::radiationModelHolder& rad, 
               const compressible::turbulenceModelHolder& turb )
{
  smart_tmp< fvScalarMatrix > hEqn( fvm::ddt( rho(), h() ) + fvm::div( phi(), h() ) - fvm::laplacian( turb->alphaEff(), h() )
                                    == DpDt() + rad->Sh( *thermo ) );

  hEqn->relax();
  hEqn->solve( mesh->solver( h->select( finalIter ) ) );

  thermo->correct();

  rad->correct();

  Info<< "Min/max T:" << min( thermo->T() ).value() << ' '
        << max( thermo->T() ).value() << endl;
}


//---------------------------------------------------------------------------
void compressibleContinuityErrors( size_t& i, const fvMeshHolder& mesh,
                                   const basicRhoThermoHolder& thermo,
                                   volScalarFieldHolder& rho,
                                   TList<scalar>::list& cumulativeContErr )
{
  dimensionedScalar totalMass = fvc::domainIntegrate( rho() );

  scalar sumLocalContErr =( fvc::domainIntegrate( mag( rho() - thermo->rho() ) ) / totalMass ).value();
  
  scalar globalContErr = ( fvc::domainIntegrate( rho() - thermo->rho() ) / totalMass ).value();

  cumulativeContErr[i] += globalContErr;

  Info << "time step continuity errors (" << mesh->name() << ")"
       << ": sum local = " << sumLocalContErr
       << ", global = " << globalContErr
       << ", cumulative = " << cumulativeContErr[i]
       << endl;
}


//---------------------------------------------------------------------------
void fun_pEqn( size_t& i,
               fvMeshHolder& mesh,
               basicRhoThermoHolder& thermo,
               TList<basicRhoThermoHolder>::list& thermoFluid,
               volScalarFieldHolder& rho,
               volScalarFieldHolder& p,
               volScalarFieldHolder& h,
               volScalarFieldHolder& psi,
               volVectorFieldHolder& U,
               surfaceScalarFieldHolder& phi,
               compressible::turbulenceModelHolder& turb,
               volScalarFieldHolder& gh,
               surfaceScalarFieldHolder& ghf,
               volScalarFieldHolder& p_rgh,
               fvVectorMatrixHolder& UEqn,
               volScalarFieldHolder& DpDt,
               volScalarFieldHolder& K,
               int& nNonOrthCorr, int& oCorr, int& nOuterCorr,  int& corr, int& nCorr,
               TList<scalar>::list& cumulativeContErr,
               dimensionedScalar& initialMass )
{
  bool closedVolume = p_rgh->needReference();
  dimensionedScalar compressibility = fvc::domainIntegrate( psi() );
  bool compressible = (compressibility.value() > SMALL);

  rho = thermo->rho();

  smart_tmp< volScalarField > rAU( 1.0 / UEqn->A() );
  surfaceScalarField rhorAUf( "(rho*(1|A(U)))", fvc::interpolate( rho() * rAU() ) );

  U = rAU() * UEqn->H();

  smart_tmp< surfaceScalarField > phiU( fvc::interpolate( rho() ) * ( ( fvc::interpolate( U() ) & mesh->Sf() ) + 
                                                                        fvc::ddtPhiCorr( rAU(), rho(), U(), phi () ) ) );

  phi = phiU() - rhorAUf * ghf() * fvc::snGrad( rho() ) * mesh->magSf();

  {
    smart_tmp< fvScalarMatrix > p_rghDDtEqn( fvc::ddt( rho() ) + psi() *correction( fvm::ddt( p_rgh() ) ) + fvc::div( phi() ) );

    // Thermodynamic density needs to be updated by psi*d(p) after the
    // pressure solution - done in 2 parts. Part 1:
    thermo->rho() -= psi() * p_rgh();

    for (int nonOrth=0; nonOrth<=nNonOrthCorr; nonOrth++)
    {
      smart_tmp< fvScalarMatrix > p_rghEqn( p_rghDDtEqn() - fvm::laplacian( rhorAUf, p_rgh() ) );

      p_rghEqn->solve( mesh->solver( p_rgh->select( ( oCorr == nOuterCorr-1 && corr == nCorr-1 && nonOrth == nNonOrthCorr ) ) ) );

      if (nonOrth == nNonOrthCorr)
      {
        phi += p_rghEqn->flux();
      }
    }

    // Second part of thermodynamic density update
    thermo->rho() += psi() * p_rgh();
  } 

  // Correct velocity field
  U += rAU() * fvc::reconstruct( ( phi() - phiU() ) / rhorAUf );
  U->correctBoundaryConditions();

  p = p_rgh() + rho() * gh();

  // Update pressure substantive derivative
  DpDt = fvc::DDt( surfaceScalarField( "phiU", phi() / fvc::interpolate( rho() ) ), p() );

  // Solve continuity
  rhoEqn( rho, phi );

  // Update continuity errors
  compressibleContinuityErrors( i, mesh, thermo, rho, cumulativeContErr );  

  // For closed-volume cases adjust the pressure and density levels
  // to obey overall mass continuity
  if (closedVolume && compressible )
  {
    p += ( initialMass - fvc::domainIntegrate( thermo->rho() ) ) / compressibility;
    rho = thermo->rho();
    p_rgh = p() - rho()*gh();
  }

  // Update thermal conductivity
  K = thermoFluid[i]->Cp() * turb->alphaEff();

}


//---------------------------------------------------------------------------
void solveFluid( size_t& i, fvMeshHolder& mesh, basicRhoThermoHolder& thermo,  
                 TList<basicRhoThermoHolder>::list& thermoFluid, volScalarFieldHolder& rho, 
                 volScalarFieldHolder& K, volVectorFieldHolder& U, surfaceScalarFieldHolder& phi,
                 compressible::turbulenceModelHolder& turb, volScalarFieldHolder& p_rgh, volScalarFieldHolder& gh,
                 surfaceScalarFieldHolder& ghf, radiation::radiationModelHolder& rad, volScalarFieldHolder& DpDt,
                 volScalarFieldHolder& p, volScalarFieldHolder& psi, volScalarFieldHolder& h, bool& finalIter, int& oCorr,
                 int& nCorr, int& nNonOrthCorr, int& nOuterCorr,  bool& momentumPredictor, TList<scalar>::list& cumulativeContErr, dimensionedScalar& initialMass  )
{
  if (finalIter)
  {
    (*mesh).data::add("finalIteration", true);
  }
  
  if (oCorr == 0)
  {
    rhoEqn( rho, phi );
  }
  
  
  fvVectorMatrixHolder UEqn = fun_Ueqn( momentumPredictor, finalIter, mesh, rho, U, phi, turb, ghf, p_rgh );
  
  fun_hEqn( finalIter, mesh, thermo, rho, p, h, DpDt, phi, rad, turb );

  // --- PISO loop
  for (int corr=0; corr<nCorr; corr++)
  {
    fun_pEqn( i, mesh, thermo, thermoFluid, rho, p, h, psi, U, phi, turb, gh, ghf, p_rgh, 
              UEqn, DpDt, K, nNonOrthCorr, oCorr, nOuterCorr,  corr, nCorr, cumulativeContErr, initialMass );
  }

  turb->correct();

  rho = thermo->rho();
  if (finalIter)
  {
    (*mesh).data::remove("finalIteration");
  }
}


//---------------------------------------------------------------------------
