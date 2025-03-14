#include <iostream>
#include <vector>
#include <memory>

#include "Application.h"

#define CREATE_APPLICATION(AppClass, Config) \
    std::unique_ptr<Engine::Application> createApplication() { return std::make_unique<AppClass>(Config); }

extern std::unique_ptr<Engine::Application> createApplication();

using namespace std;
using namespace Engine;

int main()
{
	auto app = createApplication();
	app->Init();
	app->Run();
	app->Terminate();

	return 0;
}