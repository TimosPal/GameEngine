#ifndef GAME_OBJECT_MANAGER_H
#define GAME_OBJECT_MANAGER_H

#include <vector>

#include "GameObject.h"

namespace Engine {
namespace GameObjects {

class GameObjectManager
{
public:
	GameObjectManager();
	~GameObjectManager();

	void addGameObject(GameObject&& gameObject);
	bool removeGameObject(const GameObject& gameObject);
	void upodateGameObjects();

private:
	std::vector<GameObject> m_gameObjects;
};

} // namespace GameObjects
} // namespace Engine

#endif 