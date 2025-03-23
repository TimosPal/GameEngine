#include "./GameObject.h"

#include <memory>

#include <Utility/IdentifierGenerator.h>

namespace Engine {
namespace GameObjects {

std::set<Identifier> GameObject::m_componentTypes;

GameObject::GameObject() : m_id(IdentifierGenerator<GameObject>::getInstanceID())
{}

GameObject::GameObject(const GameObject& other)
{
	// Copy id
	m_id = other.m_id;

	// Populate dictionary with component ids for fast lookup.
	for (const auto& [id, component] : other.m_components) {
		m_components[id] = std::move(component->clone());
	}
}

GameObject::GameObject(GameObject&& other) noexcept
{
	// Move id
	m_id = other.m_id;

	// Populate dictionary with component ids for fast lookup.
	m_components = std::move(other.m_components);
}

GameObject::~GameObject() {}

GameObject& GameObject::operator=(const GameObject& other)
{
	if (this != &other)
	{
		GameObject tmp(other);
		*this = std::move(tmp);
	}

	return *this;
}

std::set<Identifier> GameObject::getComponentTypes()
{
	return m_componentTypes;
}

std::shared_ptr<IComponentBase> GameObject::getComponent(Identifier id)
{
	auto it = m_components.find(id);
	if (it != m_components.end()) {
		return it->second;
	}

	return std::shared_ptr<IComponentBase>();
}

} // namespace GameObjects
} // namespace Engine