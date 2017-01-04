#include <vector>
#include <iostream>

template <class T, template <class ELEM> class CONT>
void f()
{
}

int main()
{
    f<int, std::vector>();
}
