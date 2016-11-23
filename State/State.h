#ifndef State_H
#define State_H

#include <functional>
#include <type_traits>
#include <std::tuple>

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
 const std::function<const State<const S, const B>(const A) g)
{
    const std::function<const std::tuple<const A, const S>(const S)> func =
        [=](const S s)
    {
        std::tie(a, s1) = f.runState(s);
        std::tie(a1, s2) = (g(a)).runState(s1);
        return std::tuple<const A, const S>(a1, s1);
    }
    return State(func);
}

template <class S, class A>
const State<const S, const A> inject(const A a)
{
    const std::function<const S, const A> func =
        [=](const S s)
    {
        return std::tuple<const S, const A>(s, a);
    };
    return State(func);
}

#endif
