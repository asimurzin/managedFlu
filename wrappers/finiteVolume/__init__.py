from wrappers.src.fvMeshHolder import *
from wrappers.src.GeometricFieldHolders import *


#----------------------------------------------------------------------------
volScalarFieldHolder = GeometricFieldHolder_scalar_fvPatchField_volMesh
volVectorFieldHolder = GeometricFieldHolder_vector_fvPatchField_volMesh

surfaceScalarFieldHolder = GeometricFieldHolder_scalar_fvsPatchField_surfaceMesh
surfaceVectorFieldHolder = GeometricFieldHolder_vector_fvsPatchField_surfaceMesh
