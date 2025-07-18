#include "layers/types/GraphicsLayer.hpp"

#include "ecs/types/SpriteRenderSystem.hpp"
#include "ecs/types/TilemapRenderSystem.hpp"
#include "renderer/Renderer2D.hpp"
#include "events/types/WindowResizeEvent.hpp"

namespace Engine
{

GraphicsLayer::GraphicsLayer(std::shared_ptr<Renderer2D> renderer2D)
	: Layer(getName()),
	m_renderer2D(renderer2D)
{}

void GraphicsLayer::onAttach()
{
	// Resize window
	EventCallback<WindowResizeEvent> windowResizeEventCallback([&](WindowResizeEvent& event) {
		event.consume();
		m_renderer2D->setViewportSize(event.getWidth(), event.getHeight());
	});
	getEventDispatcher().subscribe<WindowResizeEvent>(windowResizeEventCallback);

	getSystemManager().addSystem(std::make_unique<SpriteRenderSystem>(m_renderer2D));
	getSystemManager().addSystem(std::make_unique<TilemapRenderSystem>(m_renderer2D));
}

} // Engine