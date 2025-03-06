#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <unordered_map>
#include <memory>

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
	GameObject();
	GameObject(std::vector<std::unique_ptr<ComponentBase>>&& components);
	~GameObject();

	void update();

	// NOTE: This is slow due to sorting in O(N) time.
	bool addComponent(std::unique_ptr<ComponentBase> component);

	template<typename T>
	ComponentBase* getComponent() {
		Identifier id = Component<T>::getTypeID();
			
		auto it = m_componentsDictionary.find(id);
		if (it != m_componentsDictionary.end()) {
			return it->second;
		}

		return nullptr;
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