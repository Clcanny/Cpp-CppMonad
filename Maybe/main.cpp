#include "Maybe.h"
#include <iostream>

int main()
{
    const Maybe<const int> a = Just<const int>(2);
    const Maybe<const int> b = Nothing<const int>();
    std::function<const Maybe<const int>(const int)> f = [](const int x)
    {
        return Just<const int>(x + 1);
    };
    a >>= f;
    (a >>= f) >>= f;
    std::cout << show(a >>= f) << std::endl;
    std::cout << show(((a >>= f) >>= f) >>= f) << std::endl;
    std::cout << show(a >> b) << std::endl;
    std::cout << show(b >> a) << std::endl;
    std::cout << show(inject(2)) << std::endl;
    /* std::cout << show(Maybe<Maybe<int> >::Just(a)) << std::endl; */
}
