#include <iostream>
#include <vector>
#include <memory> // Include memory header for std::unique_ptr

#include "GameObjects/GameObjectManager.h"

using namespace std;
using namespace Engine;

class Transform : public Engine::GameObjects::Component<Transform>
{
public:
	Transform() = default;

	// Inherited via Component
	void update() override
	{
		std::cout << getInstanceID() << std::endl;
	}
};

class Transform2 : public Engine::GameObjects::Component<Transform2>
{
public:
	Transform2() = default;

	// Inherited via Component
	void update() override
	{
		std::cout << getInstanceID() << std::endl;
	}
};

int main()
{
	GameObjects::GameObjectManager manager;
	
	std::vector<std::unique_ptr<Engine::GameObjects::ComponentBase>> components;
	components.emplace_back(std::make_unique<Transform>());
	components.emplace_back(std::make_unique<Transform2>());
	manager.addGameObject(std::move(components));

	return 0;
}