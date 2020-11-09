namespace Math
{
    template<typename T>
    inline T GetRange(T raw, int start, int end)
    {
        ASSERT(start <= end);
        int range = end - start + 1;
        return static_cast<T>((raw >> start) & (_ULONG_MAX_ >> (64 - range)));
    }
}