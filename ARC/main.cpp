#include <algorithm>
#include "ARC.h"
#include <list>
#include <iostream>

#include "ARC.hpp"

using namespace std;

int main ()
{
    ARC <int> cache;

    int n = 0;

    long int res = 0;

    cin >> n;

    while(n)
    {
        cin >> n;

        res += cache.push(n);
    }           

    cout << res << endl;

    return 0;
}