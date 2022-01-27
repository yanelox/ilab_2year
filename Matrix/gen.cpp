#include <iostream>
#include <cmath>
#include "lib/matrix.hpp"

#define TYPE int

int main (int argc, char* argv[])
{
    std::cout.precision(10);

    srand(time(NULL));

    size_t size = 10;

    int c = 1;

    matrix::matrix_ <TYPE> M {size};
    
    TYPE det = 1;

    if (argc == 2)
        det = atoi (argv[1]);

    for (size_t i = 0; i < size; ++i)
        for (size_t j = 0; j < size; ++j)
            if (i == j)
                M[i][j] = 1;

            else
                M[i][j] = 0;

    for (int i = size - 1; i >= 0; --i)
        for (int j = i + 1; j < size; ++j)
        {
            c = rand () % 4 + 1;

            M[j] = M[j] + M[i] * c;
        }

    for (int i = 0; i < size - 1; ++i)
    {
        c = rand () % 7 - 3;

        M[i] = M[i] + M[size - 1] * c;
    }

    for (int i = 0; i < size; ++i)
    {
        M[i][0] = -M[i][0];
        M[i][1] = -M[i][1];
        M[i][4] = -M[i][4];
        M[i][7] = -M[i][7];
    }

    M[4] = M[4] * det;

    std::cout << size << std::endl;

    std::cout << M;
}