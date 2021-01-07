#include "ArcheTypeManager.hpp"

namespace Nano
{
    void ArcheTypeManager::Clear()
    {
        for (auto&& item : m_TypeLookup)
        {
            std::for_each(item.second.begin(), item.second.end(), [](ArcheType* acheType) { delete acheType; });
            item.second.clear();
        }

        m_TypeLookup.clear();
    }
}
