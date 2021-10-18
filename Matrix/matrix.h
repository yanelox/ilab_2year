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
        n1 = (n1 > 0) ? n1 : -n1;
        n2 = (n2 > 0) ? n2 : -n2;

        if (equal(n1, T{0}) or equal(n2, T{1}))
            return (T) 1;

        while(!equal(n1, n2))
        {
            if (n1 > n2)
                n1 -= n2;

            else
                n2 -= n1;
        }
        
        return n1;
    }

    template <typename T>
    struct frac_
    {
        T numerator, denominator;

        frac_ (): numerator{}, denominator{} {}
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

        frac_ <T> operator + (const frac_ &rhs)
        {
            frac_ <T> res;
            
            res.numerator = numerator * rhs.denominator + rhs.numerator * denominator;
            res.denominator = denominator * rhs.denominator;
            
            res.reduction();

            return res;
        }

        frac_ <T> operator - (const frac_ &rhs)
        {
            frac_ <T> res;

            res.numerator = numerator * rhs.denominator - rhs.numerator * denominator;
            res.denominator = denominator * rhs.denominator;
            
            res.reduction();
            
            return res;
        }

        frac_ <T> operator * (const frac_ &rhs)
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

        frac_ <T> operator / (const frac_ &rhs)
        {
            frac_ <T> res;

            res.numerator = numerator * rhs.denominator;
            res.denominator = denominator * rhs.numerator;
            
            res.reduction();
            
            return res;
        }

        frac_ <T> operator += (const frac_ &rhs)
        {
            (*this) = (*this) + rhs;

            return *this;
        }

        frac_ <T> operator -= (const frac_ &rhs)
        {
            (*this) = (*this) - rhs;

            return *this;
        }

        frac_ <T> operator *= (const frac_ &rhs)
        {
            (*this) = (*this) * rhs;

            return *this;
        }

        int is_valid () const;

        void print () const;
    };

    template <typename T>
    std::ostream & operator<< (std::ostream &out, frac_ <T> &rhs)
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
    class matrix_
    {
        T* numbers;

        size_t size;

        public:
        
        matrix_ (): numbers{NULL}, size{0} {}
        
        matrix_ (size_t Size): numbers{new T[Size * Size]}, size{Size} {}

        matrix_ (const matrix_ &rhs): numbers {new T[rhs.size * rhs.size]}, size{rhs.size}
        {
            size_t q_size = size * size;

            for (size_t i = 0; i < q_size; ++i)
                numbers[i] = rhs.numbers[i];
        }

        matrix_ (matrix_ && rhs): numbers{rhs.numbers}, size{rhs.size}
        {
            rhs.numbers = nullptr;
        }

        matrix_ (const std::vector <T> &Vec, size_t Size)
        {
            if (Vec.size() != Size * Size)
            {
                numbers = nullptr;
                size = 0;

                return;
            }

            numbers = new T[Size * Size];
            size = Size;

            size_t q_size = size * size;

            for (size_t i = 0; i < q_size; ++i)
                numbers[i] = Vec[i];
        }

        matrix_ <T> & operator = (const matrix_ &rhs)
        {
            if (this == &rhs)
                return *this;

            size = rhs.size;

            delete[] numbers;

            numbers = new T[size];

            size_t q_size = size * size;

            for (size_t i = 0; i < q_size; ++i)
                numbers[i] = rhs.numbers[i];

            return *this;
        }

        matrix_ <T> & operator = (matrix_ && rhs)
        {
            if (this == &rhs)
                return *this;

            delete[] numbers;

            numbers = rhs.numbers;

            rhs.numbers = nullptr;

            return *this;
        }

        ~matrix_ ()
        {
            delete[] numbers;
        }

        T & operator () (long i, long j) const
        {
            return numbers[(i % size) * size + (j % size)];
        }

        matrix_ <T> operator + (const matrix_ &rhs)
        {
            if (size != rhs.size)
                return matrix_ {};

            matrix_ res{size};

            size_t q_size = size * size;

            for (size_t i = 0; i < q_size; ++i)
                res.numbers[i] = numbers[i] + rhs.numbers[i];

            return res;
        }

        matrix_ <T> operator - (const matrix_ &rhs)
        {
            if (size != rhs.size)
                return matrix_ {};

            matrix_ res{size};

            size_t q_size = size * size;

            for (size_t i = 0; i < q_size; ++i)
                res.numbers[i] = numbers[i] - rhs.numbers[i];

            return res;
        }

        int is_valid () const;

        int fill ();

        void print (int mode = 0) const;

        std::pair <matrix_ <frac_ <T>>, matrix_  <frac_ <T>>> get_LU () const;

        frac_ <T> get_det () const;
    };
}