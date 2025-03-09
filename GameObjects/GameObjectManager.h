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

	template<typename... component>
	void addGameObject(const component&... components)
	{
		GameObject go(std::make_unique<component>(components)...);
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