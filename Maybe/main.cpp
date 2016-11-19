#include "Maybe.h"
#include <iostream>

Maybe<int> f(int x)
{
    return Maybe<int>::Just(x + 1);
}

int main()
{
    const Maybe<int> a = Maybe<int>::Just(2);
    const Maybe<int> b = Maybe<int>::Nothing();
    std::function<Maybe<int>(const int &)> f = [](int x)
    {
        return Maybe<int>::Just(x + 1);
    };
    std::cout << show(a >>= f) << std::endl;
    std::cout << show(((a >>= f) >>= f) >>= f) << std::endl;
    std::cout << show(a >> b) << std::endl;
    std::cout << show(b >> a) << std::endl;
    std::cout << show(inject(2)) << std::endl;
}
