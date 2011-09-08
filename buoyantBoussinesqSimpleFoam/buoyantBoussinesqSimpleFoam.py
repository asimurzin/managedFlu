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
  
  from wrappers.transportModels import singlePhaseTransportModelHolder
  laminarTransport = singlePhaseTransportModelHolder( U, phi )

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
  from wrappers.OpenFOAM import IOobjectHolder
  from wrappers.finiteVolume import volScalarFieldHolder
  T = volScalarFieldHolder( IOobjectHolder( word( "T" ),
                                            fileName( runTime.timeName() ),
                                            mesh,
                                            IOobject.MUST_READ,
                                            IOobject.AUTO_WRITE ),
                            mesh )

  ext_Info() << "Reading field p_rgh\n" << nl
  p_rgh = volScalarFieldHolder( IOobjectHolder( word( "p_rgh" ),
                                                fileName( runTime.timeName() ),
                                                mesh,
                                                IOobject.MUST_READ,
                                                IOobject.AUTO_WRITE ),
                                mesh )
  
  ext_Info() << "Reading field U\n" << nl
  from wrappers.finiteVolume import volVectorFieldHolder
  U = volVectorFieldHolder( IOobjectHolder( word( "U" ),
                                            fileName( runTime.timeName() ),
                                            mesh,
                                            IOobject.MUST_READ,
                                            IOobject.AUTO_WRITE ),
                            mesh )
  from wrappers.finiteVolume import createPhi
  phi = createPhi( runTime, mesh, U )
    
  laminarTransport, beta, TRef, Pr, Prt = readTransportProperties( U, phi )
  
  ext_Info()<< "Creating turbulence model\n" << nl
  from wrappers import incompressible
  turbulence = incompressible.RASModelHolder.New(U, phi, laminarTransport)

  # Kinematic density for buoyancy force
  rhok = volScalarFieldHolder( IOobjectHolder( word( "rhok" ),
                                               fileName( runTime.timeName() ),
                                               mesh ),
                               volScalarFieldHolder( 1.0 - beta * ( T() - TRef ), T ) )
  
  # kinematic turbulent thermal thermal conductivity m2/s
  ext_Info() << "Reading field kappat\n" << nl
  kappat = volScalarFieldHolder( IOobjectHolder( word( "kappat" ),
                                                 fileName( runTime.timeName() ),
                                                 mesh,
                                                 IOobject.MUST_READ,
                                                 IOobject.AUTO_WRITE ),
                                 mesh )

  ext_Info() << "Calculating field g.h\n" << nl
  field = g & mesh.C()
  gh = volScalarFieldHolder( word( "gh" ), volScalarFieldHolder( field, mesh ) )
  from wrappers.finiteVolume import surfaceScalarFieldHolder
  field = g & mesh.Cf()
  ghf = surfaceScalarFieldHolder( word( "ghf" ), surfaceScalarFieldHolder( field, mesh ) )

  p = volScalarFieldHolder( IOobjectHolder( word( "p" ),
                                            fileName( runTime.timeName() ),
                                            mesh,
                                            IOobject.NO_READ,
                                            IOobject.AUTO_WRITE ),
                            p_rgh + rhok * gh )

  pRefCell = 0
  pRefValue = 0.0

  from wrappers.finiteVolume import setRefCell
  pRefCell, pRefValue = setRefCell( p, p_rgh, mesh.solutionDict().subDict( word( "SIMPLE" ) ), pRefCell, pRefValue )

  from Foam.finiteVolume import getRefCellValue
  from Foam.OpenFOAM import dimensionedScalar
  if p_rgh.needReference():
    p().ext_assign( p() + dimensionedScalar( word( "p" ),p.dimensions(), pRefValue - getRefCellValue( p(), pRefCell ) ) )
    pass
  
  return T, p_rgh, U, phi, laminarTransport, turbulence, rhok, kappat, gh, ghf, p, pRefCell, pRefValue, beta, TRef, Pr, Prt


#---------------------------------------------------------------------------
def fun_UEqn( mesh, simple, U, phi, turbulence, p, rhok, p_rgh, ghf ):

  from wrappers import fvm, Deps, fvc
  from wrappers.finiteVolume import fvVectorMatrixHolder
  UEqn = fvm.div(phi, U) + fvVectorMatrixHolder( turbulence.divDevReff( U() ), Deps( turbulence, U ) ) 

  UEqn().relax();

  if  simple.momentumPredictor():
    from wrappers.finiteVolume import solve, surfaceScalarFieldHolder
    solve( UEqn == fvc.reconstruct( ( - ghf * fvc.snGrad( rhok ) - fvc.snGrad( p_rgh ) ) * surfaceScalarFieldHolder( mesh.magSf(), mesh ) ) )
    pass
  return UEqn;


#---------------------------------------------------------------------------
def fun_TEqn( phi, turbulence, kappat, T, rhok, beta, TRef, Prt, Pr ):
  
  kappat().ext_assign( turbulence.ext_nut() / Prt )
  
  kappat.correctBoundaryConditions()
  
  from Foam.finiteVolume import volScalarField 
  from Foam.OpenFOAM import word
  kappaEff = volScalarField ( word( "kappaEff" ) , turbulence.ext_nu() / Pr  + kappat() )
  from Foam import fvm, fvc
  TEqn = fvm.div( phi(), T() ) - fvm.Sp(fvc.div( phi() ), T() ) - fvm.laplacian( kappaEff, T() ) 

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

  phi().ext_assign( fvc.interpolate( U() ) & mesh.Sf() )
  from wrappers.finiteVolume import adjustPhi
  adjustPhi( phi, U, p_rgh );

  buoyancyPhi = rAUf * ghf() * fvc.snGrad( rhok() ) * mesh.magSf()
  phi().ext_assign( phi() - buoyancyPhi )

  from Foam import fvm
  for nonOrth in range( simple.nNonOrthCorr() + 1 ):
    p_rghEqn = fvm.laplacian( rAUf, p_rgh() ) == fvc.div( phi() )
    from Foam.finiteVolume import getRefCellValue
    p_rghEqn.setReference( pRefCell, getRefCellValue( p_rgh(), pRefCell ) )
    
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
  cumulativeContErr = ContinuityErrs( phi(), runTime(), mesh(), cumulativeContErr )

  p.ext_assign( p_rgh + rhok * gh )

  if p_rgh.needReference():
    from Foam.OpenFOAM import dimensionedScalar, word
    p().ext_assign( p() + dimensionedScalar( word( "p" ), p.dimensions(), pRefValue - getRefCellValue( p(), pRefCell ) ) )
    p_rgh.ext_assign( p - rhok * gh )
    pass
  
  return cumulativeContErr



#---------------------------------------------------------------------------
def main_standalone( argc, argv ):
  
  from Foam.OpenFOAM.include import setRootCase
  args = setRootCase( argc, argv )
  
  from wrappers.OpenFOAM import createTime  
  runTime=createTime( args )
    
  from wrappers.OpenFOAM import createMesh
  mesh = createMesh( runTime )
    
  g = readGravitationalAcceleration( runTime(), mesh() );

  T, p_rgh, U, phi, laminarTransport, turbulence, rhok, \
     kappat, gh, ghf, p, pRefCell, pRefValue, beta, TRef, Pr, Prt  = createFields( runTime, mesh, g )
                                                        
  from Foam.finiteVolume.cfdTools.general.include import initContinuityErrs
  cumulativeContErr = initContinuityErrs();

  from wrappers.finiteVolume import simpleControlHolder
  simple = simpleControlHolder (mesh)


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

