/*!
 *  \file       main.cpp
 *  \brief
 *
 */


#include <cstdlib>
#include <string>
#include <iostream>


std::string say_hello();

int main(int argc, char* argv[])
{
    std::cout << say_hello() << std::endl;
    std::cout << "Compiler name is " << COMPILER_NAME << std::endl;

    return EXIT_SUCCESS;
}

std::string say_hello()
{
#ifdef IS_INTEL_CXX_COMPILER
    return std::string("Hello Intel compiler");
#elif IS_GNU_CXX_COMPILER
    return std::string("Hello GNU compiler");
#elif IS_PGI_CXX_COMPILER
    return std::string("Hello PGI compiler");
#elif IS_XL_CXX_COMPILER
    return std::string("Hello XL compiler")
#else
    return std::string("Hello unknown compiler - have we met before?");
#endif
}