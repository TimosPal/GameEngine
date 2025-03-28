#include <Core/EntryPoint.h>
#include <iostream>

#include <Core/World.h>
#include <GameObjects/EngineComponents/SpriteComponent.h>

Configuration config{ 800, 600, "MyAppTest" };

class Test : public Application
{
public:
	Test() : Application(config) {}

	void start() override
	{
		GameObjects::GameObject newGo;
		auto& go = Application::getWorld().getGOManager().createGameObject(newGo);
		GameObjects::SpriteComponent spriteComponent(0.7f, 0.3f, 0.8f);
		go.addComponent<GameObjects::SpriteComponent>(spriteComponent);
	}

};

CREATE_APPLICATION(Test)