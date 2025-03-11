#include "Application.h"

#include <memory>
#include <Core/GLFWWindow.h>

namespace Engine {

Application::Application(const Configuration& config)
	: m_config(config)
{}

Application::~Application() {}

void Application::Init()
{
	std::unique_ptr<IWindow> window = std::make_unique<GLFWWindow>(m_config.width, m_config.height, m_config.title);
	window->Init();
}

} // Engine