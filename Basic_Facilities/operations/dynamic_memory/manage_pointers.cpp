/*!
 *  \file       manage_pointers.cpp
 *  \brief
 *
 */


#include "manage_pointers.hpp"

#include <memory>
#include <cstring>
#include <iostream>

void leakage(int n)
{
    int* p1 = new int[n];
    std::unique_ptr<int[]> p2{new int[n]};

    // Doing something else

    if (n % 2)
    {
        throw std::runtime_error("odd");
    }
    delete [] p1;
}

char* save_string(const char* p)
{
    char* s = new char[std::strlen(p) + 1];
    std::strcpy(s, p);
    return s;
}

void release_string()
{
    char* p = save_string("hello");

    std::cout << "current string is " << p << std::endl;
    delete [] p;
}
