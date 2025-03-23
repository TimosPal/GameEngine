#include <algorithm>

#include "GameObjectManager.h"

namespace Engine {
namespace GameObjects {

GameObjectManager::GameObjectManager()
{
}

GameObjectManager::~GameObjectManager()
{
}

GameObject& GameObjectManager::createGameObject(const GameObject& obj)
{
	m_gameObjects.emplace_back(obj);
	return m_gameObjects.back();
}

bool GameObjectManager::removeGameObject(const GameObject& gameObject)
{
	// Swap last element with current position then pop_back
	auto it = std::find(m_gameObjects.begin(), m_gameObjects.end(), gameObject);
	if (it != m_gameObjects.end())
	{
		std::iter_swap(it, m_gameObjects.end() - 1);
		m_gameObjects.pop_back();
		return true;
	} 

	return false;
}

void GameObjectManager::updateGameObjects()
{
	// Udapte all game objects
	for (Identifier id : GameObject::getComponentTypes())
	{
		for (auto& gameObject : m_gameObjects)
		{
			// TODO: O(N^2) due to component lookup. (SLOW!) 
			auto comp = gameObject.getComponent(id);
			if (comp != nullptr)
			{
				comp->update();
			}
		}
	}
}

}
}