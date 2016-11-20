#include "Maybe.h"
#include <iostream>

int main()
{
    const Maybe<const int> a = Just<const int>(2);
    const Maybe<const int> b = Nothing<const int>();
    
    const Maybe<const char> c = Just<const char>('t');
    const Maybe<const char> d = Nothing<const char>();
    
    const Maybe<const Maybe<const int> > e = Just<const Maybe<const int> >(a);
    const Maybe<const Maybe<const int> > f = Nothing<const Maybe<const int> >();
    
    std::function<const Maybe<const int>(const int)> funF = [](const int x)
    {
        return Just<const int>(x + 1);
    };
    std::function<const Maybe<const char>(const char)> funG = [](const char c)
    {
        return Just<const char>(c + 1);
    };
    std::function<const Maybe<const char>(const int)> funH = [](const char x)
    {
        return Just<const char>('y');
    };
    
    std::cout << show((a >>= funH) >>= funG) << std::endl;
    std::cout << show(c) << std::endl;
    std::cout << show(e) << std::endl;
    std::cout << show(f) << std::endl;
    std::cout << show(a >>= funF) << std::endl;
    std::cout << show(((a >>= funF) >>= funF) >>= funF) << std::endl;
    std::cout << show(c >>= funG) << std::endl;
    std::cout << show(d >>= funG) << std::endl;
    std::cout << show(a >> b) << std::endl;
    std::cout << show(b >> a) << std::endl;
    std::cout << show(inject(2)) << std::endl;
    std::cout << show(Just<const Maybe<const int> >(a)) << std::endl;
}
