#ifndef IRESOURCE_H
#define IRESOURCE_H

namespace Engine {

struct IResource{
public:
	virtual bool init() = 0;
	virtual void destroy() = 0;
};

} // Engine

#endif // !IRESOURCE_H
