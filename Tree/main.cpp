#include "lib/tree.hpp"
#include <vector>

#ifdef DUMP
#define WORK_MOD 1
#else
#define WORK_MOD 0
#endif

int main ()
{
    tree::Tree_ t{};

    char c = 0;
    int n = 0;

    std::vector <int> res{};
    
    while (!std::cin.eof())
    {
        std::cin >> c;
        
        if (std::cin.eof())
            break;

        else
            std::cin >> n;

        if (c == 'k')
            t.push (n);

        else if (c == 'm')
        {
            if (n > t.get_size())
            {
                printf ("Incorrect input\n");

                return 0;
            }

            res.push_back (t.k_min (n));
        }

        else if (c == 'n')
            res.push_back (t.m_less (n));
    }

    for (auto i:res)
        std::cout << i << " ";

    std::cout << std::endl;

    if (WORK_MOD)
        t.fprint ("graph.dot");

    return 0;
}