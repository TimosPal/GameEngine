#ifndef ACTION_H
#define ACTION_H

#include "KeyCodes.h"
#include "KeyState.h"

namespace Engine {

struct Action
{
	const char* name;
	KeyCode keyCodeID;
	KeyState::Type type;

	Action() : name("NoneAction"), keyCodeID(Key::Invalid), type(KeyState::Type::Pressed) {}

	Action(const char* name, KeyCode keyCodeID, KeyState::Type type)
		: name(name), keyCodeID(keyCodeID), type(type)
	{}
};

} // Engine

#endif // !ACTION_H
