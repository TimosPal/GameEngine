#include "Application.h"

#include <memory>
#include <Window/GLFWWindow.h>

#include <Utility/Logger.h>

namespace Engine {

Application::Application(const Configuration& config)
	: m_config(config)
{}

Application::~Application() {}

void Application::Init()
{
	m_window = std::make_unique<GLFWWindow>(m_config.width, m_config.height, m_config.title);
	m_window->Init();
}

void Application::Run()
{
	while (!m_window->ShouldClose())
	{

		m_window->PollEvents();
	}
}

void Application::Terminate()
{
	m_window->Terminate();
}

} // Engine