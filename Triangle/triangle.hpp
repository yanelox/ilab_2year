#pragma once

#include "triangle.h"

namespace geom
{
bool d_equal (double x, double y)
{
    double acc = 0.00001;

    return abs (x - y) < acc;
}


//vector


bool vector_::is_valid () const
{
    return std::isfinite (x) and std::isfinite (y) and std::isfinite (z);
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

    return std::sqrt (x * x + y * y + z * z);
}

int vector_::print (int tab_number) const
{
    std::cout << "vector (" << x << ", " << y << ", " << z << ")\n";

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

int line_::print (int tab_number) const
{
    tab_func (tab_number);

    std::cout << "line\n";

    tab_func (tab_number);

    std::cout << "{\n";

    tab_func (tab_number);

    std::cout << "r = ";
    r.print(tab_number + 1);

    std::cout << "a = ";
    a.print(tab_number + 1);

    tab_func (tab_number);

    std::cout << "}\n";

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

int triangle_::print (int tab_number) const
{
    tab_func (tab_number);

    std::cout << "triangle\n";

    tab_func (tab_number);

    std::cout << "{\n";

    tab_func (tab_number);

    std::cout << "a = ";
    a.print(tab_number + 1);

    tab_func (tab_number);

    std::cout << "b = ";
    b.print(tab_number + 1);

    tab_func (tab_number);

    std::cout << "c = ";
    c.print(tab_number + 1);

    tab_func (tab_number);

    std::cout << "}\n";

    return 0;
}


//surface

bool surface_::is_valid () const
{
    return std::isfinite(a) and std::isfinite(b)  and std::isfinite (c) and std::isfinite (d) 
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

bool surface_::content_vec (const vector_ &vec) const
{
    return d_equal (a * vec.x + b * vec.y + c * vec.z + d, 0);
}

int surface_::print (int tab_number) const
{
    tab_func (tab_number);

    std::cout << "surface\n";

    tab_func (tab_number);

    std::cout << "{\n";

    tab_func (tab_number);

    std::cout << a << "*x ";

    tab_func (tab_number);

    if (b > 0)
        std::cout << "+ " << b;

    else
        std::cout << "- " << abs(b);

    tab_func (tab_number);

    std::cout << "*y ";

    tab_func (tab_number);

    if (c > 0)
        std::cout << "+ " << c;

    else
        std::cout << "- " << abs(c);

    tab_func (tab_number);

    std::cout << "*z ";

    tab_func (tab_number);

    if (d > 0)
        std::cout << "+ " << d << std::endl;

    else
        std::cout << "- " << abs(d) << " = 0" << std::endl;
    
    n.print(tab_number + 1);
    r.print(tab_number + 1);

    tab_func (tab_number);

    std::cout << "}" << std::endl;;

    return 0;
}


//line segment


bool line_segment_::is_valid () const
{
    return a.is_valid() and b.is_valid();
}

mutual_loc line_segment_::sur_intersect (const surface_ &s) const
{
    bool ac = 0, bc = 0;

    ac = s.content_vec (a);
    bc = s.content_vec (b);

    if(!s.is_valid() or !this->is_valid())
        return ERROR;

    if (ac and bc)
        return IS_CONTENTS;

    if (ac or bc)
        return IS_INTERSECT;

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

    double alpha = 0;
    
    int its_res = -1;

    if (!s.is_valid() or !this->is_valid())
        return res;

    its_res = sur_intersect(s);

    if (its_res == IS_CONTENTS)
        return a;

    if (its_res != IS_INTERSECT)
        return res;
    
    alpha = (s.r ^ s.n) - (a ^ s.n);
    alpha = alpha / ((b - a) ^ s.n);
    
    res = a + (b - a) * alpha;
    
    return res;
}

int line_segment_::print  (int tab_number) const
{
    tab_func (tab_number);

    std::cout << "line_segment\n";

    tab_func (tab_number);

    std::cout << "{\n";

    tab_func (tab_number);

    std::cout << "a = ";
    a.print(tab_number + 1);

    tab_func (tab_number);

    std::cout << "b = ";
    b.print(tab_number + 1);

    tab_func (tab_number);

    std::cout << "}\n";

    return 0;
}


//parallelepiped


bool prlppd_::is_valid ()
{
    return  std::isfinite (x1) and std::isfinite (x2) and
            std::isfinite (y1) and std::isfinite (y2) and
            std::isfinite (z1) and std::isfinite (z2) and
            (x1 < x2) and (y1 < y2) and (z1 < z2);
}

int prlppd_::contain_vec (const vector_ &vec)
{
    int res = 0;

    if (x1 + (x2 - x1) / 2 < vec.x and vec.x <= x2)
        res += 4; //0b100

    else if (vec.x <= x1 or vec.x > x2)
        return -1;

    if (y1 + (y2 - y1) / 2 < vec.y and vec.y <= y2)
        res += 2; //0b010

    else if (vec.y <= y1 or vec.y > y2)
        return -1;

    if (z1 + (z2 - z1) / 2 < vec.z and vec.z <= z2)
        res += 1; //0b001

    else if (vec.z <= z1 or vec.z > z2)
        return -1;

    return res;
}

int prlppd_::contain_tr (const triangle_ &t)
{
    int i1 = contain_vec (t.a), 
        i2 = contain_vec (t.b),
        i3 = contain_vec (t.c);
    
    if  (i1 == -1 or i2 == -1 or i3 == -1)
        return -1;

    if (i1 == i2 and i2 == i3)
        return i1;

    return 8;
}

int prlppd_::print (int tab_number) const
{
    tab_func (tab_number);

    std::cout << "parallelepiped:\n";

    tab_func (tab_number);

    std::cout << "{\n";

    tab_func (tab_number);

    std::cout << x1 << " < x <= " << x2 << std::endl;

    tab_func (tab_number);

    std::cout << y1 << " < y <= " << y2 << std::endl;

    tab_func (tab_number);

    std::cout << z1 << " < z <= " << z2 << std::endl;

    tab_func (tab_number);

    std::cout << "}\n";

    return 0;
}


//node


bool node_::is_valid ()
{
    return p.is_valid();
}

int node_::make_childs ()
{
    if (nodes == nullptr)
        return -1;

    for (int i = 0; i < 8; ++i)
    {
        nodes[i].p.x1 = p.x1 + ((i & 4) != 0) * (p.x2 - p.x1) / 2;
        nodes[i].p.x2 = (p.x1 + p.x2) / 2 + ((i & 4) != 0) * (p.x2 - p.x1) / 2;

        nodes[i].p.y1 = p.y1 + ((i & 2) != 0) * (p.y2 - p.y1) / 2;
        nodes[i].p.y2 = (p.y1 + p.y2) / 2 + ((i & 2) != 0) * (p.y2 - p.y1) / 2;

        nodes[i].p.z1 = p.z1 + ((i & 1) != 0) * (p.z2 - p.z1) / 2;
        nodes[i].p.z2 = (p.z1 + p.z2) / 2 + ((i & 1) != 0) * (p.z2 - p.z1) / 2;
    }

    return 0;
}

int node_::push (const triangle_ &t) 
{
    int tmp = p.contain_tr (t);
    
    if (tmp == -1)
    {
        // std::cout << -1;
        return -1;
    }

    else if (tmp == 8)
    {
        // std::cout << 8;
        t_.push_back(t);
    }

    else
    {
        if (nodes == nullptr)
            nodes = new node_ [8];

        make_childs ();
         
        /*std::cout <<*/ nodes[tmp].push (t);
    }

    return 0;
}

int node_::print (int tab_number) const
{
    tab_func (tab_number);

    std::cout << "node:\n";

    tab_func (tab_number);

    std::cout << "{\n";

    p.print(tab_number + 1);

    tab_func (tab_number + 1);

    std::cout << "triangle vector\n";

    tab_func (tab_number + 1);

    std::cout << "{\n";

    for (auto i:t_)
        i.print(tab_number + 2);

    tab_func (tab_number + 1);

    std::cout << "}\n";

    if (nodes != nullptr)
    {
        tab_func (tab_number + 1);

        std::cout << "nodes:\n";

        tab_func (tab_number + 1);

        std::cout << "{\n";

        for (int i = 0; i < 8; ++i)
        {   
            tab_func (tab_number + 2);

            std::cout << std::bitset <3> (i) << std::endl;

            nodes[i].print(tab_number + 2);
        }

        tab_func (tab_number + 1);

        std::cout << "}\n";
    }

    tab_func (tab_number);

    std::cout << "}\n";

    return 0;
}


//tree


int my_tree::fill_tree (const triangle_ *t, int n)
{
    double init[6];
    double tmp[6];

    for (int i = 0; i < n; ++i)
    {
        tmp[0] = std::max (t[i].a.x, std::max (t[i].b.x, t[i].c.x));
        tmp[1] = std::min (t[i].a.x, std::min (t[i].b.x, t[i].c.x));
        tmp[2] = std::max (t[i].a.y, std::max (t[i].b.y, t[i].c.y));
        tmp[3] = std::min (t[i].a.y, std::min (t[i].b.y, t[i].c.y));
        tmp[4] = std::max (t[i].a.z, std::max (t[i].b.z, t[i].c.z));
        tmp[5] = std::min (t[i].a.z, std::min (t[i].b.z, t[i].c.z));

        if (i == 0)
            for (int j = 0; j < 6; ++j)
                init[j] = tmp[j];

        else
            for (int j = 0; j < 3; ++j)
            {
                init[2 * j] = std::max (init[2 * j], tmp[2 * j]);
                init[2 * j + 1] = std::min (init[2 * j + 1], tmp[2 * j + 1]);
            }
    }

    top.p = {init[1] - 1, init[0] + 1, 
             init[3] - 1, init[2] + 1, 
             init[5] - 1, init[4] + 1};

    for (int i = 0; i < n; ++i)
        push (t[i]);

    return 0;
}

int my_tree::push (const triangle_ &t)
{
    return top.push (t);
}

int my_tree::print () const
{
    std::cout << "tree:\n{\n";

    top.print(1);

    std::cout << "}\n";

    return 0;
}


//solution


void solution (const my_tree &Tree)
{
    ;
}

//func for printing

int tab_func (int tab_number)
{
    for (int i = 0; i < tab_number; ++i)
        std::cout << "\t";

    return 0;
}
}