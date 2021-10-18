#include "triangle.hpp"

int main ()
{
    int n;
    std::vector <geom::triangle_> T;
    std::vector <geom::vector_> V(3);

    std::set <int> res1;

    geom::my_tree Tree;

    std::cin >> n;

    for (int i = 0; i < n; ++i)
    {  
        for (int j = 0; j < 3; ++j)
            std::cin >> V[j].x >> V[j].y >> V[j].z;

        T.push_back ({V[0], V[1], V[2]});
    }

    Tree.fill_tree(T, n);

    res1 = Tree.start_sol();
    for (auto i:res1)
        std::cout << i << std::endl;

    // res1 = geom::triv_sol (T, 11);
    // for (auto i:res1)
    //     std::cout << i << std::endl;

    // Tree.print();
}