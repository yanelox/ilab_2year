#pragma once

#include "triangle.h"

bool d_equal (double x, double y)
{
    double acc = 0.00001;

    return abs (x - y) < acc;
}


//vector


bool vector_::is_valid () const
{
    return isfinite (x) and isfinite (y) and isfinite (z);
}  

bool vector_::is_equal (const vector_ &an_vec) const
{
    if(!an_vec.is_valid() or !this->is_valid())
        return false;

    return  d_equal (x, an_vec.x) and 
            d_equal (y, an_vec.y) and 
            d_equal (z, an_vec.z);
}

double vector_::mod () const
{
    if (!this->is_valid())
        return NAN;

    return sqrt (x * x + y * y + z * z);
}

int vector_::print () const
{
    if(!this->is_valid())
        return -1;

    printf ("(%lg, %lg, %lg)\n", x, y, z);

    return 0;
}


//line


bool line_::is_valid () const
{
    return r.is_valid() and a.is_valid();
}

int line_::point_to_line (vector_ &v1, vector_ &v2)
{
    if (!v1.is_valid() or !v2.is_valid())
        return -1;

    r = v1;
    a = v2 - v1;

    return 0;
}


//triangle


bool triangle_::is_valid () const
{
    return a.is_valid() and b.is_valid() and c.is_valid();
}

int triangle_::vec_to_tr (const vector_ &v1, const vector_ &v2, const vector_ &v3)
{
    if (!v1.is_valid() or !v2.is_valid() or !v3.is_valid())
        return -1;

    a = v1;
    b = v2;
    c = v3;

    return 0;
}

bool triangle_::contain_vec (const vector_ &v) const
{
    if (!v.is_valid() or !this->is_valid())
        return false;

    double a1, a2, a3;

    if (v.is_equal (a))
        return true;

    else
        a1 = acos ((v ^ a) / (v.mod() * a.mod()));


    if (v.is_equal (b))
        return true;

    else
        a2 = acos ((v ^ b) / (v.mod() * b.mod()));


    if (v.is_equal (c))
        return true;

    else
        a3 = acos ((v ^ c) / (v.mod() * c.mod()));

    if (d_equal (a1 + a2 + a3, 360.0))
        return true;

    return false;
}

bool triangle_::trl_intersect (const triangle_ &t) const
{
    if (!t.is_valid() or !this->is_valid())
        return false;

    surface_ s {};

    s.tr_to_sur (t);

    line_segment_ a1 {a, b}, a2 {b, c}, a3 {c, a};

    vector_ res1 = a1.sur_its_loc (s), res2 = a2.sur_its_loc (s), res3 = a3.sur_its_loc (s);

    return t.contain_vec (res1) or t.contain_vec (res2) or t.contain_vec (res3);
}


//surface

bool surface_::is_valid () const
{
    return isfinite(a) and isfinite(b)  and isfinite (c) and isfinite (d) 
                       and n.is_valid() and r.is_valid();
}

mutual_loc surface_::sur_intersect (const surface_ &an_sur) const
{
    if (!an_sur.is_valid() or !this->is_valid())
        return ERROR;

    double ar = 0.0, br = 0.0, cr = 0.0, dr = 0.0;

    bool res = 0;

    if (d_equal (0, a) != d_equal (0, an_sur.a))
        return IS_INTERSECT;
    
    else
        if (!d_equal (0, a))
            ar = a / an_sur.a;


    if (d_equal (0, b) != d_equal (0, an_sur.b))
        return IS_INTERSECT;
    
    else
        if (!d_equal (0, b))
            br = b / an_sur.b;


    if (d_equal (0, c) != d_equal (0, an_sur.c))
        return IS_INTERSECT;

    else
        if (!d_equal (0, c))
            cr = c / an_sur.c;


    if (d_equal (0, d) != d_equal (0, an_sur.d))
        return IS_INTERSECT;

    else
        if (!d_equal (0, d))
            dr = d / an_sur.d;

    res = d_equal (ar, br) and d_equal (br, cr);

    if (res)
        if (d_equal (ar, dr))
            return IS_EQUAL;
        
        else
            return IS_PARALLEL;

    return IS_INTERSECT;
}

int surface_::vec_to_sur (const vector_ &v1, const vector_ &v2, const vector_ &v3)
{
    if (!v1.is_valid() or !v2.is_valid() or !v3.is_valid())
        return -1;

    double x1 = v1.x, y1 = v1.y, z1 = v1.z;
    double x2 = v2.x, y2 = v2.y, z2 = v2.z;
    double x3 = v3.x, y3 = v3.y, z3 = v3.z;

    a = (y2 - y1) * (z3 - z1) - (y3 - y1) * (z2 - z1);
    b = (x3 - x1) * (z2 - z1) - (x2 - x1) * (z3 - z1);
    c = (x2 - x1) * (y3 - y1) - (x3 - x1) * (y2 - y1);
    d = -a * x1 - b * y1 - c * z1;

    return 0;
}

int surface_::tr_to_sur (const triangle_ &t)
{
    if (!t.is_valid())
        return -1;

    return vec_to_sur (t.a, t.b, t.c);
}


//line segment


bool line_segment_::is_valid () const
{
    return a.is_valid() and b.is_valid();
}

mutual_loc line_segment_::sur_intersect (const surface_ &s) const
{
    if(!s.is_valid() or !this->is_valid())
        return ERROR;

    double f = (a - s.r) ^ s.n;
    double l = (b - s.r) ^ s.n;
    double v = (a - b)   ^ s.n;

    if ((f > 0 and l < 0) or (f < 0 and l > 0))
        return IS_INTERSECT;

     if (d_equal (v, 0))
        return IS_PARALLEL;

    return NOT_INTERSECT;
}

vector_ line_segment_::sur_its_loc (const surface_ &s) const
{
    vector_ res;

    if (!s.is_valid() or !this->is_valid())
        return res;

    double alpha = 0;

    if (sur_intersect (s) != IS_INTERSECT)
        return res;

    alpha = (s.r ^ s.n) - (a ^ s.n);
    alpha = alpha / ((b - a) ^ s.n);

    res = a + (b - a) * alpha;

    return res;
}