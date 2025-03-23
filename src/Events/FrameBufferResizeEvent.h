#ifndef FRAME_BUFFER_RESIZE_EVENT_H
#define FRAME_BUFFER_RESIZE_EVENT_H

#include "IEvent.h"

namespace Engine {

struct FrameBufferResizeEvent : public IEvent<FrameBufferResizeEvent> {
	FrameBufferResizeEvent(int width, int height) : width(width), height(height) {}
	
	int width, height;
};

} // Engine

#endif // !FRAME_BUFFER_RESIZE_EVENT_H