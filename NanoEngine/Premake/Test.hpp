#ifdef ATTRIBUTE
#define PROPERTY(...) __attribute__((annotate(#__VA_ARGS__)))
#else
#define PROPERTY(...)
#endif

namespace Nano
{

    namespace Test
    {
        struct Point
        {
            PROPERTY(x)
            float x;
            float y;

            float Sum() { return x + y; }
        };

        struct Vector3
        {
            float x;
            float y;
            float z;

            float Sum() { return x + y; }
        };
    }

    struct Vector4
        {
            float x;
            float y;
            float z;
            float w;

            float Sum() { return x + y; }
        };
}