#include <type_traits>
#include <iostream>

template <class T>
class ImpShow
{
    public:
        typedef std::false_type Has;
};

template <>
class ImpShow<int>
{
    public:
        typedef std::true_type Has;
};

template <class T>
std::string show(const T &value);
