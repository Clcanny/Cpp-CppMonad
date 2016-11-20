#ifndef Identity_H
#define Identity_H

#include "../Monad.h"
#include <functional>

template <class T>
class Identity
{
    private:
        const T value;
        
    private:
        template <class A, class B>
        friend Identity<B> operator>>=
        (const Identity<A> &a,
         const std::function<Identity<B>(const A &)> func);
         
    public:
        Identity(T v);
        ~Identity();
};

template <class T>
Identity<T>::Identity(T v): value(v) {}

template <class T>
Identity<T>::~Identity() {}

template <class A, class B>
Identity<B> operator>>=
(const Identity<A> &a,
 const std::function<Identity<B>(const A &)> func)
{
    return func(a.value);
}

template <class T>
Identity<T> inject(const T &v)
{
    return Identity<T>(v);
}

#endif
