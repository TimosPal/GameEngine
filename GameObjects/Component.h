#ifndef COMPONENT_H  
#define COMPONENT_H  

#include <misc/IdentifierGenerator.h>

namespace Engine {  
namespace GameObjects {  

class ComponentBase  
{  
public:  
   virtual ~ComponentBase() = default;  
   virtual void update() = 0;  
   virtual Identifier getID() const = 0;  

private:  
};  

template<typename Derived>  
class Component : public ComponentBase  
{  
public:  
   virtual ~Component() = default;  

   virtual void update() = 0;  

   inline Identifier getID() const override {
	   // Returns the same value, but can be queried from polymorphic objects
	   return Component<Derived>::getTypeID();
   }  

   inline static Identifier getTypeID() {
       return IdentifierGenerator<ComponentBase>::template getID<Derived>();
   }

private:  
};  

} // namespace GameObjects  
} // namespace Engine  

#endif
