#include "Identity.h"
/* #include "../Maybe/Maybe.h" */
#include <iostream>

int main()
{
    const std::function<const Identity<const int>(const int)> f =
        [](const int x)
    {
        return Identity<const int>(x + 1);
    };
    std::cout << show(inject<Identity, const int>()(2) >>= f) << std::endl;
    const Identity<const char> a = inject<Identity, const char>()('c');
    const Identity<const Identity<const char> > b = inject<Identity, const Identity<const char> >()(a);
    std::cout << show(b) << std::endl;
    /* const Maybe<const int> c = Just<const int>(2); */
    /* const Identity<const Maybe<const int> > d = inject<Identity, const Maybe<const int> >()(c); */
}
