#ifndef SYSTEM_LAYER_HPP
#define SYSTEM_LAYER_HPP

#include "core/pch.hpp"
#include "layers/Layer.hpp"

namespace Engine {

// Layer for handling system level events (eg window callbacks)
class SystemLayer : public Layer {
public:
	SystemLayer(std::function<void()> stopAppCallback);

	void onAttach() override;

	static std::string getName() { return "SystemLayer"; }

private:
	std::function<void()> m_stopAppCallback;
};
} // Engine

#endif // !SYSTEM_LAYER_HPP
