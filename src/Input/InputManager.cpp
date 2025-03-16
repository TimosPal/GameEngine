#include "InputManager.h"

#include "Utility/Logger.h"

#include <GLFW/glfw3.h>

namespace Engine {

bool InputManager::registerAction(const Action& action)
{
	if(m_registeredActions.find(action.name) == m_registeredActions.end())
	{
		m_registeredActions[action.name] = action;
		return true;
	}
	else
	{
		return false;
	}
}

Action InputManager::getAction(const std::string& actionName)
{
	if (m_registeredActions.find(actionName) != m_registeredActions.end())
	{
		return m_registeredActions[actionName];
	}
	else
	{
		return Action{};
	}
}

std::vector<Action> InputManager::getActions()
{
	std::vector<Action> actions;
	for (const auto& [_, value] : m_registeredActions) {
		actions.push_back(value);
	}

	return actions;
}

bool InputManager::isActionTriggered(const Action& action)
{
	switch (action.type)
	{
	case KeyState::Type::Pressed:
		return isKeyPressed(action.keyCodeID);
	case KeyState::Type::Released:
		return isKeyReleased(action.keyCodeID);
	case KeyState::Type::Hold:
		return isKeyDown(action.keyCodeID);
	default:
		break;
	}
	return false;
}

bool InputManager::isKeyPressed(KeyCode key)
{
	KeyState& state = getKeyState(key);
	return state.type == KeyState::Type::Pressed;
}

bool InputManager::isKeyReleased(KeyCode key)
{
	KeyState& state = getKeyState(key);
	return state.type == KeyState::Type::Released;
}

bool InputManager::isKeyDown(KeyCode key)
{
	KeyState& state = getKeyState(key);
	return state.type == KeyState::Type::Pressed || state.type == KeyState::Type::Hold;
}

KeyState& InputManager::getKeyState(KeyCode key)
{
	auto [it, inserted] = m_keyStates.try_emplace(key, KeyState()); // Inserts only if missing
	return it->second;
}

void InputManager::setHoldKeys()
{
	for (auto state : m_activeKeys)
	{
		if (state->type == KeyState::Type::Pressed)
		{
			state->type = KeyState::Type::Hold;
		}
	}
}

void InputManager::resetReleasedKeys() // TODO: can be done faster. (Slow removal)
{
	for (auto it = m_activeKeys.begin(); it != m_activeKeys.end(); )
	{
		if ((*it)->type == KeyState::Type::Released)
		{
			(*it)->type = KeyState::Type::NotPressed;
			it = m_activeKeys.erase(it); // Erase returns the next valid iterator
		}
		else
		{
			++it; // Only increment if not erasing
		}
	}
}

void InputManager::onKeyEvent(KeyCode key, KeyState::Type action)
{
	KeyState& state = getKeyState(key);
	switch (action)
	{
	case KeyState::Type::Pressed:
		state.type = KeyState::Type::Pressed;
		m_activeKeys.push_back(&state);
		break;
	case KeyState::Type::Released:
		state.type = KeyState::Type::Released;
		break;
	default:
		break;
	}
}

void InputManager::update()
{
	resetReleasedKeys();
	setHoldKeys();
}

} // Engine