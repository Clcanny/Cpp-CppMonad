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
    )
    {
        const function<const typename apply_wrap1<MonadType, const B>::type(const A)>
        fn = [&](const A)
        {
            return b;
        };
        return bind(a, fn);
    }
};

#endif
