#ifndef ICOMPONENT_H  
#define ICOMPONENT_H  

#include <Utility/IdentifierGenerator.h>
#include <Utility/Util.h>

namespace Engine {  
namespace GameObjects {  

class GameObject;

class IComponentBase  
{  
public:
	virtual ~IComponentBase() = default;  

	virtual void start() {};
	virtual void update() {};

	virtual Identifier getInstanceTypeID() const = 0;  
	virtual std::unique_ptr<IComponentBase> clone() const = 0;

	virtual std::string toString() const;

	void setOwner(GameObjects::GameObject& owner);
	GameObject& getOwner() const;

protected:
	GameObject* m_owner = nullptr;
};  

template<typename Derived>  
class IComponent : public IComponentBase  
{  
public:  

	inline Identifier getInstanceTypeID() const override
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
