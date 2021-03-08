#pragma once
#include <thread>
#include <functional>

#include "common/type/array_wrapper.hpp"

namespace Nano
{
    class ThreadPool
    {
    public:
        ThreadPool(uint32_t size) : m_Size(size), m_Pool(Vector<std::thread>(size)) {}
        ~ThreadPool() = default;

        bool Init(std::function<void(uint32_t)> handler)
        {
            for (uint32_t i = 0; i < m_Size; ++i)
                m_Pool.push_back(std::thread(handler, i));

            return true;
        }

        void Close()
        {
            for (auto& thread : m_Pool)
            {
                thread.join();
            }
            m_Pool.clear();
        }
    private:
        uint32_t m_Size{ 0 };
        Vector<std::thread> m_Pool;
    };
}