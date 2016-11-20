#include <string>
#include <locale>

template <class T>
concept bool EqualityComparable = requires(T a, T b)
{
    {
        a == b
    } -> bool;
}

template <class T>
void f(T v)
{
    static_assert(EqualityComparable<T>(v));
}

int main()
{
    f(1);
}

/* class IFoo */
/* { */
/*     public: */
/*         typedef int IsDerivedFromIFoo; */
/* }; */

/* template <typename T> */
/* class Foo<T> */
/* { */
/*     public: */
/*         typedef typename T::IsDerivedFromIFoo IFooGuard; */
/* }; */
