#ifndef GLFWWINDOW_H
#define GLFWWINDOW_H

#include "IWindow.h"

#include <GLFW/glfw3.h>

#include <string>

namespace Engine {

class GLFWWindow : public IWindow {
public:
	GLFWWindow(int width, int height, const std::string& title);

	bool init() override;
	void pollEvents() override;
	bool shouldClose() override;
	void swapBuffers() override;
	void terminate() override;

private:
	GLFWwindow* m_window;

};

} // Engine

#endif