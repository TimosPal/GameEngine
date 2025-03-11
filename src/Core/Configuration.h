#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <string>

namespace Engine {

constexpr int default_width = 800;
constexpr int default_height = 600;
constexpr const char* default_title = "MyApp";

struct Configuration
{
	int width = default_width;
	int height = default_height;
	std::string title = default_title;
};

} // Engine

#endif // !CONFIGURATION_H
