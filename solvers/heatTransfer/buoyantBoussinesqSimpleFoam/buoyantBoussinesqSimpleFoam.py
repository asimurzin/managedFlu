#!/usr/bin/env python

#---------------------------------------------------------------------------
## pythonFlu - Python wrapping for OpenFOAM C++ API
## Copyright (C) 2010- Alexey Petrov
## Copyright (C) 2009-2010 Pebble Bed Modular Reactor (Pty) Limited (PBMR)
## 
## This program is free software: you can redistribute it and/or modify
## it under the terms of the GNU General Public License as published by
## the Free Software Foundation, either version 3 of the License, or
## (at your option) any later version.
##
## This program is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
## 
## You should have received a copy of the GNU General Public License
## along with this program.  If not, see <http://www.gnu.org/licenses/>.
## 
## See http://sourceforge.net/projects/pythonflu
##
## Author : Alexey PETROV
##


#---------------------------------------------------------------------------
from Foam import man


#---------------------------------------------------------------------------
def readGravitationalAcceleration( runTime, mesh ):
    from Foam.OpenFOAM import ext_Info, nl
    ext_Info() << "\nReading g" << nl
    
    from Foam.OpenFOAM import uniformDimensionedVectorField
    from Foam.OpenFOAM import word, IOobject,fileName
    g= uniformDimensionedVectorField( IOobject( word("g"),
                                                fileName( runTime.constant() ),
                                                mesh,
                                                IOobject.MUST_READ,
                                                IOobject.NO_WRITE ) )
    return g


#---------------------------------------------------------------------------
def readTransportProperties( U, phi ):
  
  laminarTransport = man.singlePhaseTransportModel( U, phi )

  from Foam.OpenFOAM import word, dimensionedScalar
  # Thermal expansion coefficient [1/K]
  beta = dimensionedScalar( laminarTransport.lookup( word( "beta" ) ) )

  # Reference temperature [K]
  TRef = dimensionedScalar( laminarTransport.lookup( word( "TRef" ) ) )

  # Laminar Prandtl number
  Pr = dimensionedScalar( laminarTransport.lookup( word( "Pr" ) ) )

  # Turbulent Prandtl number
  Prt = dimensionedScalar( laminarTransport.lookup( word( "Prt" ) ) )
  
  return laminarTransport, beta, TRef, Pr, Prt


#---------------------------------------------------------------------------
def createFields( runTime, mesh, g ):
  
  from Foam.OpenFOAM import ext_Info, nl
  ext_Info() << "Reading thermophysical properties\n" << nl
  
  ext_Info() << "Reading field T\n" << nl
  from Foam.OpenFOAM import IOobject, word, fileName
  T = man.volScalarField( man.IOobject( word( "T" ),
                                        fileName( runTime.timeName() ),
                                        mesh,
                                        IOobject.MUST_READ,
                                        IOobject.AUTO_WRITE ), mesh )

  ext_Info() << "Reading field p_rgh\n" << nl
  p_rgh = man.volScalarField( man.IOobject( word( "p_rgh" ),
                                            fileName( runTime.timeName() ),
                                            mesh,
                                            IOobject.MUST_READ,
                                            IOobject.AUTO_WRITE ),
                                mesh )
  
  ext_Info() << "Reading field U\n" << nl
  U = man.volVectorField( man.IOobject( word( "U" ),
                                        fileName( runTime.timeName() ),
                                        mesh,
                                        IOobject.MUST_READ,
                                        IOobject.AUTO_WRITE ), mesh )
  phi = man.createPhi( runTime, mesh, U )
    
  laminarTransport, beta, TRef, Pr, Prt = readTransportProperties( U, phi )
  
  ext_Info()<< "Creating turbulence model\n" << nl
  turbulence = man.incompressible.RASModel.New(U, phi, laminarTransport)

  # Kinematic density for buoyancy force
  field = 1.0 - beta * ( T() - TRef )
  rhok = man.volScalarField( man.IOobject( word( "rhok" ),
                                           fileName( runTime.timeName() ),
                                           mesh ), man.volScalarField( field, T ) )
  
  # kinematic turbulent thermal thermal conductivity m2/s
  ext_Info() << "Reading field kappat\n" << nl
  kappat = man.volScalarField( man.IOobject( word( "kappat" ),
                                             fileName( runTime.timeName() ),
                                             mesh,
                                             IOobject.MUST_READ,
                                             IOobject.AUTO_WRITE ), mesh )

  ext_Info() << "Calculating field g.h\n" << nl
  field = g & mesh.C()
  gh = man.volScalarField( word( "gh" ), man.volScalarField( field, mesh ) )
  field = g & mesh.Cf()
  ghf = man.surfaceScalarField( word( "ghf" ), man.surfaceScalarField( field, mesh ) )

  p = man.volScalarField( man.IOobject( word( "p" ),
                                        fileName( runTime.timeName() ),
                                        mesh,
                                        IOobject.NO_READ,
                                        IOobject.AUTO_WRITE ), p_rgh + rhok * gh )

  pRefCell = 0
  pRefValue = 0.0

  from Foam.finiteVolume import setRefCell
  pRefCell, pRefValue = setRefCell( p, p_rgh, mesh.solutionDict().subDict( word( "SIMPLE" ) ), pRefCell, pRefValue )

  from Foam.finiteVolume import getRefCellValue
  from Foam.OpenFOAM import dimensionedScalar
  if p_rgh.needReference():
    p().ext_assign( p() + dimensionedScalar( word( "p" ),p.dimensions(), pRefValue - getRefCellValue( p, pRefCell ) ) )
    pass
  
  return T, p_rgh, U, phi, laminarTransport, turbulence, rhok, kappat, gh, ghf, p, pRefCell, pRefValue, beta, TRef, Pr, Prt


