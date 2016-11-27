#ifndef StaticFunc
#define StaticFunc

#include "Header.h"

template <class A, class B>
struct And
{
    typedef false_type res_type;
};

template <>
struct And<true_type, true_type>
{
    typedef true_type res_type;
};

template <class A, class B>
struct Or
{
    typedef true_type res_type;
};

template <>
struct Or<false_type, false_type>
{
    typedef false_type res_type;
};

#endif
