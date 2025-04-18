#ifndef APPLICATION_H
#define APPLICATION_H

#include <Window/IWindow.h>
#include <Core/Configuration.h>
#include <Core/World.h>
#include <Utility/Logger.h>

#include <Events/EventQueue.h>
#include <Events/FrameBufferResizeEvent.h>

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
		if (id == FrameBufferResizeEvent::getTypeID())
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
		if (id == FrameBufferResizeEvent::getTypeID())
		{
			m_systemQueue.subscribe<EventType>(cb);
		}
		else
		{
			m_generalQueue.subscribe<EventType>(cb);
		}
	}

	RendererAPI& getRenderer() { return m_renderer; }

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

#endif //!APPLICATION_H