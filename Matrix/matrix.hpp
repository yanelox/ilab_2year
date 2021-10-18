#include "matrix.h"
#include <iostream>

namespace matrix
{
    //frac

    template <typename T>
    int frac_ <T>::is_valid () const
    {
        return !equal(denominator, (T) 0);
    }

    template<typename T>
    void frac_ <T>::print () const
    {
        std::cout << numerator << "/" << denominator;
    }

    //matrix

    template <typename T>
    void matrix_ <T>::print (int mode) const
    {
        if (mode == 0)
            std::cout << "matrix:\n";

        for (size_t i = 0; i < size; ++i)
        {
            if (mode == 0)
                std::cout << "{";

            for (size_t j = 0; j < size; ++j)
            {
                std::cout << (*this)(i, j);

                if (j != size - 1)
                    std::cout << " ";
            }

            if (mode == 0)
                std::cout << "}\n";

            else
                std::cout << std::endl;
        }
    }

    template <typename T>
    int matrix_ <T>::is_valid () const
    {
        return (size > 0) and numbers;
    }

    template <typename T>
    int matrix_ <T>::fill ()
    {
        if (!is_valid())
            return -1;

        size_t q_size = size * size;

        for (size_t i = 0; i < q_size; ++i)
            std::cin >> numbers[i];

        return 0;
    }

    template <typename T>
    std::pair <matrix_ <frac_ <T>>, matrix_ <frac_ <T>>> matrix_ <T>::get_LU () const
    {
        std::pair <matrix_ <frac_ <T>>, matrix_ <frac_ <T>>> res {{size}, {size}};
        
        for (size_t i = 0; i < size; ++i)
            for (size_t j = 0; j < size; ++j)
            {
                res.second(i, j) = frac_ <T>{0};
                res.first(i, j) = (i == j) ? frac_ <T>{1} : frac_ <T>{0};
            }
        
        for (size_t i = 0; i < size; ++i)
            for (size_t j = 0; j < size; ++j)
                if (i <= j)
                {
                    frac_ <T> tmp{0};

                    res.second(i, j) = (*this)(i, j);
                    
                    for (size_t k = 0; k < i; ++k)
                    {
                        tmp -= res.first(i, k) * res.second(k, j);
                    }

                    res.second(i, j) += tmp;
                }

                else
                {
                    frac_ <T> tmp{0};

                    res.first(i, j) = (*this)(i, j);

                    for (size_t k = 0; k < j; ++k)
                        tmp -= res.first(i, k) * res.second(k, j);

                    res.first(i, j) += tmp;

                    res.first(i, j) = res.first(i, j) / res.second(j, j);
                }

        return res;
    }

    template <typename T>
    frac_ <T> matrix_ <T>::get_det () const
    {
        std::pair <matrix_ <frac_ <T>>, matrix_ <frac_ <T>>> res = get_LU();
    
        frac_ <T> det1{1}, det2{1};

        for (size_t i = 0; i < size; ++i)
        {
            // std::cout << "--" << std::endl << i << std::endl;
            // res.first(i, i).print(); std::cout << std::endl;
            // res.second(i, i).print();std::cout << std::endl;
            
            det1 *= res.first(i, i);
            det2 *= res.second(i, i);

            // det1.print();std::cout << std::endl;
            // det2.print();std::cout << std::endl;
        }

        return det1 * det2;
    }
}
