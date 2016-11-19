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
        
    public:
        std::string print() const;
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

template <class T>
std::string Maybe<T>::print() const
{
    if (isJust())
    {
        return std::string("Just ") + std::to_string(fromJust());
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

template <class A, class B>
Maybe<B> operator>>=(const Maybe<A> &a, const std::function<Maybe<B>(A)> func)
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

#endif
