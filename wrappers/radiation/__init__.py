#---------------------------------------------------------------------------
from wrappers.src.thermophysicalModels.radiationModelHolder import *


#---------------------------------------------------------------------------
def createRadiationModel( thermo ) :
    from wrappers import radiation
    from wrappers.finiteVolume import volScalarFieldHolder
    pRadiation = radiation.radiationModelHolder.New( volScalarFieldHolder( thermo.T(), thermo ) )
    
    return pRadiation

