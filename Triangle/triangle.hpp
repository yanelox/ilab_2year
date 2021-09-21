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
    printf ("vector (%lg, %lg, %lg)\n", x, y, z);

    return 0;
}


//line


bool line_::is_valid () const
{
    return r.is_valid() and a.is_valid();
}

int line_::point_to_line (const vector_ &v1, const vector_ &v2)
{
    if (!v1.is_valid() or !v2.is_valid())
        return -1;

    r = v1;
    a = v2 - v1;

    return 0;
}

int line_::print () const
{
    cout << "line\n{\n";

    cout << "r = ";
    r.print();

    cout << "a = ";
    a.print();

    cout << "}\n";

    return 0;
}

//triangle


bool triangle_::is_valid () const
{
    return a.is_valid() and b.is_valid() and c.is_valid();
}

bool triangle_::contain_vec (const vector_ &v) const
{
    if (!v.is_valid() or !this->is_valid())
        return false;

    double a1, a2, a3;
    
    const vector_ r1 = a - v, r2 = b - v, r3 = c - v;

    if (d_equal(0, r1.mod()) or d_equal(0, r2.mod()) or d_equal(0, r3.mod()))
        return true;

    a1 = acos ((r1 ^ r2) / (r1.mod() * r2.mod()));
    a2 = acos ((r2 ^ r3) / (r2.mod() * r3.mod()));
    a3 = acos ((r3 ^ r1) / (r3.mod() * r1.mod()));

    if (d_equal (a1 + a2 + a3, 2 * pi_))
        return true;
    
    return false;
}

bool triangle_::trl_intersect (const triangle_ &t) const
{
    if (!t.is_valid() or !this->is_valid())
        return false;
    
    surface_ s {t.a, t.b, t.c};

    line_segment_ a1 {a, b}, a2 {b, c}, a3 {c, a};

    vector_ res1 = a1.sur_its_loc (s), res2 = a2.sur_its_loc (s), res3 = a3.sur_its_loc (s);

    return t.contain_vec (res1) or t.contain_vec (res2) or t.contain_vec (res3);
}

int triangle_::print () const
{
    cout << "triangle\n{\n";

    cout << "a = ";
    a.print();

    cout << "b = ";
    b.print();

    cout << "c = ";
    c.print();

    cout << "}\n";

    return 0;
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

int surface_::print () const
{
    cout << "surface\n{\n";

    cout << a << "*x ";

    if (b > 0)
        cout << "+ " << b;

    else
        cout << "- " << abs(b);

    cout << "*y ";

    if (c > 0)
        cout << "+ " << c;

    else
        cout << "- " << abs(c);

    cout << "*z ";

    if (d > 0)
        cout << "+ " << d << endl;

    else
        cout << "- " << abs(d) << " = 0" << endl;
    
    n.print();
    r.print();

    cout << "}\n";

    return 0;
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

int line_segment_::print  () const
{
    cout << "line_segment\n{\n";

    cout << "a = ";
    a.print();

    cout << "b = ";
    b.print();

    cout << "}\n";

    return 0;
}