#include "matrix.h"
#include <iostream>

namespace matrix
{
    //row 

    //matrix

    template <typename T>
    double matrix_ <T>::g_elimination ()
    {
        double res = 1.0;
        double c = 1.0;
        int k = 0;

        for (int i = 0; i < size; ++i)
        {
            if (equal (static_cast <double> ((*this)[i][i]), 0.0))
            {
                for (k = i + 1; k < size; ++k)
                    if (!equal (static_cast <double> ((*this)[k][i]), 0.0))
                    {
                        std::swap ((*this)[i], (*this)[k]);
                        break;
                    }

                if (k == size)
                {
                    res = 0.0;
                    break;
                }
            }

            for (int j = i + 1; j < size; ++j)
            {
                    c = - static_cast <double> ((*this)[j][i]) / static_cast <double> ((*this)[i][i]);
                    (*this)[j] = (*this)[j] + (*this)[i] * c;
            }
        }

        for (int i = 0; i < size; ++i)
            res *= static_cast <double> ((*this)[i][i]);

        return res;
    }

    template <typename T>
    int matrix_ <T>::fill ()
    {
        for (size_t i = 0; i < size; ++i)
            for (size_t j = 0; j < size; ++j)
                std::cin >> (*this)[i][j];

        return 0;
    }
}
