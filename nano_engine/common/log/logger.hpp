#pragma once
#ifndef SPDLOG_FMT_EXTERNAL
#define SPDLOG_FMT_EXTERNAL
#endif

#include <sstream>
#include "spdlog/spdlog.h"
#include "common/type/common_marco.hpp"

namespace Nano
{
#ifndef LOG_INFO
#define LOG_INFO(format, ...){\
    std::stringstream ss;\
    ss << "[" << __FUNCTION__ <<"] " << format;\
    spdlog::info(ss.str(), ## __VA_ARGS__);}
#endif // !LOG_INFO

#undef LOG_INFO_DEBUG
#ifdef ENGINE_DEBUG
#define LOG_INFO_DEBUG(format, ...){\
    std::stringstream ss;\
    ss << "[" << __FUNCTION__ <<"] " << format;\
    spdlog::info(ss.str(), ## __VA_ARGS__);}
#else
    #define LOG_INFO_DEBUG(format, ...)
#endif

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
    spdlog::critical(ss.str(), ## __VA_ARGS__);\
    assert(false);}
#endif // !LOG_CRITICAL

#undef ASSERT
#define ASSERT(expression) {\
    if (!(expression)) { LOG_CRITICAL("assert({0})", #expression); }\
    assert(expression);};
}