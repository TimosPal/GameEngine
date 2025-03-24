#include "Util.h"

namespace Engine {

std::string fileToString(const std::string& filePath, bool& openedFile) {
    std::ifstream file(filePath);
    if (!file) {
        openedFile = false;
        LOG_CRITICAL("Error opening file: {}", filePath);
        return "";
    }

    std::stringstream buffer;
    buffer << file.rdbuf();

    openedFile = true;
    return buffer.str();
}

} // Engine