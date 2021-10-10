#include "prfct.hpp"
#include <iostream>

int main ()
{
    int size, n;

    std::cin >> size;

    prfct::Cache_ <int, int> cache(size);

    std::cin >> n;

    std::vector <std::pair <int, int>> req(n);

    for (int i = 0; i < n; ++i)
    {
        std::cin >> req[i].first;

        req[i].second = req[i].first;
    }

    std::cout << cache.start_push (req) << std::endl;

    // cache.print();
}