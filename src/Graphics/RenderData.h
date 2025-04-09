#ifndef RENDER_DATA_H
#define RENDER_DATA_H

#include <Graphics/Mesh.h>
#include <Graphics/GraphicsIncludes.h>

#include "Attributes.h"

namespace Engine {

struct RenderData
{
	Mesh& mesh;
	
	ProgramImpl& program;
	TextureImpl& texture;

	RenderData(
		Mesh& mesh,
		ProgramImpl& program,
		TextureImpl& texture
	);
};

} // Engine

#endif // !RENDER_DATA_H
