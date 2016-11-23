#ifndef Monad_H
#define Monad_H

#include <functional>
#include <type_traits>

template <class T>
class ImpMonad
{
    public:
        typedef std::true_type Has;
};

template <template<class> class Monad, class A>
class inject
{
    public:
        const Monad<const A> operator()(const A value);
};

/* template <template<class> class Monad, class A> */
/* const Monad<const A> inject<Monad, A>::operator()(const A value) */
/* {} */

template <template<class> class Monad, class A, class B>
const Monad<const B> operator>>=
(const Monad<const A> a, const std::function<const Monad<const B>(const A)> func);

template <template<class> class Monad, class A, class B>
const Monad<const B> operator>>(const Monad<const A> a, const Monad<const B> b)
{
    std::function<const Monad<const B>(const A)> f = [=](const A)
    {
        return b;
    };
    return (a >>= f);
}

#endif
