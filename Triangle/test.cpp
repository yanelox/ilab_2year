#include "triangle.hpp"

void vector_test ()
{
    geom::vector_ a {};
    geom::vector_ b {1, 2, 3};

    printf ("%d %d %lg\n", a.is_equal(a), a.is_valid(), a.mod());
    a.print(0);

    printf ("%d %d %lg\n", b.is_equal(b), b.is_valid(), b.mod());
    b.print(0);
}

void line_test ()
{
    geom::line_ a {};
    geom::line_ b {{1, 1, 1}, {1, 2, 3}};

    std::cout << a.is_valid() << std::endl;

    a.print(0);

    a.point_to_line({1, 1, 1}, {1, 2, 3});

    std::cout << a.is_valid() << " " << b.is_valid() << std::endl;

    a.print(0);
    b.print(0);
}

void triangle_test ()
{
    geom::triangle_ a {};
    geom::triangle_ b {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};

    std::cout << a.is_valid() << " " << b.is_valid() << std::endl;

    a = geom::triangle_ {{0, 0, 0}, {1, 1, 0}, {1, 1, 1}};

    a.print(0);
    b.print(0);

    std::cout << a.contain_vec ({1, 1, 0.5}) << " " << b.contain_vec ({1, 0, 0}) << std::endl;

    std::cout << a.trl_intersect(b) << std::endl;
}

void surface_test ()
{
    geom::surface_ a {};
    geom::surface_ b {1, 1, 1, 1};
    geom::surface_ c {{1, 1, 1}, {-1, -1, 1}};
    geom::surface_ d {{1, -1, -1}, {-1, 1, -1}, {-1, -1, 1}};

    std::cout << a.is_valid() << b.is_valid() << c.is_valid() << d.is_valid() << std::endl;

    a.print(0);
    b.print(0);
    c.print(0);
    d.print(0);

    std::cout << b.sur_intersect(d) << c.sur_intersect(d) << c.sur_intersect(b) << std::endl;   
}

void line_segment_test ()
{
    geom::line_segment_ a {};
    geom::line_segment_ b {{0, 0, 0}, {1, 1, 1}};

    geom::surface_ c {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};

    geom::vector_ d {};

    std::cout << a.is_valid() << b.is_valid() << std::endl;

    a.print(0);
    b.print(0);

    std::cout << b.sur_intersect (c) << std::endl;

    d = b.sur_its_loc (c);

    d.print(0);
}

void end_to_end_test ()
{
    std::vector <geom::triangle_> a(10);

    int res[] = {0, 1, 2, 3, 4, 5};

    a[0] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
    a[1] = {{2, 0, 0}, {0, 2, 0}, {0, 0, 2}};
    a[2] = {{0, 0, 0}, {0, 1, 1}, {1, 1, 2}};
    a[3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
    a[4] = {{0, 0, 0}, {1, 0, 0}, {0, 1, 0}};
    a[5] = {{0, 0, 0}, {0, 0, -1}, {1, 0, -1}};
    a[6] = {{0, 0, 7}, {1, 0, 7}, {0, 1, 7}};

    geom::my_tree Tree;
    Tree.fill_tree (a, 7);

    std::cout << "programm answers:" << std::endl;

    std::set <int> res_ =  Tree.start_sol();

    for (auto i:res_)
        std::cout << i << std::endl;

    std::cout << "true answers:" << std::endl;

    for (auto i:res)
        std::cout << i << std::endl;
}

void big_test ()
{
    int size = 100000;

    std::vector <geom::triangle_> t(size);

    for (int i = 0; i < size; ++i)
    {
        t[i].a = {(double) (rand() % 200 - 100), (double) (rand() % 200 - 100), (double) (rand() % 200 - 100)};
        t[i].b = {(double) (rand() % 200 - 100), (double) (rand() % 200 - 100), (double) (rand() % 200 - 100)};
        t[i].c = {(double) (rand() % 200 - 100), (double) (rand() % 200 - 100), (double) (rand() % 200 - 100)};
    }

    geom::my_tree Tree;
    Tree.fill_tree (t, size);

    std::set <int> res =  Tree.start_sol();

    for (auto i:res)
        std::cout << i << std::endl;
}