namespace Nano
{
    template<typename T>
    Vector2<T> Vector2<T>::operator* (T scale) const
    {
        return Vector2<T>(this->x * scale, this->y * scale);
    }

    template<typename T>
    Vector2<T> Vector2<T>::operator+ (const Vector2<T>& rhs) const
    {
        return Vector2<T>(x + rhs.x, y + rhs.y);
    }

    template<typename T>
    T Vector2<T>::Dot(const Vector2<T>& rhs)
    {
        return x * rhs.x + y * rhs.y;
    }

    template<typename T>
    T Vector2<T>::Cross(const Vector2& rhs)
    {
        return x * rhs.y - y * rhs.x;
    }

    template<>
    Vector2i::Vector2() : x(0), y(0) {}

    template<>
    Vector2i Vector2i::Zero()
    {
        return Vector2i(0, 0);
    }

    template<>
    Vector2f::Vector2() : x(0.0f), y(0.0f) {}

    template<>
    Vector2f Vector2f::Zero()
    {
        return Vector2f(0.0f, 0.0f);
    }

    template<>
    Vector2d::Vector2() : x(0.0), y(0.0) {}

    template<>
    Vector2d Vector2d::Zero()
    {
        return Vector2d(0.0, 0.0);
    }

    template<typename T>
    Vector3<T> Vector3<T>::operator* (T scale) const
    {
        return Vector3<T>(this->x* scale, this->y* scale, this->z* scale);
    }

    template<typename T>
    T Vector3<T>::Dot(const Vector3<T>& rhs)
    {
        return x * rhs.x + y * rhs.y + z * rhs.z;
    }

    template<typename T>
    Vector3<T> Vector3<T>::Cross(const Vector3& rhs)
    {
        return Vector3(y * rhs.z - z * rhs.y, z * rhs.x - x * rhs.z, x * rhs.y - y * rhs.x);
    }
}