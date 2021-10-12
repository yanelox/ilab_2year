#pragma once

#include "triangle.h"

namespace geom
{
bool d_equal (double x, double y)
{
    double acc = 0.00001;

    return std::abs (x - y) < acc;
}


//vector

bool vector_::is_zero () const
{
    return d_equal(x, 0) and d_equal (y, 0) and d_equal (z, 0);
}

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


triangle_stat triangle_::is_valid () const
{
    if (!a.is_valid() or !b.is_valid() or !c.is_valid())
        return IS_NAN;

    if (a.is_equal (b) and b.is_equal(c))
        return IS_POINT;

    if (((a - b) * (a - c)).is_zero())
        return IS_LINES;

    return IS_VALID;
}

bool triangle_::contain_vec (const vector_ &v) const
{
    if (!v.is_valid())
        return false;
    
    switch (is_valid())
    {
        case IS_NAN:
            return false;
        
        case IS_POINT:
            return a.is_equal (v);

        case IS_LINES:
            if ((a.is_equal(b) or b.is_equal(c)) and ((a - v) * (c - v)).is_zero())
                return true;

            else if (a.is_equal(c) and ((a - v) * (b - v)).is_zero())
                return true;

            else
                return false;

        default:
            break;
    }
    
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
    triangle_stat tmp1 = t.is_valid(), tmp2 = is_valid();

    if (tmp1 == IS_NAN or tmp2 == IS_NAN)
        return false;

    if (tmp1 == IS_POINT and tmp2 == IS_POINT)
        return t.a.is_equal(a);

    if (tmp1 == IS_POINT and tmp2 == IS_LINES)
        return contain_vec (t.a);

    if (tmp1 == IS_LINES and tmp2 == IS_POINT)
        return t.contain_vec (a);

    if (tmp1 == IS_LINES and tmp2 == IS_LINES)
    {
        vector_ v1 = a, v2, v3 = t.a, v4;

        if (a.is_equal(b))
            v2 = c;

        else
            v2 = b;

        if (t.a.is_equal(t.b))
            v4 = t.c;

        else
            v4 = t.b;

        line_segment_ ls1 = {v1, v2}, ls2 = {v3, v4};

        return ls1.is_intersect (ls2);
    }
    
    surface_ s1 {t.a, t.b, t.c};

    surface_ s11 {a, b, c};

    line_segment_ a1 {a, b}, a2 {b, c}, a3 {c, a};

    line_segment_ a11 {t.a, t.b}, a21 {t.b, t.c}, a31 {t.c, t.a};
   
    vector_ res1 = a1.sur_its_loc (s1), res2 = a2.sur_its_loc (s1), res3 = a3.sur_its_loc (s1);
    
    vector_ res11 = a11.sur_its_loc (s11), res21 = a21.sur_its_loc (s11), res31 = a31.sur_its_loc (s11);
    
    return t.contain_vec (res1) or t.contain_vec (res2) or t.contain_vec (res3) or
           this->contain_vec (res11) or this->contain_vec (res21) or this->contain_vec (res31);
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

int triangle_::print (int tab_number, int index) const
{
    tab_func (tab_number);

    std::cout << "triangle_" << index << std::endl;

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
        std::cout << "- " << std::abs(b);

    tab_func (tab_number);

    std::cout << "*y ";

    tab_func (tab_number);

    if (c > 0)
        std::cout << "+ " << c;

    else
        std::cout << "- " << std::abs(c);

    tab_func (tab_number);

    std::cout << "*z ";

    tab_func (tab_number);

    if (d > 0)
        std::cout << "+ " << d << std::endl;

    else
        std::cout << "- " << std::abs(d) << " = 0" << std::endl;
    
    n.print(tab_number + 1);
    r.print(tab_number + 1);

    tab_func (tab_number);

    std::cout << "}" << std::endl;;

    return 0;
}

int surface_::vec_init (double a, double b, double c, double d)
{
    r.x = (d_equal (a, 0)) ? 0 : - d / a; 
    r.y = (d_equal (b, 0)) ? 0 : - d / b; 
    r.z = (d_equal (c, 0)) ? 0 :   d / c;

    return 0;
}


//line segment

bool line_segment_::is_intersect (const line_segment_ &ls) const
{
    vector_ v1 = a - b, v2 = ls.a - ls.b, v3 = a - ls.a;

    double res = (v1 * v2) ^ v3;

    return d_equal(res, 0);
}

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


bool parallelepiped_::is_valid () const
{
    return  std::isfinite (x1) and std::isfinite (x2) and
            std::isfinite (y1) and std::isfinite (y2) and
            std::isfinite (z1) and std::isfinite (z2) and
            (x1 < x2) and (y1 < y2) and (z1 < z2);
}

int parallelepiped_::contain_vec (const vector_ &vec) const
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

int parallelepiped_::contain_tr (const triangle_ &t) const
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

int parallelepiped_::print (int tab_number) const
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


bool node_::is_valid () const
{
    return p.is_valid();
}

int node_::make_childs ()
{
    node_ tmp;

    for (int i = 0; i < 8; ++i)
    {
        tmp.p.x1 = p.x1 + ((i & 4) != 0) * (p.x2 - p.x1) / 2;
        tmp.p.x2 = (p.x1 + p.x2) / 2 + ((i & 4) != 0) * (p.x2 - p.x1) / 2;

        tmp.p.y1 = p.y1 + ((i & 2) != 0) * (p.y2 - p.y1) / 2;
        tmp.p.y2 = (p.y1 + p.y2) / 2 + ((i & 2) != 0) * (p.y2 - p.y1) / 2;

        tmp.p.z1 = p.z1 + ((i & 1) != 0) * (p.z2 - p.z1) / 2;
        tmp.p.z2 = (p.z1 + p.z2) / 2 + ((i & 1) != 0) * (p.z2 - p.z1) / 2;
    
        nodes.push_back(tmp);
    }

    return 0;
}

int node_::push (const triangle_ &t, int i) 
{
    int tmp = p.contain_tr (t);

    triangle_stat tr_stat = t.is_valid();
    
    if (tmp == -1)
        return -1;

    else if (tmp == 8)
    {
        T_.push_back (t);
        I_.push_back (i);
    }

    else if (tr_stat != IS_POINT)
    {
        make_childs ();
        
        nodes[tmp].push (t, i);
    }

    else
    {
        if (nodes.empty())
        {
            T_.push_back (t);
            I_.push_back (i);
        }

        else
            nodes[tmp].push (t, i);
    }

    return 0;
}

int node_::print (int tab_number, int node_number) const
{
    if (T_.empty() and nodes.empty())
        return 0;
    
    tab_func (tab_number);

    std::cout << std::bitset <3> (node_number) << std::endl;

    tab_func (tab_number);

    std::cout << "node:\n";

    tab_func (tab_number);

    std::cout << "{\n";

    p.print(tab_number + 1);

    if (!T_.empty())
    {
        tab_func (tab_number + 1);

        std::cout << "triangle vector\n";

        tab_func (tab_number + 1);

        std::cout << "{\n";

        for (int i = 0; i < T_.size(); ++i)
            T_[i].print (tab_number + 2, I_[i]);

        tab_func (tab_number + 1);

        std::cout << "}\n";
    }

    if (!nodes.empty())
    {
        tab_func (tab_number + 1);

        std::cout << "nodes:\n";

        tab_func (tab_number + 1);

        std::cout << "{\n";

        for (int i = 0; i < 8; ++i)
            nodes[i].print(tab_number + 2, i);

        tab_func (tab_number + 1);

        std::cout << "}\n";
    }

    tab_func (tab_number);

    std::cout << "}\n";

    return 0;
}


//tree


int my_tree::fill_tree (std::vector <triangle_> &t, int n)
{
    std::vector <triangle_> t1;
    std::vector <int>       i1;

    geom::vector_ vmax, vmin;
    geom::vector_ tmp_max, tmp_min;

    for (int i = 0; i < n; ++i)
    {
        tmp_max.x = std::max (t[i].a.x, std::max (t[i].b.x, t[i].c.x));
        tmp_max.y = std::max (t[i].a.y, std::max (t[i].b.y, t[i].c.y));
        tmp_max.z = std::max (t[i].a.z, std::max (t[i].b.z, t[i].c.z));

        tmp_min.x = std::min (t[i].a.x, std::min (t[i].b.x, t[i].c.x));
        tmp_min.y = std::min (t[i].a.y, std::min (t[i].b.y, t[i].c.y));
        tmp_min.z = std::min (t[i].a.z, std::min (t[i].b.z, t[i].c.z));
        
        if (i == 0)
        {
            vmax = tmp_max;
            vmin = tmp_min;
        }

        else
        {
            vmax.x = std::max (vmax.x, tmp_max.x);
            vmax.y = std::max (vmax.y, tmp_max.y);
            vmax.z = std::max (vmax.z, tmp_max.z);
        
            vmin.x = std::min (vmin.x, tmp_min.x);
            vmin.y = std::min (vmin.y, tmp_min.y);
            vmin.z = std::min (vmin.z, tmp_min.z);
        }
    }

    top.p = {vmin.x - 1, vmax.x + 1,
             vmin.y - 1, vmax.y + 1, 
             vmin.z - 1, vmax.z + 1};

    for (int i = 0; i < n; ++i)
    {
        triangle_stat tr_stat = t[i].is_valid();
        
        if (tr_stat == IS_NAN)
            std::cout << "wrong triangle " << i << std::endl;

        else if (tr_stat == IS_POINT)
        {
            t1.push_back (t[i]);
            i1.push_back (i);
        }

        else
            push (t[i], i);
    }

    for (int i = 0; i < t1.size(); ++i)
        push (t1[i], i1[i]);

    return 0;
}

int my_tree::push (const triangle_ &t, int i)
{
    return top.push (t, i);
}

int my_tree::print () const
{
    std::cout << "tree:\n{\n";

    top.print(1, 0);

    std::cout << "}\n";

    return 0;
}


//solution

std::set <int> my_tree::start_sol () const
{
    std::set <int> res;

    top.main_step (res);

    return res;
}

int node_::main_step (std::set <int> &res) const
{
    for (int i = 0; i < T_.size(); ++i)
            for (int j = i + 1; j < T_.size(); ++j)
                if (T_[i].trl_intersect (T_[j]))
                {
                    res.insert (I_[i]);
                    res.insert (I_[j]);
                }

    if (!nodes.empty())
    {
        for (int i = 0; i < T_.size(); ++i)
                for (int j = 0; j < 8; ++j)
                    nodes[j].step_sol (T_[i], I_[i], res);

        for (int i = 0; i < 8; ++i)
            nodes[i].main_step(res);
    }

    return 0;   
}

int node_::step_sol (const triangle_ &t, const int i, std::set <int> &res) const
{
    if (!t.is_valid())
        return -1;

    for (int j = 0; j < T_.size(); ++j)
        if (T_[j].trl_intersect (t))
        {
            res.insert (i);
            res.insert (I_[j]);
        }
        
    if (!nodes.empty())
        for (int j = 0; j < 8; ++j)
            nodes[j].step_sol (t, i, res);
                

    return 0;
}

std::set <int> triv_sol (std::vector <triangle_> &t, const int size)
{
    std::set <int> res;

    for (int i = 0; i < t.size(); ++i)
        if (res.find (i) == res.end())
            for (int j = i + 1; j < t.size(); ++j)
                if (t[i].trl_intersect (t[j]))
                {
                    res.insert (i);
                    res.insert (j);
                    break;
                }

    return res;
}

//func for printing

int tab_func (int tab_number)
{
    for (int i = 0; i < tab_number; ++i)
        std::cout << "\t";

    return 0;
}
}