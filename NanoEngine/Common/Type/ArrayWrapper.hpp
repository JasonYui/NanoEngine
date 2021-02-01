#pragma once
#include <vector>
#include <array>
#include <queue>
#include <span>

namespace Nano
{
    template<typename type>
    using Vector = std::vector<type>;

    template<typename T, size_t MAX_SIZE>
    using Array = std::array<T, MAX_SIZE>;

    template<typename T>
    using Queue = std::queue<T>;

    template<typename T>
    using Span = std::span<T>;
}