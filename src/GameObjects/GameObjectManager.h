#ifndef GAME_OBJECT_MANAGER_H
#define GAME_OBJECT_MANAGER_H

#include <vector>

#include "GameObject.h"
#include "IComponent.h"

namespace Engine {
namespace GameObjects {

class GameObjectManager
{
public:
	GameObjectManager();
	~GameObjectManager();

	GameObject& createGameObject(const GameObject& obj);

	template<typename... ComponentDerived>
	GameObject& createGameObject(const ComponentDerived&... components)
	{
		return createGameObject(GameObject(components...));
	}

	bool removeGameObject(const GameObject& gameObject);

	void startGameObjects();
	void updateGameObjects();

private:
	std::vector<std::shared_ptr<GameObject>> m_gameObjects;

	std::vector<GameObject*> m_newGameObjects;
	std::vector<GameObject*> m_dirtyGameObjects;
	std::vector<GameObject*> m_activeGameObjects;
};

} // namespace GameObjects
} // namespace Engine

#endif 