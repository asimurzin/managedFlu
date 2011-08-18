from wrappers.src.fvMeshHolder import *
from wrappers.src.GeometricFieldHolders import *
from wrappers.src.fvMatrices import *
from wrappers.src.findRefCell import *

from wrappers.src.linear import *
from wrappers.src.adjustPhi import *

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



