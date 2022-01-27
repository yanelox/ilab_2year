#include <cassert>
#include <vector>
#include <iostream>

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
        T *elements;

        size_t size;

        public:

        row_ (): elements {NULL}, size{0} {}

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

            delete[] elements;

            elements = rhs.elements;

            size = rhs.size;

            rhs.elements = nullptr;

            return *this;
        }

        ~row_ ()
        {
            delete[] elements;
        }

        T& operator [] (int x)
        {
            return elements[x];
        }

        const T& operator [] (int x) const
        {
            return elements[x];
        }

        row_ <T> operator + (const row_ &rhs) const
        {
            if (size != rhs.size)
                return row_ <T> {};

            row_ res{size};

            for (size_t i = 0; i < size; ++i)
                res[i] = elements[i] + rhs.elements[i];

            return res;
        }

        row_ <T> operator - (const row_ &rhs) const
        {
            if (size != rhs.size)
                return row_ <T> {};

            row_ res{size};

            for (size_t i = 0; i < size; ++i)
                res[i] = elements[i] - rhs.elements[i];

            return res;
        }

        row_ <T> operator * (const T &rhs) const
        {
            row_ res{size};

            for (size_t i = 0; i < size; ++i)
                res[i] = elements[i] * rhs;

            return res;
        }

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
        matrix_ (It start, It end, size_t Size)
        {
            (*this) = matrix_ <T> {Size};

            size_t i = 0, j = 0;

            for (i = 0; i < Size and start != end; ++i)
                for (j = 0; j < Size and start != end; ++j)
                {
                    (*this)[i][j] = *start;
                    ++start;
                }

            for (; i < Size; ++i)
                for (; j < Size; ++j)
                    (*this)[i][j] = T {0};
        }

        row_ <T> & operator [] (int x)
        {
            return elements[x];
        }

        const row_ <T> & operator [] (int x) const
        {
            return elements[x];
        }

        matrix_ <T> operator + (const matrix_ &rhs) const
        {
            if (size != rhs.size)
                return matrix_ <T> {};

            matrix_ <T> res{size};

            for (size_t i = 0; i < size; ++i)
                res[i] = elements[i] + rhs.elements[i];

            return res;
        }

        matrix_ <T> operator - (const matrix_ &rhs) const
        {
            if (size != rhs.size)
                return matrix_ <T> {};

            matrix_ <T> res{size};

            for (size_t i = 0; i < size; ++i)
                res[i] = elements[i] - rhs.elements[i];

            return res;
        }

        matrix_ <T> operator * (const matrix_ &rhs) const
        {
            if (size != rhs.size)
                return matrix_ <T> {};

            matrix_ <T> res{size};

            T sum = static_cast <T> (0);

            for (int i = 0; i < size; ++i)
                for (int j = 0; j < size; ++j)
                {
                    sum = static_cast <T> (0);

                    for (int k = 0; k < size; ++k)
                        sum = sum + (*this)[i][k] * rhs[k][j];

                    res[i][j] = sum;
                }

            return res;
        }

        matrix_ <T> operator * (const T &c) const
        {
            matrix_ <T> res{size};

            for (int i = 0; i < size; ++i)
                res[i] = (*this)[i] * c;

            return res;
        }

        size_t get_size () const
        {
            return size;
        }

        int fill ();

        double g_elimination ();
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