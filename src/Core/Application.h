#ifndef GAME_H
#define GAME_H

#include "Configuration.h"

namespace Engine {


class Application
{
public:
	Application(const Configuration& config);
	~Application();

	void Init();

private:
	Configuration m_config;
};

} // Engine

#endif 