#ifndef StaticFunc
#define StaticFunc

#include <type_traits>

template <class A, class B>
class And
{
    public:
        typedef std::false_type res_type;
};

template <>
class And<std::true_type, std::true_type>
{
    public:
        typedef std::true_type res_type;
};

#endif
