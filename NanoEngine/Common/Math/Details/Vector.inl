namespace Nano
{
    template<typename T>
    Vector2<T> Vector2<T>::operator* (T scale) const
    {
        return Vector2<T>(this->x * scale, this->y * scale);
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