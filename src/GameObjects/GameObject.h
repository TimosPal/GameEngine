#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <unordered_map>
#include <algorithm>
#include <memory>

#include "./IComponent.h"


namespace Engine {
namespace GameObjects {

/*
This class is modeled arround OOP game objects (cache ineficient, pointer indirections, etc).
Can retrieve a component in O(1) time, but adding/removing components is O(N) time. Thats because
we rarely want to add or remove components, but we often want to retrieve / iterate them.
Components are owned by the GameObject, and are stored in a vector. The vector is sorted by component id
*/
class GameObject
{
public:
	GameObject();
	GameObject(const GameObject& other);
	GameObject(GameObject&& other) noexcept;

	template<typename... IComponent>
	GameObject(const IComponent&... components)
		: m_id(IdentifierGenerator<GameObject>::getInstanceID())
	{
		(m_componentsRaw.emplace_back(std::make_unique<IComponent>(components)), ...);
		std::sort(m_componentsRaw.begin(), m_componentsRaw.end(), 
			[](const std::shared_ptr<IComponentBase>& a, const std::shared_ptr<IComponentBase>& b) {
				return a->getInstanceID() < b->getInstanceID();
			});
	
		for (auto& component : m_componentsRaw) {
			// Ensure component is not already in the dictionary.
			if (m_componentsDictionary.find(component->getInstanceID()) != m_componentsDictionary.end()) {
				continue;
			}

			m_componentsDictionary[component->getInstanceID()] = std::weak_ptr<IComponentBase>(component);
		}
	}

	~GameObject();
	
	GameObject& operator=(const GameObject& other);
	bool operator==(const GameObject& other) const { return m_id == other.m_id; }

	void start();
	void update();

	// NOTE: This is slow due to sorting in O(N) time.
	template<typename IComponent>
	bool addComponent(const IComponent& component)
	{
		std::shared_ptr<IComponentBase> comp_ptr = std::make_shared<IComponent>(component);
		
		// Check if component already exists.
		int id = comp_ptr->getInstanceID();
		if (m_componentsDictionary.find(id) != m_componentsDictionary.end())
		{
			return false;
		}

		m_componentsDictionary[id] = std::weak_ptr<IComponentBase>(comp_ptr);

		// Find the correct insertion position to keep the vector sorted
		auto it = std::lower_bound(m_componentsRaw.begin(), m_componentsRaw.end(), comp_ptr,
			[](const std::shared_ptr<IComponentBase>& a, const std::shared_ptr<IComponentBase>& b) {
				return a->getInstanceID() < b->getInstanceID();
			});
		// Insert the script at the found position
		m_componentsRaw.insert(it, std::move(comp_ptr));

		return true;
	}

	Identifier getInstanceID() const { return m_id; }

	template<typename T>
	std::weak_ptr<IComponentBase> getComponent()
	{
		Identifier id = IComponent<T>::getTypeID();
			
		auto it = m_componentsDictionary.find(id);
		if (it != m_componentsDictionary.end()) {
			return it->second;
		}

		return nullptr;
	}

	// NOTE: This is slow due to O(N) search.
	template<typename T>
	bool removeComponent() 
	{
		Identifier id = IComponent<T>::getTypeID();

		// Remove from dictionary.
		auto it = m_componentsDictionary.find(id);
		if (it != m_componentsDictionary.end()) {
			m_componentsDictionary.erase(it);
		} 
		else {
			return false;
		}

		// Remove from raw list. 
		for (auto it = m_componentsRaw.begin(); it != m_componentsRaw.end(); ++it) {
			if ((*it)->getInstanceID() == id) {
				m_componentsRaw.erase(it);
				return true;
			}
		}

		return false;
	}

private:
	std::vector<std::shared_ptr<IComponentBase>> m_componentsRaw;
	std::unordered_map<Identifier, std::weak_ptr<IComponentBase>> m_componentsDictionary;

	Identifier m_id;
};

} // namespace GameObjects
} // namespace Engine

#endif 