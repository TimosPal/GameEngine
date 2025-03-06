#include <iostream>
#include <vector>
#include <memory> // Include memory header for std::unique_ptr

#include "GameObjects/GameObject.h"

using namespace std;
using namespace Engine;

class Transform : public Engine::GameObjects::Component<Transform>
{
public:
	Transform() = default;

	// Inherited via Component
	void update() override
	{
		std::cout << getID() << std::endl;
	}
};

class Transform2 : public Engine::GameObjects::Component<Transform2>
{
public:
	Transform2() = default;

	// Inherited via Component
	void update() override
	{
		std::cout << getID() << std::endl;
	}
};

int main()
{
	{
		std::vector<std::unique_ptr<Engine::GameObjects::ComponentBase>> components;
		components.emplace_back(std::make_unique<Transform>());
		components.emplace_back(std::make_unique<Transform2>());

		GameObjects::GameObject obj(std::move(components));
		obj.update();


		obj.removeComponent<Transform>();
		obj.addComponent(std::make_unique<Transform>());

		obj.update();

		obj.removeComponent<Transform>();

		if (obj.getComponent<Transform>() == nullptr) {
			std::cout << "Component not found" << std::endl;
		}
	}

	return 0;
}
