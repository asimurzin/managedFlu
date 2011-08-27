//---------------------------------------------------------------------------
#include "core.hpp"
#include "thermophysicalModels.hpp"
#include "radiationModels.hpp"


//---------------------------------------------------------------------------
Foam::radiation::radiationModelHolder createRadiationModel( const basicThermoHolder& pThermo )
{
  return Foam::radiation::radiationModelHolder::New( Foam::volScalarFieldHolder( pThermo->T(), &pThermo ) );
}


//---------------------------------------------------------------------------
