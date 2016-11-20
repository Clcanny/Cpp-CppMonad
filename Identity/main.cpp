#include "Identity.h"
#include <iostream>

int main()
{
    const std::function<Identity<int>(const int &)> f = [](const int &x)
    {
        return Identity<int>(x + 1);
    };
    (Identity<int>(2)) >>= f;
}
