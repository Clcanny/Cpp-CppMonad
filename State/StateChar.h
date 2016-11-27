#ifndef StateChar_H
#define StateChar_H

#include "State.h"

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
    
    template <class A, class B>
    static const typename apply_wrap1<StateChar, const B>::type bind_
    (
        const typename apply_wrap1<StateChar, const A>::type a,
        const typename apply_wrap1<StateChar, const B>::type b
    )
    {
        const function<const typename apply_wrap1<StateChar, const B>::type(const A)>
        fn = [&](const A)
        {
            return b;
        };
        return bind<const A, const B>(a, fn);
    }
};

template <class A>
const State<const char, const A> inject(const A a)
{
    return Monad<StateChar>::inject<const A>(a);
}

template <class A, class B>
const State<const char, const A> operator>>=
(
    const State<const char, const A> a,
    const function<const State<const char, const B>(const A)> b
)
{
    return Monad<StateChar>::bind<const A, const B>(a, b);
}

template <class A, class B>
const State<const char, const A> operator>>
(
    const State<const char, const A> a,
    const State<const char, const B> b
)
{
    return Monad<StateChar>::bind_<const A, const B>;
}

#endif
