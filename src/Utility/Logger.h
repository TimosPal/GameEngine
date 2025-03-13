#ifndef LOGGER_H
#define LOGGER_H

#include <spdlog/spdlog.h>

namespace Engine {
namespace Logger {

inline void set_default_pattern()
{
    spdlog::set_pattern("%^[%l]%$ %v");
}

inline void log_info(const std::string& message) {
    spdlog::info(message);  
}

inline void log_error(const std::string& message) {
    spdlog::error(message);  
}

inline void log_warning(const std::string& message) {
    spdlog::warn(message);  
}

inline void log_critical(const std::string& message) {
    spdlog::critical(message);
}

} // Logger
} // Engine

#endif // !LOGGER_H
