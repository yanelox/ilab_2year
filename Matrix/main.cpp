#include "lib/matrix.hpp"
#include <iostream>
#include <vector>
#include <time.h>

#define TYPE int

int main ()
{
    size_t n = 0;

    std::cin >> n;

    std::vector <matrix::frac_ <TYPE>> vec(n * n);

    for (size_t i = 0; i < n * n; ++i)
    {
        TYPE x;

        std::cin >> x;

        vec[i] = matrix::frac_ <TYPE> {x};
    }

    matrix::matrix_ <matrix::frac_ <TYPE>> M{vec.begin(), vec.end(), n};

    // std::cout << M;
    // std::cout << std::endl;

    int tmp = M.g_elimination();

    // std::cout << M; 

    matrix::frac_ <TYPE> res = M.get_det(tmp);

    std::cout << res.numerator / res.denominator << std::endl;
}