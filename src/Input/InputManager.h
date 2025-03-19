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

	double getScrollOffset() const { return m_scrollWheelYOffset; }
	double getMousePosX() const { return m_mousePosX; }
	double getMousePosY() const { return m_mousePosY; }

	void onKeyEvent(KeyCode key, KeyState::Type action);
	void onScrollEvent(double yOffset);
	void onMouseMoveEvent(double xPos, double yPos);

	void update();

private:
	InputManager() {}

	void resetReleasedKeys();
	void setHoldKeys();

	KeyState& getKeyState(KeyCode key);

	std::unordered_map<std::string, Action> m_registeredActions;

	std::unordered_map <KeyCode, KeyState> m_keyStates;
	std::vector<KeyState*> m_activeKeys;

	// TODO: integrate to actions system
	// Add vec2 in the future.
	double m_scrollWheelYOffset = 0;
	double m_mousePosX = 0;
	double m_mousePosY = 0;

};

} // Engine

#endif // !INPUT_MANAGER_H
