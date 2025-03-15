#include <Core/EntryPoint.h>
#include <iostream>

#include <Input/InputManager.h>
#include <Utility/Logger.h>

Configuration config{ 800, 600, "MyAppTest" };

class Test : public Application
{
public:
	Test() : Application(config) {}

	void Start() override
	{
		InputManager::registerAction(Action("MoveUP", Key::Up));
		InputManager::registerAction(Action("MoveDown", Key::Down));
		InputManager::registerAction(Action("MoveLeft", Key::Left));
		InputManager::registerAction(Action("MoveRight", Key::Right));

		for (const auto& i : InputManager::getActions())
		{
			LOG_INFO("{} -> {}", i.name, i.keyCodeID);
		}
	}
};

CREATE_APPLICATION(Test)