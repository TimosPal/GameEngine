#ifndef EVENT_QUEUE_H
#define EVENT_QUEUE_H

#include "IEvent.h"

#include <memory>
#include <unordered_map>
#include <queue>
#include <functional>

namespace Engine {

class EventQueue {
public:
	template <typename EventType>
	using Callback = std::function<void(const EventType&)>;

	template<typename EventType>
	void add(const EventType& event)
	{
		m_events.push(event.clone());
	}

	template<typename EventType>
	void subscribe(Callback<EventType> cb)
	{
		// Accepts callbacks of derived types
		// Converts to wrapper callbacks with polymorphic type CallbackBase
		Identifier id = EventType::getTypeID();
		auto wrapper = [cb](const IEventBase& e) {
			cb(static_cast<const EventType&>(e));
		};
		m_listeners[id].push_back(wrapper);
	}

	void dispatch()
	{
		while (!m_events.empty()) {
			std::unique_ptr<IEventBase> event = std::move(m_events.front());
			m_events.pop();

			Identifier id = event->getInstanceID();
			if (m_listeners.find(id) != m_listeners.end()) {
				for (auto& callback : m_listeners[id]) {
					callback(*event);
				}
			}
		}
	}

private:
	std::queue<std::unique_ptr<IEventBase>> m_events;
	std::unordered_map<Identifier, std::vector<Callback<IEventBase>>> m_listeners;
};

} // Engine

#endif // !EVENT_QUEUE_H
