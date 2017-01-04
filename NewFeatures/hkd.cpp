#include <functional>

template<template <typename> class M, class A, class B>
concept bool Monad = requires(M<A> a) 
{
    { a == b } -> bool;
};

template <template <typename> class M>
struct Monad
{
    template <class A>
    static const M<const A> inject(const A a);

    template <class A, class B>
    static const M<const B> bind
    (const M<const A> a, 
     const std::function<const M<const B>(const A)> b);

    template <class A, class B>
    static const M<const A> bind_
    (const M<const A> a, const M<const B> b)
    {
        return bind(a, [&]{ return b; });
    }
};

template <class T>
class Maybe
{
    private:
        const bool isNothing;
        const T value;

    public:
        Maybe(T v): isNothing(true), value(v) {}
        /* Maybe(): isNothing(false) {} */
};

template <>
struct Monad<Maybe>
{
    template <class A>
    static const Maybe<const A> inject(const A a)
    {
        return Maybe<const A>(a);
    }

    template <class A, class B>
    static const Maybe<const B> bind
    (const Maybe<const A> a,
     const std::function<const Maybe<const B>(const A)> b)
    {
        return Maybe<const B>(a);
    }
};

int main()
{
    auto x = Monad<Maybe>::inject<const int>(2);
    Monad<Maybe>::bind_<const int, const int>(x, x);
    return 0;
}
