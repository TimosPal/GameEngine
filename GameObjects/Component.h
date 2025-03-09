#ifndef COMPONENT_H  
#define COMPONENT_H  

#include <misc/IdentifierGenerator.h>

namespace Engine {  
namespace GameObjects {  

class ComponentBase  
{  
public:
	virtual ~ComponentBase() = default;  

	virtual void update() {};
	virtual void start() {};

	virtual Identifier getInstanceID() const = 0;  
	virtual std::unique_ptr<ComponentBase> clone() const = 0;

private:  
};  

template<typename Derived>  
class Component : public ComponentBase  
{  
public:  

	inline Identifier getInstanceID() const override
	{
		// Returns the same value, but can be queried from polymorphic objects
		return Component<Derived>::getTypeID();
	}  

	inline static Identifier getTypeID() 
	{
		return IdentifierGenerator<ComponentBase>::template getTypeID<Derived>();
	}

	inline std::unique_ptr<ComponentBase> clone() const override
	{
		return std::make_unique<Derived>(static_cast<const Derived&>(*this));
	}

private:  
};  

} // namespace GameObjects  
} // namespace Engine  

#endif
