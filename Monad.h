#ifndef Monad_H
#define Monad_H

#include "Header.h"

template <class MonadType>
struct Monad
{
    typedef false_type ImpMonad;
    
    template <class A>
    static const typename apply_wrap1<MonadType, const A>::type inject(const A value);
    
    template <class A, class B>
    static const typename apply_wrap1<MonadType, const B>::type bind
    (
        const typename apply_wrap1<MonadType, const A>::type a,
        const function<const typename apply_wrap1<MonadType, const B>::type(const A)> b
    );
    
    template <class A, class B>
    static const typename apply_wrap1<MonadType, const B>::type bind_
    (
        const typename apply_wrap1<MonadType, const A>::type a,
        const typename apply_wrap1<MonadType, const B>::type b
    );
    /* 实现不要在这里写，写了也没有用 */
    /* 特化的时候并不会把这个函数带过去 */
    /* 写一个声明提醒自己在特化的时候要写这个函数 */
    /* { */
    /*     const function<const typename apply_wrap1<MonadType, const B>::type(const A)> */
    /*     fn = [&](const A) */
    /*     { */
    /*         return b; */
    /*     }; */
    /*     return bind<const A, const B>(a, fn); */
    /* } */
};

template <class MonadType, class A>
const typename apply_wrap1<MonadType, const A>::type inject(const A value);

/* C++的type infer真的菜，不能更菜 */
/* 需要针对每一个具体的Monad写一个重载，不要针对MonadWrapper */
/* 具体参考Maybe */
template <class MonadType, class A, class B>
const typename apply_wrap1<MonadType, const B>::type operator>>=
(
    const typename apply_wrap1<MonadType, const A>::type a,
    const function<const typename apply_wrap1<MonadType, const B>::type(const A)> b
);
/* { */
/*     return Monad<MonadType>::bind<const A, const B>(a, b); */
/* } */

template <class MonadType, class A, class B>
const typename apply_wrap1<MonadType, const B>::type operator>>
(
    const typename apply_wrap1<MonadType, const A>::type a,
    const typename apply_wrap1<MonadType, const B>::type b
);

#endif
