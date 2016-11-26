#include "State.h"
#include <iostream>

int main()
{
    Monad<StateChar>::inject(2);
    const function<const typename apply_wrap1<StateChar, const int>::type(const int)>
    f = [](const int a)
    {
        return Monad<StateChar>().inject(a);
    };
    Monad<StateChar>::bind<const int, const int>(Monad<StateChar>().inject(2), f);
    std::cout << Monad<StateChar>::bind<const int, const int>(Monad<StateChar>().inject(2), f).evalState('c') << std::endl;
    /* std::cout << (Monad<StateChar>().inject(2)).evalState('c') << std::endl; */
    const State<const char, const int> s = Monad<StateChar>::inject(2);
    std::cout << s.evalState('c') << std::endl;
}
