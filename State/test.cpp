#ifndef State_H
#define State_H

#include "Monad.h"

template <class S, class A>
class State
{
    private:
        const std::function<const std::tuple<const A, const S>(const S)> fn;
        
        template <class T>
        friend class Monad;
        
    public:
        State(const std::function<const std::tuple<const A, const S>(const S)> f) :
            fn(f) {};
            
        const tuple<const A, const S> runState(const S s) const
        {
            return fn(s);
        }
        const A evalState(const S s) const
        {
            return get<0>(runState(s));
        }
        const S execState(const S s) const
        {
            return get<1>(runState(s));
        }
};

template <class S>
struct StateWrapper
{
    template <class A>
    struct apply
    {
        typedef const State<const S, const A> type;
    };
};

typedef bind1<StateWrapper<const char>, _1> StateChar;
template <>
struct Monad<StateChar>
{
    typedef true_type ImpMonad;
    
    template <class A>
    static const typename apply_wrap1<StateChar, const A>::type inject(const A a)
    {
        const function<const tuple<const A, const char>(const char)>
        fn = [=](const char s)
        {
            return tuple<const A, const char>(a, s);
        };
        return State<const char, const A>(fn);
    }
    
    template <class A, class B>
    static const typename apply_wrap1<StateChar, const B>::type bind
    (
        const typename apply_wrap1<StateChar, const A>::type a,
        const function<const typename apply_wrap1<StateChar, const B>::type(const A)> b
    )
    {
        const function<const tuple<const B, const char>(const char)> fn
            = [=](const char s)
        {
            const tuple<const A, const char> tmp = a.fn(s);
            return b(get<0>(tmp)).fn(get<1>(tmp));
        };
        return State<const char, const B>(fn);
    }
};

#endif
