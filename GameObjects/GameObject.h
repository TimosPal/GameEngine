#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <unordered_map>
#include <memory>
#include <algorithm>

#include "./Component.h"


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
		GameObject()
		{
		}

		GameObject(std::vector<std::unique_ptr<ComponentBase>>&& components)
			: m_componentsRaw(std::move(components)) {

			// Sort components by id.
            std::sort(m_componentsRaw.begin(), m_componentsRaw.end(), 
				[](const std::unique_ptr<ComponentBase>& a, const std::unique_ptr<ComponentBase>& b) {
                return a->getID() < b->getID();
            });

			// Populate dictionary with component ids for fast lookup.
			for (auto& component : m_componentsRaw) {
				m_componentsDictionary[component->getID()] = component.get();
			}
		}

		~GameObject() = default;

		void update() {
			// Components should already be in proper order of prefeared excecution.
			// eg: consistent within objects.
			for (auto& component : m_componentsRaw) {
				component->update();
			}
		}

		template<typename T>
		ComponentBase* getComponent() {
			Identifier id = Component<T>::getTypeID();
			
			auto it = m_componentsDictionary.find(id);
			if (it != m_componentsDictionary.end()) {
				return it->second;
			}

			return nullptr;
		}

		// NOTE: This is slow due to sorting in O(N) time.
		bool addComponent(std::unique_ptr<ComponentBase> component) {
			if (component == nullptr) {
				return false;
			}
			
			// Check if component already exists.
			if (m_componentsDictionary.find(component->getID()) != m_componentsDictionary.end()) {
				return false;
			}

			// Find the correct insertion position to keep the vector sorted
			auto it = std::lower_bound(m_componentsRaw.begin(), m_componentsRaw.end(), component,
				[](const std::unique_ptr<ComponentBase>& a, const std::unique_ptr<ComponentBase>& b) {
					return a->getID() < b->getID();
				});

			m_componentsDictionary[component->getID()] = component.get();
			// Insert the script at the found position
			m_componentsRaw.insert(it, std::move(component));
		
			return true;
		}

		// NOTE: This is slow due to O(N) search.
		template<typename T>
		bool removeComponent() {
			Identifier id = Component<T>::getTypeID();

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
				if ((*it)->getID() == id) {
					m_componentsRaw.erase(it);
					return true;
				}
			}

			return false;
		}

	private:
		std::vector<std::unique_ptr<ComponentBase>> m_componentsRaw;
		std::unordered_map<Identifier, ComponentBase*> m_componentsDictionary;

	};

} // namespace GameObjects
} // namespace Engine

#endif 