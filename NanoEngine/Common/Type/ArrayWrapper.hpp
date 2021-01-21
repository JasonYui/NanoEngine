#pragma once
#include <vector>
#include <array>
#include <cassert>
#include <queue>
#include <span>

namespace Nano
{
    template<typename type>
    using Vector = std::vector<type>;

    /*template<typename T>
    class Vector
    {
    public:
        Vector() = default;
        explicit Vector(size_t count) : m_Data(count) {};
        explicit Vector(size_t count, const T& value) : m_Data(count, value) {};

        T& operator[] (size_t index) { return m_Data.at(index); }
        const T& operator[] (size_t index) const { return m_Data.at(index); }

        void PushBack(const T& value) { m_Data.push_back(value); }
        void PushBack(T&& value) { m_Data.push_back(std::forward<T>(value)); }

        size_t Capacity() const { return m_Data.capacity(); }
        size_t Size() const { return m_Data.size(); }

        T* ToArray()
        {
            T* tempData = new T[Size()];

            std::copy(m_Data.begin(), m_Data.end(), tempData);

            return tempData;
        }

    private:
        std::vector<T> m_Data;
    };*/

    template<typename T, size_t MAX_SIZE>
    using Array = std::array<T, MAX_SIZE>;

    template<typename T>
    using Queue = std::queue<T>;

    template<typename T>
    using Span = std::span<T>;
}