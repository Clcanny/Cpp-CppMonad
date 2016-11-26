#ifndef Maybe_H
#define Maybe_H

#include "Header.h"
#include "TrivalValue.h"
#include "Monad.h"
#include "Show.h"

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
class TrivalValue<const Maybe<const A> >
{
    public:
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
};

template <>
struct Show<MaybeWrapper>
{
    template <class A>
    using ImpShow = typename Show<const A>::ImpShow;
    /* typedef true_type ImpShow; */
    
    template <class A>
    static const string show(typename apply_wrap1<MaybeWrapper, const A>::type a)
    {
        typedef typename Show<const A>::ImpShow Has;
        /* static_assert(std::is_same<Has, std::true_type>::value, ""); */
        if (a.m_valid == false)
        {
            return "Nothing";
        }
        else
        {
            return std::string("Just ") + Show<const A>::show(a.m_value);
        }
    }
};

#endif
