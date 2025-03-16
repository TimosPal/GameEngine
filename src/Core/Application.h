#ifndef GAME_H
#define GAME_H

#include <memory>
#include <Window/IWindow.h>

#include "Configuration.h"

#include <Core/World.h>

namespace Engine {

class Application
{
public:
	Application(const Configuration& config);
	~Application();

	World& getWorld() { return m_world; }

	void init();
	void run();
	void terminate();

	// Use this method for custom app startup configurations.
	virtual void start() {}

private:
	Configuration m_config;
	std::unique_ptr<IWindow> m_window;

	World m_world;
};

} // Engine

#endif 