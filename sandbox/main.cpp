#include <iostream>
#include <vector>
#include <memory>

#include <GameObjects/GameObjectManager.h>

using namespace std;
using namespace Engine;

class Transform : public Engine::GameObjects::Component<Transform>
{
public:
	Transform() = default;

	void start() override 
	{
		std::cout << "Init " << getInstanceID() << std::endl;
	}

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

	void start() override
	{
		std::cout << "Init " << getInstanceID() << std::endl;
	}

	// Inherited via Component
	void update() override
	{
		std::cout << getInstanceID() << std::endl;
	}
};

static void test() {
	Engine::GameObjects::GameObjectManager gm;

	Transform t1;
	Transform2 t2;

	gm.createGameObject(t1, t2);

	Engine::GameObjects::GameObject g1(t1);
	gm.createGameObject(g1);

	gm.upodateGameObjects();
}

int main()
{
	test();

	return 0;
}