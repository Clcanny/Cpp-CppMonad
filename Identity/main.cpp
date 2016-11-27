#include "Identity.h"
#include "../Monad.h"
#include "../Show.h"
#include "../Maybe/Maybe.h"
#include <iostream>

int main()
{
    const std::function<const Identity<const int>(const int)> f =
        [](const int x)
    {
        return Identity<const int>(x + 1);
    };
    /* const Identity<const int> a = inject(2); */
    /* std::cout << Show<const Identity<const int> >::show(a) << std::endl; */
    std::cout << show(Monad<IdentityWrapper>::inject(2)) << std::endl;
    std::cout << show(Monad<IdentityWrapper>::inject(2) >>= f) << std::endl;
    const Identity<const char> a = Monad<IdentityWrapper>::inject('c');
    const Identity<const Identity<const char> > b = Monad<IdentityWrapper>::inject(a);
    std::cout << show(b) << std::endl;
    const Maybe<const int> c = Just<const int>(2);
    const Identity<const Maybe<const int> > d = Monad<IdentityWrapper>::inject(c);
    std::cout << show(d) << std::endl;
}
