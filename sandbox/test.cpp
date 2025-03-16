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
	}
};

CREATE_APPLICATION(Test)