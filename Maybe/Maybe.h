#ifndef Maybe_H
#define Maybe_H

#include <cassert>
#include <functional>
#include <string>
#include "../Show.h"

template <class T>
class TrivalValue
{
    public:
        static T value;
};

template <>
class TrivalValue<const int>
{
    public:
        static const int value;
};

const int TrivalValue<const int>::value = 0;

template <class T>
class Maybe
{
    private:
        const T m_value;
        const bool m_valid;
        
    private:
        Maybe();
        Maybe(const T value);
        
    private:
        template <class A, class B>
        friend const Maybe<const B> operator>>=
        (const Maybe<const A> a,
         const std::function<const Maybe<const B>(const A)> func);
         
        template <class A>
        friend const Maybe<const A> inject(const A value);
        
        template <class A>
        friend const Maybe<const A> Just(const A value);
        
        template <class A>
        friend const Maybe<const A> Nothing();
        
        template <class A>
        friend const std::string show(const Maybe<const A> a);
};

template <class T>
Maybe<T>::Maybe(): m_value(TrivalValue<T>::value), m_valid(false)
{
}

template <class T>
Maybe<T>::Maybe(const T value): m_value(value), m_valid(true)
{
}

template <class A>
const Maybe<const A> Just(const A value)
{
    return Maybe<const A>(value);
}

template <class A>
const Maybe<const A> Nothing()
{
    return Maybe<const A>();
}

template <class A, class B>
const Maybe<const B> operator>>=
(const Maybe<const A> a, const std::function<const Maybe<const B>(const A)> func)
{
    if (a.m_valid == false)
    {
        return Nothing<const B>();
    }
    else
    {
        return func(a.m_value);
    }
}

template <class A, class B>
const Maybe<const B> operator>>
(const Maybe<const A> a, const Maybe<const B> b)
{
    std::function<const Maybe<const B>(const A)> f = [=](const A)
    {
        return b;
    };
    return a >>= f;
}

template <class A>
const Maybe<const A> inject(const A value)
{
    return Maybe<const A>(value);
}

template <class A>
class ImpShow<const Maybe<const A> >
{
    public:
        typedef typename ImpShow<const A>::Has Has;
};

template <class A>
const std::string show(const Maybe<const A> a)
{
    typedef typename ImpShow<const A>::Has Has;
    static_assert(std::is_same<Has, std::true_type>::value, "");
    if (a.m_valid == false)
    {
        return "Nothing";
    }
    else
    {
        return std::string("Just ") + show(a.m_value);
    }
}

#endif
