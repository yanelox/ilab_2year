#include "graph.cpp"

int main ()
{
    graph::graph_ <int> G {};

    if (G.input() == 0)
    {
        std::cout << "Incorrect input\n";

        return 0;
    }
    // std::cout << G;

    int res = G.colorize();

    // G.recolorize();

    if (res == 1)
        G.print_colors(std::cout);

    else
        std::cout << "Error: non-bipartite graph\n";
}