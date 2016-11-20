#ifndef TrivalValue_H
#define TrivalValue_H

template <class T>
class TrivalValue
{
    public:
        static T value;
};

template <>
class TrivalValue<const int>
{
    public:
        static const int value;
};

const int TrivalValue<const int>::value = 0;

template <>
class TrivalValue<const char>
{
    public:
        static const char value;
};

const char TrivalValue<const char>::value = '0';

#endif
