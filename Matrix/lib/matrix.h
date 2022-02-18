#include <algorithm>
#include <cassert>
#include <vector>
#include <iostream>
#include <assert.h>

namespace matrix
{
    double eps = 0.00001;
    
    template <typename T>
    bool equal (T n1, T n2)
    {
        if (n1 == n2)
            return true;

        if (n1 > n2)
            return (n1 - n2) <= eps;

        else
            return (n2 - n1) <= eps;

        return false;
    }

    template <typename T>
    class row_
    {
        T *elements = NULL;

        size_t size = 0;

        public:

        row_ () = default;

        row_ (size_t Size)
        {
            try
            {
                elements = new T[Size];
                size = Size;
            }

            catch(const std::exception& e)
            {
                throw e;
            }
        }

        row_ (const std::vector <T> &Vec)
        {
            T* buffer = nullptr;

            try
            {
                buffer = new T[Vec.size()];

                std::copy (Vec.begin(), Vec.end(), buffer);
            }

            catch(const std::exception& e)
            {
                delete[] buffer;
                throw e;
            }

            size = Vec.size();
            elements = buffer;
        }

        row_ (const row_ <T> &rhs)
        {
            T* buffer = nullptr;

            try
            {
                buffer = new T[rhs.size];
                
                std::copy (rhs.begin(), rhs.end(), buffer);
            }

            catch(const std::exception& e)
            {
                delete[] buffer;

                throw e;
            }
            
            elements = buffer;
            size = rhs.size;
        }

        T* begin () const
        {
            return elements;
        }

        T* end () const
        {
            return elements + size;
        }

        row_ (row_ <T> && rhs): elements{rhs.elements}, size{rhs.size}
        {
            rhs.elements = nullptr;
        }

        row_ <T> & operator = (const row_ &rhs)
        {
            T* buffer = nullptr;

            try
            {
                buffer = new T[rhs.size];
                std::copy (rhs.begin(), rhs.end(), buffer);
            }

            catch(const std::exception& e)
            {
                delete[] buffer;
                throw e;
            }

            delete[] elements;

            elements = buffer;
            size = rhs.size;

            return *this;
        }

        row_ <T> & operator = (row_ &&rhs)
        {
            if (this == &rhs)
                return *this;

            std::swap (elements, rhs.elements);

            size = rhs.size;

            return *this;
        }

        ~row_ ()
        {
            delete[] elements;
        }

        T& operator [] (int x)
        {
            assert (x < size);

            return elements[x];
        }

        const T& operator [] (int x) const
        {
            assert (x < size);

            return elements[x];
        }

        row_ <T> operator + (const row_ &rhs) const;

        row_ <T> operator - (const row_ &rhs) const;

        size_t get_size () const
        {
            return size;
        }
    };

    template <typename T>
    std::ostream & operator << (std::ostream &out, const row_ <T> &Row)
    {
        out << "{";

        for (size_t i = 0; i < Row.get_size(); ++i)
        {
            out << Row[i];
            
            if (i != Row.get_size() - 1)
                out << " ";
        }

        out << "}" << std::endl;

        return out;
    }

    template <typename T>
    class matrix_
    {
        row_ <row_ <T>> elements;

        size_t size;

        public:

        matrix_ () = default;

        matrix_ (size_t Size): elements{Size}, size{Size}
        {
            for (size_t i = 0; i < Size; i++)
                elements[i] = row_ <T> {Size};
        }

        template <typename It>
        matrix_ (It start, It end, size_t Size): elements {Size}, size{Size}
        {
            for (size_t i = 0; i < Size; ++i)
                elements[i] = row_ <T> {Size};

            size_t i = 0, j = 0;

            for (i = 0; i < Size and start != end; ++i)
                for (j = 0; j < Size and start != end; ++j)
                {
                    elements[i][j] = *start;
                    ++start;
                }

            for (; i < Size; ++i)
                for (; j < Size; ++j)
                    elements[i][j] = static_cast <T> (0);
        }

        matrix_ (const matrix_ <T> &rhs): elements {rhs.size}, size{rhs.size}
        {
            for (size_t i = 0; i < size; ++i)
                elements[i] = rhs.elements[i];
        }

        template <typename U>
        matrix_ (const matrix_ <U> &rhs): elements {rhs.size()}, size{rhs.size()}
        {
            for (size_t i = 0; i < size; ++i)
                elements[i] = row_ <T> {size};

            for (int i = 0; i < size; ++i)
                for (int j = 0; j < size; ++j)
                    elements[i][j] = static_cast <T> (rhs.elements[i][j]);
        }

        row_ <T> & operator [] (int x)
        {
            assert (x < size);

            return elements[x];
        }

        const row_ <T> & operator [] (int x) const
        {
            assert (x < size);

            return elements[x];
        }

        matrix_ <T> operator + (const matrix_ &rhs) const;

        matrix_ <T> operator - (const matrix_ &rhs) const;

        matrix_ <T> operator * (const matrix_ &rhs) const;

        size_t get_size () const
        {
            return size;
        }

        int fill ();

        T det ();
    };

    template <typename T>
    std::ostream & operator << (std::ostream &out, const matrix_ <T> &M)
    {
        for (size_t i = 0; i < M.get_size(); ++i)
        {
            out << "";

            for (size_t j = 0; j < M.get_size(); ++j)
            {
                out << M[i][j];

                if (j != M.get_size() - 1)
                    out << " ";
            }

            out << "\n";
        }

        return out;
    }
}