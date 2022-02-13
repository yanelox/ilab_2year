#include "matrix.h"
#include <iostream>

namespace matrix
{
    //row 

    template <typename T>
    row_ <T> row_ <T>::operator + (const row_ <T> &rhs) const
    {
        assert (size == rhs.size);

        row_ res{size};

        for (size_t i = 0; i < size; ++i)
            res[i] = elements[i] + rhs.elements[i];

        return res;
    }

    template <typename T>
    row_ <T> row_ <T>::operator - (const row_ <T> &rhs) const
    {
        assert (size == rhs.size);

        row_ res{size};

        for (size_t i = 0; i < size; ++i)
            res[i] = elements[i] - rhs.elements[i];

        return res;
    }

    template <typename T>
    row_ <T> operator * (const row_ <T> &second, const T &first)
    {
        size_t Size = second.get_size();

        row_ <T> res{Size};

        for (size_t i = 0; i < Size; ++i)
            res[i] = second[i] * first;

        return res;
    }

    template <typename T>
    row_ <T> operator * (const T &first, const row_ <T> &second)
    {
        size_t Size = second.get_size();

        row_ <T> res{Size};

        for (size_t i = 0; i < Size; ++i)
            res[i] = second[i] * first;

        return res;
    }

    //matrix

    template <typename T>
    matrix_ <T> matrix_ <T>::operator + (const matrix_ &rhs) const
    {
        assert (size == rhs.size);
    
        matrix_ <T> res{size};

        for (size_t i = 0; i < size; ++i)
            res[i] = elements[i] + rhs.elements[i];

        return res;
    }

    template <typename T>
    matrix_ <T> matrix_ <T>::operator - (const matrix_ <T> &rhs) const
    {
        assert (size == rhs.size);

        matrix_ <T> res{size};

        for (size_t i = 0; i < size; ++i)
            res[i] = elements[i] - rhs.elements[i];

        return res;
    }

    template <typename T>
    matrix_ <T> matrix_ <T>::operator * (const matrix_ <T> &rhs) const
    {
        assert (size == rhs.size);

        matrix_ <T> res{size};

        T sum = static_cast <T> (0);

        for (int i = 0; i < size; ++i)
            for (int j = 0; j < size; ++j)
            {
                sum = static_cast <T> (0);

                for (int k = 0; k < size; ++k)
                    sum = sum + elements[i][k] * rhs[k][j];

                res[i][j] = sum;
            }

        return res;
    }

    template <typename T>
    matrix_ <T> operator * (matrix_ <T> &first, const T &second)
    {
        size_t Size = first.get_size();

        matrix_ <T> res{Size};

        for (int i = 0; i < Size; ++i)
            res[i] = first[i] * second;

        return res;
    }

    template <typename T>
    matrix_ <T> operator * (const T &second, matrix_ <T> &first)
    {
        size_t Size = first.get_size();

        matrix_ <T> res{Size};

        for (int i = 0; i < Size; ++i)
            res[i] = first[i] * second;

        return res;
    }

    template <typename T>
    double matrix_ <T>::det ()
    {
        matrix_ <double> work_matrix {size};

        for (int i = 0; i < size; ++i)
            for (int j = 0; j < size; ++j)
                work_matrix.elements[i][j] = elements[i][j];

        double res = 1.0;
        double c = 1.0;
        int k = 0;

        for (int i = 0; i < size; ++i)
        {
            if (equal (static_cast <double> (work_matrix.elements[i][i]), 0.0))
            {
                for (k = i + 1; k < size; ++k)
                    if (!equal (static_cast <double> (work_matrix.elements[k][i]), 0.0))
                    {
                        std::swap (work_matrix.elements[i], work_matrix.elements[k]);
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
                    c = - static_cast <double> (work_matrix.elements[j][i]) / static_cast <double> (work_matrix.elements[i][i]);
                    work_matrix.elements[j] = work_matrix.elements[j] + work_matrix.elements[i] * c;
            }
        }

        for (int i = 0; i < size; ++i)
            res *= static_cast <double> (work_matrix.elements[i][i]);

        return res;
    }

    template <typename T>
    int matrix_ <T>::fill ()
    {
        for (size_t i = 0; i < size; ++i)
            for (size_t j = 0; j < size; ++j)
                std::cin >> elements[i][j];

        return 0;
    }
}
