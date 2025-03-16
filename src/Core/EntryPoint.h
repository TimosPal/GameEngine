#include <iostream>
#include <vector>
#include <memory>

#include "Application.h"
#include <Utility/Logger.h>

#define CREATE_APPLICATION(AppClass) \
    std::unique_ptr<Engine::Application> createApplication() { return std::make_unique<AppClass>(); }

extern std::unique_ptr<Engine::Application> createApplication();

using namespace std;
using namespace Engine;

int main()
{
	auto app = createApplication();
	app->init();
	app->start();
	app->run();
	app->terminate();

	return 0;
}