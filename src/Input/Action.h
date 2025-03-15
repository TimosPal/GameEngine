#ifndef ACTION_H
#define ACTION_H

#include "KeyCodes.h"

namespace Engine {

struct Action
{
	const char* name;
	KeyCode keyCodeID;

	Action() : name("NoneAction"), keyCodeID(Key::Invalid) {}

	Action(const char* name, KeyCode keyCodeID)
		: name(name), keyCodeID(keyCodeID)
	{}
};

} // Engine

#endif // !ACTION_H
