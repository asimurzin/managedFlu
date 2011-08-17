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
def createTime( args ):
    from Foam.OpenFOAM import ext_Info, nl
    ext_Info() << "Create time\n" << nl
    
    from Foam.OpenFOAM import Time
    from wrappers.OpenFOAM import TimeHolder 

    runTime = TimeHolder( Time.controlDictName.fget(), args )  #Time && TimeHolder. It must be one class.

    return runTime

#---------------------------------------------------------------------------
def createMesh( runTime ):
    from Foam.OpenFOAM import ext_Info, nl
    ext_Info() << "Create mesh for time = " << runTime().timeName() << nl << nl #runTime() 

    from Foam.OpenFOAM import IOobject
    from Foam.OpenFOAM import fileName
    from Foam.finiteVolume import fvMesh
    from wrappers.OpenFOAM import IOobjectHolder
    from wrappers.finiteVolume import fvMeshHolder
    
    
    mesh = fvMeshHolder( IOobjectHolder( fvMesh.defaultRegion.fget(),           # fvMesh && fvMeshHolder
                                         fileName( runTime().timeName() ),      #runTime()
                                         runTime,
                                         IOobject.MUST_READ ) )                 # IOobject && IOobjectHolder
    
   
    return mesh


#---------------------------------------------------------------------------
def createPhi( runTime, mesh, U ):
    from Foam.OpenFOAM import ext_Info, nl
    ext_Info() << "Reading/calculating face flux field phi\n" << nl;


    from Foam.OpenFOAM import IOobject, fileName, word
    from wrappers.OpenFOAM import IOobjectHolder
    from wrappers.finiteVolume import surfaceScalarFieldHolder
    from wrappers.finiteVolume import linearInterpolate
    phi = surfaceScalarFieldHolder( IOobjectHolder( word( "phi" ),
                                                    fileName( runTime().timeName() ),
                                                    mesh,
                                                    IOobject.READ_IF_PRESENT,
                                                    IOobject.AUTO_WRITE ),
                                    linearInterpolate(U) & mesh().Sf() ); # mesh()
    
    return phi


#---------------------------------------------------------------------------
def createFields( runTime, mesh ):
    from Foam.OpenFOAM import ext_Info, nl
    ext_Info() << "Reading transportProperties\n"

    from Foam.OpenFOAM import IOobject, word, fileName
    from wrappers.OpenFOAM import IOdictionaryHolder, IOobjectHolder
    transportProperties = IOdictionaryHolder( IOobjectHolder( word( "transportProperties" ),
                                                            fileName( runTime().constant() ),
                                                            mesh,
                                                            IOobject.MUST_READ_IF_MODIFIED,
                                                            IOobject.NO_WRITE ) )

    from Foam.OpenFOAM import dimensionedScalar
    nu = dimensionedScalar( transportProperties().lookup( word( "nu" ) ) ) # transportProperties()

    ext_Info() << "Reading field p\n" << nl
    from wrappers.finiteVolume import volScalarFieldHolder
    p = volScalarFieldHolder( IOobjectHolder( word( "p" ),
                                            fileName( runTime().timeName() ), 
                                            mesh,
                                            IOobject.MUST_READ,
                                            IOobject.AUTO_WRITE ), mesh );


    ext_Info() << "Reading field U\n" << nl
    from wrappers.finiteVolume import volVectorFieldHolder
    U = volVectorFieldHolder( IOobjectHolder( word( "U" ),
                                              fileName( runTime().timeName() ),
                                              mesh,
                                              IOobject.MUST_READ,
                                              IOobject.AUTO_WRITE ), mesh );

    phi = createPhi( runTime, mesh, U )

    pRefCell = 0
    pRefValue = 0.0
    from Foam.finiteVolume import setRefCell
    pRefCell, pRefValue = setRefCell( p, mesh().solutionDict().subDict( word( "PISO" ) ), pRefCell, pRefValue )

    return transportProperties, nu, p, U, phi, pRefCell, pRefValue


#--------------------------------------------------------------------------------------
def readPISOControls( mesh ):
    from Foam.OpenFOAM import dictionary, readInt, Switch, word

    piso = dictionary( mesh().solutionDict().subDict( word( "PISO" ) ) )
    nCorr = readInt( piso.lookup( word( "nCorrectors" ) ) )
    
    nNonOrthCorr = piso.lookupOrDefault( word( "nNonOrthogonalCorrectors" ), 0 )
       
    momentumPredictor = piso.lookupOrDefault( word( "momentumPredictor" ), Switch( True ) )
      
    transonic = piso.lookupOrDefault( word( "transonic" ), Switch( False ) )
      
    nOuterCorr = piso.lookupOrDefault( word( "nOuterCorrectors" ), 1 )

    return piso, nCorr, nNonOrthCorr, momentumPredictor, transonic, nOuterCorr


