#ifndef Show_H
#define Show_H

#include "Header.h"

template <class T>
struct Show
{
    typedef false_type ImpShow;
    static const string show(const T value);
};

template <>
struct Show<const int>
{
    typedef true_type ImpShow;
    static const string show(const int value)
    {
        return to_string(value);
    }
};

#endif
