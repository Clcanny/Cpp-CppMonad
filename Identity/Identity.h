#ifndef Identity_H
#define Identity_H

#include "../Header.h"
#include "../TrivalValue.h"
#include "../Monad.h"
#include "../Show.h"

template <class T>
class Identity
{
    private:
        const T value;
        
        template <class A>
        friend class Monad;
        
        template <class A>
        friend class Show;
        
    public:
        Identity(const T v): value(v) {}
        ~Identity() {}
};

template <class A>
struct TrivalValue<const Identity<const A> >
{
    static const Identity<const A> value;
};

struct IdentityWrapper
{
    template <class T>
    struct apply
    {
        typedef const Identity<const T> type;
    };
};

template <class A>
const Identity<const A> TrivalValue<const Identity<const A> >::value =
    Identity<const A>(TrivalValue<const A>::value);

template <>
struct Monad<IdentityWrapper>
{
    typedef true_type ImpMonad;
    
    template <class A>
    static const typename apply_wrap1<IdentityWrapper, const A>::type inject(const A a)
    {
        return Identity<const A>(a);
    }
    
    template <class A, class B>
    static const typename apply_wrap1<IdentityWrapper, const B>::type bind
    (const typename apply_wrap1<IdentityWrapper, const A>::type a,
     const function<const typename apply_wrap1<IdentityWrapper, const B>::type(const A)> b)
    {
        return b(a.value);
    }
    
    template <class A, class B>
    static const typename apply_wrap1<IdentityWrapper, const B>::type bind_
    (
        const typename apply_wrap1<IdentityWrapper, const A>::type a,
        const typename apply_wrap1<IdentityWrapper, const B>::type b
    )
    {
        const function<const typename apply_wrap1<IdentityWrapper, const B>::type(const A)>
        fn = [&](const A)
        {
            return b;
        };
        return bind<const A, const B>(a, fn);
    }
};

template <class A>
const Identity<const A> inject(const A a)
{
    return Monad<IdentityWrapper>::inject(a);
}

template <class A, class B>
const Identity<const B> operator>>=
(
    const Identity<const A> a,
    const function<const Identity<const B>(const A)> b)
{
    return Monad<IdentityWrapper>::bind<const A, const B>(a, b);
}

template <class A, class B>
const Identity<const B> operator>>
(
    const Identity<const A> a,
    const Identity<const B> b
)
{
    return Monad<IdentityWrapper>::bind_<const A, const B>(a, b);
}

template <class T>
struct Show<const Identity<const T> >
{
    typedef typename Show<const T>::ImpShow ImpShow;
    
    static const string show(const Identity<const T> a)
    {
        typedef typename Show<const T>::ImpShow Has;
        static_assert(std::is_same<Has, std::true_type>::value, "");
        return std::string("Identity ") + show(a.value);
    }
};

#endif
