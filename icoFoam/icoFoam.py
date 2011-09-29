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
    ext_Info() << "Reading transportProperties\n"

    from Foam.OpenFOAM import IOobject, word, fileName
    transportProperties = man.IOdictionary( man.IOobject( word( "transportProperties" ),
                                                          fileName( runTime.constant() ),
                                                          mesh,
                                                          IOobject.MUST_READ_IF_MODIFIED,
                                                          IOobject.NO_WRITE ) )

    from Foam.OpenFOAM import dimensionedScalar
    nu = dimensionedScalar( transportProperties.lookup( word( "nu" ) ) ) 

    ext_Info() << "Reading field p\n" << nl
    p = man.volScalarField( man.IOobject( word( "p" ),
                                          fileName( runTime.timeName() ), 
                                          mesh,
                                          IOobject.MUST_READ,
                                          IOobject.AUTO_WRITE ), mesh );


    ext_Info() << "Reading field U\n" << nl
    U = man.volVectorField( man.IOobject( word( "U" ),
                                          fileName( runTime.timeName() ),
                                          mesh,
                                          IOobject.MUST_READ,
                                          IOobject.AUTO_WRITE ), mesh );

    phi = man.createPhi( runTime, mesh, U )

    pRefCell = 0
    pRefValue = 0.0
   
    from Foam.finiteVolume import setRefCell
    pRefCell, pRefValue = setRefCell( p, mesh.solutionDict().subDict( word( "PISO" ) ), pRefCell, pRefValue )

    return transportProperties, nu, p, U, phi, pRefCell, pRefValue


#--------------------------------------------------------------------------------------
def main_standalone( argc, argv ):

    from Foam.OpenFOAM.include import setRootCase
    args = setRootCase( argc, argv )

    runTime = man.createTime( args )

    mesh = man.createMesh( runTime )

    transportProperties, nu, p, U, phi, pRefCell, pRefValue = createFields( runTime, mesh )

    from Foam.finiteVolume.cfdTools.general.include import initContinuityErrs
    cumulativeContErr = initContinuityErrs()
    
    from Foam.OpenFOAM import ext_Info, nl
    ext_Info() << "\nStarting time loop\n"

    while runTime.loop() :
        ext_Info() << "Time = " <<  runTime.timeName() << nl << nl

        from Foam.finiteVolume.cfdTools.general.include import readPISOControls
        piso, nCorr, nNonOrthCorr, momentumPredictor, transonic, nOuterCorr = readPISOControls( mesh )

        from Foam.finiteVolume.cfdTools.general.include import CourantNo
        CoNum, meanCoNum = CourantNo( mesh, phi, runTime )

        UEqn = man.fvm.ddt( U ) + man.fvm.div( phi, U ) - man.fvm.laplacian( nu, U )

        from Foam.finiteVolume import solve
        solve( UEqn == -man.fvc.grad( p ) )

        # --- PISO loop

        for corr in range( nCorr ) :
            rUA = 1.0 / UEqn.A()
            from Foam import fvc, fvm
            U().ext_assign( rUA * UEqn.H() )
            phi().ext_assign( ( fvc.interpolate( U ) & mesh.Sf() ) + fvc.ddtPhiCorr( rUA, U, phi ) )

            from Foam.finiteVolume import adjustPhi
            adjustPhi( phi, U, p )

            for nonOrth in range( nNonOrthCorr + 1 ) :
                pEqn = ( fvm.laplacian( rUA, p ) == fvc.div( phi ) )

                pEqn.setReference( pRefCell, pRefValue ) 
                pEqn.solve()                             

                if nonOrth == nNonOrthCorr:
                    phi().ext_assign( phi() - pEqn.flux() )
                    pass
                
                pass
            
            from Foam.finiteVolume.cfdTools.incompressible import continuityErrs
            cumulativeContErr = continuityErrs( mesh, phi, runTime, cumulativeContErr )

            U().ext_assign( U() - rUA * fvc.grad( p ) )
            U.correctBoundaryConditions()    

            pass

        runTime.write()    
        
        ext_Info() << "ExecutionTime = " << runTime.elapsedCpuTime() << " s" << \
                      "  ClockTime = " << runTime.elapsedClockTime() << " s" << nl << nl

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

