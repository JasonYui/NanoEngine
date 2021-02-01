#pragma once
#ifndef SPDLOG_FMT_EXTERNAL
#define SPDLOG_FMT_EXTERNAL
#endif

#include <sstream>
#include "spdlog/spdlog.h"

namespace Nano
{
#ifndef LOG_INFO
#define LOG_INFO(format, ...){\
    std::stringstream ss;\
    ss << "[" << __FUNCTION__ <<"] " << format;\
    spdlog::info(ss.str(), ## __VA_ARGS__);}
#endif // !LOG_INFO

#ifndef LOG_WARNING
#define LOG_WARNING(format, ...){\
    std::stringstream ss;\
    ss << "[" << __FUNCTION__ <<"] " << format;\
    spdlog::warn(ss.str(), ## __VA_ARGS__);}
#endif // !LOG_WARNING

#ifndef LOG_ERROR
#define LOG_ERROR(format, ...){\
    std::stringstream ss;\
    ss << "[" << __FUNCTION__ <<"] " << format;\
    spdlog::error(ss.str(), ## __VA_ARGS__);}
#endif // !LOG_ERROR

#ifndef LOG_CRITICAL
#define LOG_CRITICAL(format, ...){\
    std::stringstream ss;\
    ss << "FILE: " << __FILE__ << " LINE: " << __LINE__ << " [" << __FUNCTION__ <<"] " << format;\
    spdlog::critical(ss.str(), ## __VA_ARGS__);}
#endif // !LOG_CRITICAL
}