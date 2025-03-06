#include "./GameObject.h"

#include <algorithm>

#include <misc/IdentifierGenerator.h>

namespace Engine {
namespace GameObjects {

GameObject::GameObject() : m_id(IdentifierGenerator<GameObject>::getInstanceID())
{}

GameObject::GameObject(std::vector<std::unique_ptr<ComponentBase>>&& components)
	: m_componentsRaw(std::move(components)),
	m_id(IdentifierGenerator<GameObject>::getInstanceID())
{
	// Sort components by id.
	std::sort(m_componentsRaw.begin(), m_componentsRaw.end(),
		[](const std::unique_ptr<ComponentBase>& a, const std::unique_ptr<ComponentBase>& b) {
			return a->getInstanceID() < b->getInstanceID();
		});

	// Populate dictionary with component ids for fast lookup.
	for (auto& component : m_componentsRaw) {
		m_componentsDictionary[component->getInstanceID()] = component.get();
	}
}

GameObject::~GameObject() {}

void GameObject::update() {
	// Components should already be in proper order of prefeared excecution.
	// eg: consistent within objects.
	for (auto& component : m_componentsRaw) {
		component->update();
	}
}

bool GameObject::addComponent(std::unique_ptr<ComponentBase>&& component) {
	if (component == nullptr) {
		return false;
	}
			
	// Check if component already exists.
	if (m_componentsDictionary.find(component->getInstanceID()) != m_componentsDictionary.end()) {
		return false;
	}

	// Find the correct insertion position to keep the vector sorted
	auto it = std::lower_bound(m_componentsRaw.begin(), m_componentsRaw.end(), component,
		[](const std::unique_ptr<ComponentBase>& a, const std::unique_ptr<ComponentBase>& b) {
			return a->getInstanceID() < b->getInstanceID();
		});

	m_componentsDictionary[component->getInstanceID()] = component.get();
	// Insert the script at the found position
	m_componentsRaw.insert(it, std::move(component));
		
	return true;
}

} // namespace GameObjects
} // namespace Engine