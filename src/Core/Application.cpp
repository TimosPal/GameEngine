#include "Application.h"

#include <memory>
#include <Window/GLFWWindow.h>

#include <Utility/Logger.h>
#include <Input/InputManager.h>

namespace Engine {

Application* Application::m_instance = nullptr;

Application::Application(const Configuration& config)
	: m_config(config)
{}

Application::~Application() {}

void Application::init()
{
	m_instance = this;

	m_window = std::make_unique<GLFWWindow>(m_config.width, m_config.height, m_config.title);
	m_window->init();
}

void Application::run()
{
	while (!m_window->ShouldClose())
	{
		InputManager::getInstance().update();
		m_window->PollEvents();

		m_systemQueue.dispatch();
		m_generalQueue.dispatch();

		m_world.update();
	}
}

void Application::terminate()
{
	m_window->terminate();
}

} // Engine