#pragma once
#include <tuple>

namespace Pixel
{
    namespace TypeTraits
    {
        template<size_t...>
        struct IndexSequence {};

        template<size_t N, size_t... Seq>
        struct SequenceGen : SequenceGen<N - 1, N - 1, Seq...> {};

        template<size_t... Seq>
        struct SequenceGen<0, Seq...>
        {
            typedef IndexSequence<Seq...> type;
        };
        
    }
}

namespace Pixel
{
    template<typename Func, typename... Args>
    class Delegate
    {
        using TRet = typename std::result_of<Func(Args...)>::type;
    public:
        Delegate(Func&& func, Args&&... args) : 
            m_Function(std::forward<Func>(func)),
            m_Args(std::forward<Args>(args)...)
        {}
        ~Delegate() = default;

        TRet Invoke()
        {
            return Invoke(typename TypeTraits::SequenceGen<sizeof...(Args)>::type());
        }

        TRet operator()()
        {
            return Invoke(typename TypeTraits::SequenceGen<sizeof...(Args)>::type());
        }
    private:
        friend class TaskManager;

        template<size_t... Seq>
        TRet Invoke(TypeTraits::IndexSequence<Seq...>)
        {
            return m_Function(std::get<Seq>(m_Args)...);
        }

        Func m_Function;
        std::tuple<typename std::decay<Args>::type...> m_Args;
    };
}