#include <Core/EntryPoint.h>
#include <iostream>

Configuration config{ 800, 600, "MyAppTest" };

class Test : public Application
{
};

CREATE_APPLICATION(Test, config)