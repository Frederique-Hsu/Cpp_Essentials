/*!
 *  \file       hello_world.cpp
 *  \brief      Demonstrate how to utilize CMake to build C++ project.
 *
 */


#include <cstdlib>
#include <iostream>
#include <string>


std::string say_hello();

int main(int argc, char* argv[])
{
    (void)argc;
    (void)argv;

    std::cout << say_hello() << std::endl;
    return EXIT_SUCCESS;
}


std::string say_hello()
{
    return std::string("Hello, welcome to the CMake build world!");
}