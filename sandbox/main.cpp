#include <iostream>
#include <vector>
#include <memory>

#include <Core/GLFWWindow.h>

using namespace std;
using namespace Engine;

int main()
{
	std::unique_ptr<IWindow> window = std::make_unique<GLFWWindow>(640, 480, "MyApp");
	window->Init();

	return 0;
}