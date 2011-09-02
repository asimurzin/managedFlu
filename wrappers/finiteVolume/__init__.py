from wrappers.src.finiteVolume.fvMeshHolder import *
from wrappers.src.OpenFOAM.GeometricFieldHolders import *
from wrappers.src.finiteVolume.fvMatrices import *
from wrappers.src.finiteVolume.findRefCell import *

from wrappers.src.finiteVolume.linear import *
from wrappers.src.finiteVolume.adjustPhi import *

#----------------------------------------------------------------------------
volScalarFieldHolder = GeometricFieldHolder_scalar_fvPatchField_volMesh
volVectorFieldHolder = GeometricFieldHolder_vector_fvPatchField_volMesh

surfaceScalarFieldHolder = GeometricFieldHolder_scalar_fvsPatchField_surfaceMesh
surfaceVectorFieldHolder = GeometricFieldHolder_vector_fvsPatchField_surfaceMesh


#----------------------------------------------------------------------------
def setRefCell( *args ):
    from wrappers.finiteVolume import ext_setRefCell
    tmp = ext_setRefCell( *args )
    return tmp.m_refCelli, tmp.m_refValue


#----------------------------------------------------------------------------
def createPhi( runTime, mesh, U ):
    from Foam.OpenFOAM import ext_Info, nl
    ext_Info() << "Reading/calculating face flux field phi\n" << nl;


    from Foam.OpenFOAM import IOobject, fileName, word
    from wrappers.OpenFOAM import IOobjectHolder
    from wrappers import deps
    from wrappers.finiteVolume import surfaceScalarFieldHolder, surfaceVectorFieldHolder
    from wrappers.finiteVolume import linearInterpolate
    phi = surfaceScalarFieldHolder( IOobjectHolder( word( "phi" ),
                                                    fileName( runTime.timeName() ),
                                                    mesh,
                                                    IOobject.READ_IF_PRESENT,
                                                    IOobject.AUTO_WRITE ),
                                    linearInterpolate(U) & surfaceVectorFieldHolder( mesh.Sf(), deps( mesh ) ) ) 
    
    return phi


#--------------------------------------------------------------------------------------
def compressibleCreatePhi( runTime, mesh, U, rho ):
     from Foam.OpenFOAM import ext_Info, nl
     ext_Info() << "Reading/calculating face flux field phi\n" << nl
     from Foam.OpenFOAM import IOobject, fileName, word
     from wrappers.OpenFOAM import IOobjectHolder
     from wrappers import deps
     from wrappers.finiteVolume import surfaceScalarFieldHolder, surfaceVectorFieldHolder
     from wrappers.finiteVolume import linearInterpolate

     phi = surfaceScalarFieldHolder( IOobjectHolder( word( "phi" ),
                                                    fileName( runTime.timeName() ),
                                                    mesh,
                                                    IOobject.READ_IF_PRESENT,
                                                    IOobject.AUTO_WRITE ),
                                    linearInterpolate( rho * U ) & surfaceVectorFieldHolder( mesh.Sf(), deps( mesh ) ) ) 
     
     return phi

