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
	std::vector<VertexData<float>::Vertex> vertices; // TODO: Expensive copy
	std::vector<unsigned int> indices;
	ProgramImpl& program;

	RenderData(
		const std::vector<VertexData<float>::Vertex>& vertices,
		const std::vector<unsigned int>& indices,
		ProgramImpl& program
	)
		: vertices(vertices), program(program), indices(indices)
	{}
};

} // Engine

#endif // !RENDER_DATA_H
