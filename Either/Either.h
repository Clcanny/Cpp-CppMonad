#ifndef Either_H
#define Either_H

#include "../Show.h"
#include "../Monad.h"
#include "../TrivalValue.h"
#include <functional>
#include <type_traits>

template <class LeftType, class RightType>
class Either
{
    private:
        const LeftType leftValue;
        const RightType rightValue;
        const bool isLeft;
        
    private:
        /* 防止Type一致导致的函数相同类型 */
        Either(const LeftType l, std::true_type);
        Either(const RightType r, std::false_type);
        
    private:
        template <class A, class B>
        friend const Either<const A, const B> operator>>=
        (
            const Either<const A, const B> a,
            const std::function<const Either<const A, const B>(const B)> func
        );
        
        template <class A, class B>
        friend const Either<const A, const B> Left(const A a);
        
        template <class A, class B>
        friend const Either<const A, const B> Right(const B b);
        
        template <class A, class B>
        friend const std::string show(const Either<const A, const B> a);
};

template <class LeftType, class RightType>
Either<LeftType, RightType>::Either(const LeftType l, std::true_type):
    leftValue(l),
    rightValue(TrivalValue<const RightType>::value),
    isLeft(true) {}

template <class LeftType, class RightType>
Either<LeftType, RightType>::Either(const RightType r, std::false_type):
    leftValue(TrivalValue<const LeftType>::value),
    rightValue(r),
    isLeft(false) {}

template <class A, class B>
const Either<const A, const B> operator>>=
(
    const Either<const A, const B> a,
    const std::function<const Either<const A, const B>(const B)> func
)
{
    if (a.isLeft)
    {
        return a;
    }
    else
    {
        return func(a.rightValue);
    }
}

template <class A, class B>
const Either<const A, const B> Left(const A a)
{
    return Either<const A, const B>(a, std::true_type());
}

template <class A, class B>
const Either<const A, const B> Right(const B b)
{
    return Either<const A, const B>(b, std::false_type());
}

/* 检测不完全 */
template <class A, class B>
class ImpShow<const Either<const A, const B> >
{
    public:
        typedef typename ImpShow<const A>::Has HasA;
        typedef typename ImpShow<const B>::Has HasB;
        typedef HasA Has;
};

template <class A, class B>
class ImpMonad<const Either<const A, const B> >
{
    public:
        typedef std::true_type Has;
};

template <class A, class B>
const std::string show(const Either<const A, const B> a)
{
    typedef typename ImpShow<const A>::Has HasA;
    typedef typename ImpShow<const B>::Has HasB;
    static_assert(std::is_same<HasA, std::true_type>::value, "");
    static_assert(std::is_same<HasB, std::true_type>::value, "");
    if (a.isLeft)
    {
        return std::string("Left ") + show(a.leftValue);
    }
    else
    {
        return std::string("Right ") + show(a.rightValue);
    }
}

#endif
