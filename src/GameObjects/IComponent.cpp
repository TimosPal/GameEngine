#include "IComponent.h"

#include <GameObjects/GameObject.h>

namespace Engine {
namespace GameObjects {

std::string IComponentBase::toString() const
{
	// TODO: cache result.
	std::string name = classToString(*this);
	return name;
}

void IComponentBase::setOwner(GameObjects::GameObject& owner)
{ 
	m_owner = &owner; 
}

GameObject& IComponentBase::getOwner() const
{
	return *m_owner;
}

} // GameObjects
} // Engine