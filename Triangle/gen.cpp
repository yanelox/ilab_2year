#include <iostream>

int main ()
{
    int n = 100000;
    double tmp = 0;

    std::cout << n << std::endl;

    for (int i = 0; i < 9 * n; ++i)
    {
        tmp = rand();

        tmp = tmp * 1000 / RAND_MAX - 500;

        std::cout << tmp << std::endl;
    }
}