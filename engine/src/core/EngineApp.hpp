#ifndef ENGINE_APP_HPP
#define ENGINE_APP_HPP

#include "core/AppConfig.hpp"
#include "events/Event.hpp"
#include "events/EventQueue.hpp"
#include "events/EventDispatcher.hpp"
#include "layers/LayerStack.hpp"
#include "window/Window.hpp"
#include "renderer/Renderer2D.hpp"
#include "resources/SystemResourceHub.hpp"
#include "resources/AssetsManager.hpp"
#include "scenes/SceneManager.hpp"

namespace Engine {

class EngineApp {
public:
	static EngineApp* getInstance() { return s_instance; }

	EngineApp();

	void init();
	void run();
	void terminate();
	
	// * =============================== *
	// * User side setup implementation. *
	// * =============================== *
	virtual void setup() = 0;
	// Override if needing custom config.
	virtual AppConfig config() { return AppConfig(); }

	void stop() { m_isRunning = false; }

	void pushEvent(std::unique_ptr<Event> event);

	void pushLayer(std::unique_ptr<Layer> layer);
	void pushOverlay(std::unique_ptr<Layer> layer);

	SceneManager& getSceneManager() { return m_sceneManager; }
	AssetsManager& getAssetsManager() { return m_assetsManager; }

private:
	static EngineApp* s_instance;

	// Resources
	SystemResourceHub m_resourceHub;
	AssetsManager m_assetsManager;

	std::unique_ptr<Window> m_window;
	std::shared_ptr<Renderer2D> m_renderer2D;

	// Layer ID -> EventDispatcher.
	EventQueue m_eventQueue;
	LayerStack m_layers;

	SceneManager m_sceneManager;

	bool m_isRunning;
};

} // Engine

#endif // !ENGINE_APP_HPP
