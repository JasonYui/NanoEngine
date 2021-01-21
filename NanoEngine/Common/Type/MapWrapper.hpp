#pragma once
#include <unordered_map>
#include <map>
#include <set>

namespace Nano
{
    template<typename key, typename value>
    using HashMap = std::pmr::unordered_map<key, value>;

    template<typename key, typename value>
    using HashSet = std::unordered_multimap<key, value>;

    template<typename key, typename value>
    using Map = std::map<key, value>;

    template<typename key>
    using Set = std::set<key>;
}