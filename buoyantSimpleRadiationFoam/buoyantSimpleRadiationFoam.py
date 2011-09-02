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
def createFields( runTime, mesh, g ):
    from Foam.OpenFOAM import ext_Info, nl
    ext_Info() << "Reading thermophysical properties\n" << nl
    
    from wrappers.thermophysicalModels import basicPsiThermoHolder
    pThermo = basicPsiThermoHolder.New( mesh );

    from wrappers.OpenFOAM import IOobjectHolder
    from wrappers import deps, Deps
    from Foam.OpenFOAM import IOobject, word, fileName
    from wrappers.finiteVolume import volScalarFieldHolder
    
    field = pThermo.rho()
    rho = volScalarFieldHolder( IOobjectHolder( word( "rho" ), 
                                                fileName( runTime.timeName() ),
                                                mesh, 
                                                IOobject.NO_READ, 
                                                IOobject.NO_WRITE ),
                                volScalarFieldHolder( field, deps( pThermo ) ) );
    
    p = volScalarFieldHolder( pThermo.p(), deps( pThermo ) )
    h = volScalarFieldHolder( pThermo.h(), deps( pThermo ) )
    psi = volScalarFieldHolder( pThermo.psi(), deps( pThermo ) )
    
    from wrappers.finiteVolume import volVectorFieldHolder
    ext_Info() << "Reading field U\n" << nl
    U = volVectorFieldHolder( IOobjectHolder( word( "U" ),
                                          fileName( runTime.timeName() ),
                                          mesh,
                                          IOobject.MUST_READ,
                                          IOobject.AUTO_WRITE ),
                              mesh )
    from wrappers.finiteVolume import compressibleCreatePhi
    phi = compressibleCreatePhi( runTime, mesh, U, rho );

    ext_Info() << "Creating turbulence model\n" << nl
    from wrappers import compressible
    turbulence = compressible.RASModelHolder.New( rho,
                                                  U,
                                                  phi,
                                                  pThermo );
    ext_Info()<< "Calculating field g.h\n" << nl
    
    from wrappers.finiteVolume import surfaceScalarFieldHolder, surfaceVectorFieldHolder
    field = g & mesh.C()                                                                                   #####################
    gh = volScalarFieldHolder( word( "gh" ), volScalarFieldHolder( field, deps( mesh ) ) )                 #We should discuss it
    field = g & mesh.Cf()                                                                                  #
    ghf = surfaceScalarFieldHolder( word( "ghf" ), surfaceScalarFieldHolder( field, deps( mesh ) ) )       ##################################
    
    ext_Info() << "Reading field p_rgh\n" << nl
    p_rgh = volScalarFieldHolder( IOobjectHolder( word( "p_rgh" ),
                                                  fileName( runTime.timeName() ),
                                                  mesh,
                                                  IOobject.MUST_READ,
                                                  IOobject.AUTO_WRITE ),
                                  mesh );
    # Force p_rgh to be consistent with p
    p_rgh.ext_assign( p - rho * gh )
    
    pRefCell = 0
    pRefValue = 0.0
    
    from wrappers.finiteVolume import setRefCell
    pRefCell, pRefValue = setRefCell( p, p_rgh, mesh.solutionDict().subDict( word( "SIMPLE" ) ), pRefCell, pRefValue );

    from Foam import fvc
    initialMass = fvc.domainIntegrate( rho() )
    totalVolume = mesh.V().ext_sum()
    
    return pThermo, rho, p, h, psi, U, phi, turbulence, gh, ghf, p_rgh, pRefCell, pRefValue, initialMass, totalVolume


#--------------------------------------------------------------------------------------
def fun_Ueqn( simple, mesh, rho, U, phi, turbulence, ghf, p_rgh ):
    from wrappers import deps
    from wrappers import fvc, fvm 
    from wrappers.finiteVolume import fvVectorMatrixHolder
    UEqn = fvm.div( phi, U ) + fvVectorMatrixHolder( turbulence.divDevRhoReff( U() ), deps( turbulence, U) )
    
    UEqn.relax()
 
    from wrappers.finiteVolume import solve, surfaceScalarFieldHolder
    if simple.momentumPredictor():
     solve( UEqn == fvc.reconstruct( ( ( - ghf * fvc.snGrad( rho ) - fvc.snGrad( p_rgh ) ) * surfaceScalarFieldHolder( mesh.magSf(), deps( mesh ) ) ) ) )

    return UEqn

#--------------------------------------------------------------------------------------
def fun_hEqn( thermo, rho, p, h, phi, radiation, turbulence ):
    from Foam import fvc, fvm 
    hEqn = fvm.div( phi(), h() ) - fvm.Sp(fvc.div( phi() ), h() ) - fvm.laplacian(turbulence.alphaEff(), h() ) \
            == fvc.div( phi() / fvc.interpolate( rho() ) * fvc.interpolate( p() ) ) - p() * fvc.div( phi() / fvc.interpolate( rho() ) ) \
               + radiation.Sh( thermo() )


    hEqn.relax()
    hEqn.solve()
    thermo.correct()
    radiation.correct()
    pass
    
    
