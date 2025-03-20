#ifndef GAME_H
#define GAME_H

#include <memory>
#include <Window/IWindow.h>

#include "Configuration.h"

#include <Core/World.h>
#include <Events/EventQueue.h>
#include <Events/WindowResizeEvent.h>
#include <Utility/Logger.h>

#include <Graphics/IRenderer.h>

#if GRAPHICS_API == API_OPENGL
	#include <Graphics/OpenGL/OpenGLRenderer.h>	
	using RendererAPI = Engine::OpenGLRenderer;
#else
	#error Invalid graphics API
#endif

#if WINDOW_LIBRARY == WINDOW_GLFW
	#include <Window/GLFWWindow.h>
	using WindowLib = Engine::GLFWWindow;
#else
	#error Invalid window library
#endif

namespace Engine {

class Application
{
public:
	Application(const Configuration& config);
	~Application();

	static Application* getInstance() { return m_instance; }

	World& getWorld() { return m_world; }

	void init();
	void run();
	void terminate();

	template<typename EventType>
	void addEvent(const EventType& event) // TODO: could be made into a switch if ids were constexpr
	{
		Identifier id = event.getInstanceID();
		if (id == WindowResizeEvent::getTypeID())
		{
			m_systemQueue.add(event);
		}
		else
		{
			LOG_WARNING("Event ({}) ignored, custom events not currently supported", event.toString());
			//m_generalQueue.add(event);
		}
	}

	template<typename EventType>
	void subscribe(EventQueue::Callback<EventType> cb) // TODO: could be made into a switch if ids were constexpr
	{
		Identifier id = EventType::getTypeID();
		if (id == WindowResizeEvent::getTypeID())
		{
			m_systemQueue.subscribe<EventType>(cb);
		}
		else
		{
			m_generalQueue.subscribe<EventType>(cb);
		}
	}

	// Use this method for custom app startup configurations.
	virtual void start() {}

private:
	static Application* m_instance;

	Configuration m_config;
	WindowLib m_window;

	RendererAPI m_renderer;

	EventQueue m_systemQueue;
	EventQueue m_generalQueue;

	World m_world;
};

} // Engine

#endif 