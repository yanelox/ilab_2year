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
    T nod (T n1_, T n2_)
    {
        T n1 = std::abs (n1_);
        T n2 = std::abs (n2_);

        T res;

        while (!equal(n1, n2))
        {
            if (n1 < 1 or n2 < 1)
                return n2_;

            if (n1 > n2)
                n1 = n1 - n2;

            else
                n2 = n2 - n1;
        }
        
        if (equal(n1, n2))
            return n1;

        return T{1};
    }

    template <typename T>
    struct frac_
    {
        T numerator, denominator;

        frac_ (T N = T{0}, T D = T{1}): numerator{N}, denominator{D} 
        {
            if (denominator < 0)
            {
                numerator = -numerator;
                denominator = -denominator;
            }

            reduction();
        }

        void reduction ()
        {
            T nod_ = nod (numerator, denominator);
            
            numerator = numerator / nod_;
            denominator = denominator / nod_;
        }

        frac_ <T> operator + (const frac_ <T> &rhs)
        {
            frac_ <T> res;
            
            T tmp1 = nod (denominator, rhs.denominator);

            T new_denominator = denominator / tmp1;
            new_denominator *= rhs.denominator;

            T tmp2 = denominator / tmp1;
            T tmp3 = rhs.denominator / tmp1;

            res.numerator = numerator * tmp3 + rhs.denominator * tmp2;
            res.denominator = new_denominator;
            
            res.reduction();

            return res;
        }

        frac_ <T> operator - (const frac_ <T> &rhs)
        {
            frac_ <T> res;

            T tmp1 = nod (denominator, rhs.denominator);

            T new_denominator = denominator / tmp1;
            new_denominator *= rhs.denominator;

            T tmp2 = denominator / tmp1;
            T tmp3 = rhs.denominator / tmp1;

            res.numerator = numerator * tmp3 - rhs.numerator * tmp2;
            res.denominator = new_denominator;

            res.reduction();
            
            return res;
        }

        frac_ <T> operator * (const frac_ <T> &rhs)
        {
            frac_ <T> res;

            T tmp1 = nod (numerator, rhs.denominator);
            T tmp2 = nod (denominator, rhs.numerator);
            
            res.numerator = numerator / tmp1;
            res.numerator *= rhs.numerator / tmp2;

            res.denominator = denominator / tmp2;
            res.denominator *= rhs.denominator / tmp1;

            res.reduction();

            return res;
        }

        frac_ <T> operator * (const T &rhs)
        {
            frac_ <T> res;

            res.numerator = numerator * rhs;
            res.denominator = denominator;

            return res;
        }

        frac_ <T> operator / (const frac_ <T> &rhs)
        {
            frac_ <T> res;

            T tmp1 = nod (numerator, rhs.numerator);
            T tmp2 = nod (denominator, rhs.denominator);

            res.numerator = numerator / tmp1;
            res.numerator *= rhs.denominator / tmp2;

            res.denominator = denominator / tmp2;
            res.denominator *= rhs.numerator / tmp1;

            if (res.denominator < 0)
            {
                res.numerator = -res.numerator;
                res.denominator = -res.denominator;
            }
            
            res.reduction();
            
            return res;
        }

        frac_ <T> operator += (const frac_ <T> &rhs)
        {
            (*this) = (*this) + rhs;

            return *this;
        }

        frac_ <T> operator -= (const frac_ <T> &rhs)
        {
            (*this) = (*this) - rhs;

            return *this;
        }

        frac_ <T> operator *= (const frac_ &rhs)
        {
            (*this) = (*this) * rhs;

            return *this;
        }

        bool operator < (const frac_ <T> rhs)
        {
            if (numerator * rhs.denominator < denominator * rhs.numerator)
                return true;

            return false;
        }

        bool operator > (const frac_ rhs)
        {
            return !((*this) < rhs);
        }

        bool is_zero () const
        {
            return equal (numerator, T{0});
        }

        bool is_valid () const;

        void print () const;
    };

    template <typename T>
    std::ostream & operator<< (std::ostream &out, const frac_ <T> &rhs)
    {
        out << rhs.numerator << "/" << rhs.denominator;

        return out;
    }

    template <typename T>
    frac_ <T> operator * (T &first, const frac_ <T> &rhs)
    {
        frac_ <T> res;

        res.numerator = first * rhs.numerator;
        res.denominator = rhs.denominator;

        res.reduction();

        return res;
    }

    template <typename T>
    class row_
    {
        T *elements;

        size_t size;

        public:

        row_ (): elements {NULL}, size{0} {}

        row_ (size_t Size): elements{new T[Size]{}}, size {Size} {}

        row_ (const std::vector <T> &Vec)
        {
            size = Vec.size();

            elements = new T[size];

            for (size_t i = 0; i < size; ++i)
                elements[i] = Vec[i];
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
            return elements[x % size];
        }

        const T& operator [] (int x) const
        {
            return elements[(x % size + size) % size];
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
            return elements[(x % size + size) % size];
        }

        const row_ <T> & operator [] (int x) const
        {
            return elements[x % size];
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

        size_t get_size () const
        {
            return size;
        }

        int fill ();

        int g_elimination ();

        T get_det (int sign = 1) const;
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