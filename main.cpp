#include "Show.h"

int main()
{
    std::cout << std::is_same<ImpShow<int>::Has, std::true_type>::value;
}
