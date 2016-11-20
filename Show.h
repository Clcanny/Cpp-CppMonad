#include <type_traits>
#include <iostream>

template <class T>
class ImpShow
{
    public:
        typedef std::false_type Has;
};

template <class T>
const std::string show(const T value);

template <>
class ImpShow<const int>
{
    public:
        typedef std::true_type Has;
};

template <>
const std::string show(const int value)
{
    return std::to_string(value);
}

template <>
class ImpShow<const char>
{
    public:
        typedef std::true_type Has;
};

template <>
const std::string show(const char value)
{
    return std::string(1, value);
}
