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
def createFields( runTime, mesh ):
  from Foam.OpenFOAM import ext_Info, nl
  ext_Info() << "Reading field p\n" << nl
  
  from Foam.OpenFOAM import IOobject, word, fileName
  p = man.volScalarField( man.IOobject( word( "p" ), fileName( runTime.timeName() ), mesh, IOobject.MUST_READ, IOobject.AUTO_WRITE ), mesh )

  ext_Info() << "Reading field U\n" << nl
  U = man.volVectorField( man.IOobject( word( "U" ),
                                            fileName( runTime.timeName() ),
                                            mesh,
                                            IOobject.MUST_READ,
                                            IOobject.AUTO_WRITE ),
                            mesh );
  
  phi = man.createPhi( runTime, mesh, U );
  
  pRefCell = 0
  pRefValue = 0.0
  from Foam.finiteVolume import setRefCell
  pRefCell, pRefValue = setRefCell( p, mesh.solutionDict().subDict( word( "SIMPLE" ) ), pRefCell, pRefValue )

  laminarTransport = man.singlePhaseTransportModel( U, phi )

  turbulence = man.incompressible.RASModel.New( U, phi, laminarTransport )
  
  return p, U, phi, pRefCell, pRefValue, laminarTransport, turbulence


#---------------------------------------------------------------------------
def fun_UEqn( U, phi, turbulence, p ):
  # Solve the Momentum equation
  
  UEqn = man.fvm.div( phi, U ) + man.fvVectorMatrix( turbulence.divDevReff( U ), man.Deps( turbulence, U ) ) 

  UEqn.relax()
  from Foam.finiteVolume import solve
  solve( UEqn == -man.fvc.grad( p ) )

  return UEqn


#---------------------------------------------------------------------------
def fun_pEqn( mesh, runTime, simple, U, phi, turbulence, p, UEqn, pRefCell, pRefValue, cumulativeContErr ):
  
  p.ext_boundaryField().updateCoeffs()

  rAU = 1.0 / UEqn().A();
  U().ext_assign( rAU * UEqn().H() )
  
  from Foam import fvc
  from Foam.OpenFOAM import word
  phi().ext_assign( fvc.interpolate( U, word( "interpolate(HbyA)" ) ) & mesh.Sf() )
  
  from Foam.finiteVolume import adjustPhi
  adjustPhi(phi, U, p)

  from Foam import fvm
  # Non-orthogonal pressure corrector loop
  for nonOrth in range( simple.nNonOrthCorr() + 1 ):
    pEqn = fvm.laplacian( rAU, p ) == fvc.div( phi )

    pEqn.setReference( pRefCell, pRefValue )

    pEqn.solve()

    if nonOrth == simple.nNonOrthCorr():
      phi().ext_assign( phi() - pEqn.flux() )
      pass
    pass
  from Foam.finiteVolume.cfdTools.incompressible import continuityErrs
  cumulativeContErr = continuityErrs(  mesh, phi, runTime, cumulativeContErr )

  # Explicitly relax pressure for momentum corrector
  p.relax()

  # Momentum corrector
  U().ext_assign( U() - rAU * fvc.grad( p ) )
  U.correctBoundaryConditions()
  
  return cumulativeContErr


#---------------------------------------------------------------------------
def main_standalone( argc, argv ):
  
  from Foam.OpenFOAM.include import setRootCase
  args = setRootCase( argc, argv )
  
  runTime = man.createTime( args )
  
  mesh = man.createMesh( runTime )
    
  p, U, phi, pRefCell, pRefValue, laminarTransport, turbulence = createFields( runTime, mesh )

  from Foam.finiteVolume.cfdTools.general.include import initContinuityErrs
  cumulativeContErr = initContinuityErrs()
  
  simple = man.simpleControl (mesh)

  # * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * #
  from Foam.OpenFOAM import ext_Info, nl
  ext_Info() << "\nStarting time loop\n" << nl

  while simple.loop():
    ext_Info() << "Time = " << runTime.timeName() << nl << nl

    p.storePrevIter()

    # --- Pressure-velocity SIMPLE corrector
    UEqn = fun_UEqn( U, phi, turbulence, p )
    cumulativeContErr = fun_pEqn( mesh, runTime, simple, U, phi, turbulence, p, UEqn, pRefCell, pRefValue, cumulativeContErr )

    turbulence.correct()

    runTime.write()

    ext_Info() << "ExecutionTime = " << runTime.elapsedCpuTime() << " s" \
            << "  ClockTime = " << runTime.elapsedClockTime() << " s" \
            << nl << nl
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
    


