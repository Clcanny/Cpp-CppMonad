#include "State.h"
#include "StateChar.h"
#include "../Maybe/Maybe.h"
#include <iostream>

int main()
{
    Monad<StateChar>::inject(2);
    /* const State<const char, const int> x = inject(2); */
    const function<const typename apply_wrap1<StateChar, const int>::type(const int)>
    f = [](const int a)
    {
        return Monad<StateChar>().inject(a);
    };
    Monad<StateChar>::bind<const int, const int>(Monad<StateChar>().inject(2), f);
    std::cout << Monad<StateChar>::bind<const int, const int>(Monad<StateChar>().inject(2), f).evalState('c') << std::endl;
    std::cout << (Monad<StateChar>::inject(2) >>= f).evalState('c') << std::endl;
    /* std::cout << (Monad<StateChar>().inject(2)).evalState('c') << std::endl; */
    const State<const char, const int> s = Monad<StateChar>::inject(2);
    std::cout << s.evalState('c') << std::endl;
    
    Monad<MaybeWrapper>::inject(2);
    const function<const typename apply_wrap1<MaybeWrapper, const int>::type(const int)>
    g = [](const int a)
    {
        return Monad<MaybeWrapper>().inject(a + 1);
    };
    std::cout << Show<const Maybe<const int> >::show(Monad<MaybeWrapper>::bind<const int, const int>(Monad<MaybeWrapper>::inject(2), g)) << std::endl;
    std::cout << show(Monad<MaybeWrapper>::inject(2) >>= g) << std::endl;
    const Maybe<const int> x = Monad<MaybeWrapper>::bind<const int, const int>(Monad<MaybeWrapper>::inject(2), g);
    std::cout << show(Monad<MaybeWrapper>::inject(2) >>= g) << std::endl;
    const Maybe<const int> y = Monad<MaybeWrapper>::bind<const int, const int>(x, g);
    std::cout << Show<const Maybe<const int> >::show(y) << std::endl;
    std::cout << show(y) << std::endl;
    std::cout << show((Monad<MaybeWrapper>::inject(2) >>= g) >>= g) << std::endl;
    const Maybe<const int> a = Just<const int>(2);
    const Maybe<const int> b = Nothing<const int>();
    const Maybe<const char> c = Just<const char>('t');
    const Maybe<const char> d = Nothing<const char>();
    const Maybe<const Maybe<const int> > e = Just<const Maybe<const int> >(a);
    const Maybe<const Maybe<const int> > h = Nothing<const Maybe<const int> >();
    std::cout << Show<const Maybe<const Maybe<const int> > >::show(e) << std::endl;
    std::cout << show(e) << std::endl;
    std::cout << Show<const Maybe<const int> >::show(b) << std::endl;
    std::cout << show(b) << std::endl;
}
