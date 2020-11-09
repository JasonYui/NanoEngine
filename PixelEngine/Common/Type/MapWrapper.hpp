#pragma once
#include <unordered_map>
#include <map>

namespace Pixel
{
    template<typename key, typename value>
    using HashMap = std::unordered_map<key, value>;

    template<typename key, typename value>
    using HashSet = std::unordered_multimap<key, value>;

    template<typename key, typename value>
    using Map = std::map<key, value>;
}