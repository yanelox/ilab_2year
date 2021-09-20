#pragma once

#include <iostream>
#include <cmath>

using namespace std;

bool d_equal (double x, double y);

enum surface_loc
{
    IS_EQUAL = 1,
    IS_PARALLEL = 2,
    IS_INTERSECT = 3
};


class vector_
{
    public:

    double x, y, z;

    bool is_equal (const vector_ &an_vec) const;

    vector_ (): x(NAN), y(NAN), z(NAN) {};
    vector_  (double X, double Y, double Z): x(X), y(Y), z(Z) {};

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


    vector_ operator + (vector_ &other)
    {
        return vector_ {x + other.x, y + other.y, z + other.z};
    }

    vector_ operator - (vector_ &other)
    {
        return vector_ {x - other.x, y - other.y, z - other.z};
    }
};


class line_
{
    public:

    vector_ r, a;

    line_ (): r{}, a{} {};
    line_ (const vector_ &R, const vector_ &A): r(R), a(A) {};

    ~line_ () {};

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

    int point_to_line (vector_ &v1, vector_ &v2);
};


class triangle_
{
    
    public:
    
    vector_ a, b, c;

    triangle_ (): a{}, b{}, c{} {};
    triangle_ (const vector_ &A, const vector_ &B, const vector_ &C): a(A), b(B), c(C) {};

    ~triangle_ () {};

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

    void vec_to_tr (vector_ &v1, vector_ &v2, vector_ &v3);
};


class surface_
{
    public:

    double a, b, c, d;

    surface_ (): a(NAN), b(NAN), c(NAN), d(NAN) {};
    surface_ (double A, double B, double C, double D): a(A), b(B), c(C), d(D) {};

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

    surface_loc get_loc (const surface_ &an_sur) const;

    void vec_to_sur (const vector_ &v1, const vector_ &v2, const vector_ &v3);

    void tr_to_sur (const triangle_ &t);
};

// TODO: 1) сделать прямую из стороны треугольника 
// TODO: 2) найти точку пересечения прямой и плоскости
// TODO: 3) проверить принадлежит ли точка прямой (либо сумма углов 360, либо два угла в сумме третьей)