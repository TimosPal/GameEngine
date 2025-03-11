#include <iostream>
#include <vector>
#include <memory>

#include "Application.h"

#define CREATE_APPLICATION(AppClass, Config) \
    Engine::Application* createApplication() { return new AppClass(Config); }

extern Engine::Application* createApplication();

using namespace std;
using namespace Engine;

int main()
{
	Engine::Application* app = createApplication();
	app->Init();
	delete app;

	return 0;
}