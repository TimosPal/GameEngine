#ifndef RENDERER_H
#define RENDERER_H

#include "RenderData.h"

namespace Engine {

class IRenderer
{
public:
	virtual bool init() = 0;
	virtual void clear() = 0;
	virtual void submit(const RenderData& data) = 0;
	virtual void render() = 0;
};

} // Engine

#endif // !RENDERER_H
