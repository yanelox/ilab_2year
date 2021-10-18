#include <iostream>
#include "matrix.hpp"

int main ()
{
    srand(time(NULL));

    size_t size = 10;

    matrix::matrix_ <double> M {size};

    for (size_t i = 0; i < size; ++i)
        for (size_t j = 0; j < size; ++j)
            if (i == j)
                M(i, j) = 1;

            else
                M(i, j) = 0;

    size_t tmpi = rand() % (size / 2);

    M(tmpi, tmpi) = 6;
    M(tmpi + size/2, tmpi + size/2) = 7;

    // M.print(0);

    for (size_t i = 0; i < size; ++i)
        for (size_t j = 0; j < size; ++j)
        {
            double c = -(double) (size - i) / 2 + rand() % (size - i);

            if (i != j)
                for (size_t k = 0; k < size; ++k)
                    M(i, k) += c * M(j, k); 
        }

    std::cout << size << std::endl;

    M.print(1);
}