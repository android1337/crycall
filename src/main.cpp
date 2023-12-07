#include <iostream>
#include "crycall.hpp"

int sum(int a, int b)
{
    return a + b;
}

int main()
{
    printf("sum: %d", crycall(int, sum, 10, 5));

    return 0;
}
