#include <iostream>
#include <vector>
#include <memory>

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
	Engine::GameObjects::GameObjectManager gm;
	auto t1 = std::make_unique<Transform>(Transform());
	Engine::GameObjects::GameObject go(t1);

	go.update();

	return 0;
}