#include "test.cpp"

int main ()
{   
    std::cout << "-------------------vector_test-------------------\n";
    vector_test();
    std::cout << std::endl;

    std::cout << "-------------------line_test-------------------\n";
    line_test();
    std::cout << std::endl;

    std::cout << "-------------------triangle_test-------------------\n";
    triangle_test();
    std::cout << std::endl;

    std::cout << "-------------------surface_test-------------------\n";
    surface_test();
    std::cout << std::endl;

    std::cout << "-------------------line_segment_test-------------------\n";
    line_segment_test();
    std::cout << std::endl;

    std::cout << "-------------------end_to_end_test-------------------\n";
    end_to_end_test();

    // big_test();
}