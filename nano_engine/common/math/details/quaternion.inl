#include <cmath>

namespace Nano
{
    template<typename T>
    Quaternion<T>::Quaternion(T _x, T _y, T _z, T _w) : 
        x(_x), y(_y), z(_z), w(_w){}

    template<typename T>
    template<typename U>
    Quaternion<T>::Quaternion(const Quaternion<U>& rhs) :
        x(static_cast<T>(rhs.x)), y(static_cast<T>(rhs.y)), z(static_cast<T>(rhs.z)), w(static_cast<T>(rhs.w)) {}

    template<typename T>
    Quaternion<T>::Quaternion(const Vector3<T>& u, const Vector3<T>& v)
    {
        Vector3<T> w = cross(u, v);
        Quaternion q = Quaternion(u.Dot(v), w.x, w.y, w.z);
        q.w += length(q);
        return normalize(q);
    }

    template<typename T>
    Quaternion<T>::Quaternion(const Vector3<T>& eulerAngles)
    {
        Vector3<T> c = eulerAngles * T(0.5);
        Vector3<T> s = eulerAngles * T(0.5);

        c.x = std::cos(c.x);
        c.y = std::cos(c.y);
        c.z = std::cos(c.z);
        s.x = std::cos(s.x);
        s.y = std::cos(s.y);
        s.z = std::cos(s.z);

        this->w = c.x * c.y * c.z + s.x * s.y * s.z;
        this->x = s.x * c.y * c.z - c.x * s.y * s.z;
        this->y = c.x * s.y * c.z + s.x * c.y * s.z;
        this->z = c.x * c.y * s.z - s.x * s.y * c.z;
    }

    template<typename T>
    template<typename U>
    inline Quaternion<T>& Quaternion<T>::operator+=(const Quaternion<U>& rhs)
    {
        const Quaternion<T> p(*this);
        const Quaternion<T> q(rhs);

        this->x = p.x + q.x;
        this->y = p.y + q.y;
        this->z = p.z + q.z;
        this->w = p.w + q.w;
        return *this;
    }

    template<typename T>
    template<typename U>
    inline Quaternion<T>& Quaternion<T>::operator-=(const Quaternion<U>& rhs)
    {
        const Quaternion<T> p(*this);
        const Quaternion<T> q(rhs);

        this->x = p.x - q.x;
        this->y = p.y - q.y;
        this->z = p.z - q.z;
        this->w = p.w - q.w;
        return *this;
    }

    template<typename T>
    template<typename U>
    inline Quaternion<T>& Quaternion<T>::operator*=(const Quaternion<U>& rhs)
    {
        const Quaternion<T> p(*this);
        const Quaternion<T> q(rhs);

        this->x = p.w * q.x + p.x * q.w + p.y * q.z - p.z * q.y;
        this->y = p.w * q.y + p.y * q.w + p.z * q.x - p.x * q.z;
        this->z = p.w * q.z + p.z * q.w + p.x * q.y - p.y * q.x;
        this->w = p.w * q.w - p.x * q.x - p.y * q.y - p.z * q.z;
        return *this;
    }
}