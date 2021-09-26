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

void end_to_end_test ()
{
    triangle_ *a = new triangle_ [10];

    int res[] = {0, 1, 2, 3, 4, 5};

    a[0] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
    a[1] = {{2, 0, 0}, {0, 2, 0}, {0, 0, 2}};
    a[2] = {{0, 0, 0}, {0, 1, 1}, {1, 1, 2}};
    a[3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
    a[4] = {{0, 0, 0}, {1, 0, 0}, {0, 1, 0}};
    a[5] = {{0, 0, 0}, {0, 0, -1}, {1, 0, -1}};
    a[6] = {{0, 0, 7}, {1, 0, 7}, {0, 1, 7}};

    cout << "programm answers:" << endl;

    solution (a, 7);

    cout << "true answers:" << endl;

    for (auto i:res)
        cout << i << endl;

    delete[] a;
}

void big_test ()
{
    int size = 100000;

    triangle_ *t = new triangle_ [size];

    for (int i = 0; i < size; ++i)
    {
        t[i].a = {(double) (rand() % 200 - 100), (double) (rand() % 200 - 100), (double) (rand() % 200 - 100)};
        t[i].b = {(double) (rand() % 200 - 100), (double) (rand() % 200 - 100), (double) (rand() % 200 - 100)};
        t[i].c = {(double) (rand() % 200 - 100), (double) (rand() % 200 - 100), (double) (rand() % 200 - 100)};
    }

    solution (t, size);

    delete[] t;
}