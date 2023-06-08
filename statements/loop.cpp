/*!
 *  \file       loop.cpp
 *  \brief
 *
 */


#include "loop.hpp"

#include <string>
#include <iostream>

void input()
{
    std::vector<std::string> str_vec;

    for (std::string s; std::cin >> s;)
    {
        str_vec.push_back(s);
    }
}

void print_backwards(char a[], int i)
{
    std::cout << '{';
    do
    {
        std::cout << a[--i];
    }
    while (i);
    std::cout << '}' << std::endl;
}
