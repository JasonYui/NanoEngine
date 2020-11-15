#include "Logger.hpp"
#include <memory>
#include <stdexcept>
#include <iostream>

using namespace Nano;

namespace Nano
{
    template<typename ... T>
    static String StringFormat(const std::string& format, T ... args)
    {
        size_t size = snprintf(nullptr, 0, format.c_str(), args ...) + 1; // Extra space for '\0'
        if (size <= 0) 
        { 
            throw std::runtime_error("Error during formatting."); 
        }
        std::unique_ptr<char[]> buf(new char[size]);
        snprintf(buf.get(), size, format.c_str(), args ...);
        return String(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
    }
}

template<typename... T>
void Nano::Logger::LogMessage(LogLevel level, const char* file, uint32_t line, const char* module, const String& format, T... args)
{
    String message = StringFormat(format, args...);
    String output = StringFormat("Log from file {0} line {1} module {2}: {3}", file, line, module, message);
    std::cout << format << std::endl;
}
void Nano::Logger::LogMessage(LogLevel level, const char* file, uint32_t line, const char* module, const String& format)
{
    std::cout << format << std::endl;
}