#include <algorithm>
#include "ARC.h"
#include <list>
#include <iostream>

#include "ARC.hpp"

int main ()
{
    int n = 0;

    unsigned long c = 0;

    int x;

    long int res = 0;
    
    std::cin >> c;

    ARC::Cache <int> cache {c};    

    std::cin >> n;

    for (int i = 0; i < n ;++i)
    {
        std::cin >> x;

        res += cache.push(x);
    }           

    std::cout << res << std::endl;

    // cache.print();

    return 0;
}