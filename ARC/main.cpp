#include <algorithm>
#include "ARC.h"
#include <list>
#include <iostream>

#include "ARC.hpp"

using namespace std;

int main ()
{
    ARC <int> cache;

    int n = 1;

    while(n)
    {
        cin >> n;

        cache.push(n);

        cache.print();
    }           

    return 0;
}