#include "Application.h"

#include <memory>

#include <Utility/Assertions.h>
#include <Input/InputManager.h>

#include <Resources/ResourceManager.h>
#include <Resources/InternalResource.h>
#include <Resources/SourceCodeResource.h>

#include <Graphics/GraphicsIncludes.h>

namespace Engine {

Application* Application::m_instance = nullptr;

Application::Application(const Configuration& config)
	: m_config(config), m_window(m_config.width, m_config.height, m_config.title)
{}

Application::~Application() {}

void Application::init()
{
	m_instance = this;

	ASSERT(m_window.init());
	ASSERT(m_renderer.init());
}

void Application::run()
{
	while (!m_window.shouldClose())
	{
		InputManager::getInstance().update();
		m_window.pollEvents();

		m_systemQueue.dispatch();
		m_generalQueue.dispatch();

		m_world.update();

		m_renderer.clear();
		m_renderer.render();
		m_window.swapBuffers();
	}
}

void Application::terminate()
{
	ResourceManager<SourceCodeResource>::getInstance().cleanup("Source codes");
	ResourceManager<InternalResource<ProgramImpl>>::getInstance().cleanup("Programs");
	
	// Window terminated last so the current API context is active for proper cleanup
	m_window.terminate();
}

} // Engine