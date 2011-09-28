//---------------------------------------------------------------------------
#include "core.hpp"
#include "basicThermoHolder.hpp"
#include "radiationModelHolder.hpp"


//---------------------------------------------------------------------------
Foam::radiation::radiationModelHolder createRadiationModel( const basicThermoHolder& pThermo )
{
  return Foam::radiation::radiationModelHolder::New( Foam::volScalarFieldHolder( pThermo->T(), &pThermo ) );
}


//---------------------------------------------------------------------------
