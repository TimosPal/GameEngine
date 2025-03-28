#ifndef OPENGL_RENDERER_H
#define OPENGL_RENDERER_H

#include <Graphics/IRenderer.h>
#include <Graphics/RenderData.h>

namespace Engine {

class OpenGLRenderer : public IRenderer
{
public:
	bool init() override;
	void clear() override;
	void submit(const RenderData& data) override;
	void render() override;
	
private:
	std::vector<RenderData> m_renderables;
};

} // Engine

#endif // !OPENGL_RENDERER_H
