#pragma once
#include "spdlog/spdlog.h"

namespace Nano
{
#ifndef LOG_INFO
#define LOG_INFO(format, ...)\
    spdlog::info(format, ## __VA_ARGS__);
#endif // !LOG_INFO

#ifndef LOG_WARNING
#define LOG_WARNING(format, ...)\
    spdlog::warn(format, ## __VA_ARGS__);
#endif // !LOG_WARNING

#ifndef LOG_ERROR
#define LOG_ERROR(format, ...)\
    spdlog::error(format, ## __VA_ARGS__);
#endif // !LOG_ERROR

#ifndef LOG_CRITICAL
#define LOG_CRITICAL(format, ...)\
    spdlog::critical(format, ## __VA_ARGS__);
#endif // !LOG_CRITICAL
}