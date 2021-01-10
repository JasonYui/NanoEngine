#pragma once

namespace Nano
{
    struct Entity
    {
        friend class EntityManager;
    public:
        ~Entity() = default;
        size_t GetIndex() { return index; }
        size_t GetVersion() { return version; }
    private:
        size_t index{ 0 };
        size_t version{ 0 };
    };
}