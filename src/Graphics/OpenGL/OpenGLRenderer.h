#ifndef OPENGL_RENDERER_H
#define OPENGL_RENDERER_H

#include <Graphics/IRenderer.h>

namespace Engine {

class OpenGLRenderer : public IRenderer
{
public:
	bool init() override;
	void clear() override;
	
	void createRenderable();
private:

};

} // Engine

#endif // !OPENGL_RENDERER_H
