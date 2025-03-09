#include "./GameObject.h"

#include <memory>

#include <misc/IdentifierGenerator.h>

namespace Engine {
namespace GameObjects {

GameObject::GameObject() : m_id(IdentifierGenerator<GameObject>::getInstanceID())
{}

GameObject::GameObject(const GameObject& other)
{
	// Copy id
	m_id = other.m_id;

	// Copy
	m_componentsRaw.reserve(other.m_componentsRaw.size());
	for (auto& component : other.m_componentsRaw) {
		m_componentsRaw.emplace_back(std::move(component->clone()));
	}

	// Populate dictionary with component ids for fast lookup.
	for (auto& component : m_componentsRaw) {
		m_componentsDictionary[component->getInstanceID()] = component.get();
	}
}

GameObject::GameObject(GameObject&& other) noexcept
{
	// Move id
	m_id = other.m_id;

	// Move
	m_componentsRaw = std::move(other.m_componentsRaw);

	// Populate dictionary with component ids for fast lookup.
	m_componentsDictionary = std::move(other.m_componentsDictionary);
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

void GameObject::update() 
{
	// Components should already be in proper order of prefeared excecution.
	// eg: consistent within objects.
	for (auto& component : m_componentsRaw) {
		component->update();
	}
}

bool GameObject::addComponent(std::unique_ptr<ComponentBase>&& component) 
{
	if (component == nullptr)
	{
		return false;
	}
		
	// Check if component already exists.
	if (m_componentsDictionary.find(component->getInstanceID()) != m_componentsDictionary.end()) 
	{
		return false;
	}

	m_componentsDictionary[component->getInstanceID()] = component.get();

	// Find the correct insertion position to keep the vector sorted
	auto it = std::lower_bound(m_componentsRaw.begin(), m_componentsRaw.end(), component,
		[](const std::unique_ptr<ComponentBase>& a, const std::unique_ptr<ComponentBase>& b) {
			return a->getInstanceID() < b->getInstanceID();
		});
	// Insert the script at the found position
	m_componentsRaw.insert(it, std::move(component));
	
	return true;
}

} // namespace GameObjects
} // namespace Engine