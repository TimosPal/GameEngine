#ifndef GAME_OBJECT_MANAGER_H
#define GAME_OBJECT_MANAGER_H

#include <vector>

#include "GameObject.h"
#include "Component.h"

namespace Engine {
namespace GameObjects {

class GameObjectManager
{
public:
	GameObjectManager();
	~GameObjectManager();

	GameObject& createGameObject(const GameObject& obj);

	template<typename... Component>
	void createGameObject(const Component&... components)
	{
		GameObject go(components...);
		go.start();
		m_gameObjects.emplace_back(std::move(go));
	}

	bool removeGameObject(const GameObject& gameObject);
	void upodateGameObjects();

private:
	std::vector<GameObject> m_gameObjects;
};

} // namespace GameObjects
} // namespace Engine

#endif 