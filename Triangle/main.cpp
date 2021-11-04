#include "lib/triangle.hpp"
#include "vulkan/vulkan.cpp"

int main ()
{
    int n;
    std::vector <geom::triangle_> T;
    std::vector <geom::vector_> V(3);

    std::set <int> res1;

    geom::my_tree Tree;

    std::cin >> n;

    double w = 1.0;

    for (int i = 0; i < n; ++i)
    {  
        for (int j = 0; j < 3; ++j)
        {
            std::cin >> V[j].x >> V[j].y >> V[j].z;

            if (w < std::abs (V[j].x))
                w = std::abs (V[j].x);

            if (w < std::abs (V[j].y))
                w = std::abs (V[j].y);

            if (w < std::abs (V[j].z))
                w = std::abs (V[j].z);
        }

        T.push_back ({V[0], V[1], V[2]});
    }

    Tree.fill_tree(T, n);

    res1 = Tree.start_sol();
    for (auto i:res1)
        std::cout << i << std::endl;

    for (int i = 0; i < n; ++i)
    {
        T[i].a.x = T[i].a.x / w;
        T[i].a.y = T[i].a.y / w;
        T[i].a.z = T[i].a.z / w;

        T[i].b.x = T[i].b.x / w;
        T[i].b.y = T[i].b.y / w;
        T[i].b.z = T[i].b.z / w;

        T[i].c.x = T[i].c.x / w;
        T[i].c.y = T[i].c.y / w;
        T[i].c.z = T[i].c.z / w;
    }

    for (size_t i = 0; i < 3 * n; ++i)
        indices.push_back (i);

    for (size_t i = 0; i < n; ++i)
    {
        glm::vec3 color = {0.0f, 1.0f, 0.0f};

        if (res1.find (i) != res1.end())
            color = {1.0f, 0.0f, 0.0f};

        vertices.push_back ({{T[i].a.x, T[i].a.y, T[i].a.z}, color});
        vertices.push_back ({{T[i].b.x, T[i].b.y, T[i].b.z}, color});
        vertices.push_back ({{T[i].c.x, T[i].c.y, T[i].c.z}, color});
    }

    HelloTriangleApplication app;

    try 
    {
        app.run();
    } 

    catch (const std::exception& e) 
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;

    // res1 = geom::triv_sol (T, 11);
    // for (auto i:res1)
    //     std::cout << i << std::endl;

    // Tree.print();
}