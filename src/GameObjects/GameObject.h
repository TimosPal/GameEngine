#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <unordered_map>
#include <algorithm>
#include <memory>
#include <set>

#include "./IComponent.h"

namespace Engine {
namespace GameObjects {

/*
This class is modeled arround OOP game objects meaning it's cache ineficient and has pointer indirections.
Components are owned by the gameObjects and are stored in a map. Leads to O(1) operations but slower iteration
due to data sparsity within the structure.
*/
class GameObject
{
public:
	enum class State {
		New, Dirty, Active
	};

	GameObject();
	GameObject(const GameObject& other);
	GameObject(GameObject&& other) noexcept;

	template<typename... ComponentDerived>
	GameObject(const ComponentDerived&... components)
		: m_id(IdentifierGenerator<GameObject>::getInstanceID())
	{
		(addComponent(components), ...);
	}

	~GameObject();

	State getState() const { return m_state; }
	void setState(const State& state) { m_state = state; }
	
	GameObject& operator=(const GameObject& other);
	bool operator==(const GameObject& other) const { return m_id == other.m_id; }

	template<typename ComponentDerived>
	bool addComponent()
	{
		return addComponent<ComponentDerived>(ComponentDerived());
	}

	template<typename ComponentDerived>
	bool addComponent(const ComponentDerived& component)
	{
		// Check if component already exists.
		int id = ComponentDerived::getTypeID();
		if (m_components.find(id) != m_components.end())
		{
			return false;
		}

		m_components[id] = std::make_shared<ComponentDerived>(component);
		m_componentTypes.insert(id); // Does not mean it will always be an active component.

		return true;
	}

	Identifier getInstanceID() const { return m_id; }

	template<typename ComponentDerived>
	std::shared_ptr<IComponentBase> getComponent()
	{
		Identifier id = ComponentDerived::getTypeID();
		return getComponent(id);
	}

	std::shared_ptr<IComponentBase> getComponent(Identifier id);

	template<typename ComponentDerived>
	bool removeComponent() 
	{
		Identifier id = ComponentDerived::getTypeID();

		// Remove from dictionary.
		auto it = m_components.find(id);
		if (it != m_components.end())
		{
			m_components.erase(it);
		} 
		else
		{
			return false;
		}

		return false;
	}

	static std::set<Identifier> getComponentTypes();

private:
	static std::set<Identifier> m_componentTypes;

	std::unordered_map<Identifier, std::shared_ptr<IComponentBase>> m_components;
	Identifier m_id;
	State m_state;
};

} // namespace GameObjects
} // namespace Engine

#endif 