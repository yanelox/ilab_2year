#include "triangle.hpp"

int main ()
{
    int n;
    std::vector <geom::triangle_> T;
    double data[9];

    std::set <int> res1, res2;

    geom::my_tree Tree;

    std::cin >> n;

    for (int i = 0; i < n; ++i)
    {  
        for (int j = 0; j < 9; ++j)
            std::cin >> data[j];

        T.push_back ({{data[0], data[1], data[2]},
                      {data[3], data[4], data[5]},
                      {data[6], data[7], data[8]}});
    }

    Tree.fill_tree(T, n);

    res1 = Tree.start_sol();
    for (auto i:res1)
        std::cout << i << std::endl;

    // res2 = geom::triv_sol (T, n);
    // for (auto i:res2)
    //     std::cout << i << std::endl;

    // Tree.print();
}