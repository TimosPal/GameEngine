#ifndef RENDER_DATA_H
#define RENDER_DATA_H

#include <Graphics/IRenderer.h>
#include <Graphics/VertexData.h>

namespace Engine {

struct RenderData
{
	float r, g, b;
	float x, y, z;
	VertexData<float> vertexData;

	RenderData(float r, float g, float b, float x, float y, float z, VertexData<float> vertexData)
		: r(r), g(g), b(b), x(x), y(y), z(z), vertexData(vertexData) {
	}
};

} // Engine

#endif // !RENDER_DATA_H
