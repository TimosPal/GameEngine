#ifndef RENDER_DATA_H
#define RENDER_DATA_H

#include <Graphics/VertexData.h>
#include <Graphics/GraphicsIncludes.h>

namespace Engine {

struct RenderData
{
	std::vector<VertexData<float>::Vertex> vertices; // TODO: Expensive copy
	std::vector<unsigned int> indices;
	ProgramImpl& program;
	TextureImpl& texture;

	RenderData(
		const std::vector<VertexData<float>::Vertex>& vertices,
		const std::vector<unsigned int>& indices,
		ProgramImpl& program,
		TextureImpl& texture
	);
};

} // Engine

#endif // !RENDER_DATA_H
