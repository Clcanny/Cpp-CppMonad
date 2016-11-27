#ifndef Either_H
#define Either_H

#include "../Header.h"
#include "../TrivalValue.h"
#include "../Show.h"
#include "../Monad.h"
#include "../StaticFunc.h"

template <class LeftType, class RightType>
class Either
{
    private:
        const LeftType leftValue;
        const RightType rightValue;
        const bool isLeft;
        
    private:
        /* 防止Type一致导致的函数相同类型 */
        Either(const LeftType l, true_type);
        Either(const RightType r, false_type);
        
    private:
        template <class A, class B>
        friend const Either<const A, const B> Left(const A a);
        
        template <class A, class B>
        friend const Either<const A, const B> Right(const B b);
        
        template <class A>
        friend class Monad;
        
        template <class A>
        friend class Show;
};

template <class LeftType, class RightType>
Either<LeftType, RightType>::Either(const LeftType l, true_type):
    leftValue(l),
    rightValue(TrivalValue<const RightType>::value),
    isLeft(true) {}

template <class LeftType, class RightType>
Either<LeftType, RightType>::Either(const RightType r, false_type):
    leftValue(TrivalValue<const LeftType>::value),
    rightValue(r),
    isLeft(false) {}

template <class A, class B>
const Either<const A, const B> Left(const A a)
{
    return Either<const A, const B>(a, true_type());
}

template <class A, class B>
const Either<const A, const B> Right(const B b)
{
    return Either<const A, const B>(b, false_type());
}

template <class A, class B>
struct TrivalValue<const Either<const A, const B> >
{
    static const Either<const A, const B> value;
};

template <class A, class B>
const Either<const A, const B> TrivalValue<const Either<const A, const B> >::value =
    Left<const A, const B>(TrivalValue<const A>::value);

template <class A>
struct EitherWrapper
{
    template <class B>
    struct apply
    {
        typedef const Either<const A, const B> type;
    };
};

template <class T>
using EitherT = EitherWrapper<const T>;

template <>
struct Monad<EitherT>
{
    typedef true_type ImpMonad;
    
    template <class A>
    static const typename apply_wrap1<EitherT, const A>::type
    inject(const A a)
    {
        return Right<const T, const A>(a);
    }
    
    template <class A, class B>
    static const typename apply_wrap1<EitherWrapper<const T>, const A>::type bind
    (const typename apply_wrap1<EitherWrapper<const T>, const A>::type a,
     const function<const typename apply_wrap1<EitherWrapper<const T>,
     const B>::type(const A)> b)
    {
        if (a.isLeft == true)
        {
            return Left<const T, const B>(a.leftValue);
        }
        else
        {
            return b(a.rightValue);
        }
    }
    
    template <class A, class B>
    static const typename apply_wrap1<EitherWrapper<const T>, const A>::type bind_
    (
        const typename apply_wrap1<EitherWrapper<const T>, const A>::type a,
        const typename apply_wrap1<EitherWrapper<const T>, const B>::type b
    )
    {
        const function<const typename apply_wrap1
        <EitherWrapper<const T>, const B>::type(const A)>
        fn = [&](const A)
        {
            return b;
        };
        return bind<const A, const B>(a, fn);
    }
};

template <class A, class B>
const Either<const A, const B> inject(const B b)
{
    return Monad<EitherWrapper<const A> >::inject<const B>(b);
}

template <class T, class A, class B>
const Either<const T, const B> operator>>=
(
    const Either<const T, const A> a,
    const function<const Either<const T, const B>(const A)> b
)
{
    return Monad<EitherWrapper<const T> >::bind<const A, const B>(a, b);
}

template <class T, class A, class B>
const Either<const T, const B> operator>>
(
    const Either<const T, const A> a,
    const Either<const T, const B> b
)
{
    return Monad<EitherWrapper<const A> >::bind_<const A, const B>(a, b);
}

template <class A, class B>
struct Show<const Either<const A, const B> >
{
    typedef typename And
    <typename Show<const A>::ImpShow,
    typename Show<const B>::ImpShow>::res_type ImpShow;
    
    static const string show(const Either<const A, const B> a)
    {
        typedef typename Show<const A>::ImpShow HasA;
        typedef typename Show<const B>::ImpShow HasB;
        static_assert(std::is_same<HasA, true_type>::value, "");
        static_assert(std::is_same<HasB, true_type>::value, "");
        if (a.isLeft)
        {
            return std::string("Left ") + Show<const A>::show(a.leftValue);
        }
        else
        {
            return std::string("Right ") + Show<const B>::show(a.rightValue);
        }
    }
};

#endif
