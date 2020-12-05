namespace Nano
{
    namespace Test
    {
        struct Point
        {
            [[name(x)]]
            float x;
            float y;

            float Sum() { return x + y; }
        };

        struct Vector3
        {
            [[name(x)]]
            float x;
            float y;
            float z;

            float Sum() { return x + y; }
        };
    }

    struct Vector4
        {
            [[name(x)]]
            float x;
            float y;
            float z;
            float w;

            float Sum() { return x + y; }
        };
}