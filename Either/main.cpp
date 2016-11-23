#include <iostream>
#include "Either.h"

int main()
{
    Either<const int, const char> a = Left<const int, const char>(2);
    Either<const int, const int> b = Left<const int, const int>(3);
    Either<const int, const int> c = Right<const int, const int>(3);
    Either<const int, const Either<const int, const int> > d
        = Right<const int, const Either<const int, const int> >(b);
    std::function<const Either<const int, const char>(const char)>
    f = [](const char)
    {
        return Left<const int, const char>(2);
    };
    std::cout << show(a) << std::endl;
    std::cout << show(b) << std::endl;
    std::cout << show(c) << std::endl;
    std::cout << show(d) << std::endl;
    std::cout << show(a >>= f) << std::endl;
}
