#ifndef LAYER_STACK_HPP
#define LAYER_STACK_HPP

#include "core/pch.hpp"
#include "layers/Layer.hpp"

namespace Engine {

// Overlays are above layers, order is enforced.
class LayerStack {
public:
	LayerStack() : m_overlaysIndex(0) {}

	void pushLayer(std::unique_ptr<Layer> layer);
	void pushOverlay(std::unique_ptr<Layer> overlay);
	void popLayer(Layer* layer);
	void popOverlay(Layer* overlay);

	void dispatchEventToLayers(Event& event);
	void onUpdate(float deltaTime);

private:
	std::vector<std::unique_ptr<Layer>> m_layers;
	uint32_t m_overlaysIndex;
};

} // Engine

#endif // LAYER_STACK_HPP
