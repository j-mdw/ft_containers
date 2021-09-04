#ifndef FT_CONTAINER_H
# define FT_CONTAINER_H

// # include "vector.hpp"
# include <string>
# include <iomanip>
# include <ios>
# include <iostream>
# include <ctime>
# include <cstdlib>

# define OK_GREEN "\033[1;32m[OK]\033[0m"
# define KO_RED "\033[1;31m[KO]\033[0m"


template <typename myContainer, typename stlContainer>
void    display(std::string error, myContainer &myCont, stlContainer &stlCont, std::ostream &o)
{
    static int error_count = 0;
    error_count++;
    std::cout << " (" << error_count << ')' << std::endl;

    o << '(' << error_count << ')' << std::endl;
    o << "Error: " << error << std::endl;
    o << "My container:\n";
    o << "Size: " << std::setw(6) << myCont.size()
    << "\tMax size: " << myCont.max_size()
    << "\tCapacity: " << myCont.capacity()
    << std::endl;
    if (!(myCont.empty()) && !(stlCont.empty()))
    {
        o << "Begin: " << *myCont.begin()
        << "\tEnd: " << *myCont.end()
        << "\tFront: " << myCont.front()
        << "\tBack: " << myCont.back()
        << std::endl;

        o << "Elements: |";
        typename myContainer::iterator my_it = myCont.begin();
        typename myContainer::iterator my_ite = myCont.end();
        for (; my_it != my_ite; my_it++)
            o << *my_it << '|';
        o << std::endl;
    }

    o << "STL container:\n";
    o << "Size: " << std::setw(6) << stlCont.size()
    << "\tMax size: " << stlCont.max_size()
    << "\tCapacity: " << stlCont.capacity()
    << std::endl;
    if (!(myCont.empty()) && !(stlCont.empty()))
    {
        o << "Begin: " << *stlCont.begin()
        << "\tEnd: " << *stlCont.end()
        << "\tFront: " << stlCont.front()
        << "\tBack: " << stlCont.back()
        << std::endl;

        o << "Elements: |";
        typename stlContainer::iterator stl_it = stlCont.begin();
        typename stlContainer::iterator stl_ite = stlCont.end();
        for (; stl_it != stl_ite; stl_it++)
            o << *stl_it << '|';
        o << std::endl;
    }
    o << std::endl;

}

template <typename myContainer, typename stlContainer>
void    testContFeature(bool ok, std::string feature, myContainer &myCont, stlContainer &stlCont)
{
    static bool initialize = false;

    if (!initialize)
    {
        std::srand(time(NULL));
        initialize = true;
    }

    std::cout.setf(std::ios::left);
    std::cout 
    << "\033[1;"
    << (90 + ((std::rand() + std::clock()) % 8))// + (60 * (std::clock() % 2)))
    << 'm' << std::setw(30) << feature << "\033[0m";

    if (ok)
        std::cout << OK_GREEN << std::endl;
    else
    {
        std::cout << KO_RED;
        display(feature, myCont, stlCont, std::cerr);
    }     
}

template <typename myContainer, typename stlContainer>
void containerCmp(myContainer &myCont, stlContainer &stlCont)
{
    testContFeature(myCont.size() == stlCont.size(), "Size", myCont, stlCont);
    testContFeature(myCont.max_size() == stlCont.max_size(), "Max size", myCont, stlCont);
    testContFeature(myCont.capacity() == stlCont.capacity(), "Capacity", myCont, stlCont);
    testContFeature(myCont.empty() == stlCont.empty(), "Empty", myCont, stlCont);

    if (!(myCont.empty()) && !(stlCont.empty()))
    {
        testContFeature(*myCont.begin() == *stlCont.begin(), "Begin", myCont, stlCont);
        testContFeature(*(myCont.end() - 1) == *(stlCont.end() - 1), "End", myCont, stlCont);
        testContFeature(myCont.front() == stlCont.front(), "Front", myCont, stlCont);
        testContFeature(myCont.back() == stlCont.back(), "Back", myCont, stlCont);

        typename myContainer::iterator my_it = myCont.begin();
        typename myContainer::iterator my_ite = myCont.end();
        typename stlContainer::iterator stl_it = stlCont.begin();
        typename stlContainer::iterator stl_ite = stlCont.end();
        while (my_it != my_ite && stl_it != stl_ite)
        {
            if (*my_it != *stl_it)
            {
                testContFeature(false, "Elements (iterator)", myCont, stlCont);
                break ;
            }
            my_it++;
            stl_it++;
        }
        if (my_it == my_ite && stl_it == stl_ite)
            testContFeature(true, "Elements (iterator)", myCont, stlCont);
        else
            testContFeature(false, "Elements end (iterator)", myCont, stlCont);

        typename myContainer::size_type i = 0;        
        for (;i < myCont.size(); i++)
        {
            if (myCont[i] != stlCont[i])
                break ;
        }
        testContFeature(i == myCont.size(), "Elements (operator[])", myCont, stlCont);
        
        for (i = 0; i < myCont.size(); i++)
        {
            if (myCont.at(i) != stlCont.at(i))
                break ;
        }
        testContFeature(i == myCont.size(), "Elements (operator 'at')", myCont, stlCont);
    }

}

#endif