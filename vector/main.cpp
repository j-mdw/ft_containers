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


        std::cout << "\n##### Vector initialize with size 100 and value 42 #####\n\n";
        ft::vector<int> v3(100, 42);
        std::vector<int> vv3(100, 42);
        containerCmp(v3, vv3);

        std::cout << "\n#### Resize to 150 with value 30 ####\n\n";
        v3.resize(150, 30);
        vv3.resize(150, 30);
        containerCmp(v3, vv3);

        std::cout << "\n#### Resize to 20 with value -10 ####\n\n";
        v3.resize(20, -10);
        vv3.resize(20, -10);
        containerCmp(v3, vv3);

        std::cout << "\n#### Resize to 201 with value 7 ####\n\n";
        v3.resize(201, 7);
        vv3.resize(201, 7);
        containerCmp(v3, vv3);

        std::cout << "\n#### Reserve 10 ####\n\n";
        v3.reserve(10);
        vv3.reserve(10);
        containerCmp(v3, vv3);

        std::cout << "\n#### Reserve 0 ####\n\n";
        v3.reserve(0);
        vv3.reserve(0);
        containerCmp(v3, vv3);

        std::cout << "\n#### Reserve 1000 ####\n\n";
        v3.reserve(1000);
        vv3.reserve(1000);
        containerCmp(v3, vv3);

        std::cout << "\n#### Assign (iterator) ####\n\n";
        std::vector<int> vvv3(10, -13);
        v3.assign(vvv3.begin(), vvv3.end());
        vv3.assign(vvv3.begin(), vvv3.end());
        containerCmp(v3, vv3);

        // std::cout << "\n#### Assign (value) ####\n\n";
        // v3.assign(5000, 11);
        // vv3.assign(5000, 11);
        // containerCmp(v3, vv3);

        std::cout << "\n#### Push-back ####\n\n";
        v3.push_back(1);
        v3.push_back(2);
        v3.push_back(3);
        vv3.push_back(1);
        vv3.push_back(2);
        vv3.push_back(3);
        containerCmp(v3, vv3);

        std::cout << "\n#### Pop-back ####\n\n";
        v3.pop_back();
        v3.pop_back();
        v3.pop_back();
        vv3.pop_back();
        vv3.pop_back();
        vv3.pop_back();
        containerCmp(v3, vv3);

        std::cout << "\n#### insert 5 values begin ####\n\n";
        v3.insert(v3.begin(), 5, 333);
        vv3.insert(vv3.begin(), 5, 333);
        containerCmp(v3, vv3);

        std::cout << "\n#### insert 5 values at begin + 5 ####\n\n";
        v3.insert(v3.begin() + 5, 5, 777);
        vv3.insert(vv3.begin() + 5, 5, 777);
        containerCmp(v3, vv3);

        std::cout << "\n#### insert 5 values at end ####\n\n";
        v3.insert(v3.end(), 5, 111);
        vv3.insert(vv3.end(), 5, 111);
        containerCmp(v3, vv3);

        std::cout << "\n#### insert 1 value at begin, begin + 5, end ####\n\n";
        v3.insert(v3.begin(), -1);
        v3.insert(v3.begin() + 5, -2);
        v3.insert(v3.end(), -3);
        vv3.insert(vv3.begin(), -1);
        vv3.insert(vv3.begin() + 5, -2);
        vv3.insert(vv3.end(), -3);
        containerCmp(v3, vv3);

        std::cout << "\n#### Erase element at begin + 5 and element at end - 1 ####\n\n";
        testContFeature(
            *v3.erase(v3.begin() + 5) ==
            *vv3.erase(vv3.begin() + 5),
            "Erase1:", v3, vv3);
        testContFeature(
            *v3.erase(v3.end() - 1) ==
            *vv3.erase(vv3.end() - 1),
            "Erase2:", v3, vv3);
        // testContFeature(
            // *
        v3.erase(v3.end());
        vv3.erase(vv3.end());
            // "Erase3:", v3, vv3);

        containerCmp(v3, vv3);
    }
    return (0);
}