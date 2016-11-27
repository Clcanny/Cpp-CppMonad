#ifndef TrivalValue_H
#define TrivalValue_H

#include "Header.h"

template <class T>
struct TrivalValue
{
    static T value;
};

template <>
struct TrivalValue<const int>
{
    static const int value;
};
const int TrivalValue<const int>::value = 0;

template <>
struct TrivalValue<const char>
{
    static const char value;
};
const char TrivalValue<const char>::value = '0';

template <>
struct TrivalValue<const string>
{
    static const string value;
};
const string TrivalValue<const string>::value = "";

#endif
