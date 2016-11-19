#ifndef Maybe_H
#define Maybe_H

/* maybe.h */

/* The Maybe type. */
/* Provides T safer way to return possible failure than NULL values. Of course, */
/* since C++ doesn't have pattern matching, it is down to you to ensure that you */
/* always call isJust() to confirm there is T value available before calling */
/* fromJust() to retrieve it. */

#include <cassert>
#include <iostream>
#include <functional>
#include <string>

template <class T>
class Maybe
{
    private:
        T m_value;
        const bool m_valid;
        
    private:
        Maybe();
        Maybe(const T value);
        
    public:
        static const Maybe<T> Just(const T &value);
        static const Maybe<T> Nothing();
        const bool isJust() const;
        const T fromJust() const;
};

template <class T>
Maybe<T>::Maybe(): m_valid(false) {}

template <class T>
Maybe<T>::Maybe(const T value): m_value(value), m_valid(true) {}

template <class T>
const Maybe<T> Maybe<T>::Just(const T &value)
{
    return Maybe(value);
}

template <class T>
const Maybe<T> Maybe<T>::Nothing()
{
    return Maybe();
}

template <class T>
const bool Maybe<T>::isJust() const
{
    return m_valid;
}

template <class T>
const T Maybe<T>::fromJust() const
{
    assert(isJust());
    return m_value;
}

/* 可以借助偏特化实现instance typeclass的效果 */
/* 不必要用继承去强制实现接口（这样instance必须和类的定义写在一起） */
template <class T>
std::string show(Maybe<T> m)
{
    if (m.isJust())
    {
        return std::string("Just ") + std::to_string(m.fromJust());
    }
    else
    {
        return "Nothing";
    }
}

/* template <class A, class Func> */
/* auto bind(const Maybe<A> &a, const Func &f) -> decltype(f(a.fromJust)) */
/* { */
/*     typedef decltype(f(a.fromJust())) return_type; */
/*     if (a.isJust == false) */
/*     { */
/*         return return_type::Nothing(); */
/*     } */
/*     else */
/*     { */
/*         return f(f.fromJust()); */
/*     } */
/* } */

template <template<class> class Monad, class A, class B>
Monad<B> operator>>=(const Monad<A> &a, const std::function<Monad<B>(const A &)> func);
/* 注释掉关于Maybe的>>=的实现，打开下面三行，可以看到偏特化起作用了 */
/* { */
/*     return Monad<A>::Nothing(); */
/* } */

/* 同Haskell一样，也可以提供一个基础实现 */
template <template<class> class Monad, class A, class B>
Monad<B> operator>>(const Monad<A> &a, const Monad<B> &b)
{
    std::function<Maybe<B>(const A &)> f = [&](const A &)
    {
        return b;
    };
    return (a >>= f);
}

template <class A, class B>
Maybe<B> operator>>=(const Maybe<A> &a, const std::function<Maybe<B>(const A &)> func)
{
    if (a.isJust() == false)
    {
        return Maybe<B>::Nothing();
    }
    else
    {
        return func(a.fromJust());
    }
}

template <template<class> class Monad, class T>
Monad<T> injetc(const T &v);

template <class T>
Maybe<T> inject(const T &v)
{
    return Maybe<T>::Just(v);
}

#endif
