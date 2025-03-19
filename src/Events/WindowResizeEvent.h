#ifndef WINDOW_RESIZE_EVENT_H
#define WINDOW_RESIZE_EVENT_H

#include "IEvent.h"

namespace Engine {

struct WindowResizeEvent : public IEvent<WindowResizeEvent> {
	WindowResizeEvent(int width, int height) : width(width), height(height) {}
	
	int width, height;
};

} // Engine

#endif // !WINDOW_RESIZE_EVENT_H