#--------------------------------------------------------------------------------------
def fun_pEqn( mesh, runTime, simple, thermo, rho, p, h, psi, U, phi, turbulence, \
                      gh, ghf, p_rgh, UEqn, pRefCell, pRefValue, cumulativeContErr, initialMass):
      rho().ext_assign( thermo.rho() )
      rho.relax()

      rAU = 1.0 / UEqn.A()
      
      from Foam import fvc
      from Foam.finiteVolume import surfaceScalarField
      from Foam.OpenFOAM import word
      rhorAUf = surfaceScalarField( word( "(rho*(1|A(U)))" ), fvc.interpolate( rho() * rAU ) )
      
      U().ext_assign( rAU * UEqn.H() )
      
      #UEqn.clear()
      
      phi().ext_assign(  fvc.interpolate( rho() ) * ( fvc.interpolate( U() ) & mesh.Sf() ) )
      
      from wrappers.finiteVolume import adjustPhi
      closedVolume = adjustPhi( phi, U, p_rgh )
      
      buoyancyPhi = rhorAUf * ghf() * fvc.snGrad( rho() ) * mesh.magSf()
      
      phi().ext_assign( phi() - buoyancyPhi )

      for nonOrth in range( simple.nNonOrthCorr() + 1 ):
          from Foam import fvm
          p_rghEqn = ( fvm.laplacian( rhorAUf, p_rgh() ) == fvc.div( phi() ) )
          
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
              U().ext_assign( U() - rAU * fvc.reconstruct( ( buoyancyPhi + p_rghEqn.flux() ) / rhorAUf ) )
              U.correctBoundaryConditions()
              pass
          pass
  
      from Foam.finiteVolume.cfdTools.general.include import ContinuityErrs
      cumulativeContErr = ContinuityErrs( phi(), runTime(), mesh(), cumulativeContErr )
      
      p.ext_assign( p_rgh + rho * gh )

      # For closed-volume cases adjust the pressure level
      # to obey overall mass continuity
      if closedVolume:
          p().ext_assign( p() + ( initialMass - fvc.domainIntegrate( psi() * p() ) ) / fvc.domainIntegrate( psi() ) )
          p_rgh.ext_assign( p - rho * gh )
          pass
      rho().ext_assign( thermo.rho() )
      rho.relax()
      from Foam.OpenFOAM import ext_Info, nl
      ext_Info() << "rho max/min : " <<  rho().ext_max().value() << " " << rho().ext_min().value() << nl
      pass

    
                      
#--------------------------------------------------------------------------------------
def main_standalone( argc, argv ):

    from Foam.OpenFOAM.include import setRootCase
    args = setRootCase( argc, argv )

    from wrappers.OpenFOAM import createTime
    runTime = createTime( args )

    from wrappers.OpenFOAM import createMesh
    mesh = createMesh( runTime )
    
    g = readGravitationalAcceleration( runTime(), mesh() )

    pThermo, rho, p, h, psi, U, phi, turbulence, gh, ghf, p_rgh, \
         pRefCell, pRefValue, initialMass, totalVolume = createFields( runTime, mesh, g )

    from wrappers.radiation import createRadiationModel
    radiation = createRadiationModel( pThermo )
    
    from Foam.finiteVolume.cfdTools.general.include import initContinuityErrs
    cumulativeContErr = initContinuityErrs()
    
    
    from wrappers.finiteVolume import simpleControlHolder
    simple = simpleControlHolder ( mesh )
    
    from Foam.OpenFOAM import ext_Info, nl
    ext_Info() << "\nStarting time loop\n" << nl

    while simple.loop():
        ext_Info() << "Time = " << runTime.timeName() << nl << nl

        p_rgh.storePrevIter()
        rho.storePrevIter()
        
        UEqn = fun_Ueqn( simple, mesh, rho, U, phi, turbulence, ghf, p_rgh )

        fun_hEqn( pThermo, rho, p, h, phi, radiation, turbulence )

        fun_pEqn( mesh, runTime, simple, pThermo, rho, p, h, psi, U, phi, turbulence, 
                      gh, ghf, p_rgh, UEqn, pRefCell, pRefValue, cumulativeContErr, initialMass)

        turbulence.correct()

        runTime.write()

        ext_Info() << "ExecutionTime = " << runTime.elapsedCpuTime() << " s" << "  ClockTime = " << runTime.elapsedClockTime() << " s" << nl << nl
        pass

    ext_Info() << "End\n"

    import os
    return os.EX_OK

    
#--------------------------------------------------------------------------------------
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
   ext_Info()<< "\nTo use this solver, It is necessary to SWIG OpenFoam1.6 \n "     
    


    
#--------------------------------------------------------------------------------------

