#include "Application.h"

#include <memory>
#include <Window/GLFWWindow.h>

#include <Utility/Logger.h>
#include <Input/InputManager.h>

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
		InputManager::getInstance().resetReleasedKeys();
		InputManager::getInstance().setHoldKeys();
		m_window->PollEvents();

		if (InputManager::getInstance().isKeyPressed(Key::B))
			LOG_INFO("pressed");
		if (InputManager::getInstance().isKeyDown(Key::B))
			LOG_INFO("hold");
		if (InputManager::getInstance().isKeyReleased(Key::B))
			LOG_INFO("release");
	}
}

void Application::Terminate()
{
	m_window->Terminate();
}

} // Engine