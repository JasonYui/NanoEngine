#pragma once
#include <initializer_list>
#include "Common/Type/TypeDef.hpp"

namespace Nano
{
    template<typename T>
    struct Vector3
    {
        Vector3() = default;
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