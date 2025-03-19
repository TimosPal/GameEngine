#ifndef UTIL_H
#define UTIL_H

#include <string>

namespace Engine {

template <typename T>
std::string classToString(const T& obj) {
    std::string name = typeid(obj).name();

    // Remove "class " or "struct " if present
    const std::string classPrefix = "class ";
    const std::string structPrefix = "struct ";
    if (name.rfind(classPrefix, 0) == 0) {
        name = name.substr(classPrefix.length());
    }
    else if (name.rfind(structPrefix, 0) == 0) {
        name = name.substr(structPrefix.length());
    }

    return name;
}

} // Engine

#endif // !UTIL_H
