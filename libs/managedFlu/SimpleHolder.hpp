#ifndef SimpleHolder_hpp
#define SimpleHolder_hpp


//---------------------------------------------------------------------------
namespace Foam
{
  class SimpleHolder
  {
    public:
      virtual SimpleHolder* clone() const = 0;
      
      virtual ~SimpleHolder()
      {}
  };
} // Foam


//---------------------------------------------------------------------------
#endif
