#include "layers/types/SystemLayer.hpp"

#include "events/types/WindowCloseEvent.hpp"
#include "events/types/WindowResizeEvent.hpp"
#include "events/EventCallback.hpp"

namespace Engine {

SystemLayer::SystemLayer(std::function<void()> stopAppCallback)
	: Layer(getName()),
	m_stopAppCallback(stopAppCallback)
{}

void SystemLayer::onAttach()
{
	// Close window
	EventCallback<WindowCloseEvent> windowCloseEventCallback([&](WindowCloseEvent& event) {
		event.consume();
		m_stopAppCallback();
	});
	getEventDispatcher().subscribe<WindowCloseEvent>(windowCloseEventCallback);
}

} // Engine