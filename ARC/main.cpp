#include <algorithm>
#include "ARC.h"
#include <list>
#include <iostream>

#include "ARC.hpp"

int main ()
{
    ARC <int> cache;

    int n = 0;

    long int res = 0;

    std::cin >> n;

    for (int i = 0; i < n ;++i)
    {
        std::cin >> n;

        res += cache.push(n);
    }           

    std::cout << res << std::endl;

    return 0;
}