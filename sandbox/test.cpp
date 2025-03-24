#include <Core/EntryPoint.h>
#include <iostream>

#include <Resources/ResourceManager.h>
#include <Resources/ShaderResource.h>

Configuration config{ 800, 600, "MyAppTest" };

class Test : public Application
{
public:
	Test() : Application(config) {}

	void start() override
	{
		auto t = ResourceManager<ShaderResource>::getInstance().load("test", "./assets/test.p");
		LOG_INFO("{}", t.getString());
	}

};

CREATE_APPLICATION(Test)