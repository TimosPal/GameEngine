#include <Core/EntryPoint.h>
#include <iostream>

Configuration config{ 800, 600, "MyAppTest" };

class Test : public Application
{
public:
	Test() : Application(config) {}

	void start() override
	{
	}

};

CREATE_APPLICATION(Test)