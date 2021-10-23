#include <iostream>
#include <cmath>
#include "lib/matrix.hpp"

#define TYPE int

int main ()
{
    std::cout.precision(10);

    srand(time(NULL));

    size_t size = 10;

    matrix::matrix_ <TYPE> M {size};
    
    TYPE det = 42;

    for (size_t i = 0; i < size; ++i)
        for (size_t j = 0; j < size; ++j)
            if (i == j)
                M[i][j] = 1;

            else
                M[i][j] = 0;

    M[0][0] = 3;
    M[5][5] = 2;
    M[9][9] = 7;

    for (size_t i = 0; i < size; ++i)
        for (size_t j = 0; j < size; ++j)
        {
            TYPE c = ((TYPE) i - size) / 2 + std::rand() % (size - i);
            
            if (i != j)
                M[j] = M[j] + M[i] * c; 
        }

    std::cout << size << std::endl;

    std::cout << M;
}