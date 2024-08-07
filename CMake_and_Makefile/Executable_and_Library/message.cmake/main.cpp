/*!
 *  \file       main.cpp
 *  \brief
 *
 */


#include "Message.hpp"

#include <cstdlib>
#include <iostream>


int main(int argc, char* argv[])
{
    (void)argc;
    (void)argv;

    Message say_hello("Hello, CMake build world!");
    std::cout << say_hello << std::endl;

    Message say_goodbye("Goodbye, CMake build world!");
    std::cout << say_goodbye << std::endl;

    return EXIT_SUCCESS;
}