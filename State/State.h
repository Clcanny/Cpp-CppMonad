#ifndef State_H
#define State_H

#include <functional>
#include <type_traits>
#include <tuple>
#include "../Monad.h"
#include "../Show.h"
#include "../StaticFunc.h"

template <class S, class A>
class State
{
    public:
        State();
        const std::function<const std::tuple<const A, const S>(const S)> runState;
};

template <class S, class A, class B>
const State<const S, const B> operator>>=
(const State<const S, const A> f,
 const std::function<const State<const S, const B>(const A)> g)
{
    const std::function<const std::tuple<const B, const S>(const S)> func =
        [=](const S s)
    {
        const std::tuple<const A, const S> res1 = f.runState(s);
        const std::tuple<const A, const S> res2 =
            g(std::get<0>(res1)).runState(std::get<1>(res1));
        return std::tuple<const A, const S>(res2);
    };
    return State<const S, const B>(func);
}

template <class S, class A>
class inject<const State<const S, _1>, const A >
{
    public:
        const State<const A, const A> operator()(const A a)
        {
            const std::function<const std::tuple<const A, const S>(const S)> func =
                [=](const S s)
            {
                return std::tuple<const A, const S>(a, s);
            };
            return State(func);
        }
};

template <class S, class A>
const std::tuple<const A, const S> runState(const State<const S, const A> state, const S s)
{
    return state.runState(s);
}

template <class S, class A>
const A evalState(const State<const S, const A> state, const S s)
{
    return std::get<0>(state.runState(s));
}

template <class S, class A>
const S execState(const State<const S, const A> state, const S s)
{
    return std::get<1>(state.runState(s));
}

template <class S, class A>
class ImpShow<const State<const S, const A> >
{
    public:
        typedef std::false_type Has;
};

template <class S, class A>
class ImpMonad<const State<const S, const A> >
{
    public:
        typedef std::true_type Has;
};

#endif
