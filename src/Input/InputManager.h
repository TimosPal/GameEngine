#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <unordered_map>
#include <string>

#include "Action.h"

namespace Engine {

class InputManager
{
public:
	static bool registerAction(const Action& action);
	static Action getAction(const std::string& actionName);
	static std::vector<Action> getActions();

private:
	static std::unordered_map<std::string, Action> m_registeredActions;
};

} // Engine

#endif // !INPUT_MANAGER_H
