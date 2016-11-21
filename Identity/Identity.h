#ifndef Identity_H
#define Identity_H

#include "../Monad.h"
#include "../Show.h"
#include <functional>

template <class T>
class Identity
{
    private:
        const T value;
        
    private:
        template <class A, class B>
        friend const Identity<const B> operator>>=
        (const Identity<const A> a,
         const std::function<const Identity<const B>(const A)> func);
         
        template <class A>
        friend const std::string show(const Identity<const A> a);
        
    public:
        Identity(const T v);
        ~Identity();
};

template <class T>
Identity<T>::Identity(const T v): value(v) {}

template <class T>
Identity<T>::~Identity() {}

template <class A, class B>
const Identity<const B> operator>>=
(const Identity<const A> a,
 const std::function<const Identity<const B>(const A)> func)
{
    return func(a.value);
}

template <class T>
class inject<Identity, T>
{
    public:
        const Identity<const T> operator()(const T value);
};

template <class T>
const Identity<const T> inject<Identity, T>::operator()(const T v)
{
    return Identity<const T>(v);
}

template <class A>
class ImpShow<const Identity<const A> >
{
    public:
        typedef typename ImpShow<const A>::Has Has;
};

template <class A>
const std::string show(const Identity<const A> a)
{
    typedef typename ImpShow<const A>::Has Has;
    static_assert(std::is_same<Has, std::true_type>::value, "");
    return std::string("Identity ") + show(a.value);
}

#endif