#--------------------------------------------------------------------------------------
def CourantNo( mesh, phi, runTime ):

    CoNum = 0.0
    meanCoNum = 0.0
    from Foam.OpenFOAM import ext_Info, nl
    
    if mesh().nInternalFaces() :
        from wrappers import fvc
        tmp = fvc.surfaceSum( phi.mag() )
        sumPhi = tmp.internalField()
        CoNum =  0.5 * ( sumPhi / mesh().V().field() ).gMax() * runTime().deltaTValue()
        meanCoNum =  0.5 * ( sumPhi.gSum() / mesh().V().field().gSum() ) * runTime().deltaTValue()
        pass

    
    ext_Info() << "Courant Number mean: " << meanCoNum << " max: " << CoNum << nl

    return CoNum, meanCoNum


#--------------------------------------------------------------------------------------
def continuityErrs( mesh, phi, runTime, cumulativeContErr ):

    from wrappers import fvm, fvc

    contErr = fvc.div( phi )
    sumLocalContErr = runTime().deltaT().value() * contErr.mag().weightedAverage( mesh().V() ).value()
    globalContErr = runTime().deltaT().value() * contErr.weightedAverage( mesh().V() ).value()
    cumulativeContErr += globalContErr

    from Foam.OpenFOAM import ext_Info, nl
    ext_Info() << "time step continuity errors : sum local = " << sumLocalContErr \
               << ", global = " << globalContErr \
               << ", cumulative = " << cumulativeContErr << nl
               
    return cumulativeContErr


#--------------------------------------------------------------------------------------
def main_standalone( argc, argv ):

    from Foam.OpenFOAM.include import setRootCase
    args = setRootCase( argc, argv )

    runTime = createTime( args )

    mesh = createMesh( runTime )

    transportProperties, nu, p, U, phi, pRefCell, pRefValue = createFields( runTime, mesh )

    from Foam.finiteVolume.cfdTools.general.include import initContinuityErrs
    cumulativeContErr = initContinuityErrs()
    
    from Foam.OpenFOAM import ext_Info, nl
    ext_Info() << "\nStarting time loop\n"

    while runTime().loop() :
        ext_Info() << "Time = " <<  runTime().timeName() << nl << nl

        piso, nCorr, nNonOrthCorr, momentumPredictor, transonic, nOuterCorr = readPISOControls( mesh )

        CoNum, meanCoNum = CourantNo( mesh, phi, runTime )

        from wrappers import fvm
        UEqn = ( fvm.ddt( U ) + fvm.div( phi, U ) - fvm.laplacian( nu, U ) )

        from wrappers import fvc
        from wrappers.finiteVolume import solve
        
        solve( UEqn == -fvc.grad( p ) )

        # --- PISO loop

        for corr in range( nCorr ) :
            rUA = 1.0 / UEqn.A()

            U.ext_assign( rUA * UEqn.H() )
            phi.ext_assign( ( fvc.interpolate( U ) & mesh().Sf() ) + fvc.ddtPhiCorr( rUA, U, phi ) )

            from Foam.finiteVolume import adjustPhi
            adjustPhi( phi, U, p )

            for nonOrth in range( nNonOrthCorr + 1 ) :
                pEqn = ( fvm.laplacian( rUA, p ) == fvc.div( phi ) )

                pEqn().setReference( pRefCell, pRefValue ) ### pEqn()
                pEqn().solve()                             ### pEqn()

                if nonOrth == nNonOrthCorr:
                    phi.ext_assign( phi - pEqn.flux() )
                    pass
                
                pass
            
            cumulativeContErr = continuityErrs( mesh, phi, runTime, cumulativeContErr )

            U.ext_assign( U - rUA * fvc.grad( p ) )
            U().correctBoundaryConditions()    #()

            pass

        runTime().write()    # ()
        
        ext_Info() << "ExecutionTime = " << runTime().elapsedCpuTime() << " s" << \
                      "  ClockTime = " << runTime().elapsedClockTime() << " s" << nl << nl

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

