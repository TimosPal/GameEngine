#include "RenderData.h"

namespace Engine {

RenderData::RenderData(
	const std::vector<VertexData<float>::Vertex>& vertices,
	const std::vector<unsigned int>& indices,
	ProgramImpl& program
)
	: vertices(vertices), program(program), indices(indices)
{
}

} // Engine