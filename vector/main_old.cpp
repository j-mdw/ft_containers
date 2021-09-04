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

        std::cout << "\n#### Copy Constructor ####\n\n";
        ft::vector<int> v3_cpy(v3);
        containerCmp(v3_cpy, vv3);

        std::cout << "\n#### Reverse iterator ####\n\n";
        {
		ft::vector<int> my_v;
		std::vector<int> std_v;
		for (int i = 0; i < 10; i++)
		{
			my_v.push_back(i);
			std_v.push_back(i);
		}

        ft::vector<int>::reverse_iterator rit = my_v.rbegin();
		ft::vector<int>::reverse_iterator rite = my_v.rend();

        std::vector<int>::reverse_iterator std_rit = std_v.rbegin();
        std::vector<int>::reverse_iterator std_rite = std_v.rend();

        for (; rit != rite; rit++)
        {
			// std::cout << "Begin: " <<
            std::cout << *rit << " : " << *std_rit << " | ";
            if (*rit != *std_rit)
			{
                std::cout << "Rev it failed\n";
				break ;
			}
			std_rit++;
        }
        std::cout << '\n';
        if (rit == rite && std_rit == std_rite)
            std::cout << "Rev it ok\n";
        else
            std::cout << "Rev it failed\n";
		if (*(rit - 1) != *(std_rit - 1))
			std::cout << "KO|";
		else
			std::cout << "OK|";
		if (*(rit - 5) != *(std_rit - 5))
			std::cout << "KO|";
		else
			std::cout << "OK|";

		rit--;
		std_rit--;
		if (*rit != *std_rit)
			std::cout << "KO|";
		else
			std::cout << "OK|";
		rit-= 6;
		std_rit -= 6;
		if (*rit != *std_rit)
			std::cout << "KO|";
		else
			std::cout << "OK|";
		rit+= 2;
		std_rit += 2;
		if (*rit != *std_rit)
			std::cout << "KO|";
		else
			std::cout << "OK|";

		if (*++rit != *++std_rit)
			std::cout << "KO|";
		else
			std::cout << "OK|";
		if (*rit-- != *std_rit--)
			std::cout << "KO|";
		else
			std::cout << "OK|";
		if (*(rit - 2) != *(std_rit -2))
			std::cout << "KO|";
		else
			std::cout << "OK|";
		
		ft::vector<int>::reverse_iterator rit_cpy(rit);
		std::vector<int>::reverse_iterator std_rit_cpy(std_rit);

		if ((rit != rit_cpy) != (std_rit != std_rit_cpy))
			std::cout << "KO|";
		else
			std::cout << "OK|";
		if ((rit == rit_cpy) != (std_rit == std_rit_cpy))
			std::cout << "KO|";
		else
			std::cout << "OK|";
		if ((rit >= rit_cpy) != (std_rit >= std_rit_cpy))
			std::cout << "KO|";
		else
			std::cout << "OK|";
		if ((rit <= rit_cpy) != (std_rit <= std_rit_cpy))
			std::cout << "KO|";
		else
			std::cout << "OK|";
		
		if ((rit < rit_cpy) != (std_rit < std_rit_cpy))
			std::cout << "KO|";
		else
			std::cout << "OK|";
		if ((rit > rit_cpy) != (std_rit > std_rit_cpy))
			std::cout << "KO|";
		else
			std::cout << "OK|";

		rit_cpy--; std_rit_cpy--;
		if ((rit != rit_cpy) != (std_rit != std_rit_cpy))
			std::cout << "KO|";
		else
			std::cout << "OK|";
		if ((rit == rit_cpy) != (std_rit == std_rit_cpy))
			std::cout << "KO|";
		else
			std::cout << "OK|";
		if ((rit >= rit_cpy) != (std_rit >= std_rit_cpy))
			std::cout << "KO|";
		else
			std::cout << "OK|";
		if ((rit <= rit_cpy) != (std_rit <= std_rit_cpy))
			std::cout << "KO|";
		else
			std::cout << "OK|";
		
		if ((rit < rit_cpy) != (std_rit < std_rit_cpy))
			std::cout << "KO|";
		else
			std::cout << "OK|";
		if ((rit > rit_cpy) != (std_rit > std_rit_cpy))
			std::cout << "KO|";
		else
			std::cout << "OK|";

		}
        std::cout << "\n\n##### Vector using Iterator constructor #####\n\n";
		{
			ft::vector<int> ft_v;
			std::vector<int> std_v;
			for (size_t i = 0; i < 100; ++i)
			{
				ft_v.push_back(i);
				std_v.push_back(i);
			}
			// ft::vector<int> vec(12, )
			ft::vector<int> ft_vit(ft_v.begin(), ft_v.end());
			std::vector<int> std_vit(std_v.begin(), std_v.end());
			
			containerCmp(ft_vit, std_vit);
		}

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
        ft::vector<int> v3v(10, -13);
        std::vector<int> vv3v(10, -13);

        v3.assign(v3v.begin(), v3v.end());
        vv3.assign(vv3v.begin(), vv3v.end());
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

        std::cout << "\n#### insert(VALUES)####\n\n";
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

		std::cout << "\n#### insert(ITERATOR)####\n\n";
		{
			ft::vector<int> ft_v;
			std::vector<int> std_v;
			for (size_t i = 0; i < 100; ++i)
			{
				ft_v.push_back(i);
				std_v.push_back(i);
			}
			std::cout << "\n#### insert 5 values begin ####\n\n";
			
			ft::vector<int> ft_v_i(5, 42);
			std::vector<int> std_v_i(5, 42);
			
			ft_v.insert(ft_v.begin(), ft_v_i.begin(), ft_v_i.end());
			std_v.insert(std_v.begin(), std_v_i.begin(), std_v_i.end());
			containerCmp(ft_v, std_v);
	
			std::cout << "\n#### insert 5 values at begin + 5 ####\n\n";
			ft_v.insert(ft_v.begin() + 5, ft_v_i.begin(), ft_v_i.end());
			std_v.insert(std_v.begin() + 5, std_v_i.begin(), std_v_i.end());
			containerCmp(ft_v, std_v);

			std::cout << "\n#### insert 5 values at end ####\n\n";
			ft_v.insert(ft_v.end(), ft_v_i.begin(), ft_v_i.end());
			std_v.insert(std_v.end(), std_v_i.begin(), std_v_i.end());
			containerCmp(ft_v, std_v);

			std::cout << "\n#### insert 1 value at begin, 2 at begin + 50, 3 at end ####\n\n";
			ft_v.insert(ft_v.begin(), ft_v_i.begin(), ft_v_i.begin() + 1);
			std_v.insert(std_v.begin(), std_v_i.begin(), std_v_i.begin() + 1);

			ft_v.insert(ft_v.begin() + 50, ft_v_i.begin(), ft_v_i.begin() + 2);
			std_v.insert(std_v.begin() + 50, std_v_i.begin(), std_v_i.begin() + 2);	

			ft_v.insert(ft_v.end(), ft_v_i.begin() + 2, ft_v_i.begin() + 5);
			std_v.insert(std_v.end(), std_v_i.begin() + 2, std_v_i.begin() + 5);	
			containerCmp(v3, vv3);
		}

        std::cout << "\n#### Erase element at begin + 5 and element at end - 1 ####\n\n";
        testContFeature(
            *v3.erase(v3.begin() + 5) ==
            *vv3.erase(vv3.begin() + 5),
            "Erase1:", v3, vv3);
        testContFeature(
            *v3.erase(v3.end() - 1) ==
            *vv3.erase(vv3.end() - 1),
            "Erase2:", v3, vv3);
        containerCmp(v3, vv3);

        std::cout << "\n#### Swap (method) ####\n\n";
        ft::vector<int> v3s(7, -7);
        std::vector<int> vv3s(7, -7);
        
        v3.swap(v3s);
        vv3.swap(vv3s);
        containerCmp(v3, vv3);
        containerCmp(v3s, vv3s);

        std::cout << "\n#### Swap (non-member function overload) ####\n\n";

        ft::swap(v3, v3s);
        std::swap(vv3, vv3s);
        containerCmp(v3, vv3);
        containerCmp(v3s, vv3s);

        std::cout << "\n#### Clear ####\n\n";
        v3.clear();
        vv3.clear();
        containerCmp(v3, vv3); 

        std::cout << "\n#### Relational operators ####\n\n";
        {
            ft::vector<int> v4(10, 42);
            ft::vector<int> v5(10, 42);
            std::vector<int> vv4(10, 42);
            std::vector<int> vv5(10, 42);
            testContFeature(v4 == v5, "operator ==", v4, v5);
            testContFeature(vv4 == vv5, "operator ==", vv4, vv5);
            v5.pop_back();
            vv5.pop_back();
            testContFeature(!(v4 == v5), "operator ==", v4, v5);
            testContFeature(!(vv4 == vv5), "operator ==", vv4, vv5);
            testContFeature(v4 >= v5, "operator >=", v4, v5);
            testContFeature(vv4 >= vv5, "operator >=", vv4, vv5);
            testContFeature(v4 > v5, "operator >", v4, v5);
            testContFeature(vv4 > vv5, "operator >", vv4, vv5);
            v5.push_back(7);
            vv5.push_back(7);
            testContFeature(!(v4 == v5), "operator ==", v4, v5);
            testContFeature(!(vv4 == vv5), "operator ==", vv4, vv5);
            testContFeature(v4 >= v5, "operator >=", v4, v5);
            testContFeature(vv4 >= vv5, "operator >=", vv4, vv5);
            testContFeature(v4 > v5, "operator >", v4, v5);
            testContFeature(vv4 > vv5, "operator >", vv4, vv5);

            testContFeature(v4 != v5, "operator !=", v4, v5);
            testContFeature(vv4 != vv5, "operator !=", vv4, vv5);
            v5.pop_back();
            vv5.pop_back();
            testContFeature(v4 != v5, "operator !=", v4, v5);
            testContFeature(vv4 != vv5, "operator !=", vv4, vv5);
            v5.push_back(42);
            vv5.push_back(42);
            testContFeature(!(v4 != v5), "operator !=", v4, v5);
            testContFeature(!(vv4 != vv5), "operator !=", vv4, vv5);
            testContFeature(v4 >= v5, "operator >=", v4, v5);
            testContFeature(vv4 >= vv5, "operator >=", vv4, vv5);
            testContFeature(!(v4 > v5), "operator >", v4, v5);
            testContFeature(!(vv4 > vv5), "operator >", vv4, vv5);


            testContFeature(!(v4 < v5), "operator <", v4, v5);
            testContFeature(!(vv4 < vv5), "operator <", vv4, vv5);
            v4.pop_back();
            vv4.pop_back();
            testContFeature(v4 < v5, "operator <", v4, v5);
            testContFeature(vv4 < vv5, "operator <", vv4, vv5);
            testContFeature(v4 <= v5, "operator <=", v4, v5);
            testContFeature(vv4 <= vv5, "operator <=", vv4, vv5);
            testContFeature(v4 != v5, "operator !=", v4, v5);
            testContFeature(vv4 != vv5, "operator !=", vv4, vv5);
            v5.pop_back();
            vv5.pop_back();
            v5.pop_back();
            vv5.pop_back();
            testContFeature(!(v4 < v5), "operator <", v4, v5);
            testContFeature(!(vv4 < vv5), "operator <", vv4, vv5);
            v5.push_back(100);
            vv5.push_back(100);
            testContFeature(v4 < v5, "operator <", v4, v5);
            testContFeature(vv4 < vv5, "operator <", vv4, vv5);
            v5.pop_back();
            vv5.pop_back();
            v4[0] = -10;
            vv4[0] = -10;
            testContFeature(v4 < v5, "operator <", v4, v5);
            testContFeature(vv4 < vv5, "operator <", vv4, vv5);
            v4.at(0) = 100;
            vv4.at(0) = 100;
            testContFeature(!(v4 < v5), "operator <", v4, v5);
            testContFeature(!(vv4 < vv5), "operator <", vv4, vv5);
           
        }
    }
    return (0);
}