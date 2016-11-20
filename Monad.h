#ifndef Monad_H
#define Monad_H

#include <functional>

template <template<class> class Monad, class T>
Monad<T> injetc(const T &v);

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
    std::function<Monad<B>(const A &)> f = [&](const A &)
    {
        return b;
    };
    return (a >>= f);
}

#endif
