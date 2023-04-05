/*!
 *  \file       in_stream.cpp
 *  \brief
 *
 */


#include "in_stream.h"

#include <iostream>

void hello()
{
    std::cout << "Please enter you name:\n";
    std::string name;
    std::cin >> name;
    std::cout << "Hello, " << name << "!\n";
}

void hello_line()
{
    std::cout << "Please enter your name:\n";
    std::string name;
    std::getline(std::cin, name);
    std::cout << "Hello, " << name << "!\n";
}
