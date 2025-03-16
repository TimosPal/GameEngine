#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <unordered_map>
#include <string>

#include "Action.h"
#include "KeyState.h"

namespace Engine {

class InputManager
{
public:
	static InputManager& getInstance()
	{
		static InputManager instance;
		return instance;
	}

	bool registerAction(const Action& action);
	Action getAction(const std::string& actionName);
	std::vector<Action> getActions();

	bool isActionTriggered(const Action& action);

	bool isKeyPressed(KeyCode key);
	bool isKeyReleased(KeyCode key);
	bool isKeyDown(KeyCode key);

	void onKeyEvent(KeyCode key, KeyState::Type action);

	void update();

private:
	InputManager() {}

	void resetReleasedKeys();
	void setHoldKeys();

	KeyState& getKeyState(KeyCode key);

	std::unordered_map<std::string, Action> m_registeredActions;

	std::unordered_map <KeyCode, KeyState> m_keyStates;
	std::vector<KeyState*> m_activeKeys;

};

} // Engine

#endif // !INPUT_MANAGER_H
