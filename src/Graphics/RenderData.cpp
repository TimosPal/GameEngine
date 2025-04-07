#include "RenderData.h"

namespace Engine {

RenderData::RenderData(
	Mesh& mesh,
	ProgramImpl& program,
	TextureImpl& texture
)
	: mesh(mesh), program(program), texture(texture)
{
}

} // Engine