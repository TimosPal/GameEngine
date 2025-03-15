#include "InputManager.h"

namespace Engine {

std::unordered_map<std::string, Action> InputManager::m_registeredActions;

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

} // Engine