#ifndef RENDERER_H
#define RENDERER_H

namespace Engine {

class IRenderer
{
public:
	virtual bool init() = 0;
	virtual void clear() = 0;

private:

};

} // Engine

#endif // !RENDERER_H
