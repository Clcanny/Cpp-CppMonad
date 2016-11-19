//listm.h
//
//The List monad.
//Provide a way to build up lists over a sequence of operations.  Adds monadic
//functionality to std::list

#pragma once

#include <list>
#include <type_traits>

#include "monad.h"

template<> struct Monad<std::list>
{
    template<typename a> static const std::list<a> unit (a value)
    {
        return std::list<a>(1, value);
    }
};

template<typename a, typename b>
auto operator>>=(const std::list<a> &in, const b &&f) -> decltype(f(in.front()))
{
    typedef typename std::remove_const<decltype(f(in.front()))>::type tmpList;
    tmpList out;
    for (auto i = in.begin(); i != in.end(); ++i)
    {
        tmpList current = f(*i);
        out.splice(out.end(), current);
    }
    return out;
}
