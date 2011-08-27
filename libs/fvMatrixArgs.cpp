//---------------------------------------------------------------------------
namespace Foam
{

  fvMatrixArgs::fvMatrixArgs( const universalHolder* args ) 
    : universalArgs( args )
  {}

  fvMatrixArgs::fvMatrixArgs( const std::set< holderPtr >& the_deps ) 
    : universalArgs( the_deps )
  {}

  fvMatrixArgs::fvMatrixArgs() 
    : universalArgs()
  {}
  
}


//---------------------------------------------------------------------------
