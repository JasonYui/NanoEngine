#pragma once

namespace Nano
{
    struct Entity
    {
    public:
        size_t GetIndex() { return m_Index; }
        size_t GetVersion() { return m_Version; }
        ~Entity();
    private:
        size_t m_Index{ 0 };
        size_t m_Version{ 0 };
    };
}