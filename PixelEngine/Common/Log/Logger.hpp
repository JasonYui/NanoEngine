#pragma once
#include <iostream>
#include "PixelEngine/Common/Type/BasicType.hpp"
#include "PixelEngine/Common/Type/StringWrapper.hpp"

namespace Pixel
{
    enum class LogLevel : uint8_t
    {
        _INFO,
        _WARNING,
        _ERROR,
        _CRITICAL,
        k_SIZE
    };

    class Logger
    {
    public:
        template<typename... T>
        static void LogMessage(LogLevel level, const char* file, uint32_t line, const char* module, const String& format, T... args);
        static void LogMessage(LogLevel level, const char* file, uint32_t line, const char* module, const String& format);
    };

#ifndef LOG_INFO
#define LOG_INFO(format, ...)\
    Logger::LogMessage(LogLevel::_INFO, __FILE__, __LINE__, __FUNCTION__, format, ## __VA_ARGS__);
#endif // !LOG_INFO

#ifndef LOG_WARNING
#define LOG_WARNING(format, ...)\
    Logger::LogMessage(LogLevel::_WARNING, __FILE__, __LINE__, __FUNCTION__, format, ## __VA_ARGS__);
#endif // !LOG_WARNING

#ifndef LOG_ERROR
#define LOG_ERROR(format, ...)\
    Logger::LogMessage(LogLevel::_ERROR, __FILE__, __LINE__, __FUNCTION__, format, ## __VA_ARGS__);
#endif // !LOG_ERROR

#ifndef LOG_CRITICAL
#define LOG_CRITICAL(format, ...)\
    Logger::LogMessage(LogLevel::_CRITICAL, __FILE__, __LINE__, __FUNCTION__, format, ## __VA_ARGS__);
#endif // !LOG_CRITICAL
}