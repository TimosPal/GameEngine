#ifndef RENDER_DATA_H
#define RENDER_DATA_H

#include <Graphics/VertexData.h>

#if GRAPHICS_API == API_OPENGL
	#include "OpenGL/Program.h"
	using ProgramImpl = Engine::Program;
#else
	#error Invalid graphics API
#endif

namespace Engine {

struct RenderData
{
	VertexData<float> vertexData;
	ProgramImpl& program;

	RenderData(VertexData<float> vertexData, ProgramImpl& program)
		: vertexData(vertexData), program(program)
	{
	}
};

} // Engine

#endif // !RENDER_DATA_H
