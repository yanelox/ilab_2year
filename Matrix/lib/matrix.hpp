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
        return second * first;
    }

    template <typename T>
    bool row_ <T>::operator == (const row_ &rhs) const
    {
        if (size != rhs.size)
            return false;

        for (int i = 0; i < size; ++i)
            if (elements[i] != rhs.elements[i])
                return false;

        return true;
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

        T sum = 0;

        for (int i = 0; i < size; ++i)
            for (int j = 0; j < size; ++j)
            {
                sum = 0;

                for (int k = 0; k < size; ++k)
                    sum = sum + elements[i][k] * rhs[k][j];

                res[i][j] = sum;
            }

        return res;
    }

    template <typename T>
    matrix_ <T> operator * (const matrix_ <T> &first, const T &second)
    {
        size_t Size = first.get_size();

        matrix_ <T> res{Size};

        for (int i = 0; i < Size; ++i)
            res[i] = first[i] * second;

        return res;
    }

    template <typename T>
    matrix_ <T> operator * (const T &second, const matrix_ <T> &first)
    {
        return first * second;
    }

    template <typename T>
    T matrix_ <T>::det () const
    {
        matrix_ <double> work_matrix {*this};
        
        double res = 1.0;
        double c = 1.0;
        int k = 0;

        for (int i = 0; i < size; ++i)
        {
            if (equal (work_matrix.elements[i][i], 0.0))
            {
                auto should_swap = [i](const row_ <double> &rhs) {return !equal (rhs[i], 0.0);};

                auto find_result = std::find_if (work_matrix.elements.begin() + i + 1, 
                                                 work_matrix.elements.end(),
                                                 should_swap);

                if (find_result != work_matrix.elements.end())
                {
                    res *= -1;
                    std::swap (work_matrix.elements[i], *find_result);
                }

                else
                {
                    res = 0.0;
                    break;
                }
            }

            for (int j = i + 1; j < size; ++j)
            {
                c = - work_matrix.elements[j][i] / work_matrix.elements[i][i];
                work_matrix.elements[j] = work_matrix.elements[j] + work_matrix.elements[i] * c;
            }
        }

        for (int i = 0; i < size; ++i)
            res *= work_matrix.elements[i][i];

        return static_cast <T> (res);
    }

    template <typename T>
    bool matrix_ <T>::operator == (const matrix_ &rhs) const
    {
        if (size != rhs.size)
            return false;

        for (int i = 0; i < size; ++i)
            if (!(elements[i] == rhs.elements[i]))
                return false;

        return true;
    }

    template <typename T>
    int matrix_ <T>::fill (std::istream &in)
    {
        for (size_t i = 0; i < size; ++i)
            for (size_t j = 0; j < size; ++j)
                in >> elements[i][j];

        return 0;
    }
}
