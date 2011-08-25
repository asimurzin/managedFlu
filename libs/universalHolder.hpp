#ifndef universalHolder_hpp
#define universalHolder_hpp


//---------------------------------------------------------------------------
namespace Foam
{
  class universalHolder
  {
    public:
      virtual universalHolder* clone() = 0;
      
      virtual ~universalHolder()
      {}
  };
} // Foam


//---------------------------------------------------------------------------
#endif
