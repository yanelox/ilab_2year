#pragma once

#include <iostream>
#include <cmath>

using namespace std;

bool d_equal (double x, double y);

enum mutual_loc
{
    ERROR = 0,
    IS_EQUAL = 1,
    IS_PARALLEL = 2,
    IS_INTERSECT = 3,
    NOT_INTERSECT = 4
};


class vector_
{
    public:

    double x, y, z;

    vector_ (): x(NAN), y(NAN), z(NAN) {}
    vector_  (double X, double Y, double Z): x(X), y(Y), z(Z) {}

    ~vector_ ()
    {
        x = NAN;
        y = NAN;
        z = NAN;
    }

    vector_ &operator = (const vector_ &other)
    {
        x = other.x;
        y = other.y;
        z = other.z;

        return *this;
    }

    vector_ (const vector_ &other)
    {
        x = other.x;
        y = other.y;
        z = other.z;
    }


    vector_ operator + (const vector_ &other) const
    {
        return vector_ {x + other.x, y + other.y, z + other.z};
    }

    vector_ operator - (const vector_ &other) const
    {
        return vector_ {x - other.x, y - other.y, z - other.z};
    }

    vector_ operator * (const vector_ &other) const
    {
        return vector_ {y * other.z - other.y * z, other.x * z - other.z * x, x * other.y - y * other.x};
    }

    vector_ operator * (double a) const
    {
        return vector_ {x * a, y * a, z * a};
    }

    double operator ^ (const vector_ &other) const
    {
        return x * other.x + y * other.y + z * other.z;
    }

    bool is_equal (const vector_ &an_vec) const;

    bool is_valid () const;

    double mod () const;

    int print () const;
};


class line_
{
    public:

    vector_ r, a;

    line_ (): r{}, a{} {}
    line_ (const vector_ &R, const vector_ &A): r(R), a(A) {}

    ~line_ () {}

    line_ &operator = (const line_ &other)
    {
        r = other.r;
        a = other.a;

        return *this;
    }

    line_ (const line_ &other)
    {
        r = other.r;
        a = other.a;
    }

    bool is_valid () const;

    int point_to_line (vector_ &v1, vector_ &v2);

    int print () const;
};


class triangle_
{
    
    public:
    
    vector_ a, b, c;

    triangle_ (): a{}, b{}, c{} {}
    triangle_ (const vector_ &A, const vector_ &B, const vector_ &C): a(A), b(B), c(C) {}

    ~triangle_ () {}

    triangle_ &operator = (const triangle_ &other)
    {
        a = other.a;
        b = other.b;
        c = other.c;

        return *this;
    }

    triangle_ (const triangle_ &other)
    {
        a = other.a;
        b = other.b;
        c = other.c;
    }

    bool is_valid () const;

    int vec_to_tr (const vector_ &v1, const vector_ &v2, const vector_ &v3);

    bool contain_vec (const vector_ &v) const;

    bool trl_intersect (const triangle_ &t) const;

    int print () const;
};


class surface_
{
    public:

    double a, b, c, d;

    vector_ n, r;

    surface_ (): a(NAN), b(NAN), c(NAN), d(NAN), n{}, r{} {}
    surface_ (double A, double B, double C, double D): a(A), b(B), c(C), d(D), n{A, B, C}, r{} 
    {
        if (d_equal (D, 0))
        {
            r.x = 0;
            r.y = 0;
            r.z = 0;
        }

        else
        {
            if (d_equal (A, 0))
                r.x = 0;

            else
                r.x = - D / A;

            if (d_equal (B, 0))
                r.y = 0;

            else
                r.y = - D / B;

            if (d_equal (C, 0))
                r.z = 0;
            
            else
                r.z = D / C;
        }
    }

    surface_ (const vector_ &N, const vector_ &R): a (N.x), b(N.y), c(N.z), d(NAN), n(N), r(R)
    {
        d = - (a * R.x + b * R.y + c * R.z);
    }

    ~surface_ ()
    {
        a = NAN;
        b = NAN;
        c = NAN;
        d = NAN;
    }

    surface_ &operator = (const surface_ &other)
    {
        a = other.a;
        b = other.b;
        c = other.c;
        d = other.d;

        return *this;
    }

    surface_ (const surface_ &other)
    {
        a = other.a;
        b = other.b;
        c = other.c;
        d = other.d;
    }

    bool is_valid () const;

    mutual_loc sur_intersect (const surface_ &an_sur) const;

    int vec_to_sur (const vector_ &v1, const vector_ &v2, const vector_ &v3);

    int tr_to_sur (const triangle_ &t);

    int print () const;
};


class line_segment_
{
    public:

    vector_ a, b;

    line_segment_ (): a{}, b{} {};
    line_segment_ (const vector_ &A, const vector_ &B): a(A), b(B) {};

    ~line_segment_ () {};

    bool is_valid () const;

    mutual_loc sur_intersect (const surface_ &s) const;

    vector_ sur_its_loc (const surface_ &s) const;

    int print () const;
};
