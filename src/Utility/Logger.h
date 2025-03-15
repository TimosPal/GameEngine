#ifndef LOGGER_H
#define LOGGER_H

#include <spdlog/spdlog.h>

#define LOG_INFO(msg, ...) Logger::getInstance().logInfo(msg, ##__VA_ARGS__)
#define LOG_ERROR(msg, ...) Logger::getInstance().logError(msg, ##__VA_ARGS__)
#define LOG_WARNING(msg, ...) Logger::getInstance().logWarning(msg, ##__VA_ARGS__)
#define LOG_CRITICAL(msg, ...) Logger::getInstance().logCritical(msg, ##__VA_ARGS__)

namespace Engine {

class Logger {
public:

    Logger()
    {
        spdlog::set_pattern("%^[%l]%$ %v");
    }

    static Logger& getInstance()
    {
        static Logger instance;
        return instance;
    }

    template <typename... Args>
    inline void logInfo(std::format_string<Args...> message, Args&&... args)
    {
        std::string formatted_message = std::format(message, std::forward<Args>(args)...);
        spdlog::info(formatted_message);
    }

    template <typename... Args>
    inline void logError(std::format_string<Args...> message, Args&&... args)
{
        std::string formatted_message = std::format(message, std::forward<Args>(args)...);
        spdlog::error(formatted_message);
    }

    template <typename... Args>
    inline void logWarning(std::format_string<Args...> message, Args&&... args)
    {
        std::string formatted_message = std::format(message, std::forward<Args>(args)...);
        spdlog::warn(formatted_message);
    }

    template <typename... Args>
    inline void logCritical(std::format_string<Args...> message, Args&&... args)
{
        std::string formatted_message = std::format(message, std::forward<Args>(args)...);
        spdlog::critical(formatted_message);
    }

};

} // Engine

#endif // !LOGGER_H