#---------------------------------------------------------------------------
def fun_UEqn( mesh, simple, U, phi, turbulence, p, rhok, p_rgh, ghf ):

  UEqn = man.fvm.div(phi, U) + man.fvVectorMatrix( turbulence.divDevReff( U() ), man.Deps( turbulence, U ) ) 

  UEqn().relax();

  if  simple.momentumPredictor():
    from Foam.finiteVolume import solve
    solve( UEqn == man.fvc.reconstruct( ( - ghf * man.fvc.snGrad( rhok ) - man.fvc.snGrad( p_rgh ) ) * man.surfaceScalarField( mesh.magSf(), mesh ) ) )
    pass
  return UEqn


#---------------------------------------------------------------------------
def fun_TEqn( phi, turbulence, kappat, T, rhok, beta, TRef, Prt, Pr ):
  
  kappat().ext_assign( turbulence.ext_nut() / Prt )
  
  kappat.correctBoundaryConditions()
  
  from Foam.finiteVolume import volScalarField 
  from Foam.OpenFOAM import word
  kappaEff = volScalarField ( word( "kappaEff" ) , turbulence.ext_nu() / Pr  + kappat() )
  from Foam import fvm, fvc
  TEqn = fvm.div( phi, T ) - fvm.Sp(fvc.div( phi ), T ) - fvm.laplacian( kappaEff, T ) 

  TEqn.relax()
  TEqn.solve()

  rhok().ext_assign( 1.0 - beta * ( T() - TRef ) )
  pass


