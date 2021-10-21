#include "matrix.hpp"
#include <iostream>
#include <vector>
#include <time.h>

int main ()
{
    size_t n = 0;

    std::cin >> n;

    std::vector <matrix::frac_ <double>> vec(n * n);

    for (size_t i = 0; i < n * n; ++i)
    {
        double x;

        std::cin >> x;

        vec[i] = matrix::frac_ <double> {x};
    }

    matrix::matrix_ <matrix::frac_ <double>> M{n};

    M.fill (vec);

    // std::cout << M;

    int tmp = M.g_elimination();

    matrix::frac_ <double> res = M.get_det(tmp);

    std::cout << res.numerator / res.denominator << std::endl;
}