#include <iostream>

int main (int argc, char* argv[])
{
    int n = atoi(argv[1]);

    std::cout << n << std::endl;

    for (int i = 0; i < n; ++i)
        std::cout << std::rand() << std::endl;

    return 0;
}