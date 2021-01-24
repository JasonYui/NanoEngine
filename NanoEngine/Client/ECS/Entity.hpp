#pragma once

namespace Nano
{
    struct Entity
    {
        friend class EntityManager;
    public:
        Entity() = default;
        Entity(size_t _index, size_t _version) :index(_index), version(_version) {}
        ~Entity() = default;
        size_t GetIndex() const { return index; }
        size_t GetVersion() const { return version; }
    private:
        size_t index{ 0 };
        size_t version{ 0 };
    };
}