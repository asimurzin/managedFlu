//---------------------------------------------------------------------------
#include "basicPsiThermoHolder.hpp"


//---------------------------------------------------------------------------
  Foam::basicPsiThermoHolder Foam::basicPsiThermoHolder::New( const Foam::fvMeshHolder& mesh )
  {
    Foam::autoPtr< Foam::basicPsiThermo > pThermo = Foam::basicPsiThermo::New( *mesh );
    
    return Foam::basicPsiThermoHolder( boost::shared_ptr< Foam::basicPsiThermo >( pThermo.ptr() ), mesh );
  }


//---------------------------------------------------------------------------
