#include "lib/matrix.hpp"
#include <iostream>
#include <vector>
#include <time.h>

int main ()
{
    size_t n = 0;

    std::cin >> n;

    std::vector <double> vec(n * n);

    for (size_t i = 0; i < n * n; ++i)
    {
        double x;

        std::cin >> x;

        vec[i] = x;
    }

    matrix::matrix_ <double> M{vec.begin(), vec.end(), n};

    // std::cout << M;
    // std::cout << std::endl;

    double det = M.det();

    // std::cout << M;

    std::cout << det << std::endl;
}
