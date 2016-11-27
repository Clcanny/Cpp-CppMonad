#ifndef Show_H
#define Show_H

#include "Header.h"

template <class T>
struct Show
{
    typedef false_type ImpShow;
    static const string show(const T value);
};

/* 加一个函数，用起来更加方便 */
template <class T>
const string show(const T value)
{
    static_assert(is_same<typename Show<const T>::ImpShow, true_type>::value, "");
    return Show<const T>::show(value);
}

template <>
struct Show<const int>
{
    typedef true_type ImpShow;
    static const string show(const int value)
    {
        return to_string(value);
    }
};

template <>
struct Show<const char>
{
    typedef true_type ImpShow;
    static const string show(const char value)
    {
        return string(1, value);
    }
};

template <>
struct Show<const string>
{
    typedef true_type ImpShow;
    static const string show(const string value)
    {
        return value;
    }
};

#endif
