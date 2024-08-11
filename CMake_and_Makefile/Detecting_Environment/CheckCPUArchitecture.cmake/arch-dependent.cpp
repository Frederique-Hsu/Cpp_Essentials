/*!
 *  \file       arch-dependent.cpp
 *  \brief
 *
 */


#include <cstdlib>
#include <string>
#include <iostream>


#define STRINGIFY(x)    #x
#define TOSTRING(x)     STRINGIFY(x)

std::string say_hello();

int main(int argc, char* argv[])
{
    std::cout << say_hello() << std::endl;
    return EXIT_SUCCESS;
}

std::string say_hello()
{
    std::string arch_info(TOSTRING(ARCHITECTURE));
    arch_info += std::string(" architecture. \n");

#ifdef IS_32_BIT_ARCH
    return arch_info + std::string("Compiled on a 32-bit host processor.");
#elif IS_64_BIT_ARCH
    return arch_info + std::string("Compiled on a 64-bit host processor.");
#else
    return arch_info + std::string("Neither 32 nor 64 bit, puzzling...");
#endif
}