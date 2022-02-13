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
                std::cerr << e.what() << '\n';
            }   
        }

        row_ (const std::vector <T> &Vec)
        {
            size = Vec.size();

            try
            {
                elements = new T[size];

                for (size_t i = 0; i < size; ++i)
                    elements[i] = Vec[i];
            }

            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }
        }

        row_ (const row_ <T> &rhs) = delete;

        row_ (row_ <T> && rhs): elements{rhs.elements}, size{rhs.size}
        {
            rhs.elements = nullptr;
        }

        row_ <T> & operator = (const row_ &rhs) = delete;

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
                    elements[i][j] = T {0};
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

        double det ();
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