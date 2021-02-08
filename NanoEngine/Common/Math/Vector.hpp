#pragma once
#include "Common/Type/TypeDef.hpp"

namespace Nano
{
    template<typename T>
    struct Vector2
    {
        explicit Vector2(T _x, T _y) : x(_x), y(_y) {}

        Vector2 operator* (T scale) const;

        T Dot(const Vector2& rhs);
        T Cross(const Vector2& rhs);

        T x;
        T y;
    };

    using Vector2i = Vector2<uint32_t>;
    using Vector2f = Vector2<float>;
    using Vector2d = Vector2<double>;

    template<typename T>
    struct Vector3
    {
        explicit Vector3(T _x, T _y, T _z) : x(_x), y(_y), z(_z) {}

        Vector3 operator* (T scale) const;

        T Dot(const Vector3& rhs);
        Vector3 Cross(const Vector3& rhs);

        union { T x, r; };
        union { T y, g; };
        union { T z, b; };
    };

    using Vector3i = Vector3<uint32_t>;
    using Vector3f = Vector3<float>;
    using Vector3d = Vector3<double>;
}

#include "Details/Vector.inl"