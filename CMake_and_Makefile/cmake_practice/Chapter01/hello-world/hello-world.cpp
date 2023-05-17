/*!
 *  \file       hello-world.cpp
 *  \brief      
 *  
 */


#include <cstdlib>
#include <iostream>
#include <string>

std::string say_hello()
{
    return std::string("Hello, CMake world!");
}

int main(int argc, char* argv[])
{
    std::cout << say_hello() << std::endl;
    return EXIT_SUCCESS;
}