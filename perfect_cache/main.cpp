#include "prfct.hpp"
#include <iostream>

int main ()
{
    prfct::Cache_ <int, int> cache(5);

    int n;

    std::cin >> n;

    std::vector <std::pair <int, int>> req(2 * n);

    for (int i = 0; i < n; ++i)
    {
        std::cin >> req[i].first;

        req[i].second = req[i].first;
    }

    std::cout << cache.start_push (req) << std::endl;

    // cache.print();
}