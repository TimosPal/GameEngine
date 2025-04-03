#ifndef GRAPHICS_INCLUDES_H
#define GRAPHICS_INCLUDES_H

// Used for centralised aliases and includes of proper derived API classes.
// Main renderer not included as it causes forward decleration issues.
// Should be seperately implemented in configuration class
#if GRAPHICS_API == API_OPENGL
	#include <Graphics/OpenGL/Program.h>
	using ProgramImpl = Engine::Program;

	#include "OpenGL/Shader.h"
	using ShaderImpl = Engine::Shader;
#else
	#error Invalid graphics API
#endif

#endif // !GRAPHICS_INCLUDES_H