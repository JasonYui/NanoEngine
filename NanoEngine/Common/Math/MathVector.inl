namespace Math
{
    template<typename T, int N>
    struct Vectors
    {
        T data[N];

        Vectors() = default;

        explicit Vectors(const T value) noexcept { Set(value); }

        explicit Vectors(std::initializer_list<T> args) { Set(args); }

        operator T* () { return reinterpret_cast<T*>(this); }

        operator const T* () const { return reinterpret_cast<const T*>(this); }

        void Set(const T value)
        {
            for (size_t i = 0; i < N; ++i)
            {
                data[i] = value;
            }
        }

        void Set(std::initializer_list<T> args)
        {
            size_t i = 0;
            assert(args.size() <= N);
            for (auto value : args)
            {
                data[i++] = value;
            }
        }

        Vectors& operator=(const T* args) 
        {
            Set(args);
            return *this;
        }

        Vectors& operator=(const T value) 
        {
            Set(value);
            return *this;
        }

        Vectors& operator=(const Vectors& v) 
        {
            std::memcpy(this, &v, sizeof(v));
            return *this;
        }

        T& operator[](size_t index) { return data[index]; }

        [[nodiscard]] const T& operator[](size_t index) const { return data[index]; }

        T Dot3(const Vectors& v) 
        {
            T result;
            //Math::DotProduct<T>(*this, v, result);
            return result;
        }

        void Normalize()
        {
            T length;// = Math::DotProduct<T>(*this, *this, N);

            length = static_cast<T>(Sqrt(length));
            float turn = 1.0f / length;

            for (int i = 0; i < N; i++)
            {
                data[i] = static_cast<T>(data[i] * turn);
            }
        }

        static Vectors Zero()
        {
            return Vectors(0);
        }
    };

    inline GMVector4 LoadGMVector4(const Vector3& v)
    {
        __m128 x = _mm_load_ss(&v[0]);
        __m128 y = _mm_load_ss(&v[1]);
        __m128 z = _mm_load_ss(&v[2]);
        __m128 xy = _mm_unpacklo_ps(x, y);
        return _mm_movelh_ps(xy, z);
    }

    inline GMVector4 GMVectorDot(GMVector4 v1, GMVector4 v2)
    {
        GMVector4 temp = _mm_mul_ps(v1, v2);
        GMVector4 temp2 = _mm_shuffle_ps(temp, temp, _MM_SHUFFLE(2, 3, 0, 1));
        temp = _mm_add_ps(temp, temp2);
        temp2 = _mm_shuffle_ps(temp, temp, _MM_SHUFFLE(1, 0, 3, 2));
        return _mm_add_ps(temp, temp2);
    }

    inline void GMStoreVector4(GMVector4 source, Vector3& target)
    {
        GMVector4 t1 = _mm_shuffle_ps(source, source,_MM_SHUFFLE(1,1,1,1));
        GMVector4 t2 = _mm_shuffle_ps(source, source,_MM_SHUFFLE(2,2,2,2));
        _mm_store_ss(&target[0], source);
        _mm_store_ss(&target[1], t1);
        _mm_store_ss(&target[2], t2);
    }
}
