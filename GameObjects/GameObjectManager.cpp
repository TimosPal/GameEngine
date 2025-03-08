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

void GameObjectManager::addGameObject(std::vector<std::unique_ptr<ComponentBase>>&& components)
{
	m_gameObjects.emplace_back(std::move(components));
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

void GameObjectManager::upodateGameObjects()
{
	// Udapte all game objects
	for (auto& gameObject : m_gameObjects)
	{
		gameObject.update();
	}
}

}
}