#---------------------------------------------------------------------------
def fun_pEqn( mesh, runTime, simple, p, rhok, U, phi, turbulence, gh, ghf, p_rgh, UEqn, pRefCell, pRefValue, cumulativeContErr ):
  
  from Foam.finiteVolume import volScalarField 
  from Foam.OpenFOAM import word
  rAU = volScalarField( word( "rAU" ), 1.0 / UEqn.A() )
  
  from Foam.finiteVolume import surfaceScalarField
  from Foam import fvc
  rAUf =surfaceScalarField( word( "(1|A(U))" ), fvc.interpolate( rAU ) )

  U().ext_assign( rAU * UEqn.H() )

  phi().ext_assign( fvc.interpolate( U ) & mesh.Sf() )
  from Foam.finiteVolume import adjustPhi
  adjustPhi( phi, U, p_rgh );

  buoyancyPhi = rAUf * ghf() * fvc.snGrad( rhok ) * mesh.magSf()
  phi().ext_assign( phi() - buoyancyPhi )

  from Foam import fvm
  for nonOrth in range( simple.nNonOrthCorr() + 1 ):
    p_rghEqn = fvm.laplacian( rAUf, p_rgh ) == fvc.div( phi )
    from Foam.finiteVolume import getRefCellValue
    p_rghEqn.setReference( pRefCell, getRefCellValue( p_rgh, pRefCell ) )
    
    p_rghEqn.solve()

    if nonOrth == simple.nNonOrthCorr():
      # Calculate the conservative fluxes
      phi().ext_assign( phi() - p_rghEqn.flux() )
      
      # Explicitly relax pressure for momentum corrector
      p_rgh.relax()

      # Correct the momentum source with the pressure gradient flux
      # calculated from the relaxed pressure
      U().ext_assign( U() - rAU * fvc.reconstruct( ( buoyancyPhi + p_rghEqn.flux() ) / rAUf ) )
      U.correctBoundaryConditions()
      pass
    pass

  from Foam.finiteVolume.cfdTools.general.include import ContinuityErrs
  cumulativeContErr = ContinuityErrs( phi, runTime, mesh, cumulativeContErr )

  p.ext_assign( p_rgh + rhok * gh )

  if p_rgh.needReference():
    from Foam.OpenFOAM import dimensionedScalar, word
    p().ext_assign( p() + dimensionedScalar( word( "p" ), p.dimensions(), pRefValue - getRefCellValue( p, pRefCell ) ) )
    p_rgh.ext_assign( p - rhok * gh )
    pass
  
  return cumulativeContErr



#---------------------------------------------------------------------------
def main_standalone( argc, argv ):
  
  from Foam.OpenFOAM.include import setRootCase
  args = setRootCase( argc, argv )
  
  runTime=man.createTime( args )
    
  mesh = man.createMesh( runTime )
    
  g = readGravitationalAcceleration( runTime, mesh );

  T, p_rgh, U, phi, laminarTransport, turbulence, rhok, \
     kappat, gh, ghf, p, pRefCell, pRefValue, beta, TRef, Pr, Prt  = createFields( runTime, mesh, g )
                                                        
  from Foam.finiteVolume.cfdTools.general.include import initContinuityErrs
  cumulativeContErr = initContinuityErrs()

  simple = man.simpleControl( mesh )


  # * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * #

  from Foam.OpenFOAM import ext_Info, nl
  ext_Info() << "\nStarting time loop\n" << nl

  while simple.loop():
   
    ext_Info() << "Time = " << runTime.timeName() << nl << nl

    p_rgh.storePrevIter()

    # Pressure-velocity SIMPLE corrector
    UEqn = fun_UEqn( mesh, simple, U, phi, turbulence, p, rhok, p_rgh, ghf )
    fun_TEqn( phi, turbulence, kappat, T, rhok, beta, TRef, Prt, Pr )

    cumulativeContErr = fun_pEqn( mesh, runTime, simple, p, rhok, U, phi, turbulence, gh, ghf, p_rgh, UEqn, pRefCell, pRefValue, cumulativeContErr )
    
    turbulence.correct()
    runTime.write()
    
    ext_Info() << "ExecutionTime = " << runTime.elapsedCpuTime() << " s" \
               << "  ClockTime = " << runTime.elapsedClockTime() << " s" \
               << nl << nl
    pass
  pass

  ext_Info() << "End\n" << nl

  import os
  return os.EX_OK


#---------------------------------------------------------------------------
from Foam import FOAM_REF_VERSION
if FOAM_REF_VERSION( ">=", "020000" ):
   if __name__ == "__main__" :
      import sys, os
      argv = sys.argv
      os._exit( main_standalone( len( argv ), argv ) )
      pass
   pass
else:
   from Foam.OpenFOAM import ext_Info
   ext_Info()<< "\nTo use this solver, It is necessary to SWIG OpenFoam2.0.0 \n "     
   pass

