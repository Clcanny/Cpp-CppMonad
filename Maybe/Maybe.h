#ifndef Maybe_H
#define Maybe_H

#include "../Header.h"
#include "../TrivalValue.h"
#include "../Monad.h"
#include "../Show.h"

template <class T>
class Maybe
{
    private:
        const T m_value;
        const bool m_valid;
        
        template <class A>
        friend class Monad;
        
        template <class A>
        friend class Show;
        
    private:
        Maybe() :
            m_value(TrivalValue<T>::value), m_valid(false) {}
        Maybe(const T value) :
            m_value(value), m_valid(true) {}
            
    private:
        template <class A>
        friend const Maybe<const A> Just(const A value);
        
        template <class A>
        friend const Maybe<const A> Nothing();
};

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

template <class A>
struct TrivalValue<const Maybe<const A> >
{
    static const Maybe<const A> value;
};

template <class A>
const Maybe<const A> TrivalValue<const Maybe<const A> >::value =
    Nothing<const A>();

struct MaybeWrapper
{
    template <class T>
    struct apply
    {
        typedef Maybe<const T> type;
    };
};

template <>
struct Monad<MaybeWrapper>
{
    typedef true_type ImpMonad;
    
    template <class A>
    static const typename apply_wrap1<MaybeWrapper, const A>::type inject(const A a)
    {
        return Just<const A>(a);
    }
    
    template <class A, class B>
    static const typename apply_wrap1<MaybeWrapper, const B>::type bind
    (const typename apply_wrap1<MaybeWrapper, const A>::type a,
     const function<const typename apply_wrap1<MaybeWrapper, const B>::type(const A)> b)
    {
        if (a.m_valid == false)
        {
            return Nothing<const B>();
        }
        else
        {
            return b(a.m_value);
        }
    }
    
    template <class A, class B>
    static const typename apply_wrap1<MaybeWrapper, const B>::type bind_
    (
        const typename apply_wrap1<MaybeWrapper, const A>::type a,
        const typename apply_wrap1<MaybeWrapper, const B>::type b
    )
    {
        const function<const typename apply_wrap1<MaybeWrapper, const B>::type(const A)>
        fn = [&](const A)
        {
            return b;
        };
        return bind<const A, const B>(a, fn);
    }
};

template <class A>
const Maybe<const A> inject(const A a)
{
    return Monad<MaybeWrapper>::inject<const A>(a);
}

/* 此处用的是重载而不是偏特化 */
/* C++的类型推断真的菜 */
/* 需要针对每一个具体Monad（比如说Maybe）而不是针对MonadWrapper（比如说MaybeWrapper） */
/* 重载操作符 */
template <class A, class B>
const Maybe<const B> operator>>=
(
    const Maybe<const A> a,
    const function<const Maybe<const B>(const A)> b
)
{
    return Monad<MaybeWrapper>::bind<const A, const B>(a, b);
}

template <class A, class B>
const Maybe<const B> operator>>
(
    const Maybe<const A> a,
    const Maybe<const B> b
)
{
    return Monad<MaybeWrapper>::bind_<const A, const B>(a, b);
}

template <class T>
struct Show<const Maybe<const T> >
{
    typedef typename Show<const T>::ImpShow ImpShow;
    
    static const string show(const Maybe<const T> a)
    {
        typedef typename Show<const T>::ImpShow Has;
        static_assert(std::is_same<Has, std::true_type>::value, "");
        if (a.m_valid == false)
        {
            return "Nothing";
        }
        else
        {
            return std::string("Just ") + Show<const T>::show(a.m_value);
        }
    }
};

#endif
