#include <queue>

namespace Nano
{
    template<typename T>
    using Queue = std::queue<T>;

    template<typename T>
    using MinHeap = std::priority_queue<T, std::greater<T>>;

    template<typename T>
    using MaxHeap = std::priority_queue<T, std::less<T>>;
}