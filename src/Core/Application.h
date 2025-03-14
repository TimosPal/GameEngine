#ifndef GAME_H
#define GAME_H

#include <memory>
#include <Window/IWindow.h>

#include "Configuration.h"

namespace Engine {


class Application
{
public:
	Application(const Configuration& config);
	~Application();

	void Init();
	void Run();
	void Terminate();

private:
	Configuration m_config;
	std::unique_ptr<IWindow> m_window;
};

} // Engine

#endif 