#ifndef RENDER_DATA_H
#define RENDER_DATA_H

#include <Graphics/IRenderer.h>
#include <Graphics/VertexData.h>

namespace Engine {

struct RenderData
{
	VertexData<float> vertexData;

	RenderData(
		VertexData<float> vertexData
	)
		: 
		vertexData(vertexData)
	{
	}
};

} // Engine

#endif // !RENDER_DATA_H
