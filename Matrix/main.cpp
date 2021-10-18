#include "matrix.hpp"
#include <iostream>
#include <vector>
#include <time.h>

int main ()
{
    size_t n;

    std::cin >> n;

    std::vector <double> v (n * n);

    for (int i = 0; i < n * n; ++i)
    {
        double x;

        std::cin >> x;

        v[i] = x;
    }

    matrix::matrix_ <double> M {v, n};

    // M.print();

    // std::pair <matrix::matrix_ <int>, matrix::matrix_ <int>> res = M.get_LU();
    // res.first.print();
    // res.second.print();

    matrix::frac_ <double> det = M.get_det();
    // det.print();

    std::cout << det.numerator / det.denominator << std::endl;

    return 0;
}