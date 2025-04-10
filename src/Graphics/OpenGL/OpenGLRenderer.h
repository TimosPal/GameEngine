#ifndef OPENGL_RENDERER_H
#define OPENGL_RENDERER_H

#include <Graphics/IRenderer.h>
#include <Graphics/RenderData.h>

#include "VBO.h"
#include "EBO.h"
#include "Drawable.h"

namespace Engine {

class OpenGLRenderer : public IRenderer
{
public:
	bool init() override;
	void clear() override;
	void submit(RenderData&& data) override;
	void render() override;
	
private:
	std::vector<RenderData> m_renderables;

	using VertexBatch = std::vector<float>;
	using IndexBatch = std::vector<unsigned int>;
	using Buffer = std::tuple<VertexBatch, VBO, IndexBatch, EBO, Program*>;
	std::unordered_map<AttributeInfo::AttributeProgramMask, Buffer> m_buffers;

	void batchRenderables();
	void renderBatches();
};

} // Engine

#endif // !OPENGL_RENDERER_H
