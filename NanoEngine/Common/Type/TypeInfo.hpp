#pragma once
#include <cstdint>
#include <string_view>
#include "nameof.hpp"

namespace Nano
{
    class StrHashGenerator
    {
    public:
        static constexpr size_t Gen(std::string_view str)
        {
            return GenHash(str.data(), str.size());
        }
    private:
        static constexpr size_t GenHash(const char* str, size_t n) noexcept
        {
            std::uint64_t hash = m_FnvOffset;

            for (size_t i = 0; i < n; i++)
                hash = (hash ^ static_cast<std::uint64_t>(str[i])) * m_FnvPrime;

            return hash;
        }

        static constexpr std::uint64_t m_FnvOffset = 14695981039346656037ull;
        static constexpr std::uint64_t m_FnvPrime = 1099511628211ull;
    };

    template<typename T>
    struct TypeID
    {
        static constexpr size_t ID()
        {
            return StrHashGenerator::Gen(nameof::nameof_type<T>());
        }
    };

    template<typename T>
    constexpr size_t TypeHash = TypeID<T>::ID();
}