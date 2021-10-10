#pragma once

#include <algorithm>
#include <bitset>
#include <iostream>
#include <cmath>
#include <map>
#include <vector>
#include <set>

namespace geom
{
bool d_equal (double x, double y);

const double pi_ = acos(-1);

enum mutual_loc
{
    ERROR           = 0,
    IS_EQUAL        = 1,
    IS_PARALLEL     = 2,
    IS_INTERSECT    = 3,
    NOT_INTERSECT   = 4,
    IS_CONTENTS     = 5
};

enum triangle_stat
{
    IS_NAN      = 0, //contain NAN vectors
    IS_VALID    = 1,
    IS_POINT    = 2,
    IS_LINES    = 3 //line segment
};


struct vector_
{
    double x, y, z;

    vector_ (): x{NAN}, y{NAN}, z{NAN} {}
    vector_ (double X, double Y, double Z): x(X), y(Y), z(Z) {}

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

    bool is_zero () const;

    bool is_valid () const;

    double mod () const;

    int print (int tab_number) const;
};


struct line_
{
    vector_ r, a;

    line_ (): r{}, a{} {}

    line_ (const vector_ &R, const vector_ &A): r(R), a(A) {}

    bool is_valid () const;

    int point_to_line (const vector_ &v1, const vector_ &v2);

    int print (int tab_number) const;
};


struct triangle_
{
    vector_ a, b, c;

    triangle_ (): a{}, b{}, c{} {}

    triangle_ (const vector_ &A, const vector_ &B, const vector_ &C): a(A), b(B), c(C) {}

    triangle_stat is_valid () const;

    bool contain_vec (const vector_ &v) const;

    bool trl_intersect (const triangle_ &t) const;

    int print (int tab_number) const;

    int print (int tab_number, int index) const;
};


struct surface_
{
    double a, b, c, d;

    vector_ n, r;

    surface_ (): a(NAN), b(NAN), c(NAN), d(NAN), n{}, r{} {}
    surface_ (double A, double B, double C, double D): a(A), b(B), c(C), d(D), n{A, B, C}, r{} 
    {
        if (d_equal (D, 0))
            r = {0, 0, 0};

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

    surface_ (const vector_ &N, const vector_ &R): a(N.x), b(N.y), c(N.z), d(NAN), n(N), r(R)
    {
        d = - (a * R.x + b * R.y + c * R.z);
    }

    surface_ (const vector_ &v1, const vector_ &v2, const vector_ &v3): 
    a(NAN), b(NAN), c(NAN), d(NAN), n{}, r{}
    {
        if (v1.is_valid() and v2.is_valid() and v3.is_valid())
        {
            double x1 = v1.x, y1 = v1.y, z1 = v1.z;
            double x2 = v2.x, y2 = v2.y, z2 = v2.z;
            double x3 = v3.x, y3 = v3.y, z3 = v3.z;

            a = (y2 - y1) * (z3 - z1) - (y3 - y1) * (z2 - z1);
            b = (x3 - x1) * (z2 - z1) - (x2 - x1) * (z3 - z1);
            c = (x2 - x1) * (y3 - y1) - (x3 - x1) * (y2 - y1);
            d = -a * x1 - b * y1 - c * z1;

            n = {a, b, c};
            
            if (d_equal (d, 0))
                r = {0, 0, 0};

            else
            {
                if (d_equal (a, 0))
                    r.x = 0;

                else
                    r.x = - d / a;

                if (d_equal (b, 0))
                    r.y = 0;

                else
                    r.y = - d / b;

                if (d_equal (c, 0))
                    r.z = 0;
                
                else
                    r.z = d / c;
            }
        }
    }

    bool is_valid () const;

    mutual_loc sur_intersect (const surface_ &an_sur) const;

    bool content_vec (const vector_ &vec) const;

    int print (int tab_number) const;
};


struct line_segment_
{
    vector_ a, b;

    line_segment_ (): a{}, b{} {}

    line_segment_ (const vector_ &A, const vector_ &B): a{A}, b{B} {};

    bool is_valid () const;

    bool is_intersect (const line_segment_ &ls) const;

    mutual_loc sur_intersect (const surface_ &s) const;

    vector_ sur_its_loc (const surface_ &s) const;

    int print (int tab_number) const;
};


struct prlppd_  //parallelepiped
{
    double x1, x2, y1, y2, z1, z2;

    prlppd_ (): x1{NAN}, x2{NAN}, y1{NAN}, y2{NAN}, z1{NAN}, z2{NAN} {};

    prlppd_ (double X1, double X2, 
             double Y1, double Y2, 
             double Z1, double Z2): x1{X1}, x2{X2}, y1{Y1}, y2{Y2}, z1{Z1}, z2{Z2} {};

    bool is_valid ();

    int contain_vec (const vector_ &vec);

    int contain_tr  (const triangle_ &t);

    int print (int tab_number) const;
};


struct node_
{
    prlppd_ p;

    std::vector <node_> nodes;

    std::vector <triangle_> T_;

    std::vector <int> I_;

    node_ (): nodes{}, p{}, T_{}, I_{} {};

    node_ (double x1, double x2,
           double y1, double y2,
           double z1, double z2): nodes{}, p{x1, x2, y1, y2, z1, z2}, 
                                                  T_{}, I_{} {};
                                
    node_ (const prlppd_ &P): nodes{}, p{P}, T_{}, I_{} {};

    bool is_valid ();

    int make_childs ();

    int push (const triangle_ &t, int i);

    int main_step (std::set <int> &res) const;

    int step_sol (const triangle_ &t, const int i, std::set <int> &res) const;

    int print (int tab_number, int node_number) const;
};


struct my_tree
{
    node_ top;

    my_tree (): top{} {};

    my_tree (double x1, double x2, 
             double y1, double y2, 
             double z1, double z2): top {x1, x2, y1, y2, z1, z2} {};

    int fill_tree (std::vector <triangle_> &t, int n);

    int push (const triangle_ &t, int i);

    std::set <int> start_sol () const;

    int print () const;
};

    int tab_func (int tab_number);

    std::set <int> triv_sol (std::vector <triangle_> &t, const int size);
}