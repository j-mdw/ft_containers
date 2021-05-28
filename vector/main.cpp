#include <vector>
#include "vector.hpp"
#include "ft_container.hpp"

int
main(void)
{

    std::cout << "\n\nSTL VECTOR BEHAVIOR TESTS\n\n";
    // {
        // std::vector<int> v;
        // std::vector<int> v1(10);
    //     display(v1);

    //     for (int i = 0; i < 1000; i++)
    //     {
    //         v1.push_back(5);
    //         display(v1);
    //     }
    //     for (int i = 0; i < 100; i++)
    //     {
    //         v1.pop_back();
    //         display(v1);
    //     }    
    //     v1.resize(100);
    //     display(v1);
    // }

    std::cout << "\nMY VECTOR TESTS\n\n";
    {
        std::cout << "\n##### Empty vector #####\n\n";
        ft::vector<int> v1;
        std::vector<int> vv1;
        containerCmp(v1, vv1);

        std::cout << "\n##### Vector initialize with size 10 #####\n\n";
        ft::vector<int> v2(10);
        std::vector<int> vv2(10);
        containerCmp(v2, vv2);

    }
    return (0);
}