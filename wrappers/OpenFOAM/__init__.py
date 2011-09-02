from wrappers.src.OpenFOAM.TimeHolder import *
from wrappers.src.OpenFOAM.IOobjectHolder import *
from wrappers.src.OpenFOAM.IOdictionaryHolder import *


#---------------------------------------------------------------------------
def createTime( args ):
    from Foam.OpenFOAM import ext_Info, nl
    ext_Info() << "Create time\n" << nl
    
    from Foam.OpenFOAM import Time
    from wrappers.OpenFOAM import TimeHolder 

    runTime = TimeHolder( Time.controlDictName.fget(), args ) 
    
    return runTime

#---------------------------------------------------------------------------
def createMesh( runTime ):
    from Foam.OpenFOAM import ext_Info, nl
    ext_Info() << "Create mesh for time = " << runTime.timeName() << nl << nl 

    from Foam.OpenFOAM import IOobject
    from Foam.OpenFOAM import fileName
    from Foam.finiteVolume import fvMesh
    from wrappers.OpenFOAM import IOobjectHolder
    from wrappers.finiteVolume import fvMeshHolder
    
    
    mesh = fvMeshHolder( IOobjectHolder( fvMesh.defaultRegion.fget(),           
                                         fileName( runTime.timeName() ),      
                                         runTime,
                                         IOobject.MUST_READ ) )                     
   
    return mesh


#---------------------------------------------------------------------------
