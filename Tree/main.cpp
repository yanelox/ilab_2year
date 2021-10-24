#include "lib/tree.hpp"

int main ()
{
    tree::Tree_ t{};

    t.push (1);
    t.push (2);
    t.push (0);

    t.fprint ("graph.dot");

    return 0;
}