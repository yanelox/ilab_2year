#include "triangle.hpp"

int main ()
{
    int n;
    geom::triangle_ *T = nullptr; 
    double data[9];

    geom::my_tree Tree;

    std::cin >> n;

    T = new geom::triangle_ [n];

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < 9; ++j)
            std::cin >> data[j];

        T[i] = {{data[0], data[1], data[2]},
                {data[3], data[4], data[5]},
                {data[6], data[7], data[8]}};
    }

    Tree.fill_tree(T, n);

    Tree.print();

    delete[] T;
}