#include "triangle.hpp"
#include <stdio.h>

void vector_test ()
{
    vector_ a {};
    vector_ b {1, 2, 3};

    printf ("%d %d %lg\n", a.is_equal(a), a.is_valid(), a.mod());
    a.print();

    printf ("%d %d %lg\n", b.is_equal(b), b.is_valid(), b.mod());
    b.print();
}

void line_test ()
{
    line_ a {};
    line_ b {{1, 1, 1}, {1, 2, 3}};

    cout << a.is_valid() << endl;

    a.print();

    a.point_to_line({1, 1, 1}, {1, 2, 3});

    cout << a.is_valid() << " " << b.is_valid() << endl;

    a.print();
    b.print();
}

void triangle_test ()
{
    triangle_ a {};
    triangle_ b {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};

    cout << a.is_valid() << " " << b.is_valid() << endl;

    a = triangle_ {{0, 0, 0}, {1, 1, 0}, {1, 1, 1}};

    a.print();
    b.print();

    cout << a.contain_vec ({1, 1, 0.5}) << " " << b.contain_vec ({1, 0, 0}) << endl;

    cout << a.trl_intersect(b) << endl;
}

void surface_test ()
{
    surface_ a {};
    surface_ b {1, 1, 1, 1};
    surface_ c {{1, 1, 1}, {-1, -1, 1}};
    surface_ d {{1, -1, -1}, {-1, 1, -1}, {-1, -1, 1}};

    cout << a.is_valid() << b.is_valid() << c.is_valid() << d.is_valid() << endl;

    a.print();
    b.print();
    c.print();
    d.print();

    cout << b.sur_intersect(d) << c.sur_intersect(d) << c.sur_intersect(b) << endl;   
}

void line_segment_test ()
{
    line_segment_ a {};
    line_segment_ b {{0, 0, 0}, {1, 1, 1}};

    surface_ c {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};

    vector_ d {};

    cout << a.is_valid() << b.is_valid() << endl;

    a.print();
    b.print();

    cout << b.sur_intersect (c) << endl;

    d = b.sur_its_loc (c);

    d.print();
}

//TODO: make tests for line_segment_