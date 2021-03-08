#pragma once
#include "common/math/vector.hpp"

namespace Nano
{
    template<typename T>
    class Quaternion
    {
    private:
        T x, y, z, w;
    
    public:
        Quaternion(const Quaternion<T>& rhs) = default;

        Quaternion(T _x, T _y, T _z, T _w);

        template<typename U>
        Quaternion(const Quaternion<U>& rhs);

        Quaternion(const Vector3<T>& u, const Vector3<T>& v);

        Quaternion(const Vector3<T>& eulerAngles);

        template<typename U>
        inline Quaternion<T>& operator+=(const Quaternion<U>& rhs);

        template<typename U>
        inline Quaternion<T>& operator-=(const Quaternion<U>& rhs);

        template<typename U>
        inline Quaternion<T>& operator*=(const Quaternion<U>& rhs);

        template<typename U>
        inline Quaternion<T>& operator/=(const Quaternion<U>& rhs);
    };

    using Quaternionf = Quaternion<float>;

}

#include "details/quaternion.inl"