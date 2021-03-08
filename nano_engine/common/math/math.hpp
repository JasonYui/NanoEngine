#pragma once

#include <cmath>
#include <initializer_list>
#include <nmmintrin.h>
#include "common/fwd.hpp"
#include "common/type/limit.hpp"

using namespace Nano;

namespace Math
{
    const float PI = 3.141592654f;
    const float PIDIV4 = 0.785398163f;

    inline float Pow(float x, float y) { return std::pow(x, y); }
    inline float Sqrt(float rhs) noexcept { return std::sqrt(rhs); }

    inline size_t Align(size_t x, size_t alignment)
    {
        return (x + alignment - 1) & ~(alignment - 1);
    }

    template<typename T>
    inline T GetRange(T raw, int start, int end);

    template<typename T, int N>
    struct Vectors;

    using Vector2 = Vectors<float, 2>;

    using Vector3 = Vectors<float, 3>;
    using Vector3d = Vectors<double, 3>;
    using Vector3s = Vectors<int16_t, 3>;
    using Vector3i = Vectors<int32_t, 3>;

    using Vector4 = Vectors<float, 4>;
    using R8G8B8A8Unorm = Vectors<int8_t, 4>;
    using Vector4i = Vectors<int32_t, 4>;

    typedef __m128 GMVector4;
    typedef __m128i GMVector4i;

    template<typename T, int N>
    Vectors<T, N> operator+(const Vectors<T, N>& lhs, const Vectors<T, N>& rhs)
    {
        Vectors<T, N> result;
        //Math::AddByElement<T>(lhs, rhs, result, N);
        return result;
    }

    template<typename T, int N>
    Vectors<T, N> operator-(const Vectors<T, N>& lhs, const Vectors<T, N>& rhs)
    {
        Vectors<T, N> result;
        //Math::AddByElement<T>(lhs, rhs, result, N);
        return result;
    }

    GMVector4 LoadGMVector4(const Vector3& v);
    GMVector4 GMVectorDot(GMVector4 v1, GMVector4 v2);
    void GMStoreVector4(GMVector4 source, Vector3& target);
}

#include "common/math/details/math_arithmetic.inl"