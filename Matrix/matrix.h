#include <cassert>
#include <vector>
#include <iostream>

namespace matrix
{
    double eps = 0.00001;
    
    template <typename T>
    bool equal (T n1, T n2)
    {
        if (n1 > n2)
            return (n1 - n2) < eps;

        else
            return (n2 - n1) < eps;

        return 0;
    }

    template <typename T>
    T nod (T n1, T n2)
    {
        T res;

        while (n1 > T{1} and n2 > T{1} and !equal(n1, n2))
        {
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

        frac_ (): numerator{0}, denominator{1} {}
        frac_ (T N): numerator{N}, denominator{(T) 1} {}
        frac_ (T N, T D): numerator{N}, denominator{D} 
        {
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
            
            res.numerator = numerator * rhs.denominator + rhs.numerator * denominator;
            res.denominator = denominator * rhs.denominator;
            
            res.reduction();

            return res;
        }

        frac_ <T> operator - (const frac_ <T> &rhs)
        {
            frac_ <T> res;

            res.numerator = numerator * rhs.denominator - rhs.numerator * denominator;
            res.denominator = denominator * rhs.denominator;
            
            res.reduction();
            
            return res;
        }

        frac_ <T> operator * (const frac_ <T> &rhs)
        {
            frac_ <T> res;

            res.numerator = numerator * rhs.numerator;
            res.denominator = denominator * rhs.denominator;

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

            res.numerator = numerator * rhs.denominator;
            res.denominator = denominator * rhs.numerator;
            
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
            return elements[x % size];
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

        row_ <T> & operator [] (int x)
        {
            return elements[x % size];
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
        int fill (const std::vector <T> &Vec);

        int g_elimination ();

        T get_det (int sign) const;
    };

    template <typename T>
    std::ostream & operator << (std::ostream &out, const matrix_ <T> &M)
    {
        for (size_t i = 0; i < M.get_size(); ++i)
        {
            out << "{";

            for (size_t j = 0; j < M.get_size(); ++j)
            {
                out << M[i][j];

                if (j != M.get_size() - 1)
                    out << " ";
            }

            out << "}\n";
        }

        return out;
    }
}