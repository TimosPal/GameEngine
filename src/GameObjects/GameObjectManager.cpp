#include <algorithm>

#include "GameObjectManager.h"
#include <Utility/Assertions.h>

namespace Engine {
namespace GameObjects {

GameObjectManager::GameObjectManager() {}

GameObjectManager::~GameObjectManager() {}

GameObject& GameObjectManager::createGameObject(const GameObject& obj)
{
	m_gameObjects.emplace_back(std::make_shared<GameObject>(obj));
	GameObject* newObj = m_gameObjects.back().get();

	m_newGameObjects.emplace_back(newObj);

	return *newObj;
}

bool GameObjectManager::removeGameObject(const GameObject& gameObject)
{
	int success = 0;

	// Define a helper lambda to remove the object from a given container
	auto removeFromContainer = [&gameObject, &success](auto& container) {
		auto it = std::find_if(container.begin(), container.end(),
			[&gameObject](const auto& obj) { return *obj == gameObject; });

		if (it != container.end())
		{
			std::iter_swap(it, container.end() - 1);
			container.pop_back();
			success++;
		}
		};

	// Check the object's state and remove it from relevant containers
	switch (gameObject.getState())
	{
	case GameObject::State::Active:
		removeFromContainer(m_activeGameObjects);
		break;
	case GameObject::State::New:
		removeFromContainer(m_newGameObjects);
		break;
	case GameObject::State::Dirty:
		removeFromContainer(m_dirtyGameObjects);
		break;
	default:
		break;
	}
	
	removeFromContainer(m_gameObjects);

	ASSERT(!success || success == 2, "Invalid removal");
	return success > 0;
}

void GameObjectManager::startGameObjects()
{
	// Ensure correct excecution even if start adds new GOs.
	for (GameObject* gameObject : m_newGameObjects)
	{
		m_dirtyGameObjects.emplace_back(gameObject);
		gameObject->setState(GameObject::State::Dirty);
	}
	m_newGameObjects.clear();

	// Init all game objects
	for (Identifier id : GameObject::getComponentTypes())
	{
		for (GameObject* gameObject : m_dirtyGameObjects)
		{
			// TODO: O(N^2) due to component lookup. (SLOW!) 
			auto comp = gameObject->getComponent(id);
			if (comp != nullptr)
			{
				comp->start();
			}
		}
	}

	for (GameObject* gameObject : m_dirtyGameObjects)
	{
		m_activeGameObjects.emplace_back(gameObject);
		gameObject->setState(GameObject::State::Active);
	}
	m_dirtyGameObjects.clear();
}

void GameObjectManager::updateGameObjects()
{
	// Udapte all game objects
	for (Identifier id : GameObject::getComponentTypes())
	{
		for (GameObject* gameObject : m_activeGameObjects)
		{
			// TODO: O(N^2) due to component lookup. (SLOW!) 
			auto comp = gameObject->getComponent(id);
			if (comp != nullptr)
			{
				comp->update();
			}
		}
	}
}

}
}