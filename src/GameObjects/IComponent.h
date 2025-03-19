#ifndef ICOMPONENT_H  
#define ICOMPONENT_H  

#include <Utility/IdentifierGenerator.h>

namespace Engine {  
namespace GameObjects {  

class IComponentBase  
{  
public:
	virtual ~IComponentBase() = default;  

	virtual void start() {};
	virtual void update() {};

	virtual Identifier getInstanceID() const = 0;  
	virtual std::unique_ptr<IComponentBase> clone() const = 0;
};  

template<typename Derived>  
class IComponent : public IComponentBase  
{  
public:  

	inline Identifier getInstanceID() const override
	{
		// Returns the same value, but can be queried from polymorphic objects
		return IComponent<Derived>::getTypeID();
	}  

	inline static Identifier getTypeID() 
	{
		return IdentifierGenerator<IComponentBase>::template getTypeID<Derived>();
	}

	inline std::unique_ptr<IComponentBase> clone() const override
	{
		return std::make_unique<Derived>(static_cast<const Derived&>(*this));
	}
};  

} // namespace GameObjects  
} // namespace Engine  

#endif
