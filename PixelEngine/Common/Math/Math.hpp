#pragma once
#include <cassert>
#include <cmath>
#include <initializer_list>
#include <nmmintrin.h>
#include "PixelEngine/Common/Type/BasicType.hpp"
#include "PixelEngine/Common/Type/CommonMarco.hpp"
#include "PixelEngine/Common/Type/Limit.hpp"
#include "PixelEngine/Common/Log/Logger.hpp"
//#include "DirectXMath.h"

using namespace Pixel;

namespace Pixel
{
    class Math
    {
    public:
        template<typename T>
        static void AddByElement(const T* a, const T* b, T* result, size_t count)
        {
            for (int i = 0; i < count; ++i)
            {
                result[i] = a[i] + b[i];
            }
        }

        template<typename T>
        static void SubByElement(const T* a, const T* b, T* result, size_t count)
        {
#ifdef USE_SIMD
            
#else
            for (int i = 0; i < count; ++i)
            {
                result[i] = a[i] - b[i];
            }
#endif
        }

        template<typename T>
        static void MulByElement(const T* a, const T* b, T* result, size_t count)
        {
            for (int i = 0; i < count; ++i)
            {
                result[i] = a[i] * b[i];
            }
        }

        template<typename T>
        static T DotProduct(const T* a, const T* b, const size_t count)
        {
            T* temp = new T[count];
            T result = static_cast<T>(0);

            MulByElement<T>(a, b, temp, count);

            for (size_t i = 0; i < count; i++)
            {
                result += temp[i];
            }

            delete[] temp;
            return result;
        }

    public:
        template<typename T>
        static void SubByElementSIMD(const T* a, const T* b, T* result, size_t count)
        {
            for (int i = 0; i < count; ++i)
            {
                result[i] = a[i] - b[i];
            }
        }

        template<>
        static void SubByElementSIMD(const float* a, const float* b, float* result, size_t count)
        {
            for (size_t i = 0; i < count; i += 4)
            {
                __m128 lTemp = _mm_loadu_ps(a + i);
                __m128 rTemp = _mm_loadu_ps(b + i);
                __m128 tResult = _mm_sub_ps(lTemp, rTemp);
                _mm_storeu_ps(result + i, tResult);
            }

            for (int i = 0; i < 5; i++)
            {
                
            }
        }
    };
}

namespace Math
{
    const float PI = 3.141592654f;
    const float PIDIV4 = 0.785398163f;

    inline float Pow(float x, float y) { return std::pow(x, y); }
    inline float Sqrt(float rhs) noexcept { return std::sqrt(rhs); }

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
        Math::AddByElement<T>(lhs, rhs, result, N);
        return result;
    }

    template<typename T, int N>
    Vectors<T, N> operator-(const Vectors<T, N>& lhs, const Vectors<T, N>& rhs)
    {
        Vectors<T, N> result;
        Math::AddByElement<T>(lhs, rhs, result, N);
        return result;
    }

    GMVector4 LoadGMVector4(const Vector3& v);
    GMVector4 GMVectorDot(GMVector4 v1, GMVector4 v2);
    void GMStoreVector4(GMVector4 source, Vector3& target);
}

#include "PixelEngine/Common/Math/MathVector.inl"
#include "PixelEngine/Common/Math/MathArithmetic.inl"