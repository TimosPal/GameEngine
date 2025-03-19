#include "Application.h"

#include <memory>

#include <Utility/Logger.h>
#include <Utility/Assertions.h>
#include <Input/InputManager.h>

#if GRAPHICS_API == API_OPENGL
	#include <Graphics/OpenGL/OpenGLRenderer.h>
	using RendererAPI = Engine::OpenGLRenderer;
#else
	STATIC_ASSERT_FALSE("Invalid graphics API");
#endif

#if WINDOW_LIBRARY == WINDOW_LIBRARY
#include <Window/GLFWWindow.h>
	using WindowLib = Engine::GLFWWindow;
#else
	STATIC_ASSERT_FALSE("Invalid window library");
#endif

namespace Engine {

Application* Application::m_instance = nullptr;

Application::Application(const Configuration& config)
	: m_config(config)
{}

Application::~Application() {}

void Application::init()
{
	m_instance = this;
	
	m_window = std::make_unique<WindowLib>(m_config.width, m_config.height, m_config.title);
	m_renderer = std::make_unique<RendererAPI>();

	ASSERT(m_window->init());
	ASSERT(m_renderer->init());
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