#ifndef GLFWWINDOW_H
#define GLFWWINDOW_H

#include "IWindow.h"

#include <string>

namespace Engine {

class GLFWWindow : public IWindow {
public:
	GLFWWindow(int width, int height, const std::string& title);

	bool Init() override;
};

} // Engine

#endif