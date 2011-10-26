//---------------------------------------------------------------------------
#include "core.hpp"


//---------------------------------------------------------------------------
argList setRootCase( int argc, char *argv[] )
{
  argList args(argc, argv);
  if (!args.checkRootCase())
  {
    FatalError.exit();
  }
  
  return args;
}

//---------------------------------------------------------------------------
TimeHolder createTime(  const word& dict_name, const argList& args )
{
  Info<< "Create time\n" << endl;
      
  return TimeHolder( dict_name, args);
} 


//---------------------------------------------------------------------------
fvMeshHolder createMesh( const TimeHolder& runTime )
{
  Info << "Create mesh for time = "  << runTime->timeName() << nl << endl;
  return fvMeshHolder( IOobjectHolder( fvMesh::defaultRegion,
                                             runTime->timeName(),
                                             runTime,
                                             IOobject::MUST_READ ) );
} 


//---------------------------------------------------------------------------
fvMeshHolder createMeshNoClear( const TimeHolder& runTime )
{
  Info << "Create mesh, no clear-out for time = "  << runTime->timeName() << nl << endl;
  return fvMeshHolder( IOobjectHolder( fvMesh::defaultRegion,
                                             runTime->timeName(),
                                             runTime,
                                             IOobject::MUST_READ ) );
} 


//---------------------------------------------------------------------------
