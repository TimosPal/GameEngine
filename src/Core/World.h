#ifndef WORLD_H
#define WORLD_H

#include <GameObjects/GameObjectManager.h>

namespace Engine {

class World
{
public:
	// TODO: refactor later
	GameObjects::GameObjectManager& getGOManager()
	{
		return m_GOManager;
	}

	void update()
	{
		m_GOManager.startGameObjects();
		m_GOManager.updateGameObjects();
	}

private:
	GameObjects::GameObjectManager m_GOManager;
};


} // Engine

#endif // !WORLD_H
