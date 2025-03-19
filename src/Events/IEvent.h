#ifndef EVENT_H
#define EVENT_H

#include <Utility/IdentifierGenerator.h>
#include <Utility/Util.h>

namespace Engine {

class IEventBase {
public:
	virtual Identifier getInstanceID() const = 0;
	virtual std::unique_ptr<IEventBase> clone() const = 0;

	virtual std::string toString() const {
		// TODO: cache result.
		std::string name = classToString(*this);
		return name;
	}
};

template<typename Derived>
class IEvent : public IEventBase{
public:
	inline Identifier getInstanceID() const override
	{
		// Returns the same value, but can be queried from polymorphic objects
		return IEvent<Derived>::getTypeID();
	}

	inline static Identifier getTypeID()
	{
		return IdentifierGenerator<IEventBase>::template getTypeID<Derived>();
	}

	inline std::unique_ptr<IEventBase> clone() const override
	{
		return std::make_unique<Derived>(static_cast<const Derived&>(*this));
	}
};

} // Engine

#endif // !EVENT_H
