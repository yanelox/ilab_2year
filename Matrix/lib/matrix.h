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
    class row_buff
    {
        protected:

        T* elements;
        size_t size;

        protected:

        row_buff (size_t Size = 0): elements ((Size == 0) ? nullptr : 
                                                         static_cast <T*> (::operator new (sizeof (T) * Size))),
                                    size (Size)
        {
            
        }

        ~row_buff ()
        {
            T* iter = elements;

            while (iter != elements + size)
            {
                iter->~T();
                ++iter;
            }

            ::operator delete (elements);
        }

        row_buff (const row_buff &) = delete;
        row_buff & operator = (const row_buff &) = delete;

        row_buff (row_buff &&rhs) noexcept : elements (rhs.elements), size(rhs.size)
        {
            rhs.elements = nullptr;
            rhs.size = 0;
        }

        row_buff & operator = (row_buff &&rhs) noexcept
        {
            std::swap (elements, rhs.elements);
            std::swap (size, rhs.size);

            return *this;
        }
    };

    template <typename T>
    class row_ : row_buff <T>
    {
        using row_buff <T>::elements;
        using row_buff <T>::size;

        public:

        row_ (size_t Size = 0): row_buff <T> (Size) {}

        row_ (const row_ &rhs): row_buff <T> (rhs.size)
        {
            for (size_t i = 0; i < size; ++i)
                new (elements + i) T (rhs.elements[i]);
        }

        template <typename It>
        row_ (It start, It end, size_t Size): row_buff <T> {Size}
        {
            size_t i = 0;

            for (i = 0; i < Size and start != end; ++i)
            {
                new (elements + i) T (*start);
                ++start;
            }

            for (; i < Size; ++i)
                new (elements + i) T (0);
        }

        row_ & operator = (const row_ &rhs)
        {
            row_ tmp(rhs);
            std::swap (*this, tmp);

            return *this;
        }

        row_ (row_ &&rhs) = default;

        row_ & operator = (row_ &&rhs) = default;

        T* begin () const
        {
            return elements;
        }

        T* end () const
        {
            return elements + size;
        }

        T& operator [] (size_t x)
        {
            assert (x < size);

            return elements[x];
        }

        const T& operator [] (size_t x) const
        {
            assert (x < size);

            return elements[x];
        }

        row_ <T> operator + (const row_ &rhs) const;

        row_ <T> operator - (const row_ &rhs) const;

        bool operator == (const row_ &rhs) const;

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
            for (size_t i = 0; i < size; ++i)
                new (&elements[i]) row_ <T> (Size);
        }

        template <typename It>
        matrix_ (It start, It end, size_t Size): elements {Size}, size{Size}
        {
            for (size_t i = 0; i < Size; ++i)
                new (&elements[i]) row_ <T> (Size);

            size_t i = 0, j = 0;

            for (i = 0; i < Size and start != end; ++i)
                for (j = 0; j < Size and start != end; ++j)
                {
                    elements[i][j] = *start;
                    ++start;
                }

            for (; i < Size; ++i)
                for (; j < Size; ++j)
                    elements[i][j] = 0;
        }

        matrix_ (const matrix_ <T> &rhs): elements {rhs.size}, size{rhs.size}
        {
            for (size_t i = 0; i < size; ++i)
                new (&elements[i]) row_ <T> (size);

            for (int i = 0; i < size; ++i)
                for (int j = 0; j < size; ++j)
                    elements[i][j] = rhs.elements[i][j];
        }

        template <typename U>
        matrix_ (const matrix_ <U> &rhs): elements {rhs.size()}, size{rhs.size()}
        {
            for (size_t i = 0; i < size; ++i)
                new (&elements[i]) row_ <T> (size);

            for (int i = 0; i < size; ++i)
                for (int j = 0; j < size; ++j)
                    elements[i][j] = rhs.elements[i][j];
        }

        row_ <T> & operator [] (size_t x)
        {
            assert (x < size);

            return elements[x];
        }

        const row_ <T> & operator [] (size_t x) const
        {
            assert (x < size);

            return elements[x];
        }

        matrix_ <T> operator + (const matrix_ &rhs) const;

        matrix_ <T> operator - (const matrix_ &rhs) const;

        matrix_ <T> operator * (const matrix_ &rhs) const;

        bool operator == (const matrix_ &rhs) const;

        size_t get_size () const
        {
            return size;
        }

        int fill (std::istream &in);

        T det () const;
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