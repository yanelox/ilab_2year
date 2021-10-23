#include "matrix.h"
#include <iostream>

namespace matrix
{
    //frac

    template <typename T>
    bool frac_ <T>::is_valid () const
    {
        return !equal(denominator, (T) 0);
    }

    template <typename T>
    void frac_ <T>::print () const
    {
        std::cout << numerator << "/" << denominator;
    }

    //row 

    

    //matrix

    template <typename T>
    int matrix_ <T>::g_elimination ()
    {
        int res = 1;

        for (size_t i = 0; i < get_size(); ++i)
        {
            size_t j = i;

            while (j < get_size() and (*this)[j][i].is_zero())
                ++j;
            
            if (j != get_size())
            {
                if (j != i)
                {
                    std::swap ((*this)[j], (*this)[i]);
                    res *= -1;
                }
                
                for (size_t k = i + 1; k < get_size(); ++k)
                    if ((*this)[k][i].is_zero() == 0)
                        (*this)[k] = (*this)[k] - (*this)[i] * ((*this)[k][i] / (*this)[i][i]);
            }
        }

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

    template <typename T>
    T matrix_ <T>::get_det (int sign) const
    {
        T res = T{1};

        for (size_t i = 0; i < size; ++i)
            if (!(*this)[i][i].is_zero())
                res = res * (*this)[i][i];
            else
            {
                res = T{0};
                break;
            }

        res = res * sign;

        return res;
    }
}
