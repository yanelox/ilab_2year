#include "triangle.h"

bool d_equal (double x, double y)
{
    double acc = 0.00001;

    return abs (x - y) < acc;
}


//vector


bool vector_::is_equal (const vector_ &an_vec) const
{
    return  d_equal (x, an_vec.x) and 
            d_equal (y, an_vec.y) and 
            d_equal (z, an_vec.z);
}


//line


int line_::point_to_line (vector_ &v1, vector_ &v2)
{
    r = v1;
    a = v2 + v1;

    return 0;
}


//surface


surface_loc surface_::get_loc (const surface_ &an_sur) const
{
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

void surface_::vec_to_sur (const vector_ &v1, const vector_ &v2, const vector_ &v3)
{
    double x1 = v1.x, y1 = v1.y, z1 = v1.z;
    double x2 = v2.x, y2 = v2.y, z2 = v2.z;
    double x3 = v3.x, y3 = v3.y, z3 = v3.z;

    a = (y2 - y1) * (z3 - z1) - (y3 - y1) * (z2 - z1);
    b = (x3 - x1) * (z2 - z1) - (x2 - x1) * (z3 - z1);
    c = (x2 - x1) * (y3 - y1) - (x3 - x1) * (y2 - y1);
    d = -a * x1 - b * y1 - c * z1;
}

void surface_::tr_to_sur (const triangle_ &t)
{
    vec_to_sur (t.a, t.b, t.c);
}


//triangle

void triangle_::vec_to_tr (vector_ &v1, vector_ &v2, vector_ &v3)
{
    a = v1;
    b = v2;
    c = v3;
}