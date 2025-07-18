#ifndef EVENT_QUEUE_HPP
#define EVENT_QUEUE_HPP

#include "core/pch.hpp"
#include "events/Event.hpp"
#include "events/EventDispatcher.hpp"
#include "layers/LayerStack.hpp"

namespace Engine {

class EventQueue {
public:
	void addEventHandler(std::function<void(Event&)> handler);
	void push(std::unique_ptr<Event> event);
	void dispatchAll(LayerStack& layers);
private:
	std::queue<std::unique_ptr<Event>> m_events;

	std::vector<std::function<void(Event&)>> m_eventHandlers;
};

} // Engine

#endif // !EVENT_QUEUE_HPP