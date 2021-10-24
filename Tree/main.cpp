#include "lib/tree.hpp"

int main ()
{
    tree::Tree_ t{}, t1{};

    t.push (2);
    t.push (0);
    t.push (1);

    t1 = t;

    t1.fprint ("graph.dot");

    return 0;
}