#include <Core/EntryPoint.h>
#include <iostream>

#include <Input/InputManager.h>
#include <Utility/Logger.h>
#include <GameObjects/IComponent.h>

Configuration config{ 800, 600, "MyAppTest" };

class PlayerComponent : public GameObjects::IComponent<PlayerComponent>
{
	virtual void start() 
	{
		LOG_INFO("Init Player");
	};

	virtual void update() 
	{
		auto action = InputManager::getInstance().getAction("Bloop");
		if (InputManager::getInstance().isActionTriggered(action)) {
			LOG_INFO("pressed");
			
			double x = InputManager::getInstance().getMousePosX();
			double y = InputManager::getInstance().getMousePosY();
			LOG_INFO("{} {}", x, y);
		}

		bool aKey = InputManager::getInstance().isKeyPressed(Key::A);
		bool sKey = InputManager::getInstance().isKeyPressed(Key::S);
		if (aKey && sKey) {
			LOG_INFO("COMBO");
		}
	};
};

class Test : public Application
{
public:
	Test() : Application(config) {}

	void start() override
	{
		InputManager::getInstance().registerAction(Action("Bloop", Key::LeftClick, KeyState::Type::Pressed));

		PlayerComponent playerComp;
		getWorld().getGOManager().createGameObject(playerComp);
	}

};

CREATE_APPLICATION(Test)