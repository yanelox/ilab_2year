#include <algorithm>
#include "ARC.h"
#include <list>
#include <iostream>

using namespace std;

int main ()
{
    ARC cache;

    int n = 0;

    while(true)
    {
        cin >> n;

        if (n == 0)
            break;

        cache.push (n);

        cache.print ();
    }
}