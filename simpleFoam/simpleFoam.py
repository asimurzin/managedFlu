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
def createFields( runTime, mesh ):

  from Foam.OpenFOAM import ext_Info, nl
  ext_Info() << "Reading field p\n" << nl

  from Foam.OpenFOAM import IOobject, word, fileName
  from wrappers.OpenFOAM import IOobjectHolder
  from wrappers.finiteVolume import volScalarFieldHolder
  
  p = volScalarFieldHolder( IOobjectHolder( word( "p" ),
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
                            mesh );
  
  from wrappers.finiteVolume import createPhi
  phi = createPhi( runTime, mesh, U );
  
  pRefCell = 0
  pRefValue = 0.0
 
  from wrappers.finiteVolume import setRefCell
  pRefCell, pRefValue = setRefCell( p, mesh.solutionDict().subDict( word( "SIMPLE" ) ), pRefCell, pRefValue )

  from wrappers.transportModels import singlePhaseTransportModelHolder
  laminarTransport = singlePhaseTransportModelHolder( U, phi )

  from wrappers import incompressible
  turbulence = incompressible.RASModelHolder.New( U, phi, laminarTransport )
  
  return p, U, phi, pRefCell, pRefValue, laminarTransport, turbulence


#---------------------------------------------------------------------------
def fun_UEqn( U, phi, turbulence, p ):
  # Solve the Momentum equation
  
  from wrappers import fvm, deps, fvc
  from wrappers.finiteVolume import fvVectorMatrixHolder
  UEqn = fvm.div( phi, U ) + fvVectorMatrixHolder( turbulence.divDevReff( U() ), deps( turbulence, U ) ) 

  UEqn.relax()
  from wrappers.finiteVolume import solve
  solve( UEqn == -fvc.grad( p ) )

  return UEqn


#---------------------------------------------------------------------------
def fun_pEqn( mesh, runTime, simple, U, phi, turbulence, p, UEqn, pRefCell, pRefValue, cumulativeContErr ):
  
  p.ext_boundaryField().updateCoeffs()

  rAU = 1.0 / UEqn().A();
  U().ext_assign( rAU * UEqn().H() )
  
  from Foam import fvm, fvc
  from Foam.OpenFOAM import word
  phi().ext_assign( fvc.interpolate( U(), word( "interpolate(HbyA)" ) ) & mesh.Sf() )
  
  from wrappers.finiteVolume import adjustPhi
  adjustPhi(phi, U, p)

  # Non-orthogonal pressure corrector loop
  for nonOrth in range( simple.nNonOrthCorr() + 1 ):
    from Foam import fvc
    pEqn = fvm.laplacian( rAU, p() ) == fvc.div( phi() )

    pEqn.setReference( pRefCell, pRefValue )

    pEqn.solve()

    if nonOrth == simple.nNonOrthCorr():
      phi().ext_assign( phi() - pEqn.flux() )
      pass
    pass
  
  from Foam.finiteVolume.cfdTools.general.include import ContinuityErrs
  cumulativeContErr = ContinuityErrs( phi(), runTime(), mesh(), cumulativeContErr )

  # Explicitly relax pressure for momentum corrector
  p.relax()

  # Momentum corrector
  U().ext_assign( U() - rAU * fvc.grad( p() ) )
  U.correctBoundaryConditions()
  
  return cumulativeContErr




#---------------------------------------------------------------------------
def main_standalone( argc, argv ):
  
  from Foam.OpenFOAM.include import setRootCase
  args = setRootCase( argc, argv )
  
  from wrappers.OpenFOAM import createTime  
  runTime=createTime( args )
    
  from wrappers.OpenFOAM import createMesh
  mesh = createMesh( runTime )
    
  p, U, phi, pRefCell, pRefValue, laminarTransport, turbulence = createFields( runTime, mesh )

  from Foam.finiteVolume.cfdTools.general.include import initContinuityErrs
  cumulativeContErr = initContinuityErrs()

  from wrappers.finiteVolume import simpleControlHolder
  simple = simpleControlHolder (mesh)

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
    


